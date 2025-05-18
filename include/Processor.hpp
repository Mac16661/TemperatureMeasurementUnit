#ifndef PROCESSOR_HPP
#define PROCESSOR_HPP

#include <atomic>
#include "ThreadSafePriorityQueue.hpp"
#include "SlidingWindow.hpp"
#include "Sensor.hpp"

class Processor {
private:
    ThreadSafePriorityQueue& inputQueue;
    std::atomic<bool>& stopFlag;
    SlidingWindow window;

public:
    Processor(ThreadSafePriorityQueue& input, std::atomic<bool>& stop, int windowSize);

    void run();
};

#endif
