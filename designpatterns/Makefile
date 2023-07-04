CC=g++
CFLAGS=-pthread -std=c++17

DEMO_FILES=singleton_mt.cpp singleton.cpp visitor.cpp observer.cpp composite.cpp simplefactory.cpp


EXE_FILES=$(DEMO_FILES:.cpp=)

all: $(EXE_FILES)

%: %.cpp
	$(CC) $(CFLAGS) $< -o $@

clean:
	rm -rf $(EXE_FILES)