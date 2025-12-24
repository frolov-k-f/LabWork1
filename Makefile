CXX = g++
CXXFLAGS = -Wall -Wpedantic -Werror -std=c++17

CORE_SRC = bitmap.cpp bitmap_image.cpp image_transform.cpp
CORE_OBJ = $(CORE_SRC:.cpp=.o)

MAIN_SRC = main.cpp
MAIN_OBJ = $(MAIN_SRC:.cpp=.o)
TARGET = lab1

TEST_SRC = tests.cpp
TEST_OBJ = $(TEST_SRC:.cpp=.o) $(CORE_OBJ)
TEST_TARGET = run_tests

.PHONY: all test clean

all: $(TARGET)

$(TARGET): $(CORE_OBJ) $(MAIN_OBJ)
	$(CXX) $(LDFLAGS) -o $@ $^ $(LDLIBS)

$(TEST_TARGET): $(TEST_OBJ)
	$(CXX) $(LDFLAGS) -o $@ $^ -lgtest -lgtest_main -pthread

test: $(TEST_TARGET)
	./$(TEST_TARGET)

clean:
	rm -f $(CORE_OBJ) $(MAIN_OBJ) $(TEST_OBJ) $(TARGET) $(TEST_TARGET) *.d \
		test_output.bmp rot_cw.bmp rot_ccw.bmp gauss.bmp
