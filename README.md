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
```

### Sensor Statistics

```text
Temperature statistics
Health: FAILED
Valid readings: 4
Invalid readings: 1
Minimum value: 648
Maximum value: 752
Average value: 701

Pressure statistics
Health: FAILED
Valid readings: 3
Invalid readings: 2
Minimum value: 209
Maximum value: 226
Average value: 218

Vibration statistics
Health: DEGRADED
Valid readings: 5
Invalid readings: 0
Minimum value: 1.15
Maximum value: 2.25
Average value: 1.48
```

## Project Evolution

Rather than building the final application all at once, the project was developed through a series of small, testable iterations.

Major milestones included:

1. Basic sensor simulation and acquisition loop
2. Threshold monitoring and status reporting
3. CSV export and reporting infrastructure
4. Refactoring into modular components
5. Sensor configuration management with SensorConfig
6. Fault injection (failures, spikes, and dropouts)
7. Anomaly detection
8. Sensor health assessment
9. Enhanced reporting and CSV exports

This incremental approach mirrors how production engineering software is commonly developed and maintained.

## Technology Stack

- C++17
- Standard Template Library (STL)
- Object-Oriented Programming
- File I/O
- CSV Data Export
- Git
- GitHub
- Xcode

## Project Structure

```text
TestStandDAQ/
├── Sensor
│   └── Sensor simulation and fault injection
├── TestStand
│   └── Acquisition coordination and reporting
├── SensorReading
│   └── Shared data models and summary structures
├── Reporting
│   └── Statistics, summaries, and health assessment
├── CsvWriter
│   └── CSV export utilities
├── Status
│   └── Status and health classifications
└── main.cpp
    └── Application entry point and configuration
```

## Resume Project Summary

Developed a modular C++ test stand data acquisition and monitoring simulation that models sensor behavior, injects realistic fault conditions, evaluates sensor health, and generates automated reports. Implemented anomaly detection, fault simulation, statistical analysis, CSV export functionality, and object-oriented system architecture through an incremental engineering-focused development process.

## Skills Demonstrated

- C++
- Object-Oriented Design
- Software Refactoring
- Data Acquisition Concepts
- Fault Detection and Monitoring
- Data Modeling
- CSV File Processing
- Modular Software Architecture
- Git Version Control
- Technical Documentation

## Future Enhancements

Potential future improvements include:

- Real-time data visualization dashboard
- Configuration file support for sensor definitions
- Additional anomaly detection techniques
- Unit testing framework integration
- Database-backed data storage

These ideas were intentionally left out of the current version to keep the project focused, maintainable, and representative of an incremental engineering workflow.
