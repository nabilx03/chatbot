import javax.imageio.ImageIO;
import javax.imageio.ImageReadParam;
import javax.imageio.ImageReader;
import javax.imageio.stream.ImageInputStream;
import java.awt.*;
import java.awt.image.BufferedImage;
import java.awt.image.DataBufferByte;
import java.awt.image.Raster;
import java.io.ByteArrayInputStream;
import java.io.ByteArrayOutputStream;
import java.io.IOException;
import java.io.InputStream;
import java.nio.ByteBuffer;
import java.sql.Array;
import java.util.ArrayList;
import java.util.Arrays;
import java.util.Iterator;
import java.util.List;

import java.lang.*;
import java.io.*;

import org.json.simple.JSONArray;
import org.json.simple.JSONObject;


public class DigitImageLoadingService {

    private String labelFileName;
    private String imageFileName;

    /** the following constants are defined as per the values described at http://yann.lecun.com/exdb/mnist/ **/

    private static final int MAGIC_OFFSET = 0;
    private static final int OFFSET_SIZE = 4; //in bytes

    private static final int LABEL_MAGIC = 2049;
    private static final int IMAGE_MAGIC = 2051;

    private static final int NUMBER_ITEMS_OFFSET = 4;
    private static final int ITEMS_SIZE = 4;

    private static final int NUMBER_OF_ROWS_OFFSET = 8;
    private static final int ROWS_SIZE = 4;
    public static final int ROWS = 28;

    private static final int NUMBER_OF_COLUMNS_OFFSET = 12;
    private static final int COLUMNS_SIZE = 4;
    public static final int COLUMNS = 28;

    private static final int IMAGE_OFFSET = 16;
    private static final int IMAGE_SIZE = ROWS * COLUMNS;


    public DigitImageLoadingService(String labelFileName, String imageFileName) {
        this.labelFileName = labelFileName;
        this.imageFileName = imageFileName;
    }

    public void writeImage(byte[] imageData, int fileNumber) {
        /*String filePath = "D:\\Dokumente\\Programmierung\\Schriftidentifizierungs-KI\\Schriftidentifizierungs-KI\\Schriftidentifizierungs-KI\\sorted\\chatbot\\readTrainingData\\src\\main\\java\\MNIST_rendered\\" + Integer.toString(fileNumber) + ".png";
        File file = new File(filePath);
        FileOutputStream fos = null;
        try {
            fos = new FileOutputStream(file);
            fos.write(imageData);
            fos.flush();
        } catch (FileNotFoundException e) {
            System.err.println(file + " doesn't exist!");
        } catch (IOException e) {
            System.err.println("Problems writing data to " + file);
        } finally {
            try {
                if(fos != null) fos.close();
            }catch(IOException e){}
        }*/
        /*try {
            ByteArrayInputStream istream = new ByteArrayInputStream(imageData);
            BufferedImage img = ImageIO.read(istream);
            System.out.println(img);
            String filePath = "D:\\Dokumente\\Programmierung\\Schriftidentifizierungs-KI\\Schriftidentifizierungs-KI\\Schriftidentifizierungs-KI\\sorted\\chatbot\\readTrainingData\\src\\main\\java\\MNIST_rendered\\" + Integer.toString(fileNumber) + ".png";
            File file = new File(filePath);
            ImageIO.write(img, "png", file);
        } catch (IOException e) {
            System.out.println(e);
        }*/
        /*String filePath = "D:\\Dokumente\\Programmierung\\Schriftidentifizierungs-KI\\Schriftidentifizierungs-KI\\Schriftidentifizierungs-KI\\sorted\\readTrainingData\\src\\main\\java\\MNIST_rendered\\" + Integer.toString(fileNumber) + ".png";
        try {
            FileOutputStream ostream = new FileOutputStream(filePath);
            ostream.write(imageData);
            ostream.close();
        } catch (IOException e) {
            System.err.println(e);
        }*/
        try {
            ByteArrayInputStream istream = new ByteArrayInputStream(imageData);
            Iterator<?> readers = ImageIO.getImageReadersByFormatName("jpg");

            //ImageIO is a class containing static methods for locating ImageReaders
            //and ImageWriters, and performing simple encoding and decoding.

            ImageReader reader = (ImageReader) readers.next();
            Object source = istream;
            ImageInputStream iis = ImageIO.createImageInputStream(source);
            reader.setInput(iis, true);
            ImageReadParam param = reader.getDefaultReadParam();
            Image image = reader.read(0, param);
            //got an image file
            BufferedImage bufferedImage = new BufferedImage(image.getWidth(null), image.getHeight(null), BufferedImage.TYPE_INT_RGB);
            //bufferedImage is the RenderedImage to be written
            Graphics2D g2 = bufferedImage.createGraphics();
            g2.drawImage(image, null, null);
            String filePath = "D:\\Dokumente\\Programmierung\\Schriftidentifizierungs-KI\\Schriftidentifizierungs-KI\\Schriftidentifizierungs-KI\\sorted\\readTrainingData\\src\\main\\java\\MNIST_rendered\\" + Integer.toString(fileNumber) + ".jpg";
            File imageFile = new File(filePath);
            ImageIO.write(bufferedImage, "jpg", imageFile);
            System.out.println(imageFile.getPath());
        } catch (IOException e) {
            e.printStackTrace();
        }
    }

