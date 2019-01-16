import java.io.File;
import java.io.FileNotFoundException;
import java.io.IOException;
import java.io.PrintWriter;
import java.util.Scanner;

public class Main {
	public static void main(String[]args) throws IOException{
		File inFile= new File(args[0]);
		File outFile = new File(args[1]);
		Scanner input = null;
		PrintWriter printer=new PrintWriter(outFile);
		
		try{
			input= new Scanner(inFile);
		}catch(FileNotFoundException e){
			System.out.println("File not found");
			System.exit(1);
		
	}
		int numNode;
		int sourceNode;
		int row;
		int col;
		int cost;
		int currentNode=0;
		int newCost=0;
		int minNode;
		numNode=input.nextInt();
		sourceNode=input.nextInt();
		
		DijkstraSSS sss = new DijkstraSSS(numNode,sourceNode);
		
		while(input.hasNext()){
			row=input.nextInt();
			col=input.nextInt();
			cost=input.nextInt();
			sss.loadCostMatrix(row,col,cost);
		}
		sss.setBestCostAry(sourceNode);
		sss.setFatherAry(sourceNode);
		sss.setToDoAry(sourceNode);  //step 2
		
		for(int i =1;i<numNode+1;i++){
			
			if(sss.toDoAry[i]!=0){
		
				minNode=sss.findMinNode(); //step 3
				//sss.debugPrint();
				sss.setCurrentNode(currentNode);
				currentNode=1;//step 4
				
		while(currentNode <= numNode){//step 7
			if(sss.toDoAry[currentNode]==1){  //step 5
				newCost=sss.computeCost(currentNode);
				if(newCost < sss.bestCostAry[currentNode]){	
					sss.changeCost(currentNode, newCost);
					sss.changeFather(currentNode, minNode);
					//sss.debugPrint();
			}
			}
			currentNode++;  //step 6
		}
		}
		}
		
		currentNode=1;
		sss.printHeadLine(currentNode,printer);
	
		while(currentNode<=numNode){
			printer.print("The path from "+sourceNode+ " to "+currentNode+" : "+ currentNode+" <- ");
			sss.printShortestPaths(currentNode,printer); //step 10;
			sss.printCost(currentNode,printer);
			currentNode++;					   //step 11;
		}	
		input.close();
		printer.close();
		
}
}