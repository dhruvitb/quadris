#ifndef _OBSERVER_H_
#define _OBSERVER_H_
#include "structures.h"
#include "subject.h"

template <typename InfoType> class Subject;

template <typename InfoType> class Observer {
public:
    virtual bool notify(Subject<InfoType> &from) = 0;
};

#endif
