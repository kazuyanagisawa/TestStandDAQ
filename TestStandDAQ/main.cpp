#include <iostream>
#include <string>

#include "Sensor.h"
#include "TestStand.h"

using namespace std;

const int TEST_DURATION_SECONDS = 5;
const string DATA_LOG_FILE_NAME = "test_log.csv";
const string SENSOR_STATISTICS_FILE_NAME = "sensor_statistics.csv";
const string TEST_SUMMARY_FILE_NAME = "test_summary.csv";

int main() {
    cout << "Starting Test Stand Data Acquisition Simulation..." << endl;
    cout << "System initialized successfully." << endl;
    cout << endl;

    TestStand testStand(TEST_DURATION_SECONDS);

    testStand.addSensor(Sensor("Temperature", "C", 700.0, 800.0, 650.0, 25.0, 4));
    testStand.addSensor(Sensor("Pressure", "psi", 235.0, 250.0, 210.0, 8.0));
    testStand.addSensor(Sensor("Vibration", "g", 1.8, 2.2, 1.2, 0.3));

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
