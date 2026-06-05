#include <fstream>
#include <iostream>
#include <string>
#include <vector>
#include "Status.h"
#include "SensorReading.h"
#include "Sensor.h"
#include "Reporting.h"

using namespace std;

const int TEST_DURATION_SECONDS = 5;
const string DATA_LOG_FILE_NAME = "test_log.csv";
const string SENSOR_STATISTICS_FILE_NAME = "sensor_statistics.csv";
const string TEST_SUMMARY_FILE_NAME = "test_summary.csv";



// CSV output helpers
bool writeReadingsToCsv(const vector<SensorReading>& readings, const string& fileName)
{
    ofstream outputFile(fileName);

    if (!outputFile) {
        cout << "Error: Could not open file for writing: " << fileName << endl;
        return false;
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
    return true;
}

bool writeSensorStatisticsToCsv(const vector<SensorStatistics>& statisticsList, const string& fileName)
{
    ofstream outputFile(fileName);

    if (!outputFile) {
        cout << "Error: Could not open file for writing: " << fileName << endl;
        return false;
    }

    outputFile << "sensor_name,valid_count,invalid_count,minimum_value,maximum_value,average_value" << endl;

    for (const SensorStatistics& statistics : statisticsList) {
        outputFile << statistics.sensorName << ","
                   << statistics.validCount << ","
                   << statistics.invalidCount << ",";

        if (statistics.validCount > 0) {
            outputFile << statistics.minimumValue << ","
                       << statistics.maximumValue << ","
                       << statistics.averageValue;
        } else {
            outputFile << "N/A,N/A,N/A";
        }

        outputFile << endl;
    }

    outputFile.close();

    cout << "Statistics report written to: " << fileName << endl;
    return true;
}

bool writeTestSummaryToCsv(const TestSummary& summary, const string& fileName)
{
    ofstream outputFile(fileName);

    if (!outputFile) {
        cout << "Error: Could not open file for writing: " << fileName << endl;
        return false;
    }

    outputFile << "total_readings,ok_count,warning_count,critical_count,sensor_failure_count,valid_reading_count,invalid_reading_count,overall_result" << endl;

    string overallResult = determineOverallResult(summary);

    outputFile << summary.totalReadings << ","
               << summary.okCount << ","
               << summary.warningCount << ","
               << summary.criticalCount << ","
               << summary.sensorFailureCount << ","
               << summary.validReadingCount << ","
               << summary.invalidReadingCount << ","
               << overallResult << endl;

    outputFile.close();

    cout << "Test summary written to: " << fileName << endl;
    return true;
}

// Domain classes
class TestStand
{
private:
    vector<Sensor> sensors;
    vector<SensorReading> readings;
    int durationSeconds;
    bool hasRun;

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

    bool validateTestHasRun(const string& operationName) const
    {
        if (!hasRun) {
            cout << "Error: Cannot " << operationName << " before test run." << endl;
            return false;
        }

        return true;
    }

    void runAcquisitionLoop()
    {
        for (int timeStep = 0; timeStep < durationSeconds; timeStep++) {
            cout << "Time: " << timeStep << " seconds" << endl;

            for (const Sensor& sensor : sensors) {
                SensorReading reading = sensor.createReading(timeStep);
                readings.push_back(reading);
                printReading(reading);
            }

            cout << endl;
        }
    }

public:
    TestStand(int testDurationSeconds)
        : durationSeconds(testDurationSeconds),
          hasRun(false)
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
        hasRun = true;
        return true;
    }

    void printSummary() const
    {
        if (!validateTestHasRun("print summary")) {
            return;
        }

        TestSummary summary = generateTestSummary(readings);
        printTestSummary(summary);
    }

    bool writeSummaryCsv(const string& fileName) const
    {
        if (!validateTestHasRun("write summary CSV")) {
            return false;
        }

        TestSummary summary = generateTestSummary(readings);
        return writeTestSummaryToCsv(summary, fileName);
    }

    void printSensorStatisticsReport() const
    {
        if (!validateTestHasRun("print sensor statistics")) {
            return;
        }

        cout << "SENSOR STATISTICS" << endl;

        for (const Sensor& sensor : sensors) {
            SensorStatistics statistics = generateSensorStatistics(readings, sensor.getName());
            printSensorStatistics(statistics);
            cout << endl;
        }
    }

    bool writeSensorStatisticsCsv(const string& fileName) const
    {
        if (!validateTestHasRun("write sensor statistics CSV")) {
            return false;
        }

        vector<SensorStatistics> statisticsList;

        for (const Sensor& sensor : sensors) {
            SensorStatistics statistics = generateSensorStatistics(readings, sensor.getName());
            statisticsList.push_back(statistics);
        }

        return writeSensorStatisticsToCsv(statisticsList, fileName);
    }

    bool writeCsvLog(const string& fileName) const
    {
        if (!validateTestHasRun("write data log")) {
            return false;
        }

        return writeReadingsToCsv(readings, fileName);
    }
};


int main() {
    cout << "Starting Test Stand Data Acquisition Simulation..." << endl;
    cout << "System initialized successfully." << endl;
    cout << endl;

    TestStand testStand(TEST_DURATION_SECONDS);

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
    testStand.printSensorStatisticsReport();

    if (!testStand.writeCsvLog(DATA_LOG_FILE_NAME)) {
        return 1;
    }

    if (!testStand.writeSensorStatisticsCsv(SENSOR_STATISTICS_FILE_NAME)) {
        return 1;
    }

    if (!testStand.writeSummaryCsv(TEST_SUMMARY_FILE_NAME)) {
        return 1;
    }

    return 0;
}
