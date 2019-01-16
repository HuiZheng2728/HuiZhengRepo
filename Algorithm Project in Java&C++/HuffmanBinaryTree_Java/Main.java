import java.io.File;
import java.io.FileNotFoundException;
import java.io.FileWriter;
import java.io.IOException;
import java.io.PrintWriter;
import java.util.Scanner;

public class Main {
	public static void main(String[] args) throws IOException{
	File input = new File(args[0]);
	File output1 = new File(args[1]);
	File output2 = new File(args[2]);
	File output3 = new File(args[3]);
	File output4 = new File(args[4]);
	File output5 = new File(args[5]);
	
	HuffmanLinkedList myLinkList = new HuffmanLinkedList();
	Scanner inputData=null;
	PrintWriter printer1 = new PrintWriter(output1);
	PrintWriter printer2 = new PrintWriter(output2);
	PrintWriter printer3 = new PrintWriter(output3);
	PrintWriter printer4 = new PrintWriter(output4);
	PrintWriter printer5 = new PrintWriter(new FileWriter( output5));

	try{
		inputData= new Scanner(input);
	}catch(FileNotFoundException e){
		System.out.println("File not found");
		System.exit(1);
	}
	while(inputData.hasNext()){
		String data=inputData.next();
		int count=inputData.nextInt();
		myLinkList.insert(data,count,printer5);	
	}
	
	HuffmanBinaryTree myHBT = new  HuffmanBinaryTree();
	ListNode rootNode =myLinkList.listBTNode(printer5);
	
	myHBT.constructHBT(rootNode, "",printer1);	
	myHBT.preOrder(rootNode,printer2);
	myHBT.inOrder(rootNode,printer3);
	myHBT.postOrder(rootNode,printer4);
	
	inputData.close();
	printer1.close();
	printer2.close();
	printer3.close();
	printer4.close();
	printer5.close();
	}
}
