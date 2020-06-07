import javax.imageio.ImageIO;
import java.awt.*;
import java.awt.image.BufferedImage;
import java.awt.image.DataBufferByte;
import java.awt.image.Raster;
import java.io.ByteArrayInputStream;
import java.io.ByteArrayOutputStream;
import java.io.IOException;
import java.io.InputStream;
import java.nio.ByteBuffer;
import java.util.ArrayList;
import java.util.Arrays;
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

    public void loadDigitImages() throws IOException {

        ByteArrayOutputStream labelBuffer = new ByteArrayOutputStream();
        ByteArrayOutputStream imageBuffer = new ByteArrayOutputStream();

        InputStream labelInputStream;
        InputStream imageInputStream;


        File initialFile = new File(this.imageFileName);
        imageInputStream = new FileInputStream(initialFile);

        File initialFile2 = new File(this.imageFileName);
        labelInputStream = new FileInputStream(initialFile2);

        int read;
        byte[] buffer = new byte[16384];

        System.out.println(labelInputStream);

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

        for(int i = 0; i < numberOfLabels; i++) {
            int label = labelBytes[OFFSET_SIZE + ITEMS_SIZE + i];
            byte[] imageData = Arrays.copyOfRange(imageBytes, (i * IMAGE_SIZE) + IMAGE_OFFSET, (i * IMAGE_SIZE) + IMAGE_OFFSET + IMAGE_SIZE);
            //imageList.add(new DigitImages(label, getBuffered(imageData)));
        }

        for(int i=0; i<imageList.size(); i++) {
            BufferedImage image = imageList.get(i).imageBuffered;
            if(image == null) {
                System.out.println("Null");
                System.out.println(imageList.get(5764).label);
            }
            final byte[] pixels = ((DataBufferByte) image.getRaster().getDataBuffer()).getData();
            final int width = image.getWidth();
            final int height = image.getHeight();
            final int pixelLength = 3;
            int[][] result = new int[height][width];

            String[][] resultHex = new String[width][height];

            for (int pixel = 0, row = 0, col = 0; pixel + 2 < pixels.length; pixel += pixelLength) {
                int argb = 0;
                argb += -16777216; // 255 alpha
                argb += ((int) pixels[pixel] & 0xff); // blue
                argb += (((int) pixels[pixel + 1] & 0xff) << 8); // green
                argb += (((int) pixels[pixel + 2] & 0xff) << 16); // red
                result[row][col] = argb;
                col++;
                if (col == width) {
                    col = 0;
                    row++;
                }
            }

            for(int j=0; i<result.length; j++) {
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
            System.out.println(i/imageList.size());
        }
    }
}