#include"Order.h"
#include<iostream>
#include<string>
using namespace std;

Order::Order(const string &id, const string &bookId, long timestamp, double price, double quantity) 
	        :_id(id), _bookId(bookId), _timestamp(timestamp), _price(price), _quantity(quantity){
}


const string Order::getId(){
	return _id;
}

const string Order::getBookId(){
	 return _bookId;
  
 }

const long Order::getTimestamp(){
	 return _timestamp;
 
 }

const double Order::getPrice(){
	 return _price;
 }

const double Order::getQuantitiy(){
 
	 return _quantity;
 }
