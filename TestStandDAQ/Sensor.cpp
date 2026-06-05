#include "Sensor.h"

Sensor::Sensor(
    std::string sensorName,
    std::string sensorUnit,
    double warningLimit,
    double criticalLimit,
    double startingValue,
    double changeRate,
    double noiseLimit,
    int failureTime,
    int spikeTime,
    double spikeSize)
    : name(sensorName),
      unit(sensorUnit),
      warningThreshold(warningLimit),
      criticalThreshold(criticalLimit),
      baseValue(startingValue),
      rateOfChange(changeRate),
      noiseAmplitude(noiseLimit),
      failureTimeSeconds(failureTime),
      spikeTimeSeconds(spikeTime),
      spikeMagnitude(spikeSize)
{
}

std::string Sensor::getName() const
{
    return name;
}

double Sensor::simulateValue(int timeSeconds) const
{
    double deterministicValue = baseValue + (timeSeconds * rateOfChange);
    double simpleNoise = noiseAmplitude * ((timeSeconds % 3) - 1);
    double simulatedValue = deterministicValue + simpleNoise;

    if (hasSpike(timeSeconds)) {
        simulatedValue += spikeMagnitude;
    }

    return simulatedValue;
}

SensorReading Sensor::createReading(int timeSeconds) const
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

bool Sensor::hasFailed(int timeSeconds) const
{
    return failureTimeSeconds != NO_FAILURE && timeSeconds >= failureTimeSeconds;
}

bool Sensor::hasSpike(int timeSeconds) const
{
    return spikeTimeSeconds != NO_SPIKE && timeSeconds == spikeTimeSeconds;
}

Status Sensor::determineStatus(double value) const
{
    if (value >= criticalThreshold) {
        return Status::CRITICAL;
    } else if (value >= warningThreshold) {
        return Status::WARNING;
    }

    return Status::OK;
}
