#ifndef _SUBJECT_H_
#define _SUBJECT_H_
#include "observer.h"
#include <vector>
#include <string>

class Subject {
    std::string request;
    std::vector<Observer> observers;
public:
    void attachObserver(Observer ob);
    bool notifyObservers();
    void setRequest(std::string request);
    std::string getRequest();
};

#endif