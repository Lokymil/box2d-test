CXX = g++

CXXFLAGS = -g -Wall -Wformat
CXXFLAGS += -std=c++17
LIBS = -lBox2D -lGL -lSDL2
EXE = out/box2d-test
BUILDDIR = build
SRCDIR = src
MAIN=main

SOURCES = $(shell find . -type f -wholename "**/*.cpp" | grep -v main.cpp | sed -e 's/\.\/$(SRCDIR)\///')
OBJS = $(addprefix $(BUILDDIR)/, $(addsuffix .o, $(basename $(SOURCES))))

.PHONY: start debug build builddir clear valgrind single
##----------------------------------------------------

start: clear build
	@echo "Start $(EXE)"
	./$(EXE)

debug: build
	@echo "Start $(EXE) in debug mode"
	gdb ./$(EXE)

build: builddir $(EXE)
	@echo "Build completed"

builddir:
	mkdir -p $(BUILDDIR)
	mkdir -p out

$(EXE): $(BUILDDIR)/$(MAIN).o $(OBJS)
	mkdir -p $(dir $@)
	$(CXX) $(CXXFLAGS) -o $@ $^ $(LIBS)

$(BUILDDIR)/$(MAIN).o: $(SRCDIR)/$(MAIN).cpp
	$(CXX) $(CXXFLAGS) -c $^ -o $@

$(BUILDDIR)/%.o: $(SRCDIR)/%.cpp $(SRCDIR)/%.h
	mkdir -p $(dir $@)
	$(CXX) $(CXXFLAGS) -c $< -o $@

single: $(SRCDIR)/$(MAIN).cpp clear builddir
	mkdir -p $(dir $@)
	$(CXX) $(CXXFLAGS) -o $(EXE) $< $(LIBS)
	@echo "Start $(EXE)"
	./$(EXE)

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