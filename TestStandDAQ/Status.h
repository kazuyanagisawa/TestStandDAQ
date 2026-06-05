#ifndef STATUS_H
#define STATUS_H

#include <string>

enum class Status
{
    OK,
    WARNING,
    CRITICAL,
    ANOMALY,
    SENSOR_FAILURE
};

enum class SensorHealth
{
    HEALTHY,
    DEGRADED,
    FAILED
};

std::string statusToString(Status status);

std::string sensorHealthToString(SensorHealth health);

#endif
