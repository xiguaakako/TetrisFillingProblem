CC = g++
CFLAGS = -std=c++20
LIBS = -lminisat
SRC_DIR = src
BIN_DIR = bin
INCLUDES = -I./$(SRC_DIR)/minisat
LFLAGS = -L./$(SRC_DIR)/minisat/build/release/lib
EXECUTABLE = $(BIN_DIR)/TetrisSAT

# List of source files
SOURCES = $(SRC_DIR)/main.cpp \
		$(SRC_DIR)/TetrisSolver.cpp \
		$(SRC_DIR)/TetrisData.cpp \
		$(SRC_DIR)/Clauses.cpp \
		$(SRC_DIR)/AuxFuncs.cpp \
		$(SRC_DIR)/IO.cpp

# List of header files
HEADERS = $(SRC_DIR)/TetrisSolver.h \
		$(SRC_DIR)/TetrisData.h \
		$(SRC_DIR)/Cell.h \
		$(SRC_DIR)/Clauses.h \
		$(SRC_DIR)/AuxFuncs.h \
		$(SRC_DIR)/IO.h

# Rule to build the executable
$(EXECUTABLE): $(SOURCES) $(SRC_DIR)/lodepng/lodepng.o
	@ $(CC) -o $@ $(INCLUDES) $(CFLAGS) $(SOURCES) $(SRC_DIR)/lodepng/lodepng.o $(LFLAGS) $(LIBS)

# Compile lodepng.cpp with specific flags
$(SRC_DIR)/lodepng/lodepng.o: $(SRC_DIR)/lodepng/lodepng.cpp
	@$(CC) $(CFLAGS) -Wall -Wextra -pedantic -ansi -O3 -c -o $@ $<

# Rule to clean the project
clean:
	@rm -f $(EXECUTABLE) $(SRC_DIR)/lodepng/lodepng.o

.PHONY: all clean
