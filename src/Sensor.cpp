#include "Sensor.hpp"
#include <chrono>
#include <thread>
#include <cstdlib>

bool SensorData::operator>(const SensorData& other) const {
    return timestamp > other.timestamp;
}

Sensor::Sensor(const std::string& name_, int freq, std::queue<SensorData>& q, std::mutex& mtx, std::atomic<bool>& stop)
    : name(name_), frequency(freq), outputQueue(q), queueMutex(mtx), stopFlag(stop) {}

void Sensor::run() {
    using namespace std::chrono;
    auto interval = duration<double>(1.0 / frequency);

    while (!stopFlag.load()) {
        double now_time = duration<double>(system_clock::now().time_since_epoch()).count();
        double temp_value = 20.0 + ( 10.0 * std::rand() / RAND_MAX );

        SensorData data{ now_time, temp_value };

        {
            std::lock_guard<std::mutex> lock(queueMutex);
            outputQueue.push(data);
        }

        std::this_thread::sleep_for(interval);
    }
}
