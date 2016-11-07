#include <bits/stdc++.h>
using namespace std;

#define HASH_CONST 31

#define tr(container, it) \
      for(typeof(container.begin()) it = container.begin(); it != container.end(); it++)

class Hash{
	int blocksize = 0;
	int numofblocks = 0;
	int numofattr = 0;
	vector<unordered_set<string> > arrofsets;

	int hashFunc(string line){
		vector<int> numbers(numofattr);
		int index = 0;
		for(int i = 0; i < numofattr; i++){
			string tempstr = "";
			char temp = line[index];
			while(isdigit(temp)){
				tempstr += temp;
				index++;
				temp = line[index];
			}
			index++;
			numbers[i] = atoi(tempstr.c_str());
		}
		int sum = 0;
		tr(numbers, it){
			sum = (sum * HASH_CONST) + (*it);
			sum = sum%numofblocks;
		}
		return sum%(numofblocks);
	}
	public:
		Hash(int block_size, int num_of_blocks, int num_of_attr){
			blocksize = block_size;
			numofblocks = num_of_blocks - 1; //Last block is output block
			numofattr = num_of_attr;
			arrofsets.resize(numofblocks);
		}
		int getsize(int i){
			return arrofsets[i].size();
		}
		int insertintoset(string val, Hash &diskblock){
			arrofsets[hashFunc(val)].insert(val);
			if(getsize(hashFunc(val)) > blocksize){
				arrofsets[hashFunc(val)].erase(val);
				if(copytodisk(diskblock, hashFunc(val)) == -1){
					cout<<"ERROR"<<endl;
					exit(0);
				}
				arrofsets[hashFunc(val)].clear();
				arrofsets[hashFunc(val)].insert(val);
			}
		}
		int insertspecial(string val){
			arrofsets[hashFunc(val)].insert(val);
		}
		int copytodisk(Hash &diskblock, int num){
			tr(this->arrofsets[num], it){
				diskblock.insertspecial((*it));
				if(diskblock.getsize(num) > diskblock.getparams(1)){
					return -1;
				}
			}
		}
		int getparams(int i){
			switch(i){
				case 1:
					return blocksize;
				case 2:
					return numofblocks;
				case 3:
					return numofattr;
			}
		}
		int setunion(Hash &memoryblocks, Hash &diskblocks){
			for(int i = 0; i < memoryblocks.getparams(2); i++){
				unordered_set<string> tempset;
				tr(memoryblocks.arrofsets[i], it1){
					tempset.insert((*it1));
				}
				tr(diskblocks.arrofsets[i], it1){
					tempset.insert((*it1));
				}
				tr(tempset, it1){
					this->arrofsets[i].insert((*it1));
				}
			}
		}
		void printset(ofstream &outputstream){
			int count = 0;
			for(int i = 0; i < numofblocks; i++){
				tr(arrofsets[i], it){
					outputstream<<(*it)<<endl;
					count+=1;
				}
			}
			cout<<count<<endl;
		}
};



void hashopen(ifstream &inputstream, string filename, ofstream &outputstream, string opfile){
	inputstream.open(filename);
	outputstream.open(opfile);
}

void hashgetnext(ifstream &inputstream, int num_of_attr, int num_of_blocks, ofstream &outputstream, int block_size){
	clock_t startTime = clock();

	Hash memoryblocks(block_size, num_of_blocks, num_of_attr);

	Hash diskblocks(block_size * (num_of_blocks - 2), num_of_blocks, num_of_attr);

	string lines;
	while(getline(inputstream, lines)){
		memoryblocks.insertintoset(lines, diskblocks);
	}

	Hash final(block_size * (num_of_blocks - 1), num_of_blocks, num_of_attr);
	final.setunion(memoryblocks, diskblocks);
	final.printset(outputstream);

	cout<<double(clock() - startTime) / (double)CLOCKS_PER_SEC<<" seconds"<<endl;
}

void hashclose(ifstream &inputstream, ofstream &outputstream){
	inputstream.close();
	outputstream.close();
}

int hashmain(string filename, int num_of_attr, int num_of_blocks, string opfile, int block_size){
	
	ifstream inputstream;
	ofstream outputstream;
	hashopen(inputstream, filename, outputstream, opfile);
	hashgetnext(inputstream, num_of_attr, num_of_blocks, outputstream, block_size);
	hashclose(inputstream, outputstream);
	
	return 0;
}