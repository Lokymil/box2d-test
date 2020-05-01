CXX = g++

CXXFLAGS = -g -Wall -Wformat
CXXFLAGS += -std=c++17
LIBS = -lBox2D
EXE = out/box2d-test
BUILDDIR = build
SRCDIR = src

SOURCES = $(shell find . -type f -wholename "**/*.cpp" | grep -v main.cpp | sed -e 's/\.\/$(SRCDIR)\///')
OBJS = $(addprefix $(BUILDDIR)/, $(addsuffix .o, $(basename $(SOURCES))))

.PHONY: start debug build buildir clear valgrind
##----------------------------------------------------

start: build
	@echo "Start $(EXE)"
	./$(EXE)

debug: build
	@echo "Start $(EXE) in debug mode"
	gdb ./$(EXE)

build: buildir $(EXE)
	@echo "Build completed"

buildir:
	mkdir -p build

$(EXE): $(BUILDDIR)/main.o $(OBJS)
	mkdir -p $(dir $@)
	$(CXX) $(CXXFLAGS) -o $@ $^ $(LIBS)

$(BUILDDIR)/main.o: $(SRCDIR)/main.cpp
	$(CXX) $(CXXFLAGS) -c $^ -o $@

$(BUILDDIR)/%.o: $(SRCDIR)/%.cpp $(SRCDIR)/%.h
	mkdir -p $(dir $@)
	$(CXX) $(CXXFLAGS) -c $< -o $@

clear:
	rm -rf $(dir $(EXE))
	rm -rf build
	rm -rf log

valgrind: build
	mkdir -p log
	rm -f log/valgrind-out.txt
	valgrind --leak-check=full \
         --show-leak-kinds=all \
		 --leak-resolution=low \
         --track-origins=yes \
         --verbose \
         --log-file=log/valgrind-out.txt \
         $(EXE)