#ifndef THREADSAFEPRIORITYQUEUE_HPP
#define THREADSAFEPRIORITYQUEUE_HPP

#include <queue>
#include <mutex>
#include "Sensor.hpp"

class ThreadSafePriorityQueue {
private:
    std::priority_queue<SensorData, std::vector<SensorData>, std::greater<SensorData>> pq;
    std::mutex mtx;
public:
    void push(const SensorData& data);
    bool pop(SensorData& data);
    bool empty();
};

#endif
