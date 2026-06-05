#ifndef CSV_WRITER_H
#define CSV_WRITER_H

#include <string>
#include <vector>
#include "SensorReading.h"

bool writeReadingsToCsv(const std::vector<SensorReading>& readings, const std::string& fileName);
bool writeSensorStatisticsToCsv(const std::vector<SensorStatistics>& statisticsList, const std::string& fileName);
bool writeTestSummaryToCsv(const TestSummary& summary, const std::string& fileName);

#endif
