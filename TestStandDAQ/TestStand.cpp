#include "TestStand.h"

#include <iostream>

#include "Reporting.h"
#include "CsvWriter.h"

using namespace std;

TestStand::TestStand(int testDurationSeconds)
    : durationSeconds(testDurationSeconds),
      hasRun(false)
{
}

bool TestStand::validateConfiguration() const
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

bool TestStand::validateTestHasRun(const string& operationName) const
{
    if (!hasRun) {
        cout << "Error: Cannot " << operationName << " before test run." << endl;
        return false;
    }

    return true;
}

int TestStand::countAnomalies() const
{
    int anomalyCount = 0;

    for (const SensorReading& reading : readings) {
        if (reading.status == Status::ANOMALY) {
            anomalyCount++;
        }
    }

    return anomalyCount;
}

void TestStand::runAcquisitionLoop()
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

void TestStand::addSensor(const Sensor& sensor)
{
    sensors.push_back(sensor);
}

bool TestStand::run()
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

void TestStand::printSummary() const
{
    if (!validateTestHasRun("print summary")) {
        return;
    }

    TestSummary summary = generateTestSummary(readings);
    printTestSummary(summary);

    cout << "Anomalies detected: "
         << countAnomalies()
         << endl;
}

void TestStand::printSensorStatisticsReport() const
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

bool TestStand::writeSummaryCsv(const string& fileName) const
{
    if (!validateTestHasRun("write summary CSV")) {
        return false;
    }

    TestSummary summary = generateTestSummary(readings);
    return writeTestSummaryToCsv(summary, fileName);
}

bool TestStand::writeSensorStatisticsCsv(const string& fileName) const
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

bool TestStand::writeCsvLog(const string& fileName) const
{
    if (!validateTestHasRun("write data log")) {
        return false;
    }

    return writeReadingsToCsv(readings, fileName);
}
