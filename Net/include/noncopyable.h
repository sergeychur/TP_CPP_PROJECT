//
// Created by alex on 17.12.18.
//

#ifndef NET_NONCOPYABLE_H
#define NET_NONCOPYABLE_H


class noncopyable
{
protected:
	noncopyable() = default;
	~noncopyable() = default;
public:
	noncopyable(noncopyable&) = delete;
	noncopyable(noncopyable&&) = delete;
	noncopyable& operator=(noncopyable&) = delete;
	noncopyable&& operator=(noncopyable&&) = delete;
};


#endif //NET_NONCOPYABLE_H
