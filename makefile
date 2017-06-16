INCDIR :=include
SRCDIR :=src
TESTDIR:=tests
OBJDIR :=.obj
CXX = clang++
CPPFLAGS += -MMD -MP
CXXFLAGS += -std=c++14 -Wall -I$(INCDIR)

SRC = $(wildcard $(SRCDIR)/*.cpp) $(wildcard $(TESTDIR)/*.cpp)
TMP = $(notdir $(SRC:%.cpp=%.o))
OBJ = $(TMP:%.o=$(OBJDIR)/%.o)
DEP = $(OBJ:.o=.d)

vpath %.cpp $(SRCDIR) $(TESTDIR)

print-%  : ; @echo $* = $($*)

all: tests

unit_tests: $(OBJ)
	$(CXX) $(CXXFLAGS) -o $@.out $^

tests: unit_tests
	./unit_tests.out

$(OBJDIR)/%.o: %.cpp | $(OBJDIR)
	$(CXX) $(CXXFLAGS) -c -o $@ $<

$(OBJDIR):
	@mkdir $@

-include $(DEP)

.PHONY: all unit_tests tests clean

clean:
	rm -f $(DEP) $(OBJ) $(PRO) 