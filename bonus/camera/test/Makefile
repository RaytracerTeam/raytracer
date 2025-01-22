
SRC		=	testCamera.cpp		\
			../RealCamera.cpp

OBJ		=	$(SRC:.cpp=.o)

INCLUDES = -I/opt/homebrew/Cellar/sfml/2.6.1/include -I/opt/homebrew/Cellar/opencv/4.9.0_8/include/opencv4 -I..
LIBPATHS = -L/opt/homebrew/Cellar/sfml/2.6.1/lib -L/opt/homebrew/Cellar/opencv/4.9.0_8/lib
LIBS =	-lSFML-Graphics\
		-lSFML-Window	\
		-lSFML-System	\
		$(shell pkg-config --libs opencv4)

%.o: %.cpp
	g++ $(INCLUDES) -c $< -o $@ -std=c++20 $(LIBS) $(LIBPATHS)

all: $(OBJ)
	g++ $(INCLUDES) $(OBJ) $(LIBS) $(LIBPATHS) -std=c++20 -o a.out
