#include "Processor.hpp"
#include <iostream>
#include <chrono>
#include <thread>

Processor::Processor(ThreadSafePriorityQueue& input, std::atomic<bool>& stop, int windowSize)
    : inputQueue(input), stopFlag(stop), window(windowSize) {}

void Processor::run() {
    using namespace std::chrono;
    SensorData data;

    while (!stopFlag.load()) {
        if (inputQueue.pop(data)) {
            window.add(data.value);
            double gm = 0;
            if (window.computeTempreature(gm)) {
                // TODO: Need asyncio to improve performance
                std::cout << "[" << data.timestamp << "] Tempreature : " << gm <<" degree Celsius"<< std::endl;  
            }
        } else {
            std::this_thread::sleep_for(microseconds(10));
        }
    }
}
