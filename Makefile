PROG_NAME ?= sudoku_solver
DEBUG ?= n
VERBOSE ?= n

SRC_DIR = ./src
OBJ_DIR = ./obj

SRCS += $(shell find $(SRC_DIR) -name "*.cpp")

ifeq ($(VERBOSE),y)
CC = g++
LD = g++
else
CC = @echo '   ' CC $@; g++
LD = @echo '   ' LD $@; g++
endif

INC_DIRS += $(SRC_DIR)

CPPFLAGS += $(addprefix -I, $(INC_DIRS))
CPPFLAGS += -O0
CPPFLAGS += -Wall
CPPFLAGS += -Werror
ifeq ($(DEBUG),y)
CPPFLAGS += -g
endif

DEPS := $(shell find $(SRC_DIR) -name "*.h")
OBJS := $(subst $(SRC_DIR),$(OBJ_DIR),$(patsubst %.cpp,%.o,$(SRCS)))

all: $(PROG_NAME)

$(PROG_NAME): $(OBJS)
	$(LD) -o $@ $^ $(LDFLAGS)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp $(DEPS)
	@mkdir -p $(dir $@)
	$(CC) -c -o $@ $< $(CPPFLAGS)

clean:
	@rm -rf $(OBJ_DIR)
	@rm -f $(PROG_NAME)
