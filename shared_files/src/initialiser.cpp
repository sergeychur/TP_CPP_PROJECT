//
// Created by sergey on 30.11.18.
//

#include "initialiser.hpp"

void Initialiser::deserialize(boost::archive::text_iarchive& ar) {
    ar >> *this;
}

void Initialiser::serialize(boost::archive::text_oarchive& ar) {
    ar << *this;
}