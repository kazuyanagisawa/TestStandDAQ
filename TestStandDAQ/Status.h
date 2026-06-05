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

std::string statusToString(Status status);

#endif
