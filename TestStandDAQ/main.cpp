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
private:
    string name;
    string unit;

    double warningThreshold;
    double criticalThreshold;
    double baseValue;
    double rateOfChange;

public:
    Sensor(
        string sensorName,
        string sensorUnit,
        double warningLimit,
        double criticalLimit,
        double startingValue,
        double changeRate)
    {
        name = sensorName;
        unit = sensorUnit;
        warningThreshold = warningLimit;
        criticalThreshold = criticalLimit;
        baseValue = startingValue;
        rateOfChange = changeRate;
    }

    double simulateValue(int timeSeconds) const
    {
        return baseValue + (timeSeconds * rateOfChange);
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

    string determineStatus(double value) const
    {
        if (value >= criticalThreshold) {
            return "CRITICAL";
        } else if (value >= warningThreshold) {
            return "WARNING";
        }

        return "OK";
    }
};

void runAcquisitionLoop(const vector<Sensor>& sensors, vector<SensorReading>& readings, int durationSeconds)
{
    for (int timeStep = 0; timeStep < durationSeconds; timeStep++) {
        cout << "Time: " << timeStep << " seconds" << endl;

        for (size_t sensorIndex = 0; sensorIndex < sensors.size(); sensorIndex++) {
            double sensorValue = sensors[sensorIndex].simulateValue(timeStep);
            SensorReading reading = sensors[sensorIndex].createReading(sensorValue, timeStep);
            readings.push_back(reading);
            printReading(reading);
        }

        cout << endl;
    }
}

int main() {
    cout << "Starting Test Stand Data Acquisition Simulation..." << endl;
    cout << "System initialized successfully." << endl;
    cout << endl;

    vector<SensorReading> readings;
    
    Sensor temperatureSensor("Temperature", "C", 700.0, 800.0, 650.0, 25.0);
    Sensor pressureSensor("Pressure", "psi", 235.0, 250.0, 210.0, 8.0);
    Sensor vibrationSensor("Vibration", "g", 1.8, 2.2, 1.2, 0.3);
    
    vector<Sensor> sensors;

    sensors.push_back(temperatureSensor);
    sensors.push_back(pressureSensor);
    sensors.push_back(vibrationSensor);
    
    cout << "Configured sensors: "
         << sensors.size()
         << endl
         << endl;

    runAcquisitionLoop(sensors, readings, 5);

    cout << "Test complete." << endl;
    cout << endl;
    printTestSummary(readings);
    cout << endl;
    writeReadingsToCsv(readings, "test_log.csv");

    return 0;
}
