#include<iostream>
#include<string>
#include<thread>
#include <chrono>
#include"OrderPoller.h"
#include"Order.h"

using namespace std;


void simulate(Buffer<Order> &buffer) {

	buffer.add(Order("1","1000",1234,  23.5,200));
	buffer.add(Order("2", "1000", 1235, 22.5, 200));
	buffer.add(Order("3", "1000", 1236, 2332.5, 100));
	buffer.add(Order("4", "2000", 1237, 67.5, 200));

	this_thread::sleep_for(chrono::milliseconds(200));
	buffer.add(Order("5", "1000", 1238, 23.5, 200.0));
	buffer.add(Order("6", "2000", 1239, 23.5, 200.0));

	this_thread::sleep_for(chrono::milliseconds(800));
	buffer.add(Order("7", "1000", 1240, 23.5, 200.0));
	buffer.add(Order("8", "1000", 1241, 23.5, 200.0));


}

int main()
{
	Buffer<Order> buffer;
	DBClient dbClient("tcp://127.0.0.1:3306", "wtl", "root", "root");
	dbClient.executeQuery("delete from trade_order");
	OrderPoller poller(buffer, dbClient,2);

	thread pollerThread(&OrderPoller::poll, &poller);
	thread bufferSimulator(simulate, ref(buffer));

	pollerThread.join();
	bufferSimulator.join();

}