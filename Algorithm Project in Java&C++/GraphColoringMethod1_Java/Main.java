
import java.io.File;
import java.io.FileNotFoundException;
import java.io.IOException;
import java.io.PrintWriter;
import java.util.Scanner;

public class Main {

		public static void main(String[]args) throws IOException{
			
			File inFile = new File(args[0]);
			File outFile = new File(args[1]);
			Scanner input=null;
			
			PrintWriter printer = new PrintWriter(outFile);
			
			try{
				input= new Scanner(inFile);
			}catch(FileNotFoundException e){
				System.out.println("File not found");
				System.exit(1);
			}

			int numNode;
			int x;
			int y;
			numNode=input.nextInt();
			graphColoring gc = new graphColoring(numNode);
			
			printer.println("inpu pairs");
			while(input.hasNextInt()){
				x=input.nextInt();
				y=input.nextInt();
				
				gc.loadMatrix(x,y);
				gc.inputPairs(x, y,printer);
				
			}
			printer.println("initial matrix");
			gc.printAdjMatrix(printer); // initial matrix
			gc.constructNodeList();
			
			gc.newColor=0; // end of 0
			int numColor=0;
			while(true){
			gc.newColor++; //1
			numColor++;
			node current= gc.listHead.next;
			while(current!= null){ // 2 3
				
			if(current.color == 0 && gc.checkAdjacent(current.ID, gc.newColor)==0){
					gc.adjacencyMatrix[current.ID][current.ID]=gc.newColor;
					current.color=gc.newColor;
			}
			current=current.next;  // 2 3
			}  
			
			//gc.printAdjMatrix(); // 5  for debug
			if(gc.isAllColored()){
				break;
			}
			} // 6
			gc.colorUsed(numColor, printer);
			printer.println("final matrix");
			gc.printAdjMatrix(printer); // final matrix
			//gc.printList();
			input.close();
			printer.close();
			
		}
}
