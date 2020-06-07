import java.io.IOException;

public class Main {
    public static void main(String[] args) {
        String folderPath = "D:\\Dokumente\\Programmierung\\Schriftidentifizierungs-KI\\Schriftidentifizierungs-KI\\Schriftidentifizierungs-KI\\trainingData\\ki\\src\\main\\java";
        String imagePath = folderPath + "\\10k-images.idx3-ubyte",
               labelPath = folderPath + "\\10k-labels.idx1-ubyte";
        DigitImageLoadingService service = new DigitImageLoadingService(labelPath, imagePath);
        try {
            service.loadDigitImages();
        } catch (IOException exception) {
            System.out.println(exception);
        }
    }
}
