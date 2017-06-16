CXX = clang++
CXXFLAGS += -std=c++14 -Wall
DEPS = clause.h
OBJ = unit_tests.o clause.o

%.o: %.cpp $(DEPS)
	$(CXX) $(CXXFLAGS) -c -o $@ $<

unit_tests: $(OBJ)
	$(CXX) $(CXXFLAGS) -o $@.out $^ 
