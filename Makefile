
SRC_DIR   := src
INC_DIR   := include
BUILD_DIR := build
BIN_DIR   := bin


CXX       := g++
CXXFLAGS  := -std=c++14 -Wall -Wextra -Wpedantic -O2 -I$(INC_DIR) -pthread
LDFLAGS   := -pthread      


SRCS := $(wildcard $(SRC_DIR)/*.cpp) $(wildcard *.cpp)
OBJS := $(patsubst %.cpp,$(BUILD_DIR)/%.o,$(notdir $(SRCS)))


TARGET := $(BIN_DIR)/temperature_measurement_unit
all: $(TARGET)


$(BUILD_DIR)/%.o: $(SRC_DIR)/%.cpp | $(BUILD_DIR)
	@mkdir -p $(dir $@)
	$(CXX) $(CXXFLAGS) -c $< -o $@

$(BUILD_DIR)/main.o: main.cpp | $(BUILD_DIR)
	@mkdir -p $(dir $@)
	$(CXX) $(CXXFLAGS) -c $< -o $@


$(TARGET): $(OBJS) | $(BIN_DIR)
	$(CXX) $(OBJS) $(LDFLAGS) -o $@
	@echo "✓ Built $(TARGET)"


$(BIN_DIR) $(BUILD_DIR):
	@mkdir -p $@


run: $(TARGET)
	./$(TARGET)

clean:
	@$(RM) -r $(BUILD_DIR) $(BIN_DIR)
	@echo "Cleaned."

.PHONY: all clean run
