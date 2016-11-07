#include <bits/stdc++.h>
#include "hash.h"
#include "btree.h"
using namespace std;

#define BLOCK_SIZE 10

int main(int argc, char * argv[]){
	if(argc < 5){
		cout<<"Format: ./main filename numberofattributes numberofblocks indextype(0:Hash 1:BTree)"<<endl;
		exit(0);
	}
	else{
		string ipfile = string(argv[1]);
		int num_of_attr = atoi(argv[2]);
		int num_of_blocks = atoi(argv[3]);
		int index_type = atoi(argv[4]);
		string outputfile = "output.txt";
		string arguments;
		if(index_type == 1){
			btreemain(ipfile, num_of_attr, num_of_blocks, outputfile, BLOCK_SIZE);
		}
		else{
			hashmain(ipfile, num_of_attr, num_of_blocks, outputfile, BLOCK_SIZE);
		}
	}
	return 0;
}

