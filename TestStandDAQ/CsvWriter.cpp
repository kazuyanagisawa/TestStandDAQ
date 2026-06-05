#include "CsvWriter.h"
#include "Reporting.h"
#include "Status.h"

#include <fstream>
#include <iostream>

using namespace std;

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

    outputFile << "sensor_name,health,valid_count,invalid_count,minimum_value,maximum_value,average_value" << endl;

    for (const SensorStatistics& statistics : statisticsList) {
        outputFile << statistics.sensorName << ","
                   << sensorHealthToString(statistics.health) << ","
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

    outputFile << "total_readings,ok_count,warning_count,critical_count,anomaly_count,sensor_failure_count,valid_reading_count,invalid_reading_count,overall_result" << endl;

    string overallResult = determineOverallResult(summary);

    outputFile << summary.totalReadings << ","
               << summary.okCount << ","
               << summary.warningCount << ","
               << summary.criticalCount << ","
               << summary.anomalyCount << ","
               << summary.sensorFailureCount << ","
               << summary.validReadingCount << ","
               << summary.invalidReadingCount << ","
               << overallResult << endl;

    cout << "Test summary written to: " << fileName << endl;
    return true;
}
