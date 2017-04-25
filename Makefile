# Thanks to http://scottmcpeak.com/autodepend/autodepend.html

SRC_DIR=src/
BUILD_DIR=build/
SOURCES=$(wildcard src/*.cpp src/**/*.cpp)
OBJS := $(SOURCES:.cpp=.o)
OUT=run.exe
override CXXFLAGS+= -std=c++0x -g -pthread

# link
$(OUT): $(OBJS)
	$(CXX) $(OBJS) -o $@ $(CXXFLAGS)

TEST_SOURCES=$(wildcard tests/*.cpp tests/**/*.cpp)
TEST_OBJS := $(TEST_SOURCES:.cpp=.o)
test: $(TEST_OBJS) $(OBJS)
	$(CXX) $(TEST_OBJS) $(filter-out %main.o, $(OBJS)) -o $@ $(CXXFLAGS)
# pull in dependency info for *existing* .o files
-include $(OBJS:.o=.d)

# compile and generate dependency info
%.o: %.c
	$(CXX) -c $(CPPFLAGS) $*.c -o $*.o
	$(CXX) -MM $(CPPFLAGS) $*.c > $*.d

# remove compilation products
clean:
	rm -f $(OUT) test $(wildcard *.o **/*.o)