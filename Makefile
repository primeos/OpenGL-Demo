CXX=g++
CXXFLAGS=-std=c++11 -Wall -Iinclude
LIBS=-lSDL2 -lGL

OUT_DIR=out

all: mk_out_dir opengl_demo

mk_out_dir:
	mkdir -p $(OUT_DIR)

opengl_demo: main.o game_window.o opengl.o opengl_camera.o
	$(CXX) $(CXXFLAGS) $(OUT_DIR)/main.o $(OUT_DIR)/game_window.o $(OUT_DIR)/opengl.o $(OUT_DIR)/opengl_renderer.o $(OUT_DIR)/opengl_camera.o $(OUT_DIR)/opengl_camera_cameradata.o -o $(OUT_DIR)/demo $(LIBS) 

main.o: src/main.cpp
	$(CXX) $(CXXFLAGS) -c src/main.cpp -o $(OUT_DIR)/main.o

game_window.o: src/game_window.cpp
	$(CXX) $(CXXFLAGS) -c src/game_window.cpp -o $(OUT_DIR)/game_window.o

opengl.o: src/opengl.cpp
	$(CXX) $(CXXFLAGS) -c src/opengl.cpp -o $(OUT_DIR)/opengl.o
	$(CXX) $(CXXFLAGS) -c src/opengl_render.cpp -o $(OUT_DIR)/opengl_renderer.o

opengl_camera.o: src/opengl_camera.cpp
	$(CXX) $(CXXFLAGS) -c src/opengl_camera.cpp -o $(OUT_DIR)/opengl_camera.o
	$(CXX) $(CXXFLAGS) -c src/opengl_camera_cameradata.cpp -o $(OUT_DIR)/opengl_camera_cameradata.o

clean:
	rm -r $(OUT_DIR)
