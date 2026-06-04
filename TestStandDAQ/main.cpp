
#include <iostream>
#include <string>

using namespace std;

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

        cout << "Time: " << timeStep << " seconds" << endl;
        cout << "Temperature: " << temperatureCelsius << " C | Status: " << temperatureStatus << endl;
        cout << "Pressure: " << pressurePsi << " psi | Status: " << pressureStatus << endl;
        cout << "Vibration: " << vibrationG << " g | Status: " << vibrationStatus << endl;
        cout << endl;
    }

    cout << "Test complete." << endl;

    return 0;
}