    public void loadDigitImages() throws IOException {

        ByteArrayOutputStream labelBuffer = new ByteArrayOutputStream();
        ByteArrayOutputStream imageBuffer = new ByteArrayOutputStream();

        InputStream labelInputStream;
        InputStream imageInputStream;


        File initialFile = new File(this.imageFileName);
        imageInputStream = new FileInputStream(initialFile);

        File initialFile2 = new File(this.labelFileName);
        labelInputStream = new FileInputStream(initialFile2);

        int read;
        byte[] buffer = new byte[16384];

        //System.out.println(labelInputStream);

        while((read = labelInputStream.read(buffer, 0, buffer.length)) != -1) {
            labelBuffer.write(buffer, 0, read);
        }

        labelBuffer.flush();

        while((read = imageInputStream.read(buffer, 0, buffer.length)) != -1) {
            imageBuffer.write(buffer, 0, read);
        }

        imageBuffer.flush();

        byte[] labelBytes = labelBuffer.toByteArray();
        byte[] imageBytes = imageBuffer.toByteArray();

        byte[] labelMagic = Arrays.copyOfRange(labelBytes, 0, OFFSET_SIZE);
        byte[] imageMagic = Arrays.copyOfRange(imageBytes, 0, OFFSET_SIZE);

        if(ByteBuffer.wrap(labelMagic).getInt() != LABEL_MAGIC)  {
            throw new IOException("Bad magic number in label file!");
        }

        if(ByteBuffer.wrap(imageMagic).getInt() != IMAGE_MAGIC) {
            throw new IOException("Bad magic number in image file!");
        }

        int numberOfLabels = ByteBuffer.wrap(Arrays.copyOfRange(labelBytes, NUMBER_ITEMS_OFFSET, NUMBER_ITEMS_OFFSET + ITEMS_SIZE)).getInt();
        int numberOfImages = ByteBuffer.wrap(Arrays.copyOfRange(imageBytes, NUMBER_ITEMS_OFFSET, NUMBER_ITEMS_OFFSET + ITEMS_SIZE)).getInt();

        if(numberOfImages != numberOfLabels) {
            throw new IOException("The number of labels and images do not match!");
        }

        int numRows = ByteBuffer.wrap(Arrays.copyOfRange(imageBytes, NUMBER_OF_ROWS_OFFSET, NUMBER_OF_ROWS_OFFSET + ROWS_SIZE)).getInt();
        int numCols = ByteBuffer.wrap(Arrays.copyOfRange(imageBytes, NUMBER_OF_COLUMNS_OFFSET, NUMBER_OF_COLUMNS_OFFSET + COLUMNS_SIZE)).getInt();

        if(numRows != ROWS && numRows != COLUMNS) {
            throw new IOException("Bad image. Rows and columns do not equal " + ROWS + "x" + COLUMNS);
        }

        ArrayList<DigitImages> imageList = new ArrayList<DigitImages>();

        for(int i = 0; i < 1; i++) {
            int label = labelBytes[OFFSET_SIZE + ITEMS_SIZE + i];
            byte[] imageData = Arrays.copyOfRange(imageBytes, (i * IMAGE_SIZE) + IMAGE_OFFSET, (i * IMAGE_SIZE) + IMAGE_OFFSET + IMAGE_SIZE);
            //writeImage(imageData, i+1);
            BufferedImage result = new BufferedImage(28, 28, BufferedImage.TYPE_3BYTE_BGR) ;
            //System.arraycopy(src, ((DataBufferByte)result.getRaster().getDataBuffer()).getData(), src.length) ;
            result.getRaster().setDataElements(0, 0, 28, 28, imageData);


            BufferedImage img = result;
            File oFile = null;
            try {
                String filePath = "D:\\Dokumente\\Programmierung\\Schriftidentifizierungs-KI\\Schriftidentifizierungs-KI\\Schriftidentifizierungs-KI\\sorted\\readTrainingData\\src\\main\\java\\MNIST_rendered\\" + Integer.toString(i) + ".png";
                oFile = new File(filePath);
                ImageIO.write(img, "png", oFile);
            } catch (IOException e) {
                System.out.println(e);
            }

            System.out.println("");
            System.out.println("label: " + label);
            //System.out.println(imageData);
            imageList.add(new DigitImages(label, imageData));
        }

        for(int i=0; i<0/*imageList.size()*/; i++) {
            //BufferedImage image = imageList.get(i).imageBuffered;
            /*if(image == null) {
                System.out.println("Null");
                System.out.println(imageList.get(5764).label);
            }
            final byte[] pixels = ((DataBufferByte) image.getRaster().getDataBuffer()).getData();*/




            final byte[] pixels = imageList.get(i).imgByte;
            final int width = 28;
            final int height = 28;
            final int pixelLength = 3;
            int[][] result = new int[width][height];
            String[][] resultHex = new String[width][height];
            int[][][] resultRGB = new int[width][height][3];
            for (int pixel = 0, row = 0, col = 0; pixel + 2 < pixels.length; pixel += pixelLength) {
                int argb = 0;
                int alpha = -16777216; // 255 alpha
                argb += alpha;
                int blue = ((int) pixels[pixel] & 0xff); // blue
                argb += blue;
                int green = (((int) pixels[pixel + 1] & 0xff) << 8); // green
                argb += green;
                int red = (((int) pixels[pixel + 2] & 0xff) << 16); // red
                argb += red;
                result[col][row] = argb;
                col++;

                /*resultHex[col][row] = String.format("%02x%02x%02x%02x", alpha, red, green, blue);
                //resultRGB[col][row] = new int[];
                resultRGB[col][row][0] = red;
                resultRGB[col][row][1] = green;
                resultRGB[col][row][2] = blue;*/

                int out = 0;
                if(red !=0 || green !=0 || blue !=0) out = 1;
                if(col == width) {
                    System.out.println(out);
                } else {
                    System.out.print(out);
                }

                //System.out.println(String.format("%02x%02x%02x%02x", alpha, red, green, blue));
                //System.out.println(alpha + ";" + red + ";" + green + ";" + blue);


                if (col == width) {
                    col = 0;
                    row++;
                }
            }

            /*for(int j=0; j<resultRGB.length; j++) {
                //System.out.println(resultRGB[j][28]);
                for (int k=0; k<resultRGB[j].length-1; j++) {
                    int out = 0;
                    if(resultRGB[j][k][0] !=0 || resultRGB[j][k][1] !=0 || resultRGB[j][k][2] !=0) out = 1;
                    if(j == width) {
                        System.out.println(out);
                    } else {
                        System.out.print(out);
                    }
                }
            }*/


            /*for(int j=0; i<result.length; j++) {
                for(int k=0; j<result[i].length; k++) {
                    int pixelCol = image.getRGB(k, j);
                    int a = (pixelCol >>> 24) & 0xff;
                    int r = (pixelCol >>> 16) & 0xff;
                    int g = (pixelCol >>> 8) & 0xff;
                    int b = pixelCol & 0xff;
                    //System.out.println("rgba("+r+";"+g+";"+b+";"+a+")");
                    resultHex[k][j] = String.format("%02x%02x%02x%02x", a, r, g, b);
                    //double process = ((double) j)/((double) height);
                    //System.out.println(String.format("%.2f", process));
                }
            }
            System.out.println(i/imageList.size());*/
        }
    }
}