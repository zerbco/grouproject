SRC = src/
OBJ = obj/
SFML = ../SFML-3.0.0/

SRC_FILES := $(wildcard $(SRC)/*.cpp)
OBJ_FILES := $(patsubst $(SRC)/%.cpp,$(OBJ)/%.o,$(SRC_FILES))

main.exe: $(OBJ_FILES)
	g++ -o $@ $^ -L$(SFML)lib -lsfml-graphics -lsfml-window -lsfml-system 

$(OBJ)/%.o: $(SRC)/%.cpp
	g++ -c -o $@ $< -I$(SFML)include

