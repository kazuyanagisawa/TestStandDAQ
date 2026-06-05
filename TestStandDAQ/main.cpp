#include <iostream>
#include <string>

#include "Sensor.h"
#include "TestStand.h"

using namespace std;

const int TEST_DURATION_SECONDS = 5;
const string DATA_LOG_FILE_NAME = "test_log.csv";
const string SENSOR_STATISTICS_FILE_NAME = "sensor_statistics.csv";
const string TEST_SUMMARY_FILE_NAME = "test_summary.csv";

void configureSensors(TestStand& testStand)
{
    SensorConfig temperatureConfig;
    temperatureConfig.name = "Temperature";
    temperatureConfig.unit = "C";
    temperatureConfig.warningThreshold = 700.0;
    temperatureConfig.criticalThreshold = 800.0;
    temperatureConfig.baseValue = 650.0;
    temperatureConfig.rateOfChange = 25.0;
    temperatureConfig.noiseAmplitude = 2.0;
    temperatureConfig.anomalyThreshold = 40.0;
    temperatureConfig.failureTimeSeconds = 4;

    SensorConfig pressureConfig;
    pressureConfig.name = "Pressure";
    pressureConfig.unit = "psi";
    pressureConfig.warningThreshold = 235.0;
    pressureConfig.criticalThreshold = 250.0;
    pressureConfig.baseValue = 210.0;
    pressureConfig.rateOfChange = 8.0;
    pressureConfig.noiseAmplitude = 1.0;
    pressureConfig.anomalyThreshold = 15.0;
    pressureConfig.dropoutStartTimeSeconds = 2;
    pressureConfig.dropoutDurationSeconds = 2;

    SensorConfig vibrationConfig;
    vibrationConfig.name = "Vibration";
    vibrationConfig.unit = "g";
    vibrationConfig.warningThreshold = 1.8;
    vibrationConfig.criticalThreshold = 2.2;
    vibrationConfig.baseValue = 1.2;
    vibrationConfig.rateOfChange = 0.3;
    vibrationConfig.noiseAmplitude = 0.05;
    vibrationConfig.anomalyThreshold = 0.8;
    vibrationConfig.spikeTimeSeconds = 3;
    vibrationConfig.spikeMagnitude = 1.0;

    testStand.addSensor(Sensor(temperatureConfig));
    testStand.addSensor(Sensor(pressureConfig));
    testStand.addSensor(Sensor(vibrationConfig));
}

int main() {
    cout << "Starting Test Stand Data Acquisition Simulation..." << endl;
    cout << "System initialized successfully." << endl;
    cout << endl;

    TestStand testStand(TEST_DURATION_SECONDS);

    configureSensors(testStand);

    if (!testStand.run()) {
        return 1;
    }

    cout << "Test complete." << endl;
    cout << endl;
    testStand.printSummary();
    cout << endl;
    testStand.printSensorStatisticsReport();

    if (!testStand.writeCsvLog(DATA_LOG_FILE_NAME)) {
        return 1;
    }

    if (!testStand.writeSensorStatisticsCsv(SENSOR_STATISTICS_FILE_NAME)) {
        return 1;
    }

    if (!testStand.writeSummaryCsv(TEST_SUMMARY_FILE_NAME)) {
        return 1;
    }

    return 0;
}
