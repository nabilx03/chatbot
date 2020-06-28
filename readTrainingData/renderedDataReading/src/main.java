import com.google.gson.*;

import javax.imageio.ImageIO;
import java.awt.image.BufferedImage;
import java.awt.image.DataBufferByte;
import java.io.*;
import java.nio.ByteBuffer;
import java.util.ArrayList;
import java.util.Arrays;

public class main {

    private static final int OFFSET_SIZE = 4;
    private static final int NUMBER_ITEMS_OFFSET = 4;
    private static final int ITEMS_SIZE = 4;

    public static ArrayList<BufferedImage> imageList = new ArrayList<>();
    public static JsonArray output = new JsonArray();

    public static void main(String[] args) throws IOException {
        try {
            //readLabels();
            readImages();
        } catch (IOException e) {
            System.out.println(e);
        }
    }

    public static void readImages() throws IOException {
        System.out.println("========================");
        System.out.println("reading images...");
        System.out.print("0%");
        for(int i=0; i<10; i++) {
            File dir = new File("D:\\Dokumente\\Programmierung\\Schriftidentifizierungs-KI\\Schriftidentifizierungs-KI\\Schriftidentifizierungs-KI\\sorted\\readTrainingData\\renderedDataReading\\imageData\\mnist_png\\training\\" + Integer.toString(i));
            File[] directoryListing = dir.listFiles();
            if(directoryListing != null) {
                for(File child : directoryListing) {
                    BufferedImage image = ImageIO.read(child);
                    imageList.add(image);

                    final byte[] pixels = ((DataBufferByte) image.getRaster().getDataBuffer()).getData();
                    final int width = image.getWidth();
                    final int height = image.getHeight();
                    int[][] result = new int[height][width];
                    final int pixelLength = 3;
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
                    JsonArray imgValues = new JsonArray();
                    JsonArray img = new JsonArray();
                    for(int i2=0; i2<result.length; i2++) {
                        JsonArray imgW = new JsonArray();
                        for(int j=0; j<result[i].length; j++) {
                            int pixelCol = image.getRGB(j, i2);
                            int r = (pixelCol >>> 16) & 0xff;
                            //inverted Grayscale: (r=g=b)
                            double rd = r;
                            double grayscale = rd / 255.;
                            imgW.add(grayscale);
                        }
                        imgValues.add(imgW);
                        if(i2+1 == result.length) {
                            imgW = null;
                        }
                    }
                    img.add(i);
                    img.add(imgValues);
                    imgValues = null;
                    output.add(img);
                    img = null;
                }
            } else {
                throw new IOException("directory not found");
            }
            System.out.print("\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b");
            System.out.print(((i+1.) / 10.)*100. + "%");
        }
        System.out.println("");
        System.out.println("========================");
        writeImagesToJSON();
    }

    public static void writeImagesToJSON() throws IOException {
        System.out.println("converting images...");
        Gson gson = new Gson();
        String JSONString = gson.toJson(output);
        output = null;
        FileWriter file = new FileWriter("trainingImageValues.json");
        file.write(JSONString);
        file.flush();
    }

    public static void readLabels() throws IOException {
        ByteArrayOutputStream labelBuffer = new ByteArrayOutputStream();

        File initialFile = new File("D:\\Dokumente\\Programmierung\\Schriftidentifizierungs-KI\\Schriftidentifizierungs-KI\\Schriftidentifizierungs-KI\\sorted\\readTrainingData\\renderedDataReading\\imageData\\training_labels.idx1-ubyte");
        InputStream labelInputStream = new FileInputStream(initialFile);

        int read;
        byte[] buffer = new byte[16384];

        while((read = labelInputStream.read(buffer, 0, buffer.length)) != -1) {
            labelBuffer.write(buffer, 0, read);
        }

        labelBuffer.flush();

        byte[] labelBytes = labelBuffer.toByteArray();

        int numberOfLabels = ByteBuffer.wrap(Arrays.copyOfRange(labelBytes, NUMBER_ITEMS_OFFSET, NUMBER_ITEMS_OFFSET + ITEMS_SIZE)).getInt();

        for(int i = 0; i < numberOfLabels; i++) {
            int label = labelBytes[OFFSET_SIZE + ITEMS_SIZE + i];
            if(i <= 54) {
                //System.out.println("nr. " + i + " has label: " + label);
            }
        }
    }
}
