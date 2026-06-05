#include <iostream>
#include <string>
#include <vector>

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

string determineStatus(double value, double warningThreshold, double criticalThreshold)
{
    if (value >= criticalThreshold) {
        return "CRITICAL";
    } else if (value >= warningThreshold) {
        return "WARNING";
    }

    return "OK";
}

void printTestSummary(const vector<SensorReading>& readings)
{
    int okCount = 0;
    int warningCount = 0;
    int criticalCount = 0;

    for (const SensorReading& reading : readings) {
        if (reading.status == "CRITICAL") {
            criticalCount++;
        } else if (reading.status == "WARNING") {
            warningCount++;
        } else {
            okCount++;
        }
    }

    cout << "TEST SUMMARY" << endl;
    cout << "Total readings collected: " << readings.size() << endl;
    cout << "OK readings: " << okCount << endl;
    cout << "Warning readings: " << warningCount << endl;
    cout << "Critical readings: " << criticalCount << endl;

    if (criticalCount > 0) {
        cout << "Overall result: FAIL" << endl;
    } else if (warningCount > 0) {
        cout << "Overall result: PASS WITH WARNINGS" << endl;
    } else {
        cout << "Overall result: PASS" << endl;
    }
}

int main() {
    cout << "Starting Test Stand Data Acquisition Simulation..." << endl;
    cout << "System initialized successfully." << endl;
    cout << endl;

    vector<SensorReading> readings;

    for (int timeStep = 0; timeStep < 5; timeStep++) {
        double temperatureCelsius = 650.0 + (timeStep * 25.0);
        double pressurePsi = 210.0 + (timeStep * 8.0);
        double vibrationG = 1.2 + (timeStep * 0.3);

        string temperatureStatus = determineStatus(temperatureCelsius, 700.0, 800.0);
        string pressureStatus = determineStatus(pressurePsi, 235.0, 250.0);
        string vibrationStatus = determineStatus(vibrationG, 1.8, 2.2);

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

        readings.push_back(temperatureReading);
        readings.push_back(pressureReading);
        readings.push_back(vibrationReading);

        cout << "Time: " << timeStep << " seconds" << endl;
        printReading(temperatureReading);
        printReading(pressureReading);
        printReading(vibrationReading);
        cout << endl;
    }

    cout << "Test complete." << endl;
    cout << endl;
    printTestSummary(readings);

    return 0;
}
