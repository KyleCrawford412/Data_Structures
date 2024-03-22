
#include <iostream>
#include <vector>
#include <list>
#include <string>
#include <sstream>
#include <fstream>
#include <utility>

using namespace std;

namespace cop4530{
	template<typename K, typename V>
	class HashTable{

		public:
		HashTable(size_t size = 101);
		~HashTable();
		bool contains(const K& k);
		bool match(const pair<K, V>& kv);
		bool insert(const pair<K, V>& kv);
		bool insert(pair<K, V>&& kv);
		bool remove(const K& k);
		void clear();
		bool load(const char *filename);
		void dump();
		size_t size();
		bool write_to_file(const char *filename);
		
		private:
		void makeEmpty();
		void rehash();
		size_t myhash(const K& k);
		unsigned long prime_below(unsigned long);
		void setPrimes(vector<unsigned long>&);
		
		vector<list<pair<K, V>>> table;
		size_t list_size;
		
		//given
		static const unsigned int max_prime = 1301081;
		static const unsigned int default_size = 11;
	};
	
	#include "hashtable.hpp"
}

#endif