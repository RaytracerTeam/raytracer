


INCLUDES = -I/opt/homebrew/Cellar/sfml/2.6.1/include -I/opt/homebrew/Cellar/opencv/4.9.0_8/include/opencv4
LIBPATHS = -L/opt/homebrew/Cellar/sfml/2.6.1/lib -L/opt/homebrew/Cellar/opencv/4.9.0_8/lib
LIBS =	-lsfml-graphics	\
		-lsfml-window	\
		-lsfml-system	\
		$(shell pkg-config --libs opencv4)
all:
	g++ $(INCLUDES) test.cpp $(LIBS) $(LIBPATHS) -std=c++20 -o a.out
