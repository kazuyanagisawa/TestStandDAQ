#include <fstream>
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

void writeReadingsToCsv(const vector<SensorReading>& readings, const string& fileName)
{
    ofstream outputFile(fileName);

    if (!outputFile) {
        cout << "Error: Could not open file for writing: " << fileName << endl;
        return;
    }

    outputFile << "time_seconds,sensor_name,value,unit,status" << endl;

    for (const SensorReading& reading : readings) {
        outputFile << reading.timeSeconds << ","
                   << reading.sensorName << ","
                   << reading.value << ","
                   << reading.unit << ","
                   << reading.status << endl;
    }

    outputFile.close();

    cout << "Data log written to: " << fileName << endl;
}

class Sensor
{
public:
    string name;
    string unit;

    double warningThreshold;
    double criticalThreshold;

    Sensor(string sensorName, string sensorUnit, double warningLimit, double criticalLimit)
    {
        name = sensorName;
        unit = sensorUnit;
        warningThreshold = warningLimit;
        criticalThreshold = criticalLimit;
    }

    string determineStatus(double value) const
    {
        if (value >= criticalThreshold) {
            return "CRITICAL";
        } else if (value >= warningThreshold) {
            return "WARNING";
        }

        return "OK";
    }

    SensorReading createReading(double value, int timeSeconds) const
    {
        SensorReading reading;
        reading.timeSeconds = timeSeconds;
        reading.sensorName = name;
        reading.value = value;
        reading.unit = unit;
        reading.status = determineStatus(value);

        return reading;
    }
};

int main() {
    cout << "Starting Test Stand Data Acquisition Simulation..." << endl;
    cout << "System initialized successfully." << endl;
    cout << endl;

    vector<SensorReading> readings;
    
    Sensor temperatureSensor("Temperature", "C", 700.0, 800.0);
    Sensor pressureSensor("Pressure", "psi", 235.0, 250.0);
    Sensor vibrationSensor("Vibration", "g", 1.8, 2.2);

    for (int timeStep = 0; timeStep < 5; timeStep++) {
        double temperatureCelsius = 650.0 + (timeStep * 25.0);
        double pressurePsi = 210.0 + (timeStep * 8.0);
        double vibrationG = 1.2 + (timeStep * 0.3);

        SensorReading temperatureReading = temperatureSensor.createReading(temperatureCelsius, timeStep);
        SensorReading pressureReading = pressureSensor.createReading(pressurePsi, timeStep);
        SensorReading vibrationReading = vibrationSensor.createReading(vibrationG, timeStep);

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
    cout << endl;
    writeReadingsToCsv(readings, "test_log.csv");

    return 0;
}
