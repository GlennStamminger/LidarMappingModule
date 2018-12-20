#Project
PROJECT_NAME = LidarModule

#Build
BUILD_DIR = ./build

#Compiler
CXX = g++

#Flags
CFLAGS = -Wall -Werror -ggdb -O0 -std=c++11 -lwiringPi -lpthread

#Sources
SRC_DIR = ./src

SOURCES = $(SRC_DIR)/main.cpp \
					$(SRC_DIR)/MappingLogic.cpp \
					$(SRC_DIR)/Pwm.cpp \
					$(SRC_DIR)/Servo.cpp \
					$(SRC_DIR)/Uart.cpp

#Objects
OBJ_DIR = ./obj

OBJECTS = $(subst $(SRC_DIR),$(OBJ_DIR),$(SOURCES:.cpp=.o))

#Phony
.PHONY: all $(PROJECT_NAME)Clean create_dirs

#All
all: $(PROJECT_NAME)

#Build
$(PROJECT_NAME): create_dirs $(OBJECTS)
	$(CXX) $(CFLAGS) $(OBJECTS) -o $(BUILD_DIR)/$@

#Dirs
create_dirs:
	@mkdir -p $(OBJ_DIR)
	@mkdir -p $(BUILD_DIR)

#Clean
clean: $(PROJECT_NAME)Clean

$(PROJECT_NAME)Clean:
	@rm -f $(OBJECTS)
	@rm -f $(PROJECT_NAME)

#Targets
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp
	$(CXX) $(CFLAGS) $< -c -o $@