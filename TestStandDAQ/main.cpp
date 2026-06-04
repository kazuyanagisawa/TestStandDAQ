#include <iostream>

using namespace std;

int main() {
    cout << "Starting Test Stand Data Acquisition Simulation..." << endl;
    cout << "System initialized successfully." << endl;
    cout << endl;

    double timeSeconds = 0.0;
    double temperatureCelsius = 650.0;
    double pressurePsi = 210.0;
    double vibrationG = 1.2;

    string temperatureStatus = "OK";

    if (temperatureCelsius >= 800.0) {
        temperatureStatus = "CRITICAL";
    } else if (temperatureCelsius >= 700.0) {
        temperatureStatus = "WARNING";
    }

    for (int timeStep = 0; timeStep < 5; timeStep++){
        cout << "Time: " << timeStep << " seconds" << endl;
        cout << "Temperature: " << temperatureCelsius << " C | Status: " << temperatureStatus << endl;
        cout << "Pressure: " << pressurePsi << " psi" << endl;
        cout << "Vibration: " << vibrationG << " g" << endl;
        cout << endl;
    }

    cout << "Test complete." << endl;

    return 0;
}
