# Define variables that are global to the makefile
CC = gcc
CFLAGS = -I./unity/src
LDFLAGS = -L./unity/build -lunity

# Define variables that are including source files to the build script
SRC_DIR = src/glthreads
TEST_DIR = tests

SRC_FILES = $(wildcard $(SRC_DIR)/*.c)
TEST_FILES = $(wildcard $(TEST_DIR)/*.c)

OBJ_FILES = $(SRC_FILES:.c=.o)
TEST_OBJ_FILES = $(TEST_FILES:.c=.o)

# Define variables for the unit test framework Unity
UNITY_SRC_DIR = unity/src
UNITY_BUILD_DIR = unity/build
UNITY_OBJ_DIR = unity/build/obj


UNITY_SRC_FILES = $(wildcard $(UNITY_SRC_DIR)/*.c)
UNITY_OBJ_FILES = $(patsubst $(UNITY_SRC_DIR)/%.c,$(UNITY_OBJ_DIR)/%.o,$(UNITY_SRC_FILES))

LIBUNITY = unity/build/libunity.a

# Determine the platform (Windows or Linux)
ifeq ($(OS),Windows_NT)
	# Windows-specific settings
	RM = del
	FIX_PATH = $(subst /,\,$1)
	EXECUTABLE = tcpip-stack.exe
	TEST_EXECUTABLE = test_program.exe
else
	# Linux-specific settings
	RM = rm -f
	FIX_PATH = $1
	EXECUTABLE = tcpip-stack
	TEST_EXECUTABLE = test_program
endif

# Rules that compile the project and tests for the project
.PHONY: all test clean

all:

test: $(TEST_EXECUTABLE)
	./$(TEST_EXECUTABLE)

$(EXECUTABLE): $(OBJ_FILES)
	$(CC) -o $@ $^ $(CFLAGS)

$(TEST_EXECUTABLE): $(OBJ_FILES) $(TEST_OBJ_FILES) $(UNITY_OBJ_FILES) $(LIBUNITY)
	$(CC) -o $@ $^ $(CFLAGS)

# Rules to compile unit test framework Unity
$(LIBUNITY): $(UNITY_OBJ_FILES) | $(UNITY_OBJ_DIR)
	ar rcs $@ $^

$(UNITY_OBJ_DIR)/%.o: $(UNITY_SRC_DIR)/%.c | $(UNITY_OBJ_DIR)
	$(CC) -c -o $@ $< $(CFLAGS)

$(UNITY_OBJ_DIR):
	mkdir -p $(call FIX_PATH,$(UNITY_OBJ_DIR))

clean:
	$(RM) $(call FIX_PATH,$(EXECUTABLE) $(OBJ_FILES) $(TEST_EXECUTABLE) $(TEST_OBJ_FILES))
	$(RM) -r $(call FIX_PATH,$(UNITY_OBJ_DIR))
	$(RM) $(call FIX_PATH,$(LIBUNITY))
