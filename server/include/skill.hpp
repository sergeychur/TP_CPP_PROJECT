//
// Created by sergey on 19.10.18.
//

/*
 the interface for possible unit's skills
*/

#ifndef SERVER_SKILL_HPP
#define SERVER_SKILL_HPP

class Skill {
    public:
        virtual void act() = 0;    // mb returns smth, dunno for now
        virtual ~Skill() = default;
};

#endif //SERVER_SKILL_HPP
