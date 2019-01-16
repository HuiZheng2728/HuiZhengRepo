import java.io.PrintWriter;



public class PrimMST {

	int numNode;
	int[] inWhichSet;
	undirectedEdge edgeListHead;
	undirectedEdge MSTofG;
	int totalMSTCost;
	public PrimMST(int n) {
		numNode=n;
		undirectedEdge dummy = new undirectedEdge(0,0,0);
		undirectedEdge dummyJunior = new undirectedEdge(0,0,0);
		MSTofG = dummyJunior;
		edgeListHead=dummy;
		inWhichSet = new int[numNode+1];
		inWhichSet[1]=1;
		for(int i=2;i<numNode+1;i++){
			inWhichSet[i]=2;
		}
		
	}
	
	
	public void insertEdge(int ni, int nj, int cost){
		undirectedEdge node = new undirectedEdge(ni,nj,cost);
		undirectedEdge cursor = new undirectedEdge(ni,nj,cost);
		cursor=edgeListHead;
		while(cursor.next!=null && cursor.next.edgeCost <node.edgeCost){
			cursor=cursor.next;
		}
		node.next=cursor.next;
		cursor.next=node;
	}
	
	public undirectedEdge removedEdge(){
		undirectedEdge cursor = edgeListHead.next;
		while(true){
		if(inWhichSet[cursor.Ni]!=inWhichSet[cursor.Nj]){
			undirectedEdge temp=new undirectedEdge(cursor.Ni,cursor.Nj,cursor.edgeCost);
				return temp;
			}else{
				cursor=cursor.next;
			}
		}
		}
		
	public boolean setCheck(){
		for(int i =1;i <numNode+1;i++){
			if(inWhichSet[i]!=1){
				return false;
			}
		}
		return true;
	}
	
	public void pushEdge(undirectedEdge nextEdge){
		undirectedEdge cursor=MSTofG;
		while(cursor.next!=null){
			cursor=cursor.next;
		}
		nextEdge.next=cursor.next;
		cursor.next=nextEdge;
	}
	public void move2Set(int ni, int nj){
		if(inWhichSet[ni] == inWhichSet[1]){
			inWhichSet[nj] = inWhichSet[1];
		}else{
			inWhichSet[ni] = inWhichSet[1];
			inWhichSet[nj] = inWhichSet[1];
		}
	}
	
	public void printSet(PrintWriter p){
		p.print("current set = ");
		for(int i=1;i<numNode+1;i++){
			p.print(" "+inWhichSet[i]);
		}
		p.println();
	}
	
	public void printList(undirectedEdge node,PrintWriter p){
		undirectedEdge temp = node.next;
		int count=0;
		while(temp!=null && count<10){
			p.println(temp.Ni + " " + temp.Nj + " " +temp.edgeCost);
			temp = temp.next;
			count++;
		}
	}
	
	public void printMST(PrintWriter p){
		p.println("*** A Kruskal’s MST of the input graph is given below: ***");
		p.println(numNode);
		undirectedEdge current= MSTofG.next;
		while(current!=null){
			p.println(current.Ni+" " +current.Nj+ " "+ current.edgeCost);
			
			current=current.next;
		}
		p.println("*** The total cost of  a Kruskal’s MST is:  " +totalMSTCost);
		
	}	
}
