##
## EPITECH PROJECT, 2024
## B-OOP-400-LYN-4-1-raytracer-thomas.pommier
## File description:
## Makefile
##

CORESRC	=	$(wildcard ./src/*.cpp) \
			$(wildcard ./src/math/*.cpp) \
			$(wildcard ./src/parsing/*.cpp) \
			$(wildcard ./src/parsing/primitives/*.cpp) \
			$(wildcard ./src/scene/*.cpp) \
			$(wildcard ./src/scene/primitives/*.cpp) \
			$(wildcard ./src/scene/materials/*.cpp) \
			$(wildcard ./src/scene/materials/code/*.cpp) \
			$(wildcard ./src/scene/materials/texture/*.cpp) \
			$(wildcard ./src/scene/lights/*.cpp) \
			$(wildcard ./src/scene/interactive/*.cpp) \
			$(wildcard ./src/scene/interactive/imgui/*.cpp) \
			$(wildcard ./src/scene/interactive/imgui/primitives/*.cpp) \
			$(wildcard ./src/scene/interactive/imgui/objectSelection/*.cpp) \

IMGUISRC	=	$(wildcard ./bonus/imgui/*.cpp)

SRC		=	./src/main/main.cpp \
			$(CORESRC)

TESTSRC	=	$(wildcard ./tests/*.cpp) \
			$(CORESRC)

CC		=	g++
OBJ		=	$(SRC:.cpp=.o)
DEPS	=	$(SRC:.cpp=.d)
IMGUIOBJ=	$(IMGUISRC:.cpp=.o)
TESTOBJ	=	$(TESTSRC:.cpp=.o)

TESTCOV	=	$(TESTSRC:.cpp=.gcno)
TESTCOV	+=	$(TESTSRC:.cpp=.gcda)

NAME		=	raytracer
TESTNAME	=	unit-tests

CFLAGS		=	-O2 -Iinclude -std=c++20 -Wall -Wextra
DBGFLAGS	=	-g3 -O0
TESTFLAGS	=	-g3 -O0 --coverage -fprofile-arcs -ftest-coverage
DEPSFLAGS	=	-MMD -MP

LDFLAGS		=	-lconfig++ -lsfml-graphics -lsfml-window -lsfml-system
LDBONUSFLAGS=	-lGLEW -lglfw
TESTSFLAGS	=	$(LDFLAGS) -lcriterion

MACBREWSFML		= 	/opt/homebrew/Cellar/sfml/2.6.1
MACBREWCONFIG	=	/opt/homebrew/Cellar/libconfig/1.7.3
MACBREWGLFW		=	/opt/homebrew/Cellar/glfw/3.4
MACBREWGLEW		=	/opt/homebrew/Cellar/glew/2.2.0_1
MACSFMLINCLUDE	=	-I$(MACBREWSFML)/include -I$(MACBREWCONFIG)/include \
					-I$(MACBREWGLFW)/include -I$(MACBREWGLEW)/include
MACSFMLLIB		=	-L$(MACBREWSFML)/lib -L$(MACBREWCONFIG)/lib \
					-L$(MACBREWGLFW)/lib -L$(MACBREWGLEW)/lib

IMGUIFLAGS	=	-DBONUS -Ibonus/imgui

UNAME_S := $(shell uname -s)

ifeq ($(UNAME_S),Darwin)
	LDBONUSFLAGS += -framework OpenGL
	CFLAGS += $(MACSFMLINCLUDE) -DMACOSTONIO
	LDFLAGS += $(MACSFMLLIB)
else
	LDBONUSFLAGS += -lGL
endif

all: $(NAME)

bonusdbg: CFLAGS += $(DBGFLAGS)
bonusdbg: bonus

bonus: $(IMGUIOBJ)
bonus: OBJ += $(IMGUIOBJ)
bonus: LDFLAGS += $(LDBONUSFLAGS)
bonus: CFLAGS += $(IMGUIFLAGS)
bonus: $(NAME)

dbg: CFLAGS += $(DBGFLAGS)
dbg: $(NAME)
dbgs: CFLAGS += $(DBGFLAGS) -fsanitize=address
dbgs: $(NAME)
tests_compile: CFLAGS += -g3 --coverage
tests_compile: $(TESTNAME)

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

clean:
	rm -f $(OBJ)
	rm -f $(DEPS)
	rm -f $(TESTOBJ)
	rm -f $(TESTCOV)

fclean: clean
	rm -f $(NAME)
	rm -f $(TESTNAME)

re:
	@$(MAKE) fclean
	@$(MAKE) all

redbg:
	@$(MAKE) fclean
	@$(MAKE) dbg

.PHONY: all dbg tests_run tests_cov tests_compile clean fclean re redbg
