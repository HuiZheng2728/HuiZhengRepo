#include <iostream>
#include <cstdlib>
#include <cstddef>
#include <fstream>
using namespace std;

class HeapSort{
	public:
		
	int rootIndex;
	int fatherIndex;
	int leftKidIndex;
	int rightKidIndex;
	int minKidIndex;
	int *heapAry;
	int arrSize=0;
	int kidIndex;
	
	
	HeapSort(){

	}

	void buildHeap(ifstream &in,ofstream &out){	
		int data;	
		while(in >> data){
		
		insertOneDataItem(data);
		kidIndex=heapAry[0];
		bubbleUp(kidIndex);
	 	printHeap(out);
	 	
	}
	}
	void insertOneDataItem(int d){
		heapAry[0]++;
		heapAry[heapAry[0]]=d;	
		
	}
	
	
	void deleteHeap(){
		delete []heapAry;
		heapAry =NULL;
	
	}
	int getRoot(){
		
		return heapAry[1];
		
	}
	
	
	int deleteHeap(ofstream &out1 , ofstream &out2){
		while(heapAry[0]!=0){
		int data= getRoot();
		out1<< data<<endl;
		deleteRoot();
		fatherIndex=1;
		bubbleDown(fatherIndex);

		printHeap(out2);
	}	
	}
	
	void deleteRoot(){
		heapAry[1]=heapAry[heapAry[0]];
		heapAry[0]--;
	}
	
	void bubbleUp(int kidIndex){
		if(isRoot(kidIndex)){
			return;
		}else{
			
			fatherIndex=kidIndex/2;
			if(heapAry[kidIndex] < heapAry[fatherIndex]){
				int temp =heapAry[kidIndex];
				heapAry[kidIndex]=heapAry[fatherIndex];
				heapAry[fatherIndex]=temp;
				bubbleUp(fatherIndex);
			}
		}
		
	}
	
	void bubbleDown(int fatherIndex){
		if(isLeaf(fatherIndex)){
			return;
		}else{
			leftKidIndex= fatherIndex*2;
			rightKidIndex= fatherIndex*2+1;
			minKidIndex= findMinKidIndex(leftKidIndex,rightKidIndex);
		
		if(heapAry[minKidIndex] < heapAry[fatherIndex]){
			int temp=heapAry[fatherIndex];
			heapAry[fatherIndex]=heapAry[minKidIndex];
			heapAry[minKidIndex]=temp;
			bubbleDown(minKidIndex);
		}
	}
	}
	bool isLeaf(int i){
	
		return i*2 > heapAry[0]? true:false;
		
	}
	bool isRoot(int i){
		return i==1;
		
		
	}
	int findMinKidIndex(int leftKidIndex,int rightKidIndex){
		return heapAry[leftKidIndex]<heapAry[rightKidIndex]?  leftKidIndex:rightKidIndex;
	}
	
	bool isHeapEmpty(){
		return heapAry[0]==0? true:false;
	
	}
	bool isHeapFull(){
		return heapAry[0]==arrSize? true:false;
		
	}
	void printHeap(ofstream &out){
	
		for(int i=1;i<heapAry[0]+1;i++){
			out<< heapAry[i]<<" - ";
		}
		out<<endl;
		
	}
	
	
};

int main(int argc ,char** argv){
	
	ifstream inFile;
	ofstream outFile1;
	ofstream outFile2;
	inFile.open(argv[1]);
	outFile1.open(argv[2]);
	outFile2.open(argv[3]);
	HeapSort myHeapSort;
	int size;
	int data;
	while(inFile >>data){
		size++;
	}
	
	inFile.close();
	myHeapSort.heapAry = new int[size+1];
	myHeapSort.arrSize=size+1;
	myHeapSort.heapAry[0]=0;
	
	inFile.open(argv[1]);
	myHeapSort.buildHeap(inFile,outFile2);
	myHeapSort.deleteHeap(outFile1,outFile2);
	inFile.close();
	outFile1.close();
	outFile2.close();
	delete[]myHeapSort.heapAry;
	
		
	
	
}
	
