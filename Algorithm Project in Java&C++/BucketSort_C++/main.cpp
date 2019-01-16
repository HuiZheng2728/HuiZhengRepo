#include<iostream>
#include <fstream>

using namespace std;


class bucketSort{
	public:
	int *bucketAry;
	int size;
	
	bucketSort(){
		
	}
	
	bucketSort(int n){
		size=n;
		bucketAry=new int [size+1];
		for(int i = 0; i< size+1; i++){
			bucketAry[i]=0;
			
		}
	}
	
	void inBucket(int n){
		
		bucketAry[n]++;
	}
	
	

	 void outBucket(ofstream& p){
		for(int i =0;i<size+1;i++){
			while(bucketAry[i]!=0){
				p<<i<<endl;
				bucketAry[i]--;
		}
	}
}
};
int main(int argc, char **argv)
{
	ifstream inFile;
	ofstream outFile;
	inFile.open(argv[1]);
	outFile.open(argv[2]);
	
	if (!inFile)
	{
		cout << "ERROR open file";
		exit(1);
	}
	
	int num;
	int big=num;
	while(true){
			
		inFile>>num;
		if(inFile.eof()) break;
		if(num>big){
			big=num;
		}
	}
	
	bucketSort bs(big);
	inFile.close();
	inFile.open(argv[1]);

	
	while(true){
		
		inFile >> num;
		if(inFile.eof()) break;
		bs.inBucket(num);
	
	}
	bs.outBucket(outFile);
	inFile.close();
	outFile.close();
	
	delete[] bs.bucketAry;
	
	return 0;
	
}

	
	
	
