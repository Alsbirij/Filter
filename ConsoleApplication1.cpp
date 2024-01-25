// ConsoleApplication1.cpp : Diese Datei enthält die Funktion "main". Hier beginnt und endet die Ausführung des Programms.
//

//#include <iostream>

//int main()
//{
 //   std::cout << "Hello World!\n";
//}

// Programm ausführen: STRG+F5 oder Menüeintrag "Debuggen" > "Starten ohne Debuggen starten"
// Programm debuggen: F5 oder "Debuggen" > Menü "Debuggen starten"

// Tipps für den Einstieg: 
//   1. Verwenden Sie das Projektmappen-Explorer-Fenster zum Hinzufügen/Verwalten von Dateien.
//   2. Verwenden Sie das Team Explorer-Fenster zum Herstellen einer Verbindung mit der Quellcodeverwaltung.
//   3. Verwenden Sie das Ausgabefenster, um die Buildausgabe und andere Nachrichten anzuzeigen.
//   4. Verwenden Sie das Fenster "Fehlerliste", um Fehler anzuzeigen.
//   5. Wechseln Sie zu "Projekt" > "Neues Element hinzufügen", um neue Codedateien zu erstellen, bzw. zu "Projekt" > "Vorhandenes Element hinzufügen", um dem Projekt vorhandene Codedateien hinzuzufügen.
//   6. Um dieses Projekt später erneut zu öffnen, wechseln Sie zu "Datei" > "Öffnen" > "Projekt", und wählen Sie die SLN-Datei aus.
#include <opencv2/opencv.hpp>
#include <iostream>

void BrightnessCorrection(const std::string& image_path) {
    // Load an image
    cv::Mat image = cv::imread(image_path);
    if (image.empty()) {
        std::cout << "Could not open or find the image" << std::endl;
        return;
    }

    // Define the brightness factor (adjust as needed)
    double brightness_factor = 2.5; // Increase to make it brighter, decrease to make it darker

    // Apply brightness correction
    cv::Mat brightened_image;
    image.convertTo(brightened_image, -1, brightness_factor, 0);

    // Create window
    cv::namedWindow("Corrected Image", cv::WINDOW_AUTOSIZE);

    // Show the brightened image
    cv::imshow("Corrected Image", brightened_image);

    // Wait for a keystroke in the window
    cv::waitKey(0);
    cv::destroyAllWindows();
}

int main() {
    std::string image_path = "bild.png"; // Replace with your image path
    BrightnessCorrection(image_path);
    return 0;
}

