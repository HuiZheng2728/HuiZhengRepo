import java.io.File;
import java.io.FileNotFoundException;
import java.io.IOException;
import java.io.PrintWriter;
import java.util.Scanner;

public class Main {
	
	public static void main(String[] args) throws IOException{
		File inFile= new File(args[0]);
		
		File outFile1=new File(args[1]);
		File outFile2=new File(args[2]);
		Scanner input = null;
		PrintWriter printer1 = new PrintWriter(outFile1);
		PrintWriter printer2 = new PrintWriter(outFile2);
		
		try{
			input= new Scanner(inFile);
		}catch(FileNotFoundException e){
			System.out.println("File not found");
			System.exit(1);
		}
		int numNode;
		int Ni;
		int Nj;
		int cost;
		
		numNode = input.nextInt();
		PrimMST prim= new PrimMST(numNode);
		prim.printSet(printer2);
		while(input.hasNext()){ // step 123
			Ni = input.nextInt();
			Nj = input.nextInt();
			cost=input.nextInt();
			prim.insertEdge(Ni,Nj,cost);
			printer2.println("current linklist");
			prim.printList(prim.edgeListHead, printer2);
			
		}// 123 end
	  
	    
		undirectedEdge nextEdge;
		
	
		while(true){
			
		nextEdge = prim.removedEdge();  //4		
		prim.pushEdge(nextEdge);   //6
		
		prim.totalMSTCost+=nextEdge.edgeCost;
		prim.move2Set(nextEdge.Ni,nextEdge.Nj);
		
		prim.printSet(printer2);
		if(prim.setCheck()){
			break;
		}
		
		
	}
	prim.printMST(printer1);
	input.close();
	printer1.close();
	printer2.close();
}
}
