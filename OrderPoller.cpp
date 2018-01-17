#include<iostream>
#include<string>
#include<list>
#include <sstream>
#include"OrderPoller.h"
#include"DBClient.h"
#include <chrono>


OrderPoller::OrderPoller(Buffer<Order> &buffer,const DBClient &dbClient,int batchSize,int maxbatchTimeInterval) :_buffer(buffer),_dbClient(dbClient) {
	_batchSize = batchSize;
	 _timer = chrono::high_resolution_clock::now();
	 _maxBatchTimeInterval = maxbatchTimeInterval;
}

void OrderPoller::poll() {
	list<Order> polledOrders;
	while (true) {
		Order order = _buffer.remove();
		polledOrders.push_back(order);	
	
		int time_span = chrono::duration_cast<chrono::milliseconds>(chrono::high_resolution_clock::now() - _timer).count();
		if (time_span> _maxBatchTimeInterval  || polledOrders.size() >= _batchSize){
			
			if (time_span>_maxBatchTimeInterval){
				_timer = chrono::high_resolution_clock::now();
			}
			persist(polledOrders);
			polledOrders.clear();
		}
	}
}

void OrderPoller::persist(list<Order> &polledOrders){

	if (polledOrders.empty()){
		return;
	}
	ostringstream stream;
	stream<< "insert into trade_order (id,book_id,event_time,price,quantity) values ";
	for (list<Order>::iterator itr = polledOrders.begin(); itr != polledOrders.end(); ++itr){
		//Better way ?
		if (itr != polledOrders.begin()){
			stream << ",";  
		}
		stream << "( " << itr->getId() << "," << itr->getBookId() << "," << "FROM_UNIXTIME("<<itr->getTimestamp()<<")" << "," << itr->getPrice() << "," << itr->getQuantitiy() << ")";
		
	}	
	string query= stream.str();
	_dbClient.executeQuery(query);
}
	
	

