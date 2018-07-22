#include "subject.h"

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