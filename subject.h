#ifndef _SUBJECT_H_
#define _SUBJECT_H_
#include "observer.h"
#include <vector>
#include <string>
#include <memory>
#include "structures.h"

template <typename InfoType> class Observer;

template <typename InfoType> class Subject {
    std::vector<std::shared_ptr<Observer<InfoType>>> observers;
    Request request;
public:
    void attachObserver(std::shared_ptr<Observer<InfoType>> ob);
    bool notifyObservers();
    virtual InfoType getInfo() const = 0;
    void setRequest(Request r);
    Request getRequest() const;
};

template <typename InfoType> void Subject<InfoType>::
attachObserver(std::shared_ptr<Observer<InfoType>> ob) {
    observers.emplace_back(ob);
}

template <typename InfoType> bool Subject<InfoType>::notifyObservers() {
    for (Observer<InfoType> &ob: observers) {
        ob.notify(*this);
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