#ifndef SENSOR_HPP
#define SENSOR_HPP

#include <string>
#include <queue>
#include <mutex>
#include <atomic>
#include <random>

struct SensorData {
    double timestamp;
    double value;
    bool operator>(const SensorData& other) const;
};

class Sensor {
private:
    std::string name;
    int frequency;
    std::queue<SensorData>& outputQueue;
    std::mutex& queueMutex;
    std::atomic<bool>& stopFlag;
    
public:
    Sensor(const std::string& name, int freq, std::queue<SensorData>& q, std::mutex& mtx, std::atomic<bool>& stop);

    void run();
};

#endif 
