//
// Created by sergey on 30.11.18.
//

#ifndef SERVER_INITIALISER_HPP
#define SERVER_INITIALISER_HPP


#include <boost/serialization/access.hpp>

#include "Serializable.h"

struct Initialiser : public Serializable {
    public:
        Initialiser() = default;
        Initialiser(const size_t _player_id, const size_t _player_num) :
        player_id(_player_id), player_num(_player_num){
        }
        template<class Archive>
        inline void serialize(Archive& ar, const unsigned int version) {
            ar & player_id & player_num;
        }

        void serialize(boost::archive::text_iarchive &ar, const unsigned int version) override;
        void serialize(boost::archive::text_oarchive &ar, const unsigned int version) override;

        size_t player_id;
        size_t player_num;
};

#endif //SERVER_INITIALISER_HPP
