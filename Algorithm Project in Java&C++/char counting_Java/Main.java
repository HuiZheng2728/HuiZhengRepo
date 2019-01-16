
import java.io.File;
import java.io.FileNotFoundException;
import java.io.IOException;
import java.io.PrintWriter;
import java.util.Scanner;

import javax.swing.JOptionPane;

public class Main {

	public static void main(String[] args) throws IOException{
		
		File input = new File(args[0]);
		File output=new File(args[1]);
		
		Scanner inputChar =null;
		
		PrintWriter printer = new PrintWriter(output);
		try{
			inputChar=new Scanner(input);
		}catch(FileNotFoundException e){
			JOptionPane.showMessageDialog(null, "File not found!");
			System.exit(1);
		}
		
		int[] charList =new int[256];
		
		while(inputChar.hasNext()){
			String line =new String();
			line =inputChar.next();
			
			for(char i: line.toCharArray()){	
				charList[i]++;	
			}
		}
			for(int i ='!';i<='~';i++){
				printer.println((char)i+" # "+charList[i]);
				
			}
		inputChar.close();
		printer.close();
	}
	}

