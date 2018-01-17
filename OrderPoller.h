#ifndef OrderPoller_H
#define OrderPoller_H

#include<iostream>
#include<string>
#include<chrono>
#include"Buffer.h"
#include"Order.h"
#include"DBClient.h"
using namespace std;

/*
Defined poll method which runs as a separte thread , polling buffer 
*/
class OrderPoller{

public:

	OrderPoller(Buffer<Order> &buffer, const DBClient &dbClient, int batchSize, int maxBatchTimeInterval=100);
	void poll();
	//need to remove from here
	void persist(list<Order> &polledOrders);

private:
	Buffer<Order> &_buffer;
	DBClient _dbClient;
	int _batchSize;
	chrono::high_resolution_clock::time_point _timer;
	int _maxBatchTimeInterval;

};


#endif 