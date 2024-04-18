##
## EPITECH PROJECT, 2024
## B-OOP-400-LYN-4-1-raytracer-thomas.pommier
## File description:
## Makefile
##

CORESRC	=	$(wildcard ./src/*.cpp) \
			$(wildcard ./src/math/*.cpp) \
			$(wildcard ./src/primitives/*.cpp) \
			$(wildcard ./src/interactive/*.cpp)

SRC	=	./src/main/main.cpp \
		$(CORESRC)

TESTSRC	= 	$(wildcard ./tests/*.cpp) \
			$(CORESRC)

CC = g++
OBJ	=	$(SRC:.cpp=.o)
TESTOBJ	=	$(TESTSRC:.cpp=.o)

TESTCOV =	$(TESTSRC:.cpp=.gcno)
TESTCOV +=	$(TESTSRC:.cpp=.gcda)

NAME	=	raytracer
TESTNAME	=	unit-tests

CFLAGS	=	-Iinclude -std=c++20 -Wall -Wextra
DBGFLAGS	=	-g3
TESTFLAGS	=	-g3 --coverage -fprofile-arcs -ftest-coverage

LDFLAGS	=	-lconfig++ -lsfml-graphics -lsfml-window -lsfml-system
TESTSFLAGS = $(LDFLAGS) -lcriterion

all: $(NAME)
dbg: CFLAGS += $(DBGFLAGS)
dbg: $(NAME)
dbgs: CFLAGS += $(DBGFLAGS) -fsanitize=address
dbgs: $(NAME)
tests_compile: CFLAGS += -g3 --coverage
tests_compile: $(TESTNAME)

%.o: %.cpp
	$(CC) $(CFLAGS) -c $< -o $@

$(NAME):	 $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) -o $(NAME) $(LDFLAGS)

$(TESTNAME):	$(TESTOBJ)
	$(CC) $(CFLAGS) $(TESTFLAGS) $(TESTOBJ) -o $(TESTNAME) $(TESTSFLAGS)

tests_run: tests_compile
	./$(TESTNAME)

tests_cov: tests_compile
	./$(TESTNAME)
	gcov -n -b -f $(TESTSRC)

clean:
	rm -f $(OBJ)
	rm -f $(TESTOBJ)
	rm -f $(TESTCOV)

fclean: clean
	rm -f $(NAME)
	rm -f $(TESTNAME)

re:     fclean all
redbg:     fclean dbg

.PHONY: all dbg tests_run tests_cov tests_compile clean fclean re redbg
