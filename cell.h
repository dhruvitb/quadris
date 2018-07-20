#ifndef _CELL_H_
#define _CELL_H_
#include "structures.h"
#include "gamepiece.h"
#include "subject.h"
#include "observer.h"
#include <memory>

class Cell: public Subject, public Observer {
    Coordinate position;
    Colour colour;
    std::shared_ptr<GamePiece> piece;
    Request request;
    std::vector<shared_ptr<Observer>> observers;
public:
    Cell(Coordinate position, Colour colour);
    ~Cell();
    void setRequest(Request r);
    CellInfo getInfo() override;
    bool notify(Subject &from) override;
    void attachObserver(Observer &ob) override;
    bool notifyObservers() override;
};

#endif