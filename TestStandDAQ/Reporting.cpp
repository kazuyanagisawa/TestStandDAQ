#include "Reporting.h"
#include "Status.h"

#include <iostream>
#include <limits>

using namespace std;

// Summary and statistics logic
string determineOverallResult(const TestSummary& summary)
{
    if (summary.sensorFailureCount > 0 || summary.criticalCount > 0 || summary.anomalyCount > 0) {
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
    summary.anomalyCount = 0;
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
        } else if (reading.status == Status::ANOMALY) {
            summary.anomalyCount++;
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
    cout << "Anomaly readings: " << summary.anomalyCount << endl;
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
    statistics.health = SensorHealth::HEALTHY;

    int warningCount = 0;
    int criticalCount = 0;
    int anomalyCount = 0;
    double totalValue = 0.0;

    for (const SensorReading& reading : readings) {
        if (reading.sensorName != sensorName) {
            continue;
        }

        if (reading.status == Status::WARNING) {
            warningCount++;
        } else if (reading.status == Status::CRITICAL) {
            criticalCount++;
        } else if (reading.status == Status::ANOMALY) {
            anomalyCount++;
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

    if (statistics.invalidCount > 0) {
        statistics.health = SensorHealth::FAILED;
    } else if (criticalCount > 0 || anomalyCount > 0 || warningCount > 0) {
        statistics.health = SensorHealth::DEGRADED;
    } else {
        statistics.health = SensorHealth::HEALTHY;
    }

    return statistics;
}

void printSensorStatistics(const SensorStatistics& statistics)
{
    cout << statistics.sensorName << " statistics" << endl;
    cout << "Health: " << sensorHealthToString(statistics.health) << endl;
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
