import java.io.PrintWriter;

public class DijkstraSSS {
		
	int numNodes;
	int sourceNode;
	int minNode;
	int currentNode;
	int newCost;
	int [][]costMatrix;
	int []fatherAry;
	int []toDoAry;
	int []bestCostAry;
	
	public DijkstraSSS(int numNode,int s) {
		this.numNodes =numNode;
		this.sourceNode=s;
		costMatrix=new int[numNodes+1][numNodes+1];
		fatherAry = new int[numNodes+1];
		toDoAry =new int [numNodes+1];
		bestCostAry = new int[numNodes+1];
		for(int i =1;i<numNodes+1;i++){
			for(int j=1;j<numNodes+1;j++){
				if(j==i){
					costMatrix[i][j]=0;
				}else{
					costMatrix[i][j]=99999;
				}
			}
		}	
		for(int i = 0; i<numNodes+1;i++){  // initializing fatherAry & bestCostAry;
			fatherAry[i]=i;
			bestCostAry[i]=99999;	
		}
	}
	
	public void loadCostMatrix(int row,int col,int cost){
		costMatrix[row][col]=cost;
	}
	public void setBestCostAry(int s){
		
		for(int i=1;i<numNodes+1;i++){
				bestCostAry[i]=costMatrix[sourceNode][i];
		}
	}
	public void setFatherAry(int s){
		
		for(int i=1;i<numNodes+1;i++){
			fatherAry[i]=sourceNode;
		}
	}
	
	public void setToDoAry(int s){
		for(int i =1;i<numNodes+1;i++){
			if(i==sourceNode){
				toDoAry[i]=0;
			}else{
			toDoAry[i]=1;
		}
	}
	}
	
	public int findMinNode(){
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
	public void markMinNode(){
		toDoAry[minNode]=0;	
	}
	
	public void setCurrentNode(int current){
		this.currentNode=current;
	}
	
	public void debugPrint(){
		System.out.println("source node is "+ sourceNode);
		
		System.out.print("fatherAry = ");
		for(int i =1;i<numNodes+1;i++){
			System.out.print(fatherAry[i]+" ");
		}
		System.out.println();
		System.out.print("bestCostAry");
		for(int i =1;i<numNodes+1;i++){
			System.out.print(" "+ bestCostAry[i]+" ");
		}
		System.out.println();
		System.out.print("ToDoAry  ");
		for(int i =1;i<numNodes+1;i++){
			System.out.print(" "+ toDoAry[i]+" ");
		}
		System.out.println();
	}
	
	public void printHeadLine(int current,PrintWriter p){
		p.println("===========================================");
		p.println("There are "+ numNodes+" nodes in the input graph.");
		p.println("============================================");
		p.println("Source node = "+ sourceNode);
		p.println("The shortest path from node "+sourceNode+" are: ");	
	}
	
	
	public void printShortestPaths(int current,PrintWriter p){
		if(current==sourceNode){
			p.print( sourceNode);
		}
		else if(current!=sourceNode){
			if(fatherAry[current]!=sourceNode){
			p.print(fatherAry[current] + " <- ");
			printShortestPaths(fatherAry[current],p);
			
		}else{
			p.print(sourceNode);	
		}
		}
		}
	public void printCost(int current,PrintWriter p){
			p.println(" cost = "+bestCostAry[current]);
	}
	
	
	public int computeCost(int current){
		int cost=0;
		this.currentNode=current;
		cost = bestCostAry[minNode]+costMatrix[minNode][currentNode];
		
		return cost;
	}
	
	public void changeFather(int current,int min){
		this.minNode=min;
		fatherAry[current]=minNode;
	}
	public void changeCost(int current,int newCost){
		this.currentNode=current;
		bestCostAry[current]=newCost;
	}
	
}



