# TestStandDAQ

C++ test stand data acquisition and monitoring simulation inspired by engineering test environments used for equipment validation and performance monitoring.

## Overview

TestStandDAQ simulates the collection, monitoring, and analysis of sensor data generated during an engineering test. The application models multiple sensors, injects realistic fault conditions, evaluates sensor health, and generates summary reports and CSV exports.

The project was developed incrementally to demonstrate object-oriented design, modular architecture, fault simulation, reporting systems, and engineering-focused data analysis workflows.

## Features

- Multi-sensor data acquisition simulation
- Warning and critical threshold monitoring
- Permanent sensor failure simulation
- Transient spike fault injection
- Temporary sensor dropout simulation
- Anomaly detection
- Sensor health classification
- Statistical analysis of sensor performance
- CSV export of test results and summaries
- Modular C++ architecture

## Architecture

The application is organized into modular components with clearly defined responsibilities.

| Component | Responsibility |
|------------|----------------|
| Sensor | Simulates sensor behavior, fault conditions, and status evaluation |
| TestStand | Coordinates acquisition, validation, reporting, and data export |
| SensorReading | Defines shared data structures used throughout the system |
| Reporting | Generates statistics, summaries, and health assessments |
| CsvWriter | Exports test results and analysis to CSV files |
| Status | Defines system status and health classifications |

This separation of responsibilities was introduced incrementally through refactoring as the project grew in complexity.

## Simulated Fault Conditions

The simulator supports multiple categories of sensor faults commonly encountered in engineering test environments.

### Permanent Sensor Failure

A sensor can be configured to fail at a specified point in time, causing all subsequent readings to become invalid.

### Transient Spike

A sensor can experience a temporary one-time excursion from its expected value.

### Sensor Dropout

A sensor can temporarily stop producing valid data before recovering automatically.

### Anomaly Detection

The system evaluates changes between readings and flags unusually large deviations as anomalies.

## Engineering Decisions and Learning Outcomes

This project was developed incrementally to practice software engineering concepts rather than simply produce a working simulation.

Key lessons learned throughout the project:

- Refactoring large source files into modular components
- Using configuration structures to replace long parameter lists
- Separating acquisition, simulation, reporting, and export responsibilities
- Designing reusable data models for summaries and statistics
- Building features through small, testable commits
- Translating engineering requirements into software behavior

Examples of engineering decisions include introducing a SensorConfig structure to improve maintainability, adding health assessment logic to convert raw telemetry into actionable information, and implementing anomaly detection to identify unexpected sensor behavior.

## Example Output

### Test Summary

```text
Overall Result: FAIL

Total readings: 15
OK readings: 7
Warning readings: 2
Critical readings: 1
Anomaly readings: 1
Sensor failures: 2

Valid readings: 13
Invalid readings: 2
