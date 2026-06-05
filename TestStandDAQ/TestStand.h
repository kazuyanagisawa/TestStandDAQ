#ifndef TEST_STAND_H
#define TEST_STAND_H

#include <string>
#include <vector>

#include "Sensor.h"
#include "SensorReading.h"

class TestStand
{
private:
    std::vector<Sensor> sensors;
    std::vector<SensorReading> readings;

    int durationSeconds;
    bool hasRun;
    int countAnomalies() const;

    bool validateConfiguration() const;
    bool validateTestHasRun(const std::string& operationName) const;
    void runAcquisitionLoop();

public:
    TestStand(int testDurationSeconds);

    void addSensor(const Sensor& sensor);

    bool run();

    void printSummary() const;
    void printSensorStatisticsReport() const;

    bool writeCsvLog(const std::string& fileName) const;
    bool writeSensorStatisticsCsv(const std::string& fileName) const;
    bool writeSummaryCsv(const std::string& fileName) const;
};

#endif
