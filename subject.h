#ifndef _SUBJECT_H_
#define _SUBJECT_H_
#include "observer.h"
#include <vector>
#include <string>
#include <memory>
#include "structures.h"

class Observer;

class Subject {
    std::vector<std::shared_ptr<Observer>> observers;
    Request request;
public:
    virtual void attachObserver(Observer &ob);
    virtual bool notifyObservers();
    virtual InfoType getInfo() = 0;
    void setRequest(std::string request);
    Request getRequest();
};

#endif