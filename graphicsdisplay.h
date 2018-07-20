#ifndef _GRAPHICS_DISPLAY_H_
#define _GRAPHICS_DISPLAY_H_
#include <vector>
#include <memory>
#include <X11/Xlib.h>
#include "window.h"

class GraphicsDisplay: public Observer {
    std::vector<Xwindow> xw;
public:
    bool notify(Subject &from);
};

#endif