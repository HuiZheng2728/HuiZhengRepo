#include<iostream>
#include <fstream>
#include <cstdlib>
#include <cstddef>
using namespace std;

class graphNode{
	int nodeId;
	graphNode *next;
	
	
	graphNode(){
		next = NULL;
		
}
};
class undirectedEdge{
	public:
	int Ni;
	int Nj;
	int edgeCost;
	undirectedEdge *nextE;
	
	void printEdge(){
		
	}
	
	undirectedEdge(){
		Ni=0;
		Nj=0;
		edgeCost=0;
		nextE = NULL;
	};
	
	undirectedEdge(int Ni,int Nj,int edgeCost){
		this->Ni=Ni;
		this->Nj=Nj;
		this->edgeCost=edgeCost;	
		nextE = NULL;
	
	}
	~undirectedEdge(){
		Ni=0;
		Nj=0;
		edgeCost=0;
		nextE=NULL;
	}

};

class KruskalMST{
	public:
	int numNode;
	int *inWhichSet;
	int numSet;
	int totalMSTCost=0;
	undirectedEdge *MSTofG;
	undirectedEdge *edgeListHead;
	
	KruskalMST(int n){
		numNode=n;
		numSet=numNode;
		undirectedEdge *dummy = new undirectedEdge();
		undirectedEdge *dummyJunior = new undirectedEdge();
		MSTofG = dummyJunior;
		edgeListHead=dummy;
		
		inWhichSet= new int[numNode+1];
		for(int i=1;i<numNode+1;i++){
			inWhichSet[i]=i;
		}
		
	}
	
	void insertEdge(int i,int j ,int cost){
		undirectedEdge *e = new undirectedEdge(i,j,cost);
	
		undirectedEdge *cursor = new undirectedEdge;
		
		cursor=edgeListHead;
		
		while(cursor->nextE!=NULL &&cursor->nextE->edgeCost < e->edgeCost){
		
			cursor=cursor->nextE;
		}

		e->nextE=cursor->nextE;
		cursor->nextE=e;
		
	}
	
	
	undirectedEdge* removedEdge(){
		undirectedEdge* cursor=edgeListHead->nextE;
		while(inWhichSet[cursor->Ni] == inWhichSet[cursor->Nj]&&cursor!=NULL){
			
			cursor=cursor->nextE;
		}
		edgeListHead->nextE=cursor->nextE;
		
	
		
		
		
		return cursor;
}
	
	void pushEdge(undirectedEdge *nextEdge){
		
		undirectedEdge *cursor= MSTofG;
		while(cursor->nextE!=NULL){
			cursor=cursor->nextE;
		}
		nextEdge->nextE=cursor->nextE;
		cursor->nextE=nextEdge;
	}

	
	void merge2Sets(int ni , int nj){
		int temp;
		if(ni<nj){
			temp=inWhichSet[nj];
			for(int i=1;i<numNode+1;i++){
				if(inWhichSet[i]==temp){
				
				inWhichSet[i]=inWhichSet[ni];
			}
		}
	}else{
		temp=inWhichSet[ni];
		for(int i=1;i<numNode+1;i++){
			if(inWhichSet[i]=temp){
				inWhichSet[i]=inWhichSet[nj];
			}
		}
	}
			
		}
		
	
	void printSet(ofstream &p){
		p<<"InWhichSet = ";
		for(int i=1;i<numNode+1;i++){
			
			p<<inWhichSet[i]<<" ";
		}
		p<<endl;
	}
		
	void printList(undirectedEdge *node,ofstream &p){
		undirectedEdge *temp =node->nextE;
		int count=0; 
	
		while(temp!=NULL &&count <10){
			p << temp->Ni << " " << temp->Nj << "   "<< temp->edgeCost<<endl;
			temp=temp->nextE;
			count++;
		}
		
	}
	
	
	void printFinal(ofstream &p){
		undirectedEdge *temp =MSTofG->nextE;
		p<<"*** A Kruskal's MST of the input graph is given below: ***"<<endl;
		p<< numNode<<endl;
		
		while(temp!=NULL){
			p<< temp->Ni <<" " << temp->Nj << " " << temp->edgeCost<<endl;
			temp=temp->nextE;
			
		}
		
		p<<"*** The total cost of  a Kruskal's MST is: "<<totalMSTCost<<endl;
	}
};	




int main(int argc ,char** argv){
	ifstream inFile;
	ofstream outFile1;
	ofstream outFile2;
	inFile.open(argv[1]);
	
	if(!inFile){
		cout<<"no file"<<endl;
		exit(1);
	}
	
	outFile1.open(argv[2]);
	outFile2.open(argv[3]);
	
	int numNode;
	int Ni;
	int Nj;
	int edgeCost;
	inFile >> numNode;
	KruskalMST kmst(numNode);
	kmst.printSet(outFile2);
	while(true){
		inFile>>Ni>>Nj>>edgeCost;
		if(inFile.eof()) break;
		kmst.insertEdge(Ni,Nj,edgeCost);
		outFile2<<"*** current EdgeListHead LinkedList ***"<<endl;
		kmst.printList(kmst.edgeListHead,outFile2);
		
	}
	undirectedEdge *nextEdge;
	while(kmst.numSet!=1){
	
	nextEdge=kmst.removedEdge();// step 6
	
	kmst.pushEdge(nextEdge);
	
	
	kmst.totalMSTCost += nextEdge->edgeCost;
	kmst.merge2Sets(nextEdge->Ni,nextEdge->Nj);
	kmst.numSet--;
	kmst.printSet(outFile2);  //end of 6
	outFile2<<"*** current MSTofG ***"<<endl;
	kmst.printList(kmst.MSTofG,outFile2); // 7
	} // step 8
	kmst.printFinal(outFile1); //9
	
	
	inFile.close();
	outFile1.close();
	outFile2.close();
	return 0;
}
