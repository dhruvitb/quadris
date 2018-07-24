#ifndef _GRAPHICS_DISPLAY_H_
#define _GRAPHICS_DISPLAY_H_
#include "observer.h"
#include "window.h"
#include "structures.h"
#include "subject.h"
#include <memory>

class GraphicsDisplay: public Observer<CellInfo> {
    unique_ptr<Xwindow> window;
    int width;
    int height;
    int squareSize;
public:
    GraphicsDisplay(int width, int height);
    ~GraphicsDisplay();
    bool notify(Subject<CellInfo> &from);
};

#endif