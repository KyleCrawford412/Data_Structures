
template<typename K, typename V>
cop4530::HashTable<K, V>::HashTable(size_t s){
	list_size = 0;
	table.resize(prime_below(s));
}

template<typename K, typename V>
cop4530::HashTable<K, V>::~HashTable(){
	makeEmpty();
}

template<typename K, typename V>
bool cop4530::HashTable<K, V>::contains(const K& k){
	
	//iterate through table
    for(auto i = table[myhash(k)].begin(); i != table[myhash(k)].end(); i++ ){
        if(i->first == k){ 
			return true;
		}
	}
    
	//if here then value wasn't found
	return false;
}

template<typename K, typename V>
bool cop4530::HashTable<K, V>::match(const pair<K, V>& kv){
    auto& i = table[myhash(kv.first)];
    return (find(i.begin(), i.end(), kv) != i.end());
}

template<typename K, typename V>
bool cop4530::HashTable<K, V>::insert(const pair<K, V>& kv){
	
	//check for key and value already in table
    if(match(kv)){  
		return false;   
	}
	//check for key with different value
    else if(contains(kv.first)){
		//find list
        auto& list = table[myhash(kv.first)];   
        //loop through list for value
        for(auto itr = list.begin(); itr != list.end(); itr++){
			//found value
            if(itr->first == kv.first){
				//remove element from list
                auto i = list.erase(itr);   
				//insert element with new key
                list.insert(i, kv); 
            }
		}
        return true;                         
    }
	
	table[myhash(kv.first)].push_back(kv);

	//  rehash, see Section 5.5
	if(++list_size > table.size()){
		rehash();
	}
	return true;

}

template<typename K, typename V>
bool cop4530::HashTable<K, V>::insert(pair<K, V>&& kv){
	//get data from kv
    const pair<K, V> x = move(kv);
	
	//return true for succesful insertion
    if(insert(x)){ 	
		return true;
	}
    else{
		return false;
	}
}

template<typename K, typename V>
bool cop4530::HashTable<K, V>::remove(const K& k){
	//find index of key
    auto i = myhash(k);                     
    
	//loop through list at the index
    for(auto itr = table[i].begin(); itr != table[i].end(); itr++){
		//check for key
        if(itr->first == k){
            table[i].erase(itr);       
            size--;
            return true;                              
        }
    }
    return false;
}

template<typename K, typename V>
void cop4530::HashTable<K, V>::clear(){
	makeEmpty();
}


template<typename K, typename V>
bool cop4530::HashTable<K, V>::load(const char *filename){
    ifstream infile;
	infile.open(filename);
	
	//if file didnt open return false
    if(!infile.is_open()){ 
		return false;                             
	}
	
	//variables for each hash
    pair<K, V> x;
    string currentLine;
	string token;
	
	//get each line in the file
    while(!infile.eof()){
		//get the line
        getline(infile, currentLine);
		stringstream str(currentLine);
		
		//first value
		str >> token;
		x.first = token;
		
		//second value
		str >> token;
		x.second = token;

		//insert data
        insert(x);                                
    }
	
	//close file
    infile.close();                                         
    return true;
}

template<typename K, typename V>
void cop4530::HashTable<K, V>::dump(){
	auto& list = table[0];
	for(size_t i = 0; i < table.size(); i++){
		list = table[i];
		cout << "v[" << i << "]: ";
		
		//check for data in list
		if(!list.empty()){
			auto& itr = list.begin();
			
			//get everything in that list
			while(itr != list.end()){
				cout << itr.first << " " << itr.second;
				
				if(++itr != list.end()){
					cout << " : ";
				}
			}
		}
		cout << endl;	
	}
}

template<typename K, typename V>
size_t cop4530::HashTable<K, V>::size(){
	return list_size;
}

template<typename K, typename V>
bool cop4530::HashTable<K, V>::write_to_file(const char *filename){
	//create outstream for file
    ofstream outfile;
    outfile.open(filename);
	
	//check for file
    if(!outfile.is_open()){ 
		return false;
	}
	
	//write to file if open
    for(size_t i = 0; i < table.size(); i++){
        for(auto& itr = table[i].begin(); itr != table[i].end(); itr++){
            outfile << itr.first << " " << itr.second << endl;
        }
    }
	
	//close file
    outfile.close();                               
    return true;                                
}

template<typename K, typename V>
void cop4530::HashTable<K, V>::makeEmpty(){
	
	//iterate through every index in table
    for(size_t i = 0; i < table.size(); i++){
		//delete all elements in list for each index
        while(!table[i].empty()){                   
            table[i].pop_back();
		}
    }
	
	//set size to 0
    list_size = 0;                                
}

template<typename K, typename V>
void cop4530::HashTable<K, V>::rehash(){
    vector<list<pair<K, V>>> temp = table;
	
	//double size of table
    table.resize(prime_below(2 * table.size()));
	
	for(auto& itr : table){
		itr.clear();
	}
	
	list_size = 0;
	for(auto& itr : temp){
		for(auto& x : itr){
			insert(move(x));
		}
	}
}

template<typename K, typename V>
size_t cop4530::HashTable<K, V>::myhash(const K& k){
    static hash<K> hf;
	return hf(k) % table.size();
}

// This is likely to be more efficient than prime_above(), because
// it only needs a vector of size n
template <typename K, typename V>
unsigned long HashTable<K, V>::prime_below(unsigned long n){
	if (n > max_prime){
		std::cerr << "** input too large for prime_below()\n";
		return 0;
	}
	if (n == max_prime){
		return max_prime;
    }
	if (n <= 1){
		std::cerr << "** input too small \n";
      return 0;
    }

  // now: 2 <= n < max_prime
  std::vector <unsigned long> v (n+1);
  setPrimes(v);
  while (n > 2){
    if (v[n] == 1){
		return n;
	}
    --n;
  }
  return 2;
}

//Sets all prime number indexes to 1. Called by method prime_below(n) 
template <typename K, typename V>
void HashTable<K, V>::setPrimes(std::vector<unsigned long>& vprimes){
  int i = 0;
  int j = 0;

  vprimes[0] = 0;
  vprimes[1] = 0;
  int n = vprimes.capacity();

  for (i = 2; i < n; ++i)
    vprimes[i] = 1;

  for( i = 2; i*i < n; ++i){
	if (vprimes[i] == 1){
		for(j = i + i ; j < n; j += i){
			vprimes[j] = 0;
		}
	}
  }
}