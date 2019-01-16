#include <iostream>
#include <fstream>
using namespace std;
class DijkstraSSS{
	public:
		int numNodes;
		int sourceNode;
		int minNode;
		int currentNode;
		int newCost;
		int **costMatrix;
		int *fatherAry;
		int *toDoAry;
		int *bestCostAry;
		
	DijkstraSSS(int numNodes,int sNode){
		this->sourceNode=sNode;
		this->numNodes = numNodes;
		costMatrix =new int*[numNodes+1];
		fatherAry = new int[numNodes+1];
		toDoAry = new int[numNodes+1];
		bestCostAry = new int [numNodes+1];
		
		for(int i=0;i<numNodes+1;i++){  //initializing costMartix
			costMatrix[i]=new int[numNodes+1];
		}
		
		for(int i =1;i<numNodes+1;i++){
			for(int j=1;j<numNodes+1;j++){
				if(j==i){
				costMatrix[i][j]=0;
			}else{
				costMatrix[i][j]=99999;
		}
		}	
		}	
		for(int i=0; i<numNodes+1;i++){  // initializing fatherAry & bestCostAry;
			fatherAry[i]=i;
			bestCostAry[i]=99999;
	}
	
};
	
	void loadCostMatrix(int row,int col,int cost){
		costMatrix[row][col]=cost;
	}
	void setBestCostAry(int s){
		for(int i=1;i<numNodes+1;i++){
			bestCostAry[i]=costMatrix[sourceNode][i];
		}
	}
	void setFatherAry(int s){
		for(int i =1;i<numNodes+1;i++){
			fatherAry[i]=sourceNode;
		}
	}
	
	void setToDoAry(int s){
		for(int i =1;i<numNodes+1;i++){
			if(i==sourceNode){
				toDoAry[i]=0;
			}else{
			toDoAry[i]=1;
		}
	}
}
	
	int findMinNode(){
		int tempVal=0;
		
		for(int i=1;i<numNodes+1;i++){
			if(toDoAry[i]!=0){
				tempVal=bestCostAry[i];
				minNode=i;
			}	
		}
		for(int i =1;i<numNodes+1;i++){
			if(toDoAry[i]!=0 && bestCostAry[i]<tempVal){
				tempVal=bestCostAry[i];
				minNode=i;
			}
		}
		markMinNode();
		return minNode;
	}
		
	void markMinNode(){
		toDoAry[minNode]=0;	
	}
	
	void setCurrentNode(int current){
		this->currentNode=current;
	}
	
	void debugPrint(){
		cout<<"source node is "<< sourceNode<<endl;
		
		cout<<"fatherAry = ";
		for(int i =1;i<numNodes+1;i++){
			cout<<fatherAry[i]<<" ";
		}
		cout<<endl; 
		cout<<"bestCostAry";
		for(int i =1;i<numNodes+1;i++){
			cout<<" " << bestCostAry[i]<<" ";
		}
		cout<<endl;
		cout<<"ToDoAry  ";
		for(int i =1;i<numNodes+1;i++){
			cout<<" "<<toDoAry[i]<<" ";
		}
		cout<<endl;
	}
		
	void printHeadLine(int current,ofstream &p){
		p<<"==========================================="<<endl;
		p<<"There are " << numNodes <<" nodes in the input graph."<<endl;
		p<<"============================================"<<endl;;
		p<<"Source node = " << sourceNode<<endl;
		p<<"The shortest path from node " << sourceNode <<" are: "<<endl;	
		
	}
	
	void printShortestPaths(int current,ofstream &p){
		if(current==sourceNode){
			p<<sourceNode;
		}
		else if(current!=sourceNode){
			if(fatherAry[current]!=sourceNode){
			p<<fatherAry[current] << " <- ";
			printShortestPaths(fatherAry[current],p);
			
		}else{
			p<<sourceNode;		
		}
		}
	} 
		
	void printCost(int current,ofstream &p){
			p<<" cost = " << bestCostAry[current]<<endl;;
	}
	
	int computeCost(int current){
		int cost=0;
		this->currentNode=current;
		cost = bestCostAry[minNode]+costMatrix[minNode][currentNode];
		return cost;
	}
	void changeFather(int current,int min){
		this->minNode=min;
		fatherAry[current]=minNode;
	}
	
	void changeCost(int current,int newCost){
		this->currentNode=current;
		bestCostAry[current]=newCost;
	}
	
	void printTodo(){
		for(int i =1;i<numNodes+1;i++){
			cout<<toDoAry[i]<<" ";
					
		}
	
	}
	
};
int main(int argc ,char** argv){
	ifstream inFile;
	ofstream outFile;
	inFile.open(argv[1]);
	outFile.open(argv[2]);
	
	if(!inFile){
		cout<<" no file"<<endl;
		exit(1);
	}
	
	int numNode;
	int sourceNode;
	int row;
	int col;
	int cost;
	int currentNode=0;
	int newCost=0;
	int minNode;
	
	inFile>>numNode>>sourceNode;
	DijkstraSSS sss(numNode,sourceNode);
	
	while(!inFile.eof()){
		inFile>>row>>col>>cost;
		sss.loadCostMatrix(row,col,cost);
	}
	//sss.printMatrix();
	sss.setBestCostAry(sourceNode);
	sss.setFatherAry(sourceNode);
	sss.setToDoAry(sourceNode);
	
	for(int i=1;i<numNode+1;i++){
		if(sss.toDoAry[i]!=0){
			minNode=sss.findMinNode();
			//sss.debugPrint();
			sss.setCurrentNode(currentNode);
			currentNode=1;
			while(currentNode<=numNode){
				if(sss.toDoAry[currentNode]==1){
					newCost=sss.computeCost(currentNode);
					if(newCost < sss.bestCostAry[currentNode]){
						sss.changeCost(currentNode,newCost);
						sss.changeFather(currentNode,minNode);
				//		sss.debugPrint();
			}
			}
			currentNode++;
			
		}
		}
		}
		
		currentNode=1;
		sss.printHeadLine(currentNode,outFile);
		
		while(currentNode <= numNode){
			outFile<<"The path from " << sourceNode << " to "<< currentNode<<" : "<<currentNode<<" <- ";
			sss.printShortestPaths(currentNode,outFile);
			sss.printCost(currentNode,outFile);
			currentNode++;
		}
		inFile.close();
		outFile.close();
		
		for(int i =0;i<numNode+1;i++){
			delete [] sss.costMatrix[i];
		}
		delete [] sss.costMatrix;
		
	return 0;
}

