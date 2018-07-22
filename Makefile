CXX=g++
CXXFLAGS=-std=c++14 -Wextra -Wpedantic -Wall -Werror=vla -MMD -g
OBJECTS=main.o textdisplay.o cell.o grid.o gamepiece.o level.o level0.o level1.o level2.o level3.o level4.o
DEPENDS=${OBJECTS:.o=.d}
EXEC=quadris

${EXEC}: ${OBJECTS}
	${CXX} ${CXXFLAGS} ${OBJECTS} -o ${EXEC}

-include ${DEPENDS}

clean:
	rm main.o cell.o grid.o textdisplay.o ${DEPENDS} ${EXEC}
.PHONY: clean
