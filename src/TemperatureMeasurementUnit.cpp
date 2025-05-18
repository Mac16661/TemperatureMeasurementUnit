#include "TemperatureMeasurementUnit.hpp"
#include "Sensor.hpp"
#include "Aggregator.hpp"
#include "Processor.hpp"
#include <thread>
#include <iostream>
#include <chrono>

static const std::pair<std::string, int> SENSOR_FREQS[] = {
    {"sensor_1", 96000},
    {"sensor_2", 71000},
    {"sensor_3", 69900},
    {"sensor_4", 23000}
};

static const int WINDOW_SIZE = 4096;
static const int RUN_DURATION_SEC = 10;
static const std::size_t SENSOR_CNT = 4; 

TemperatureMeasurementUnit::TemperatureMeasurementUnit() : stopFlag(false) {
    sensors.reserve(SENSOR_CNT);

    queuePtrs.reserve(SENSOR_CNT);
    mutexPtrs.reserve(SENSOR_CNT);

    for (std::size_t i = 0; i < SENSOR_CNT; ++i) {
        queuePtrs.push_back(&sensorQueues[i]);
        mutexPtrs.push_back(&sensorMutexes[i]);
    }
}

void TemperatureMeasurementUnit::run() {
    threads.reserve(SENSOR_CNT + 2);

    for (std::size_t i = 0; i < SENSOR_CNT; ++i) {
        sensors.emplace_back(
            SENSOR_FREQS[i].first, SENSOR_FREQS[i].second, sensorQueues[i],sensorMutexes[i], stopFlag);
    }


    for (std::size_t i = 0; i < sensors.size(); ++i) {
        threads.emplace_back(&Sensor::run, &sensors[i]);
    }

    Aggregator agg(queuePtrs, mutexPtrs, aggregatedQueue, stopFlag);
    threads.emplace_back(&Aggregator::run, &agg);

    Processor proc(aggregatedQueue, stopFlag, WINDOW_SIZE);
    threads.emplace_back(&Processor::run, &proc);

    std::this_thread::sleep_for(std::chrono::seconds(RUN_DURATION_SEC));
    stopFlag = true;  

    for (auto& t : threads) {
        if (t.joinable()) t.join();
    }

    std::cout << "Simulation complete." << std::endl;
}
