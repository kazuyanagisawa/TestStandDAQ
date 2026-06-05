#ifndef REPORTING_H
#define REPORTING_H

#include <string>
#include <vector>
#include "SensorReading.h"

std::string determineOverallResult(const TestSummary& summary);

TestSummary generateTestSummary(const std::vector<SensorReading>& readings);

SensorStatistics generateSensorStatistics(
    const std::vector<SensorReading>& readings,
    const std::string& sensorName
);

void printTestSummary(const TestSummary& summary);
void printSensorStatistics(const SensorStatistics& statistics);
void printReading(const SensorReading& reading);

#endif
