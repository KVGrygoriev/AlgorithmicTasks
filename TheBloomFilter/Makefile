VERSION=0.0.1
CC=g++
TARGET=TheBloomFilter

RFLAGS=-Wall -std=c++14 -DNDEBUG -O2

INCLUDES=-I.

OPTFLAGS=$(RFLAGS)
CCFLAGS=$(OPTFLAGS) $(INCLUDES)

CPPS=$(wildcard *.cpp)
OBJS=$(CPPS:.cpp=.o)

%.o: %.cpp
	$(CC) $(CCFLAGS) -c $< -o $@

$(TARGET): $(OBJS)
	$(CC) $(OBJS) -o $@

clean:
	$(RM) $(OBJS) $(TARGET)

