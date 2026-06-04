#include <iostream>
#include <string>

using namespace std;

struct SensorReading
{
    int timeSeconds;
    string sensorName;
    double value;
    string unit;
    string status;
};

void printReading(const SensorReading& reading)
{
    cout << reading.sensorName << ": "
         << reading.value << " "
         << reading.unit
         << " | Status: " << reading.status << endl;
}

int main() {
    cout << "Starting Test Stand Data Acquisition Simulation..." << endl;
    cout << "System initialized successfully." << endl;
    cout << endl;

    for (int timeStep = 0; timeStep < 5; timeStep++) {
        double temperatureCelsius = 650.0 + (timeStep * 25.0);
        double pressurePsi = 210.0 + (timeStep * 8.0);
        double vibrationG = 1.2 + (timeStep * 0.3);

        string temperatureStatus = "OK";
        string pressureStatus = "OK";
        string vibrationStatus = "OK";

        if (temperatureCelsius >= 800.0) {
            temperatureStatus = "CRITICAL";
        } else if (temperatureCelsius >= 700.0) {
            temperatureStatus = "WARNING";
        }

        if (pressurePsi >= 250.0) {
            pressureStatus = "CRITICAL";
        } else if (pressurePsi >= 235.0) {
            pressureStatus = "WARNING";
        }

        if (vibrationG >= 2.2) {
            vibrationStatus = "CRITICAL";
        } else if (vibrationG >= 1.8) {
            vibrationStatus = "WARNING";
        }

        SensorReading temperatureReading;
        temperatureReading.timeSeconds = timeStep;
        temperatureReading.sensorName = "Temperature";
        temperatureReading.value = temperatureCelsius;
        temperatureReading.unit = "C";
        temperatureReading.status = temperatureStatus;

        SensorReading pressureReading;
        pressureReading.timeSeconds = timeStep;
        pressureReading.sensorName = "Pressure";
        pressureReading.value = pressurePsi;
        pressureReading.unit = "psi";
        pressureReading.status = pressureStatus;

        SensorReading vibrationReading;
        vibrationReading.timeSeconds = timeStep;
        vibrationReading.sensorName = "Vibration";
        vibrationReading.value = vibrationG;
        vibrationReading.unit = "g";
        vibrationReading.status = vibrationStatus;

        cout << "Time: " << timeStep << " seconds" << endl;
        printReading(temperatureReading);
        printReading(pressureReading);
        printReading(vibrationReading);
        cout << endl;
    }

    cout << "Test complete." << endl;

    return 0;
}
