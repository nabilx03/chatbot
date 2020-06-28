import java.io.IOException;

public class Main {
    public static void main(String[] args) {
        String folderPath = "D:\\Dokumente\\Programmierung\\Schriftidentifizierungs-KI\\Schriftidentifizierungs-KI\\Schriftidentifizierungs-KI\\sorted\\readTrainingData\\src\\main\\java\\MNIST_data";
        String imagePath = folderPath + "\\training_images.idx3-ubyte",
               labelPath = folderPath + "\\training_labels.idx1-ubyte";
        DigitImageLoadingService service = new DigitImageLoadingService(labelPath, imagePath);
        try {
            service.loadDigitImages();
        } catch (IOException exception) {
            System.out.println(exception);
        }
    }
}
