#ifndef Order_H
#define Order_H

#include<iostream>
#include<string>
using namespace std;


/*
This class represent a limit order . Later will see if need design Order class hierarchy in a better way
*/
class Order {
public:

	//No default constructor
	Order(const string &id, const string &bookId, long timestamp, double price, double quantity);
	const string getId();
	const string getBookId();
	const long getTimestamp();
	const double getPrice();
	const double getQuantitiy();

private:
	const string _id;
	const string _bookId;
	const long _timestamp;  //need to see if long , date or string
	const double _price;
	const double _quantity;
};

#endif 