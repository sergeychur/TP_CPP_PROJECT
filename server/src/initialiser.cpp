//
// Created by sergey on 30.11.18.
//

#include "initialiser.hpp"

void Initialiser::serialize(boost::archive::text_iarchive &ar, const unsigned int version) {
    serialize<boost::archive::text_iarchive>(ar, version);
}
void Initialiser::serialize(boost::archive::text_oarchive &ar, const unsigned int version) {
    serialize<boost::archive::text_oarchive>(ar, version);
}