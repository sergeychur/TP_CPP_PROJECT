//
// Created by sergey on 19.10.18.
//

/*
    here are necessary things to know for all the clients
*/

#ifndef SERVER_UPDATE_HPP
#define SERVER_UPDATE_HPP

#include <vector>

#include <boost/serialization/vector.hpp>
#include <boost/serialization/access.hpp>
#include <boost/serialization/string.hpp>

#include "Serializable.h"

struct UpdateLine {
	UpdateLine() = default;

	UpdateLine(const size_t _player_id, const size_t _unit_id, const int _new_HP,
			const int _new_x, const int _new_y,
			const int _new_angle, const int _state, const bool _is_alive) :
			player_id(_player_id), unit_id(_unit_id), new_HP(_new_HP), new_x(_new_x),
			new_y(_new_y), new_angle(_new_angle), state(_state), is_alive(_is_alive) {}

	~UpdateLine() = default;

	size_t player_id;
	size_t unit_id;
	int new_HP;
	int new_x;
	int new_y;
	int new_angle;
	int state;
	bool is_alive;

	friend class boost::serialization::access;

	template<class Archive>
	inline void serialize(Archive &ar, const unsigned int file_version) {
		ar & player_id & unit_id & new_HP & new_x & new_y & new_angle &
		state & is_alive;
	}
};

bool operator==(const UpdateLine &first, const UpdateLine &second);

struct Update : Serializable {
 public:
	Update() = default;

	~Update() = default;


	std::vector<UpdateLine> updates;


	friend class boost::serialization::access;

	template<class Archive>
	inline void serialize(Archive &ar, const unsigned int file_version) {
		ar & updates;
	}

	void serialize(boost::archive::text_oarchive &ar) final;

	void deserialize(boost::archive::text_iarchive &ar) final;
};

std::ostream &operator<<(std::ostream &output, const Update &upd);

#endif 		//  SERVER_UPDATE_HPP
