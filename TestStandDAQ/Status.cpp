#include "Status.h"

std::string statusToString(Status status)
{
    switch (status) {
        case Status::OK:
            return "OK";
        case Status::WARNING:
            return "WARNING";
        case Status::CRITICAL:
            return "CRITICAL";
        case Status::ANOMALY:
            return "ANOMALY";
        case Status::SENSOR_FAILURE:
            return "SENSOR_FAILURE";
    }

    return "UNKNOWN";
}

std::string sensorHealthToString(SensorHealth health)
{
    switch (health) {
        case SensorHealth::HEALTHY:
            return "HEALTHY";
        case SensorHealth::DEGRADED:
            return "DEGRADED";
        case SensorHealth::FAILED:
            return "FAILED";
    }

    return "UNKNOWN";
}
