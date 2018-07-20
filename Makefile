CXX=g++
CXXFLAGS=-std=c++14 -Wextra -Wpedantic -Wall -Werror=vla -MMD -g
OBJECTS=main.o textdisplay.o cell.o grid.o gamepiece.o
DEPENDS=${OBJECTS:.o=.d}
EXEC=zzz

${EXEC}: ${OBJECTS}
	${CXX} ${CXXFLAGS} ${OBJECTS} -o ${EXEC}

-include ${DEPENDS}

clean:
	rm main.o cell.o grid.o textdisplay.o ${DEPENDS} ${EXEC}
.PHONY: clean
