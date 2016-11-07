#include <bits/stdc++.h>
using namespace std;

#define BTREE_MINDEG 20
#define tr(container, it) \
      for(typeof(container.begin()) it = container.begin(); it != container.end(); it++)
#define LC(veca, vecb) lexicographical_compare(veca.begin(), veca.end(), \
		vecb.begin(), vecb.end())

class Node{
	vector<vector<int> > keys;
	vector<Node *> pointers;
	bool isLeaf;
	int minDeg, numofkeys, numofattr;

	public:
		Node(int mindegree, bool Leaf, int num_of_attr){
			minDeg = mindegree, isLeaf = Leaf, numofattr = num_of_attr, numofkeys = 0;
			keys.resize((2*minDeg) - 1);
			tr(keys, it){
				it->resize(numofattr);
			}
			pointers.resize(2*minDeg);
		}
		void insertNonFull(vector<int> val){
			int i = numofkeys - 1;
			if(isLeaf){
				while(i >= 0 && LC(keys[i], val) != 0){
					keys[i + 1] = keys[i];
					i--;
				}
				keys[i+1] = val;
				numofkeys++;
			}
			else{
				while( i>=0 && LC(keys[i], val) != 0){
					i--;
				}
				if(pointers[i + 1]->numofkeys == ((2 * minDeg) - 1)){
					split(i + 1, pointers[i + 1]);
					if(LC(val, keys[i + 1]) != 0){
						i++;
					}
				}
				pointers[i+1]->insertNonFull(val);
			}
		}
		void split(int i, Node *ptr){
			Node *newptr = new Node(ptr->minDeg, ptr->isLeaf, ptr->numofattr);
	    	newptr->numofkeys = minDeg - 1;

	    	for(int j = 0; j < minDeg - 1; j++)	
	        	newptr->keys[j] = ptr->keys[j + minDeg];

		    if (!ptr->isLeaf) {
		        for(int j = 0; j < minDeg; j++){
	    	        newptr->pointers[j] = ptr->pointers[j + minDeg];
		        }
	    	}
	 		
	 		ptr->numofkeys = minDeg - 1;
		    
		    for(int j = numofkeys; j >= i + 1; j--){
	    	    pointers[j+1] = pointers[j];
		    }
		    pointers[i + 1] = newptr;
		    
		    for(int j = numofkeys - 1; j >= i; j--){
	        	keys[j + 1] = keys[j];
		    }
		    keys[i] = ptr->keys[minDeg - 1];
		    
		    numofkeys++;
		}
		Node * search(vector<int> val){
			int i = 0;
			while(i < numofkeys && LC(val, keys[i]) != 0){
	    		i++;
			}
		    if(val == keys[i]){
	    	    return this;
		    }
		
		    if(isLeaf){
	        	return NULL;
		    }
		
		    return pointers[i]->search(val);
		}
	friend class BTree;
};

class BTree{
	Node *root;
	int minDeg, size, numofattr;
	public:
		BTree(int num_of_attr){
	    	root = NULL;
	    	minDeg = BTREE_MINDEG;
	    	size = 0;
	    	numofattr = num_of_attr;
	    }
	    Node* search(vector<int> val) {
	    	return (root == NULL) ? NULL : root->search(val);
	    }
	    void insert(vector<int> val) {
	    	if(root == NULL) {
		        root = new Node(minDeg, true, numofattr);
	        	root->keys[0] = val;
	        	root->numofkeys = 1;
	    	}
	    	else{
		        if(root->numofkeys == (2*minDeg)-1){
		            Node *node = new Node(minDeg, false, numofattr);
		            node->pointers[0] = root;
	            	node->split(0, root);
		            int i = 0;
	            	if(LC(val, node->keys[0]) != 0){
	                	i++;
	            	}
	            	node->pointers[i]->insertNonFull(val);
		            root = node;
	    	    }
	        	else {
	        		root->insertNonFull(val);
	        	}
	    	}
	    	size++;
	    }
	    int getSize(){
	    	return size;
	    }
};

void btreeopen(ifstream &inputstream, string filename, ofstream &outputstream, string opfile){
	inputstream.open(filename);
	outputstream.open(opfile);
}

void btreegetnext(ifstream &inputstream, int num_of_attr, int num_of_blocks, ofstream &outputstream, int block_size){
	clock_t startTime = clock();
	BTree btree(num_of_attr);
	string lines;
	while(getline(inputstream, lines)){
		vector<int> numbers(num_of_attr);
		int index = 0;
		for(int i = 0; i < num_of_attr; i++){
			string tempstr = "";
			char temp = lines[index];
			while(isdigit(temp)){
				tempstr += temp;
				index++;
				temp = lines[index];
			}
			index++;
			numbers[i] = atoi(tempstr.c_str());
		}
		if(btree.search(numbers) == NULL){
			btree.insert(numbers);
			if(btree.getSize() > ((num_of_blocks - 1) * block_size)){
				cout<<"ERROR"<<endl;
				exit(0);
			}
			outputstream<<lines<<endl;
		}
	}
	cout<<btree.getSize()<<endl;
	cout<<double(clock() - startTime) / (double)CLOCKS_PER_SEC<<" seconds"<<endl;
}

void btreeclose(ifstream &inputstream, ofstream &outputstream){
	inputstream.close();
	outputstream.close();
}

int btreemain(string filename, int num_of_attr, int num_of_blocks, string opfile, int block_size){
	
	ifstream inputstream;
	ofstream outputstream;
	btreeopen(inputstream, filename, outputstream, opfile);
	btreegetnext(inputstream, num_of_attr, num_of_blocks, outputstream, block_size);
	btreeclose(inputstream, outputstream);
	
	return 0;
}