#ifndef AGGREGATOR_HPP
#define AGGREGATOR_HPP

#include <queue>
#include <mutex>
#include <vector>
#include <atomic>
#include "ThreadSafePriorityQueue.hpp"
#include "Sensor.hpp"

class Aggregator {
private:
    std::vector<std::queue<SensorData>*>& sensorQueues;
    std::vector<std::mutex*>& sensorMutexes;
    ThreadSafePriorityQueue& outputQueue;
    std::atomic<bool>& stopFlag;

public:
    Aggregator(std::vector<std::queue<SensorData>*>& queues,
               std::vector<std::mutex*>& mutexes,
               ThreadSafePriorityQueue& output,
               std::atomic<bool>& stop);

    void run();
};

#endif 
