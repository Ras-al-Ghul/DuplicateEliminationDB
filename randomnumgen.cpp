#include <bits/stdc++.h>

using namespace std;

#define NUMOFENTRIES 10000
#define MAXNUM 1000

int main(int argc, char *argv[]){
	srand(time(NULL));
	if(argc != 3){
		cout<<"Usage: ./randomnumgen <numofattributes> <percentageduplication>"<<endl;
		exit(0);
	}	

	ofstream op("numbers.txt");

	int num = float(atoi(argv[2]))/100 * NUMOFENTRIES;
	int quo = float(NUMOFENTRIES)/num;

	vector<vector<int> > nums(num, vector<int>(atoi(argv[1]), 0));

	for(int i = 0; i < num; i++){
		for(int k = 0; k < atoi(argv[1]); k++){
				nums[i][k]=rand()%MAXNUM;
		}
	}
	for(int i = 0; i < quo; i++){
		for(int j = 0; j < num; j++){
			for(int k = 0; k < atoi(argv[1]); k++){
				if(k != atoi(argv[1]) - 1){
					op<<nums[j][k]<<",";
				}
				else{
					op<<nums[j][k]<<endl;	
				}
			}
		}
	}
}