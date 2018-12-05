//
//  MyBuilding.hpp
//  RTS
//
//  Created by Сергей Апарин on 29/10/2018.
//

#ifndef MyBuilding_hpp
#define MyBuilding_hpp

#include "GameObject.hpp"

class MyBuilding : public GameObject
{
public:
    explicit MyBuilding(Vec2 pos,std::string img, unsigned int id);
};

#endif /* MyBuilding_hpp */
