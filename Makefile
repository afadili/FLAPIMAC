CC = gcc
CFLAGS = -Wall -O2 -g
LDFLAGS = -lSDL -lm -lGLU -lGL -lSDL2 -lglut
INCLUDES = 

APP_BIN = flapimac

SRC_PATH = src
OBJ_PATH = obj
INC_PATH = -I include
BIN_PATH = bin
LIB_PATH = lib

SRC_FILES = $(shell find $(SRC_PATH) -type f -name '*.c')
OBJ_FILES = $(patsubst $(SRC_PATH)/%.c,$(OBJ_PATH)/%.o, $(SRC_FILES))

all: $(APP_BIN)
	@echo "--------------------------------------------------------------"
	@echo "                      Flapimac Project"
	@echo "                Marti Emilie & Sajdak Laurine"
	@echo ""
	@echo "                 to execute type: ./bin/$(BIN) &"
	@echo ""
	@echo "                       enjoy the game !"
	@echo "--------------------------------------------------------------"

$(APP_BIN): $(OBJ_FILES)
	@mkdir -p $(BIN_PATH)
	$(CC) -o $(BIN_PATH)/$(APP_BIN) $(OBJ_FILES) $(LDFLAGS)
	
$(OBJ_PATH)/%.o: $(SRC_PATH)/%.c
	@mkdir -p "$(@D)"
	$(CC) -c $< -o $@ $(CFLAGS) $(INC_PATH)

clean:
	rm $(OBJ_FILES) $(BIN_PATH)/$(APP_BIN)