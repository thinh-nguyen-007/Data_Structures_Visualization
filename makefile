CXX = g++
CXXFLAGS = -std=c++20 \
	-Iassets \
	-Iinclude \
	-Iinclude/SceneManager \
	-Iinclude/Textures \
	-Iinclude/Drawing \
	-Iinclude/SceneManager/SnapShots \
	-Iinclude/SceneManager/Scenes \
	-Isrc \
	-I$(RAYLIB_DIR)/include -O2
LDFLAGS = -L$(RAYLIB_DIR)/lib -lraylib -lopengl32 -lgdi32 -lwinmm -luser32

SRC = $(wildcard src/*.cpp \
				 src/*/*.cpp \
				 src/*/*/*.cpp)
TARGET = run.exe

all: clean $(TARGET)
	@echo "Build complete! Running program..."
	@./$(TARGET)

$(TARGET): $(SRC)
	$(CXX) $(CXXFLAGS) $^ -o $@ $(LDFLAGS)

clean:
	rm -f $(TARGET)