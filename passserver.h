#ifndef PASSSERVER_H
#define PASSSERVER_H

#include "hashtable.h"
#include<iostream>
#include<string>
#include<crypt.h>
#include<utility>


using namespace std;
using namespace cop4530;

class PassServer{
	public:
		explicit PassServer(size_t size = 101);
		~PassServer();
		bool load(const char* filename);
		bool addUser(pair<string, string>& kv);
		bool addUser(pair<string, string>&& kv);
		bool removeUser(const string& k);
		bool changePassword(const pair<string, string>& p, const string& newpassword);
		bool find(const string& user);
		void dump();
		size_t size();
		bool write_to_file(const char *filename);
	private:
		string encrypt(const string& str);
		HashTable<string, string> server;                     
};
#endif