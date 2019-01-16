#include<iostream>
#include <fstream>
using namespace std;

class node{
	public:

	int colorID;
	node *next;
	node(){
		colorID = 0;
		next = NULL;	
	}
	node(int n){
		colorID = n;
		next = NULL;
	}
	
};

class graphColoring {
	public:
	int **adjacenyMatrix;
	node *usedColorTop;
	int newColor;
	int numNode;
	int numColor;
	
	graphColoring(int n){
		
		this->numNode = n;
		adjacenyMatrix = new int*[numNode+1];
		for(int i = 0; i < numNode + 1; i++){
			adjacenyMatrix[i]= new int[numNode+1];
		
		}
		for(int i = 0; i < numNode +1; i++){
			for(int j = 0; j < numNode +1; j++){
				adjacenyMatrix[i][j]=0;
			}
		}
		numColor=0;
		int newColor=0;
		
		node *dummy = new node();
		usedColorTop = dummy;
		
	}
	
	void loadMatrix(int x, int y){
		adjacenyMatrix[x][y]=1;
		adjacenyMatrix[y][x]=1;
	}
	int checkAdjacent(int id,int c){
		for(int i = 1; i < numNode+1; i++){
			if(adjacenyMatrix[id][i]!=0 && id != i){
				if(adjacenyMatrix[i][i]==c){
					return 1;
				}
			}
		}
		return 0;
	}
	
	void pushUsedColor(int color){
		node *n = new node(color);
		node *cursor = usedColorTop;
		while(cursor->next != NULL){
			cursor = cursor->next;
		}
		n->next = cursor->next;
		cursor->next = n;
	}
	
	int FindUsedColor(int n){
		node *temp = usedColorTop->next;
		while(temp != NULL){
			if(checkAdjacent(n,temp->colorID) == 0){
				return temp->colorID;
			}
			temp=temp->next;
		}
		return 0;
		
	}
	void printColorUsed(ofstream &p){
		node *cursor = usedColorTop -> next;
	
		p << " **** Colors used **** "<<endl;
		while(cursor!=NULL){
			numColor++;
			p <<" -> "<< cursor->colorID;
			cursor = cursor->next;
		}
		p <<endl;
		p << " **** "<< numColor <<" colors used **** "<<endl; 
		
	}
	
	void insertNode(node *n){
		node *temp= usedColorTop;
		
		while(temp->next != NULL){
			temp=temp->next;
		}
		n->next = temp->next;
		temp->next = n;
		
	}
	
	bool isAllColored(){
		for(int i = 1; i < numNode + 1; i++){
			for(int j = 1; j < numNode +1; j++){
				if(i == j && adjacenyMatrix[i][j] == 0){
					return false;
				}
			}
		}
		return true;
	}
	
	void printAdjMatrix(ofstream &p){
		p << "***********************"<<endl;
		for(int i = 1; i < numNode + 1; i++ ){
		//	p << i << " - ";
			for(int j = 1; j < numNode + 1 ; j++){
				p << adjacenyMatrix[i][j]<<" ";
			}
			p<<endl;
		}
		p << "***********************"<<endl;
	}
	
};

int main(int argc,char**argv){
	ifstream inFile;
	ofstream outFile;
	inFile.open(argv[1]);
	if(!inFile){
		cout<<"no file"<<endl;
		exit(1);
	}
	
	outFile.open(argv[2]);
	
	
	int numNode;
	int x;
	int y;
	inFile >> numNode;
	graphColoring gc(numNode);

	outFile << "input pairs"<<endl;
	while(true){
	
		inFile >> x >> y;
		if(inFile.eof()){
			break;
		}
		outFile << x <<" "<< y<<"  < "<<x<<", "<<y<<" > and < "<< y<<", "<< x<<">"<<endl;
		gc.loadMatrix(x,y);
	
		
	}
	
	
	gc.newColor=0;
	node *temp= new node(gc.newColor);
	
	int currentNode=0; // end of 0
	
	while(true) {   // 1
	currentNode++;   
	//gc.printAdjMatrix(outFile);   intentionally commented out to save some papers
	int usedColor;
	usedColor = gc.FindUsedColor(currentNode);
	if(usedColor > 0){
		gc.adjacenyMatrix[currentNode][currentNode] = usedColor;
	}else{
			gc.newColor ++;
			gc.pushUsedColor(gc.newColor);
		
			gc.adjacenyMatrix[currentNode][currentNode] = gc.newColor;	
		}
	
	if(gc.isAllColored()){
		
		break;
	}	
}    
	gc.printColorUsed(outFile);
	outFile<<"*** Final matrix ***"<<endl;
	gc.printAdjMatrix(outFile);
	for(int i = 0; i < numNode; i++){
		delete[] gc.adjacenyMatrix[i];
	}
	
	delete[] gc.adjacenyMatrix;
	
	return 0;
}

