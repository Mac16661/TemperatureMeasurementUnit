#include "SlidingWindow.hpp"

SlidingWindow::SlidingWindow(size_t size) : maxSize(size) {}

void SlidingWindow::add(double value) {
    window.push_back(value);
    if (window.size() > maxSize) {
        window.erase(window.begin());
    }
}

bool SlidingWindow::computeTempreature(double& result) {
    if (window.size() < maxSize) return false;

    double sumLog = 0.0;
    size_t validCount = 0;
    for (auto x : window) {
        if (x > 0) {
            sumLog += std::log(x);
            validCount++;
        }
    }
    if (validCount == 0) return false;

    result = std::exp(sumLog / validCount);
    return true;
}
