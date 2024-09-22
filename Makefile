# Define the compiler and the flags
CXX = g++
CXXFLAGS = -Wall -g

# Define the target executable
TARGET = Appointment.exe

# Define the source files
SRCS = Appointment.cpp

# Define the object files
OBJS = $(SRCS:.cpp=.o)

# Default rule to build the target
all: $(TARGET)

# Rule to build the target executable
$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(OBJS)

# Rule to build object files
%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Clean rule to remove generated files
clean:
	rm -f $(TARGET) $(OBJS)

# Phony targets
.PHONY: all clean