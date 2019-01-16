#include <iostream>
#include <cstdlib>
#include <cstddef>
#include <fstream>


using namespace std;

struct ListNode
{
	string charStr;
	ListNode *next;
	ListNode *left;
	ListNode *right;
	int prob;
	string code;
	
	ListNode(){
		next=NULL;
		left=NULL;
		right=NULL;
	}
	ListNode (string c,int p){
		
		charStr=c;
		prob = p;
	}
	
	string printNode(ListNode *node){
		string pNode=" ";
		pNode += ("char  " + node->charStr +" " +" Prob " +to_string(node->prob) +" ");
		if(node->next ==NULL){
			pNode+= " NULL  ";
		}else{
			pNode+=" "+ node->next->charStr + " ";
		}
		
		if(node->left==NULL){
			pNode+=" left  NULL   ";
		}else{
			pNode +=" left "+ node->left->charStr+ " "+ to_string(node->left->prob)+" ";
		}
		
		if(node->right==NULL){
			pNode += " right  NULL  ";
		}else{
			pNode +=" right " + node -> right -> charStr + " "+to_string (node -> right -> prob) + " ";  
		}
		
		return pNode;
		
	}
	
};

class HuffmanLinkedList
{	
	private:
	ListNode *head;
	ListNode *dummy;
	
	public:
		HuffmanLinkedList(){
			
			dummy=new ListNode();
			head=dummy;		
		}
	
	ListNode* findSpot(ListNode *node,ListNode *head){
		while(node->prob > head->next->prob){
			head=head->next;
			if(head->next==NULL){
				break;
			}
		}
		return head;
	}
	
	void listInsert(ListNode *spot, ListNode *n){
		n->next = spot->next;
		spot->next = n;
	}
	
	
	bool isEmpty(){
		return head->next == NULL;
	}


	void insert (string d, int p,ofstream &print){
		ListNode *newNode = new ListNode;
		ListNode *cursor = new ListNode;
		newNode->charStr = d;
		newNode->prob = p;
		cursor = head;
	
		while(cursor->next!=NULL&& cursor->next->prob < newNode->prob){
			cursor=cursor->next;
	}
		newNode->next=cursor->next;
		cursor->next=newNode;
		print<<printList(head)<<endl;
	
	}

	ListNode* ListBTNode(ofstream &p){
		ListNode* newHead = head -> next;
		ListNode LN;
		while(newHead->prob!=100){
			ListNode *newNode= new ListNode;
			newNode->prob = newHead->prob + newHead->next->prob;
			newNode->charStr = newHead->charStr + newHead->next->charStr;
			newNode->left = newHead;
			newNode->right = newHead->next;
			p <<LN.printNode(newNode)<<endl;;
			
			ListNode *spotNode;
			spotNode = findSpot(newNode,newHead);
			listInsert(spotNode,newNode);
			p<<printList(newHead)<<endl;;
			newHead=newHead->next->next;	
		}	
			p<<"ListHead-->(Dummy, 0 "+newHead->charStr+ " ) -->( " +newHead->charStr+" ,"+to_string(newHead->prob)+" NULL)"<<endl;
			return  newHead;
	}

	string printList(ListNode* headNode){
		string result ="ListHead-->(Dummy, 0 " + headNode->next->charStr + ")-->";
		ListNode *current =headNode;
		while(current->next!=NULL){
			result+="( NUll "+current->charStr+", " +current->next->charStr + " "+to_string(current->next->prob)+")--> ";
			current =current->next;
		}	
		return result + "(" + current->charStr + "-->NULL)";
}
};

class HuffmanBinaryTree{
	private:
		ListNode *head;
		ListNode *Dummy;
		
		public:
		ListNode LN;
		HuffmanBinaryTree(){
			Dummy=new ListNode();
			head=Dummy;
			
		}
	ListNode* constructHBT(ListNode* treeNode,string c,ofstream &p){

		if(treeNode == NULL){
			
		}else if(isLeaf(treeNode)){
			
			p<< treeNode->charStr +" ";
			treeNode->code = c;
			p <<treeNode->code<<endl;
			
		}else{
			constructHBT(treeNode->left, c+"0",p);
			constructHBT(treeNode->right,c+"1",p);
		} 
		return treeNode;
		
	}
	
	
	void inOrder(ListNode *node,ofstream &p){
		if(node==NULL){
			
		}else{
			inOrder(node->left,p);
			p <<LN.printNode(node)<<endl;
			inOrder(node->right,p);
		}
	}
	
	void preOrder(ListNode *node, ofstream &p){
		if(node==NULL){
			
		}else{
			
			p << LN.printNode(node)<<endl;
			preOrder(node->left,p);
			preOrder(node->right,p);
		}
	}
	
	void postOrder(ListNode *node, ofstream &p){
		if(node==NULL){
			
		}else{
			postOrder(node->left,p);
			postOrder(node->right,p);
			p << LN.printNode(node)<<endl;

		}
	}
	
	bool isLeaf(ListNode *node){
		if(node->left==NULL && node->right==NULL){
			return true;
		}
		return false;
	}	

};


int main(int argc ,char** argv){
	HuffmanLinkedList mylist;
	ifstream input;
	ofstream output1;
	ofstream output2;
	ofstream output3;
	ofstream output4;
	ofstream output5;

	

	input.open(argv[1]);
	output1.open(argv[2]);
	output2.open(argv[3]);
	output3.open(argv[4]);
	output4.open(argv[5]);
	output5.open(argv[6]);

	if(!input){
		cout<<"no file";
		exit(1);
	}	
	string cs;
	int num;

	while(!input.eof()){	
		input >> cs >> num;
		if(input.eof()){
			break;
		}
		mylist.insert(cs,num,output5);
	}
	HuffmanBinaryTree myHBT;
	ListNode* rootNode =mylist.ListBTNode(output5);
	myHBT.constructHBT(rootNode,"",output1);
	myHBT.preOrder(rootNode,output2);
	myHBT.inOrder(rootNode,output3);
	myHBT.postOrder(rootNode,output4);
	
	input.close();
	output1.close();
	output2.close();
	output3.close();
	output4.close();
	output5.close();
	
	return 0;
}






