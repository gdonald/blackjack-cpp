#CC = g++
CC = clang++
CC_FLAGS = -Wall -Wextra -std=gnu++14 -O0 -g -Iinclude
EXEC = blackjack
SOURCES = $(wildcard src/*.cpp)
OBJECTS = $(SOURCES:.cpp=.o)

$(EXEC): $(OBJECTS)
	$(CC) $(OBJECTS) -o $(EXEC)

%.o: %.cpp
	$(CC) -c $(CC_FLAGS) $< -o $@

clean:
	rm -f $(EXEC) $(OBJECTS) include/*~ src/*~
