#include "ThreadSafePriorityQueue.hpp"

void ThreadSafePriorityQueue::push(const SensorData& data) {
    std::lock_guard<std::mutex> lock(mtx);
    pq.push(data);
}

bool ThreadSafePriorityQueue::pop(SensorData& data) {
    std::lock_guard<std::mutex> lock(mtx);
    if (pq.empty()) return false;
    data = pq.top();
    pq.pop();
    return true;
}

bool ThreadSafePriorityQueue::empty() {
    std::lock_guard<std::mutex> lock(mtx);
    return pq.empty();
}
