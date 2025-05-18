#ifndef TEMPERATUREFUSIONSYSTEM_HPP
#define TEMPERATUREFUSIONSYSTEM_HPP

#include <vector>
#include <thread>
#include <queue>
#include <mutex>
#include <atomic>
#include "ThreadSafePriorityQueue.hpp"
#include "Sensor.hpp"

class TemperatureMeasurementUnit {
private:
    std::vector<Sensor> sensors; 
    std::vector<std::thread> threads;
    std::vector<std::queue<SensorData>> sensorQueues{4};
    std::vector<std::mutex> sensorMutexes{4};
    std::vector<std::queue<SensorData>*> queuePtrs;
    std::vector<std::mutex*> mutexPtrs;
    ThreadSafePriorityQueue aggregatedQueue;
    std::atomic<bool> stopFlag;

public:
    TemperatureMeasurementUnit();

    void run();
};

#endif
