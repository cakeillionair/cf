CC       := gcc
CFLAGS   := \
	-Wall \
	-Wextra \
	-std=c99
DBGFLAGS := \
	-fsanitize=address \
	-DDEBUG \
	-g \
	-Og
CCFLAGS  := $(CFLAGS) -c

BIN_PATH := bin
OBJ_PATH := obj
SRC_PATH := src
DBG_PATH := dbg
INC_PATH := inc

project_name := count_files

TARGET_NAME  := cf
TARGET       := $(BIN_PATH)/$(TARGET_NAME)
TARGET_DEBUG := $(DBG_PATH)/$(TARGET_NAME)

SRC       := $(foreach x, $(SRC_PATH), $(wildcard $(addprefix $(x)/*,.c*)))
OBJ       := $(addprefix $(OBJ_PATH)/, $(addsuffix .o, $(notdir $(basename $(SRC)))))
OBJ_DEBUG := $(addprefix $(DBG_PATH)/, $(addsuffix .o, $(notdir $(basename $(SRC)))))

DISTCLEAN_LIST := \
	$(OBJ) \
	$(OBJ_DEBUG)
CLEAN_LIST     := \
	$(TARGET) \
	$(TARGET_DEBUG) \
	$(DISTCLEAN_LIST)

default: makedir all

$(TARGET): $(OBJ)
	$(CC) $(CFLAGS) -o $@ $^ -I $(INC_PATH)
$(TARGET_DEBUG): $(OBJ_DEBUG)
	$(CC) $(CFLAGS) $(DBGFLAGS) -o $@ $^ -I $(INC_PATH)
$(OBJ_PATH)/%.o: $(SRC_PATH)/%.c*
	$(CC) $(CCFLAGS) -o $@ $^ -I $(INC_PATH)
$(DBG_PATH)/%.o: $(SRC_PATH)/%.c*
	$(CC) $(CCFLAGS) $(DBGFLAGS) -o $@ $^ -I $(INC_PATH)

makedir:
	@mkdir -p $(BIN_PATH) $(OBJ_PATH) $(DBG_PATH) $(INC_PATH)
cleanbuild: makedir clean all debug
all: $(TARGET)
debug: $(TARGET_DEBUG)
clean:
	@echo CLEAN $(CLEAN_LIST)
	@rm -f $(CLEAN_LIST)
distclean:
	@echo CLEAN $(DISTCLEAN_LIST)
	@rm -f $(DISTCLEAN_LIST)

.PHONY: makedir cleanbuild all debug clean distclean
