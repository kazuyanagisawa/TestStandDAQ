#ifndef SENSOR_H
#define SENSOR_H

#include <string>
#include "SensorReading.h"

struct SensorConfig
{
    std::string name;
    std::string unit;

    double warningThreshold;
    double criticalThreshold;

    double baseValue;
    double rateOfChange;
    double noiseAmplitude;

    int failureTimeSeconds = -1;

    int spikeTimeSeconds = -1;
    double spikeMagnitude = 0.0;

    int dropoutStartTimeSeconds = -1;
    int dropoutDurationSeconds = 0;
};

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
    int spikeTimeSeconds;
    double spikeMagnitude;
    int dropoutStartTimeSeconds;
    int dropoutDurationSeconds;


public:
    static const int NO_FAILURE = -1;
    static const int NO_SPIKE = -1;
    static const int NO_DROPOUT = -1;
    Sensor(const SensorConfig& config);
    

    std::string getName() const;
    double simulateValue(int timeSeconds) const;
    SensorReading createReading(int timeSeconds) const;
    bool hasFailed(int timeSeconds) const;
    bool hasSpike(int timeSeconds) const;
    bool hasDropout(int timeSeconds) const;
    Status determineStatus(double value) const;
};

#endif
