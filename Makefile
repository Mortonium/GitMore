TARGET_NAME=GitMore

OBJECTS=Main



INCLUDE_DIRS=~/ProgrammingLibraries/libgit2-0.20.0/include /usr/include /usr/local/include
LIBRARY_DIRS=lib /usr/lib /usr/local/lib
LIBRARIES=curses git2
MACROS=DEBUG

BUILD_DIR=build
OBJECT_DIR=$(BUILD_DIR)/objects
SOURCE_DIR=src

CC=g++
CL=g++



TARGET_FULL=$(BUILD_DIR)/$(TARGET_NAME).out
OBJECTS_FULL=$(OBJECTS:%=$(OBJECT_DIR)/%.o)

INCLUDE_DIRS_FULL=$(INCLUDE_DIRS:%=-I%)
LIBRARY_DIRS_FULL=$(LIBRARY_DIRS:%=-L%)
LIBRARIES_FULL=$(LIBRARIES:%=-l%)
MACROS_FULL=$(MACROS:%=-D%)

CFLAGS=-c $(INCLUDE_DIRS_FULL) $(MACROS_FULL) -std=c++11
LFLAGS=$(LIBRARY_DIRS_FULL) $(LIBRARIES_FULL) -std=c++11



all: $(BUILD_DIR) $(OBJECT_DIR) $(OBJECTS_FULL) $(TARGET_FULL)

$(BUILD_DIR)/%.out: $(OBJECTS_FULL)
	$(CL) -o $@ $(LFLAGS) $(OBJECTS_FULL)

$(OBJECT_DIR)/%.o: $(SOURCE_DIR)/%.cpp
	$(CC) $(CFLAGS) $< -o $@

$(BUILD_DIR):
	mkdir $(BUILD_DIR)
	
$(OBJECT_DIR): $(BUILD_DIR)
	mkdir $(OBJECT_DIR)
	
clean:
	rm -r $(BUILD_DIR)