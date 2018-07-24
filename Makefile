CXX=g++
CXXFLAGS=-std=c++14 -Wextra -Wpedantic -Wall -Werror=vla -MMD -g
OBJECTS=main.o blockbomb.o blockI.o blockJ.o blockL.o blockO.o blockS.o blockT.o blockZ.o cell.o gamepiece.o grid.o level.o level0.o level1.o level2.o level3.o level4.o textdisplay.o graphicsdisplay.o window.o
DEPENDS=${OBJECTS:.o=.d}
EXEC=quadris

${EXEC}: ${OBJECTS}
	${CXX} ${CXXFLAGS} ${OBJECTS} -o ${EXEC} -lX11

-include ${DEPENDS}

clean:
	rm ${OBJECTS} ${DEPENDS} ${EXEC}
.PHONY: clean
