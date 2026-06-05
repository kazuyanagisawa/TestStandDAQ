#include <fstream>
#include <iostream>
#include <string>
#include <vector>

using namespace std;

enum class Status
{
    OK,
    WARNING,
    CRITICAL,
    SENSOR_FAILURE
};

string statusToString(Status status)
{
    switch (status) {
        case Status::OK:
            return "OK";
        case Status::WARNING:
            return "WARNING";
        case Status::CRITICAL:
            return "CRITICAL";
        case Status::SENSOR_FAILURE:
            return "SENSOR_FAILURE";
    }

    return "UNKNOWN";
}

struct SensorReading
{
    int timeSeconds;
    string sensorName;
    double value;
    string unit;
    Status status;
    bool isValid;
};

struct TestSummary
{
    int totalReadings;
    int okCount;
    int warningCount;
    int criticalCount;
    int sensorFailureCount;
};

TestSummary generateTestSummary(const vector<SensorReading>& readings)
{
    TestSummary summary;
    summary.totalReadings = static_cast<int>(readings.size());
    summary.okCount = 0;
    summary.warningCount = 0;
    summary.criticalCount = 0;
    summary.sensorFailureCount = 0;

    for (const SensorReading& reading : readings) {
        if (reading.status == Status::SENSOR_FAILURE) {
            summary.sensorFailureCount++;
        } else if (reading.status == Status::CRITICAL) {
            summary.criticalCount++;
        } else if (reading.status == Status::WARNING) {
            summary.warningCount++;
        } else {
            summary.okCount++;
        }
    }

    return summary;
}

void printTestSummary(const TestSummary& summary)
{
    cout << "TEST SUMMARY" << endl;
    cout << "Total readings collected: " << summary.totalReadings << endl;
    cout << "OK readings: " << summary.okCount << endl;
    cout << "Warning readings: " << summary.warningCount << endl;
    cout << "Critical readings: " << summary.criticalCount << endl;
    cout << "Sensor failures: " << summary.sensorFailureCount << endl;

    if (summary.sensorFailureCount > 0 || summary.criticalCount > 0) {
        cout << "Overall result: FAIL" << endl;
    } else if (summary.warningCount > 0) {
        cout << "Overall result: PASS WITH WARNINGS" << endl;
    } else {
        cout << "Overall result: PASS" << endl;
    }
}

void printReading(const SensorReading& reading)
{
    cout << reading.sensorName << ": ";

    if (reading.isValid) {
        cout << reading.value << " " << reading.unit;
    } else {
        cout << "INVALID";
    }

    cout << " | Status: " << statusToString(reading.status) << endl;
}

void writeReadingsToCsv(const vector<SensorReading>& readings, const string& fileName)
{
    ofstream outputFile(fileName);

    if (!outputFile) {
        cout << "Error: Could not open file for writing: " << fileName << endl;
        return;
    }

    outputFile << "time_seconds,sensor_name,value,unit,status,is_valid" << endl;

    for (const SensorReading& reading : readings) {
        outputFile << reading.timeSeconds << ","
                   << reading.sensorName << ",";

        if (reading.isValid) {
            outputFile << reading.value;
        } else {
            outputFile << "INVALID";
        }

        outputFile << ","
                   << reading.unit << ","
                   << statusToString(reading.status) << ","
                   << reading.isValid << endl;
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
    int failureTimeSeconds;
    static const int NO_FAILURE = -1;

public:
    Sensor(
        string sensorName,
        string sensorUnit,
        double warningLimit,
        double criticalLimit,
        double startingValue,
        double changeRate,
        int failureTime = NO_FAILURE)
        : name(sensorName),
          unit(sensorUnit),
          warningThreshold(warningLimit),
          criticalThreshold(criticalLimit),
          baseValue(startingValue),
          rateOfChange(changeRate),
          failureTimeSeconds(failureTime)
    {
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
        if (hasFailed(timeSeconds)) {
            reading.status = Status::SENSOR_FAILURE;
            reading.isValid = false;
        } else {
            reading.status = determineStatus(value);
            reading.isValid = true;
        }

        return reading;
    }

    bool hasFailed(int timeSeconds) const
    {
        return failureTimeSeconds != NO_FAILURE && timeSeconds >= failureTimeSeconds;
    }

    Status determineStatus(double value) const
    {
        if (value >= criticalThreshold) {
            return Status::CRITICAL;
        } else if (value >= warningThreshold) {
            return Status::WARNING;
        }

        return Status::OK;
    }
};

class TestStand
{
private:
    vector<Sensor> sensors;
    vector<SensorReading> readings;
    int durationSeconds;

    bool validateConfiguration() const
    {
        if (durationSeconds <= 0) {
            cout << "Error: Test duration must be greater than zero seconds." << endl;
            return false;
        }

        if (sensors.empty()) {
            cout << "Error: Cannot run test stand with zero configured sensors." << endl;
            return false;
        }

        return true;
    }

    void runAcquisitionLoop()
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

public:
    TestStand(int testDurationSeconds)
        : durationSeconds(testDurationSeconds)
    {
    }

    void addSensor(const Sensor& sensor)
    {
        sensors.push_back(sensor);
    }

    bool run()
    {
        if (!validateConfiguration()) {
            return false;
        }

        readings.clear();

        cout << "Configured sensors: "
             << sensors.size()
             << endl
             << endl;

        runAcquisitionLoop();
        return true;
    }

    void printSummary() const
    {
        TestSummary summary = generateTestSummary(readings);
        printTestSummary(summary);
    }

    void writeCsvLog(const string& fileName) const
    {
        writeReadingsToCsv(readings, fileName);
    }
};

int main() {
    cout << "Starting Test Stand Data Acquisition Simulation..." << endl;
    cout << "System initialized successfully." << endl;
    cout << endl;

    TestStand testStand(5);

    testStand.addSensor(Sensor("Temperature", "C", 700.0, 800.0, 650.0, 25.0, 4));
    testStand.addSensor(Sensor("Pressure", "psi", 235.0, 250.0, 210.0, 8.0));
    testStand.addSensor(Sensor("Vibration", "g", 1.8, 2.2, 1.2, 0.3));

    if (!testStand.run()) {
        return 1;
    }

    cout << "Test complete." << endl;
    cout << endl;
    testStand.printSummary();
    cout << endl;
    testStand.writeCsvLog("test_log.csv");

    return 0;
}
