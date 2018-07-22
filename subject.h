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

#endif