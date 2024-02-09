CC = g++
CFLAGS = -std=c++11
SRC_DIR = src
TARGET = programa_bancario
SRCS = $(SRC_DIR)/menu.cpp $(SRC_DIR)/funciones.cpp

ifeq ($(OS),Windows_NT)
	RM = del /Q
	TARGET_EXTENSION = .exe
else
	RM = rm -f
	TARGET_EXTENSION =
endif

all: $(TARGET)

$(TARGET): $(SRCS:.cpp=.o)
	$(CC) $(CFLAGS) -o $(TARGET)$(TARGET_EXTENSION) $^

%.o: %.cpp
	$(CC) $(CFLAGS) -c -o $@ $<

run: $(TARGET)
	./$(TARGET)$(TARGET_EXTENSION)

clean:
	$(RM) $(TARGET)$(TARGET_EXTENSION) $(SRC_DIR)/*.o
