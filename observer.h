#ifndef _OBSERVER_H_
#define _OBSERVER_H_
#include "structures.h"
#include "subject.h"

class Subject;

class Observer {
public:
    virtual bool notify(Subject &from) = 0;
    virtual ~Observer() = default;
};

#endif 