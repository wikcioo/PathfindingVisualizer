EXEC = program
BUILD_DIR = build
INC_DIR = include
SRC_DIR = src
SOURCES = $(SRC_DIR)/main.cpp\
		  $(SRC_DIR)/Game.cpp\
		  $(SRC_DIR)/MazeGeneration.cpp\
		  $(SRC_DIR)/State.cpp\
		  $(SRC_DIR)/GameState.cpp\
		  $(SRC_DIR)/MenuState.cpp\
		  $(SRC_DIR)/Cell.cpp\
		  $(SRC_DIR)/Button.cpp
OBJECTS = $(addprefix $(BUILD_DIR)/, $(addsuffix .cpp.o, $(basename $(notdir $(SOURCES)))))

CXXFLAGS = -I$(INC_DIR)
CXXFLAGS += -Wall -Wformat -Wpedantic -Wshadow
LIBS = -lsfml-graphics -lsfml-window -lsfml-system -lsfml-audio

all:
	@mkdir -p build
	@make --no-print-directory $(BUILD_DIR)/$(EXEC)
	@echo "Build complete"

$(BUILD_DIR)/$(EXEC): $(OBJECTS)
	$(CXX) $(CXXFLAGS) -o $@ $^ $(LIBS)

$(BUILD_DIR)/%.cpp.o: $(SRC_DIR)/%.cpp
	$(CXX) $(CXXFLAGS) -c -o $@ $<

clean:
	rm -rf $(BUILD_DIR)
