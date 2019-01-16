import java.io.PrintWriter;

public class graphColoring {

	int[][] adjacencyMatrix;
	node listHead;
	int uncolorNode;
	int newColor;
	int numNode;
	
	public graphColoring(int n) {
		numNode=n;
		adjacencyMatrix = new int[n+1][n+1];
		node dummy = new node();
		listHead=dummy;
	}
	
	public void loadMatrix(int x,int y){
		adjacencyMatrix[x][y]=1;
		adjacencyMatrix[y][x]=1;

	
	}
	
	public void inputPairs(int x, int y,PrintWriter p){
		
		p.println(x + " "+ y + " <" + x +" ," + y  + "> and <" + y +" ," + x +">");
		
	}
	
	public void insertOneNode(node newNode){
		node cursor = listHead;
		while(cursor.next!=null && cursor.next.numEdges < newNode.numEdges){
			cursor=cursor.next;
		}
		newNode.next=cursor.next;
		cursor.next=newNode;
	}
	
	public void constructNodeList(){
		for(int i = 1; i < numNode+1;i++){
			 node temp = new node(i);
			 for(int j = 1; j< numNode+1;j++){
				 if(adjacencyMatrix[i][j]!=0){
					 temp.numEdges++;
				 }
			 }
			 insertOneNode(temp);
		}
		
	}
	public void findUncolorNode(node next){
		
	}
	
	public int checkAdjacent(int id, int c){
		for(int i = 1; i < numNode ; i++){
			if(adjacencyMatrix[id][i] !=0 && id!=i){
				if(adjacencyMatrix[i][i] == c){	
					return 1;
				}	
			}
		}
		return 0;
	}
	
	public void printAdjMatrix(PrintWriter p){
		for(int i = 1;i < numNode+1;i++){
			for(int j = 1;j < numNode+1;j++){	
			p.print(adjacencyMatrix[i][j] + " ");
			
			
			}
			p.println();
		}
		p.println("**********");
	}
	
	public void printList(int x, int y, PrintWriter p){
		node temp = listHead.next;
		while(temp!=null){
			System.out.print(" ID " + temp.ID + " Color " + temp.color + " "+ " edge = " + temp.numEdges + " -> ");
			temp=temp.next;
		}
	}
	public boolean isAllColored(){
		node temp = listHead.next;
		while(temp!=null){
			if(temp.color==0){
				return false;
			}
			temp=temp.next;
		}
		return true;
	}
	
	public void colorUsed(int n,PrintWriter p){
		p.print("color used = ");
		for(int i=1;i<n+1;i++){
			p.print(i + " ");
		}
		p.println();
	}
	
	
}
