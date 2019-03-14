//
// Created by sergey on 15.12.18.
//

#ifndef SERVER_STATE_HPP
#define SERVER_STATE_HPP

#include <iostream>

enum {
	NONE = 3,
	MOVING = 0,
	FIGHTING = 1,
	DEATH = 2
};

class State {
 public:
	State() : value(NONE), needed_notify(true) {}

	void make_moving() { value = MOVING; }

	void make_none() { value = NONE; }

	void make_dead() { value = DEATH; }

	void make_fighting() { value = FIGHTING; }

	int get_state() const { return value; }

	void set_notify_need(bool need) { needed_notify = need; }

	bool if_notify_need() { return needed_notify; }

 private:
	int value;
	bool needed_notify;
};

#endif        //  SERVER_STATE_HPP
