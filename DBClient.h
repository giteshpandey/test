#ifndef DBClient_H
#define DBClient_H

#include<iostream>
#include<string>
#include"OrderPoller.h"
#include "mysql_connection.h"
#include <cppconn/driver.h>
#include <cppconn/exception.h>
#include <cppconn/resultset.h>
#include <cppconn/statement.h>

//Need to better design this class
//need to check RAII
//when to free resources?
class DBClient {
public:
	DBClient(const string &url, const string &schema, const string &user, const string &password){
		try{
			driver = get_driver_instance();
			con = driver->connect(url, user, password);
			con->setSchema(schema);
			stmt = con->createStatement();
		}
		catch (sql::SQLException &e){
			cout << "# ERR: " << e.what();
			cout << " (MySQL error code: " << e.getErrorCode();
			cout << ", SQLState: " << e.getSQLState() << " )" << endl;
			delete con;
			delete stmt;
		}

	}

	void executeQuery(const string &query){
		try{
			//no resultset
	    	stmt->execute(query);
		}
		catch (sql::SQLException &e){
			cout << "# ERR: " << e.what();
			cout << " (MySQL error code: " << e.getErrorCode();
			cout << ", SQLState: " << e.getSQLState() << " )" << endl;
		}

	}


private:
	sql::Driver *driver;
	sql::Connection *con;
	sql::Statement *stmt;
	sql::ResultSet *res;

};


#endif


