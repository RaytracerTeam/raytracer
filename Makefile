##
## EPITECH PROJECT, 2024
## B-OOP-400-LYN-4-1-raytracer-thomas.pommier
## File description:
## Makefile
##

CORESRC	=	$(wildcard ./src/*.cpp) \
			$(wildcard ./src/math/*.cpp) \
			$(wildcard ./src/optimisation/*.cpp) \
			$(wildcard ./src/parsing/*.cpp) \
			$(wildcard ./src/parsing/primitives/*.cpp) \
			$(wildcard ./src/scene/*.cpp) \
			$(wildcard ./src/scene/primitives/*.cpp) \
			$(wildcard ./src/scene/materials/*.cpp) \
			$(wildcard ./src/scene/materials/code/*.cpp) \
			$(wildcard ./src/scene/materials/texture/*.cpp) \
			$(wildcard ./src/scene/lights/*.cpp) \
			$(wildcard ./src/scene/interactive/*.cpp) \
			$(wildcard ./src/scene/interactive/actions/*.cpp)

LIBIMGUISRC	=	$(wildcard ./bonus/imgui/*.cpp)

IMGUISRC	=	$(wildcard ./src/scene/interactive/imgui/*.cpp) \
				$(wildcard ./src/scene/interactive/imgui/camera/*.cpp) \
				$(wildcard ./src/scene/interactive/imgui/inventory/*.cpp) \
				$(wildcard ./src/scene/interactive/imgui/light/*.cpp) \
				$(wildcard ./src/scene/interactive/imgui/material/*.cpp) \
				$(wildcard ./src/scene/interactive/imgui/obj/*.cpp) \
				$(wildcard ./src/scene/interactive/imgui/objectSelection/*.cpp) \
				$(wildcard ./src/scene/interactive/imgui/primitives/*.cpp) \
				$(wildcard ./src/scene/interactive/imgui/primitives/edit/*.cpp) \

CAMERASRC	=	$(wildcard ./bonus/camera/*.cpp)

SRC		=	./src/main/main.cpp \
			$(CORESRC)

TESTSRC	=	$(wildcard ./tests/*.cpp) \
			$(CORESRC)

CC		=	g++
OBJ		=	$(SRC:.cpp=.o)
DEPS	=	$(SRC:.cpp=.d)
IMGUIOBJ=	$(IMGUISRC:.cpp=.o)
IMGUIDEPS=	$(IMGUISRC:.cpp=.d)
LIBIMGUIOBJ=$(LIBIMGUISRC:.cpp=.o)
CAMERAOBJ=	$(CAMERASRC:.cpp=.o)
TESTOBJ	=	$(TESTSRC:.cpp=.o)

TESTCOV	=	$(TESTSRC:.cpp=.gcno)
TESTCOV	+=	$(TESTSRC:.cpp=.gcda)

NAME		=	raytracer
TESTNAME	=	unit-tests

CFLAGS		=	-O2 -Iinclude -std=c++20 -Wall -Wextra
DBGFLAGS	=	-g3 -O0
TESTFLAGS	=	-g3 -O0 --coverage -fprofile-arcs -ftest-coverage
DEPSFLAGS	=	-MMD -MP

LDFLAGS		=	-lconfig++ -lSFML-Graphics -lSFML-Window -lSFML-System
LDBONUSFLAGS=	-lGLEW -lglfw
LDCAMERAFLAGS	=	$(shell pkg-config --libs opencv4)
TESTSFLAGS	=	$(LDFLAGS) -lcriterion

MACBREWSFML		= 	/opt/homebrew/Cellar/sfml/3.0.0
MACBREWCONFIG	=	/opt/homebrew/Cellar/libconfig/1.7.3
MACBREWGLFW		=	/opt/homebrew/Cellar/glfw/3.4
MACBREWGLEW		=	/opt/homebrew/Cellar/glew/2.2.0_1
MACBRWEOPENCV	=	/opt/homebrew/Cellar/opencv/4.11.0

MACSFMLINCLUDE	=	-I$(MACBREWSFML)/include -I$(MACBREWCONFIG)/include \
					-I$(MACBREWGLFW)/include -I$(MACBREWGLEW)/include \
					-I$(MACBRWEOPENCV)/include/opencv4
MACSFMLLIB		=	-L$(MACBREWSFML)/lib -L$(MACBREWCONFIG)/lib \
					-L$(MACBREWGLFW)/lib -L$(MACBREWGLEW)/lib \
					-L$(MACBRWEOPENCV)/lib

IMGUIFLAGS	=	-DBONUS -Ibonus/imgui
CAMERAFLAGS	=	-DBONUSCAMERA -Ibonus/camera

UNAME_S := $(shell uname -s)

ifeq ($(UNAME_S),Darwin)
	LDBONUSFLAGS += -framework OpenGL
	CFLAGS += $(MACSFMLINCLUDE) -DMACOSTONIO
	LDFLAGS += $(MACSFMLLIB)
else
	CAMERAFLAGS += $(shell pkg-config --cflags opencv4)
	LDBONUSFLAGS += -lGL
endif

all: $(NAME)

bonusbonusdbg: CFLAGS += $(DBGFLAGS)
bonusbonusdbg: bonusbonus

bonusbonus: $(CAMERAOBJ)
bonusbonus: OBJ += $(CAMERAOBJ)
bonusbonus: LDFLAGS += $(LDCAMERAFLAGS)
bonusbonus: CFLAGS += $(CAMERAFLAGS)
bonusbonus: bonus

bonusdbg: CFLAGS += $(DBGFLAGS)
bonusdbg: bonus

bonus: $(LIBIMGUIOBJ)
bonus: OBJ += $(LIBIMGUIOBJ)
bonus: $(IMGUIOBJ)
bonus: OBJ += $(IMGUIOBJ)
bonus: LDFLAGS += $(LDBONUSFLAGS)
bonus: CFLAGS += $(IMGUIFLAGS)
bonus: $(NAME)

prof: CFLAGS += -pg
prof: all

dbg: CFLAGS += $(DBGFLAGS)
dbg: $(NAME)
dbgs: CFLAGS += $(DBGFLAGS) -fsanitize=address
dbgs: $(NAME)

tests_compile: CFLAGS += -g3 --coverage
tests_compile: $(TESTNAME)

-include $(IMGUIDEPS)
-include $(DEPS)

%.o: %.cpp
	$(CC) $(CFLAGS) $(DEPSFLAGS) -c $< -o $@

$(NAME): $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) -o $(NAME) $(LDFLAGS)

$(TESTNAME): $(TESTOBJ)
	$(CC) $(CFLAGS) $(TESTFLAGS) $(TESTOBJ) -o $(TESTNAME) $(TESTSFLAGS)

tests_run: tests_compile
	./$(TESTNAME)

tests_cov: tests_compile
	./$(TESTNAME)
	gcov -n -b -f $(TESTSRC)

doc:
	doxygen Doxyfile

rundoc: doc
	python3 -m http.server --directory doc/html

clean:
	rm -f $(OBJ)
	rm -f $(DEPS)
	rm -f $(TESTOBJ)
	rm -f $(TESTCOV)
	rm -f $(IMGUIOBJ)
	rm -f $(IMGUIDEPS)

fclean: clean
	rm -f $(NAME)
	rm -f $(TESTNAME)

re:
	@$(MAKE) fclean
	@$(MAKE) all

redbg:
	@$(MAKE) fclean
	@$(MAKE) dbg

.PHONY: all dbg tests_run tests_cov tests_compile doc rundoc clean fclean re redbg
