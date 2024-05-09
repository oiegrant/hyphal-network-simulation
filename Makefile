CC = g++
CFLAGS = -Wall -std=c++23
SRC_DIR := src
GUI_DIR := src/imgui
OBJ_DIR := bin
SRC_FILES := $(wildcard $(SRC_DIR)/*.cpp)
OBJ_FILES := $(patsubst $(SRC_DIR)/%.cpp, $(OBJ_DIR)/%.o, $(SRC_FILES))
INCLUDE = -Isrc/include
VPATH = src

simulation: $(OBJ_FILES)
	$(CC) $(CFLAGS) -o simulation $(OBJ_FILES)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp
	$(CC) $(CFLAGS) $(INCLUDE) -c $< -o $@

.PHONY:
clean:
	make -C $(GUI_DIR) clean
	rm -rf bin/*
	rm -rf simulation
	rm -rf documentation/html
	rm -rf documentation/latex
	rm -rf build	

.PHONY:
run:
	mkdir -p bin
#make -C $(GUI_DIR) -f Makefile.emscripten serve
	make -C $(GUI_DIR) all
	make && (cd $(GUI_DIR) && ./app) 
#make && ./simulation


.PHONY:
test:
	mkdir -p bin
	make
	cmake -S . -B build
	cmake --build build
	cd build && ctest --output-on-failure

.PHONY:
docs:
	doxygen documentation/Doxyfile