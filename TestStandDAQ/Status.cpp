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
        case Status::SENSOR_FAILURE:
            return "SENSOR_FAILURE";
    }

    return "UNKNOWN";
}
