#include <iostream>
#include <fstream>
#include <string>
#include <ctime>
#include "Depth.hpp"
#include "Tempearture.hpp"
#include "phSensor.hpp"

std::string getCurrentDateTime() {
    time_t now = time(0);
    tm* localTime = localtime(&now);
    char buffer[80];
    strftime(buffer, sizeof(buffer), "%Y-%m-%d %H:%M:%S", localTime);
    return std::string(buffer);
}


std::string getCurrentDate() {
    time_t now = time(0);
    tm* localTime = localtime(&now);
    char buffer[80];
    strftime(buffer, sizeof(buffer), "%Y-%m-%d", localTime);
    return std::string(buffer);
}

void start() {
    // Create a file named with the current date
    std::string date = getCurrentDate();
    std::string dataFile = date + ".txt";
    std::ofstream outFile(dataFile);

    if (!outFile) {
        std::cerr << "Error opening file for writing: " << dataFile << std::endl;
        return;
    }

    DepthSens depthSensor;
    TempSensor temperatureSensor;
    while (true) {
        double depth = depthSensor.getDepth();
        double temperatureF = temperatureSensor.getTempF();
        double altitude = depthSensor.getAlt();

        // Get the current timestamp
        std::string currentTime = getCurrentDateTime();

        // Write data to the file
        outFile << currentTime << " - Depth: " << depth 
                << "m, Temperature: " << temperatureF 
                << "F, Altitude: " << altitude << "m" << std::endl;

        // std::this_thread::sleep_for(std::chrono::seconds(5)); // e.g., 5-second delay
    }

    // Close the file when done
    outFile.close();
}

int main() {
    std::string startInput;
    std::cout << "Type 'y' to start recording data: ";
    std::cin >> startInput;

    if (startInput == "Y" || startInput == "y") {
        start();
    }

    return 0;
}