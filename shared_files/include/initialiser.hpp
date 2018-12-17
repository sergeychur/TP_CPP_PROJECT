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

	Initialiser(size_t _player_id, size_t _player_num,
				std::vector<std::pair<int, int>> &_bases) :
			player_id(_player_id), player_num(_player_num), bases(_bases) {
	}

	template<class Archive>
	inline void serialize(Archive &ar, const unsigned int version) {
		ar & player_id & player_num;
		if (bases.size() < player_num) {
			bases.resize(player_num);
		}
		for (auto i = 0; i < player_num; ++i) {
			ar & bases[i].first & bases[i].second;
		}
	}

	void serialize(boost::archive::text_oarchive &ar) final;

	void deserialize(boost::archive::text_iarchive &ar) final;

	size_t player_id;
	size_t player_num;
	std::vector<std::pair<int, int>> bases;
};


#endif 		//  SERVER_INITIALISER_HPP
