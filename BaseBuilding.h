//
// Created by Сергей Апарин on 20.10.2018.
//

#ifndef TP_CPP_PROJECT_BASEBUILDING_H
#define TP_CPP_PROJECT_BASEBUILDING_H


#include "GameObject.h"
#include "Unit.h"

class BaseBuilding : public GameObject {
public:
    BaseBuilding();

    void makeUnit(std::string unitName);

    ~BaseBuilding();

private:
    std::map<std::string, std::vector<int>> units;
};


#endif //TP_CPP_PROJECT_BASEBUILDING_H
