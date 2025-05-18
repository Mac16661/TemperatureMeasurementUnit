#ifndef SLIDINGWINDOW_HPP
#define SLIDINGWINDOW_HPP

#include <vector>
#include <cmath>

class SlidingWindow {
private:
    std::vector<double> window;
    size_t maxSize;
public:
    explicit SlidingWindow(size_t size);

    void add(double value);

    bool computeTempreature(double& result);
};

#endif
