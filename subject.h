#ifndef _SUBJECT_H_
#define _SUBJECT_H_
#include "observer.h"
#include <vector>
#include <string>
#include "structures.h"

template <typename InfoType> class Subject {
    std::vector<Observer<InfoType>> observers;
    Request request;
public:
    void attachObserver(Observer<InfoType> &ob);
    bool notifyObservers();
    virtual InfoType getInfo() = 0;
    void setRequest(std::string request);
    Request getRequest();
};

#endif