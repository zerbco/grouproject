SRC = src/
OBJ = obj/
TST = tests/
TST_OBJ = tests_obj/
SFML = ../SFML-3.0.0/

SRC_FILES := $(wildcard $(SRC)/*.cpp)
OBJ_FILES := $(patsubst $(SRC)/%.cpp,$(OBJ)/%.o,$(SRC_FILES))

TST_FILES := $(wildcard $(TST)/*.cpp)
TST_OBJ_FILES := $(patsubst $(TST)/%.cpp,$(TST_OBJ)/%.o,$(TST_FILES))

main.exe: $(OBJ_FILES)
	g++ -std=c++20  -o $@ $^ -L$(SFML)lib -lsfml-graphics -lsfml-window -lsfml-system 

$(OBJ)/%.o: $(SRC)/%.cpp
	g++ -c -std=c++20 -o $@ $< -I$(SFML)include

test.exe: $(TST_OBJ_FILES)
	g++ -std=c++20  -o $@ $^ -L$(SFML)lib -lsfml-graphics -lsfml-window -lsfml-system 

$(TST_OBJ)/%.o: $(TST)/%.cpp
	g++ -c -std=c++20 -o $@ $< -I$(SFML)include
