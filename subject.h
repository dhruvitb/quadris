#ifndef _SUBJECT_H_
#define _SUBJECT_H_
#include "observer.h"
#include <vector>
#include <string>
#include <memory>
#include "structures.h"
#include <iostream>

template <typename InfoType> class Observer;

template <typename InfoType> class Subject {
    std::vector<Observer<InfoType>*> observers;
    Request request;
public:
    void attach(Observer<InfoType> *o);
    bool notifyObservers();
    virtual InfoType getInfo() const = 0;
    void setRequest(Request r);
    Request getRequest() const;
};

template <typename InfoType>
void Subject<InfoType>::attach(Observer<InfoType> *o) {
  observers.emplace_back(o);
}

template <typename InfoType> bool Subject<InfoType>::notifyObservers() {
    for (Observer<InfoType> *ob: observers) {
        ob->notify(*this);
    }
    return true;
}

template <typename InfoType> void Subject<InfoType>::setRequest(Request r) {
    request = r;
}

template <typename InfoType> Request Subject<InfoType>::getRequest() const {
    return request;
}

#endif