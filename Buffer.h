#ifndef Buffer_H
#define Buffer_H

#include<iostream>
#include<string>
#include<queue>
#include<thread>
#include <condition_variable>
#include <mutex>
#include"Order.h"
using namespace std;

/*
Thread safe queue wrapper class. 
*/
template<typename T>
class Buffer {

public:
	void add(T &element) {
		unique_lock<std::mutex> locker(mu);
		cond.wait(locker, [this]() {return _buffer.size() < max_size; });
		_buffer.push_back(element);
		locker.unlock();
		cond.notify_all();

	};
	T remove() {
		unique_lock<std::mutex> locker(mu);
		cond.wait(locker, [this]() {return _buffer.size() > 0; });
		T order = _buffer.front();
		_buffer.pop_front();
		locker.unlock();
		cond.notify_all();
		return order;

	};

private:
	mutex mu;
	condition_variable cond;
	deque<T> _buffer;
	const unsigned int max_size = 10000;

};



#endif