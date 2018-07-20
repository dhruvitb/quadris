#ifndef _GRAPHICS_DISPLAY_H_
#define _GRAPHICS_DISPLAY_H_
#include <vector>
#include <memory>
#include <X11/Xlib.h>
#include "window.h"

class GraphicsDisplay: public Observer<CellInfo> {
    std::vector<Xwindow> xw;
public:
};

#endif