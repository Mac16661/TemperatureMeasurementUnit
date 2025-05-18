#include "Aggregator.hpp"
#include <thread>
#include <chrono>

Aggregator::Aggregator(std::vector<std::queue<SensorData>*>& queues,
                       std::vector<std::mutex*>& mutexes,
                       ThreadSafePriorityQueue& output,
                       std::atomic<bool>& stop)
    : sensorQueues(queues), sensorMutexes(mutexes), outputQueue(output), stopFlag(stop) {}

void Aggregator::run() {
    using namespace std::chrono;
    while (!stopFlag.load()) {
        for (size_t i = 0; i < sensorQueues.size(); ++i) {
            std::lock_guard<std::mutex> lock(*sensorMutexes[i]);
            if (!sensorQueues[i]->empty()) {
                outputQueue.push(sensorQueues[i]->front());
                sensorQueues[i]->pop();
            }
        }
        std::this_thread::sleep_for(microseconds(10));
    }
}
