#include <fstream>
#include <iostream>
#include <limits>
#include <string>
#include <vector>

using namespace std;

// Status definitions
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

// Data models
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
    int validReadingCount;
    int invalidReadingCount;
};

struct SensorStatistics
{
    string sensorName;
    int validCount;
    int invalidCount;
    double minimumValue;
    double maximumValue;
    double averageValue;
};

// Summary and statistics logic
string determineOverallResult(const TestSummary& summary)
{
    if (summary.sensorFailureCount > 0 || summary.criticalCount > 0) {
        return "FAIL";
    } else if (summary.warningCount > 0) {
        return "PASS_WITH_WARNINGS";
    }

    return "PASS";
}

TestSummary generateTestSummary(const vector<SensorReading>& readings)
{
    TestSummary summary;
    summary.totalReadings = static_cast<int>(readings.size());
    summary.okCount = 0;
    summary.warningCount = 0;
    summary.criticalCount = 0;
    summary.sensorFailureCount = 0;
    summary.validReadingCount = 0;
    summary.invalidReadingCount = 0;

    for (const SensorReading& reading : readings) {
        if (reading.isValid) {
            summary.validReadingCount++;
        } else {
            summary.invalidReadingCount++;
        }

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

// Console output helpers
void printTestSummary(const TestSummary& summary)
{
    cout << "TEST SUMMARY" << endl;
    cout << "Total readings collected: " << summary.totalReadings << endl;
    cout << "OK readings: " << summary.okCount << endl;
    cout << "Warning readings: " << summary.warningCount << endl;
    cout << "Critical readings: " << summary.criticalCount << endl;
    cout << "Sensor failures: " << summary.sensorFailureCount << endl;
    cout << "Valid readings: " << summary.validReadingCount << endl;
    cout << "Invalid readings: " << summary.invalidReadingCount << endl;

    cout << "Overall result: " << determineOverallResult(summary) << endl;
}

SensorStatistics generateSensorStatistics(const vector<SensorReading>& readings, const string& sensorName)
{
    SensorStatistics statistics;
    statistics.sensorName = sensorName;
    statistics.validCount = 0;
    statistics.invalidCount = 0;
    statistics.minimumValue = numeric_limits<double>::max();
    statistics.maximumValue = numeric_limits<double>::lowest();
    statistics.averageValue = 0.0;

    double totalValue = 0.0;

    for (const SensorReading& reading : readings) {
        if (reading.sensorName != sensorName) {
            continue;
        }

        if (!reading.isValid) {
            statistics.invalidCount++;
            continue;
        }

        statistics.validCount++;
        totalValue += reading.value;

        if (reading.value < statistics.minimumValue) {
            statistics.minimumValue = reading.value;
        }

        if (reading.value > statistics.maximumValue) {
            statistics.maximumValue = reading.value;
        }
    }

    if (statistics.validCount > 0) {
        statistics.averageValue = totalValue / statistics.validCount;
    } else {
        statistics.minimumValue = 0.0;
        statistics.maximumValue = 0.0;
    }

    return statistics;
}

void printSensorStatistics(const SensorStatistics& statistics)
{
    cout << statistics.sensorName << " statistics" << endl;
    cout << "Valid readings: " << statistics.validCount << endl;
    cout << "Invalid readings: " << statistics.invalidCount << endl;

    if (statistics.validCount > 0) {
        cout << "Minimum value: " << statistics.minimumValue << endl;
        cout << "Maximum value: " << statistics.maximumValue << endl;
        cout << "Average value: " << statistics.averageValue << endl;
    } else {
        cout << "No valid readings available for statistics." << endl;
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

// CSV output helpers
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

void writeSensorStatisticsToCsv(const vector<SensorStatistics>& statisticsList, const string& fileName)
{
    ofstream outputFile(fileName);

    if (!outputFile) {
        cout << "Error: Could not open file for writing: " << fileName << endl;
        return;
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
}

void writeTestSummaryToCsv(const TestSummary& summary, const string& fileName)
{
    ofstream outputFile(fileName);

    if (!outputFile) {
        cout << "Error: Could not open file for writing: " << fileName << endl;
        return;
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
}

// Domain classes
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

    string getName() const
    {
        return name;
    }

    double simulateValue(int timeSeconds) const
    {
        return baseValue + (timeSeconds * rateOfChange);
    }

    SensorReading createReading(int timeSeconds) const
    {
        SensorReading reading;
        reading.timeSeconds = timeSeconds;
        reading.sensorName = name;
        reading.unit = unit;

        if (hasFailed(timeSeconds)) {
            reading.value = 0.0;
            reading.status = Status::SENSOR_FAILURE;
            reading.isValid = false;
        } else {
            double value = simulateValue(timeSeconds);
            reading.value = value;
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

    void writeSummaryCsv(const string& fileName) const
    {
        if (!validateTestHasRun("write summary CSV")) {
            return;
        }

        TestSummary summary = generateTestSummary(readings);
        writeTestSummaryToCsv(summary, fileName);
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

    void writeSensorStatisticsCsv(const string& fileName) const
    {
        if (!validateTestHasRun("write sensor statistics CSV")) {
            return;
        }

        vector<SensorStatistics> statisticsList;

        for (const Sensor& sensor : sensors) {
            SensorStatistics statistics = generateSensorStatistics(readings, sensor.getName());
            statisticsList.push_back(statistics);
        }

        writeSensorStatisticsToCsv(statisticsList, fileName);
    }

    void writeCsvLog(const string& fileName) const
    {
        if (!validateTestHasRun("write data log")) {
            return;
        }

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
    testStand.printSensorStatisticsReport();
    testStand.writeCsvLog("test_log.csv");
    testStand.writeSensorStatisticsCsv("sensor_statistics.csv");
    testStand.writeSummaryCsv("test_summary.csv");

    return 0;
}
