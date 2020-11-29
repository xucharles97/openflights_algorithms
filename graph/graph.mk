CXX = clang++
LD = clang++
OBJS_DIR = .objs

# Add graph object files
OBJS += graph/Edge.o graph/Graph.o

# -MMD and -MP asks clang++ to generate a .d file listing the headers used in the source code for use in the Make process.
#   -MMD: "Write a depfile containing user headers"
#   -MP : "Create phony target for each dependency (other than main file)"
#   (https://clang.llvm.org/docs/ClangCommandLineReference.html)
DEPFILE_FLAGS = -MMD -MP

# Provide lots of helpful warning/errors:
WARNINGS = -pedantic -Wall -Werror -Wfatal-errors -Wextra -Wno-unused-parameter -Wno-unused-variable -Wno-unused-function

# Flags for compile:
CXXFLAGS += $(GRAPH) -std=c++1y -stdlib=libc++ -O0 $(WARNINGS) $(DEPFILE_FLAGS) -g -c

# Flags for linking:
LDFLAGS += $(CS225) -std=c++1y -stdlib=libc++ -lc++abi

all: $(EXE)

# Ensure .objs/ exists:
$(OBJS_DIR):
	@mkdir -p $(OBJS_DIR)
	@mkdir -p $(OBJS_DIR)/graph
	@mkdir -p $(OBJS_DIR)/graph/tests

# Rules for compiling source code.
# - Every object file is required by $(EXE)
# - Generates the rule requiring the .cpp file of the same name
$(OBJS_DIR)/%.o: %.cpp | $(OBJS_DIR)
	$(CXX) $(CXXFLAGS) $< -o $@

# Rules for compiling test suite.
# - Grab every .cpp file in tests/, compile them to .o files
# - Build the test program w/ catchmain.cpp from cs225
OBJS_TEST += $(filter-out $(EXE_OBJ), $(OBJS))
CPP_TEST = $(wildcard tests/*.cpp)
CPP_TEST += graph/tests/test.cpp
OBJS_TEST += $(CPP_TEST:.cpp=.o)

$(TEST): output_msg $(patsubst %.o, $(OBJS_DIR)/%.o, $(OBJS_TEST))
	$(LD) $(filter-out $<, $^) $(LDFLAGS) -o $@

# Additional dependencies for object files are included in the clang++
# generated .d files (from $(DEPFILE_FLAGS)):
-include $(OBJS_DIR)/*.d
-include $(OBJS_DIR)/graph/*.d
-include $(OBJS_DIR)/graph/tests/*.d

# Standard C++ Makefile rules:
clean:
	rm -rf $(EXE) $(TEST) $(OBJS_DIR) $(CLEAN_RM) *.o *.d

tidy: clean
	rm -rf doc

.PHONY: all tidy clean
