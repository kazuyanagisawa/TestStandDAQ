#ifndef SENSOR_READING_H
#define SENSOR_READING_H

#include <string>
#include "Status.h"

struct SensorReading
{
    int timeSeconds;
    std::string sensorName;
    double value;
    std::string unit;
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
    std::string sensorName;
    int validCount;
    int invalidCount;
    double minimumValue;
    double maximumValue;
    double averageValue;
};

#endif
