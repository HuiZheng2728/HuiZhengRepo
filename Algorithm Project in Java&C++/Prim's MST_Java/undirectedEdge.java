
public class undirectedEdge {
	int Ni;
	int Nj;
	int edgeCost;
	undirectedEdge next;
	
	
	public undirectedEdge(){
		next=null;
	}
	public undirectedEdge(int i,int j,int cost) {
		Ni=i;
		Nj=j;
		edgeCost=cost;
		next=null;
	}
	
	public void printEdge(){
		
	}
	
}
