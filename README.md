##TemperatureMeasurementUnit

#Components:

Sensor:	Generates random temperature values ∈ [20 °C, 30 °C] at its own frequency and pushes them into a per-sensor queue.

Aggregator:	Pulls the oldest sample from every sensor queue and inserts it into a single time-ordered ThreadSafePriorityQueue.

Processor:	Pops samples in chronological order, feeds them to a SlidingWindow, and prints the geometric-mean temperature once the window is full.

SlidingWindow:	Keeps the last N values (default 4096) and computes temperature.

TemperatureMeasurementUnit:	Wires everything together, starts all threads, lets them run for 10 s, then stops and joins them.

##How to Build and Run:

# build clean
make clean

# build
make

# run the simulation
make run

# remove build artifacts
make clean
