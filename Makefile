CXX = g++
CXXFLAGS = -Wall -Wextra -std=c++20 -g

TARGET = kalah

SRCS = main.cpp Game.cpp Kalah.cpp tools.cpp Snapshot.cpp


OBJS = $(SRCS:.cpp=.o)

$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(OBJS)

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	rm -f $(TARGET) $(OBJS)
