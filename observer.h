#ifndef _OBSERVER_H_
#define _OBSERVER_H_

class Observer {
public:
    virtual bool notify(Observer whoNotified);
};

#endif 