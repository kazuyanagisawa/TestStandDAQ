#ifndef SENSOR_H
#define SENSOR_H

#include <string>

#include "SensorReading.h"

class Sensor
{
private:
    std::string name;
    std::string unit;

    double warningThreshold;
    double criticalThreshold;
    double baseValue;
    double rateOfChange;
    double noiseAmplitude;
    int failureTimeSeconds;

    static const int NO_FAILURE = -1;

public:
    Sensor(
        std::string sensorName,
        std::string sensorUnit,
        double warningLimit,
        double criticalLimit,
        double startingValue,
        double changeRate,
        double noiseLimit,
        int failureTime = NO_FAILURE);

    std::string getName() const;
    double simulateValue(int timeSeconds) const;
    SensorReading createReading(int timeSeconds) const;
    bool hasFailed(int timeSeconds) const;
    Status determineStatus(double value) const;
};

#endif
