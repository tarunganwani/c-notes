CC=g++
CFLAGS=-pthread -std=c++17

DEMO_FILES=hello.cpp pro-con-cv.cpp condition-var-simple.cpp pro-con.cpp \
			locks-part1.cpp locks-part2.cpp mutexes.cpp locks-shared-lock.cpp \
			locks-shared-lock.cpp async.cpp promise-future.cpp detach.cpp






EXE_FILES=$(DEMO_FILES:.cpp=)

all: $(EXE_FILES)

%: %.cpp
	$(CC) $(CFLAGS) $< -o $@

clean:
	rm -rf $(EXE_FILES)