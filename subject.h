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
    std::vector<Observer<InfoType>*> observers; // list of its observers
public:
    void attach(Observer<InfoType> *o); // add a new observer
    virtual bool notifyObservers(); // notify all its observers
    virtual InfoType getInfo() const = 0; // get info for this subject
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

#endif