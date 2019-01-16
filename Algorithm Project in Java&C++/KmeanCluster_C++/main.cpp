#include <iostream>
#include <cstdlib>
#include <cstddef>
#include <fstream>
#include <math.h>
using namespace std;

class Point{
	public:
	int x;
	int y;
	int label;
	double distance=0.0;
	
	void printPoint(Point){
		
	}
	
};
class K_Mean{
	struct xyCoord{
		int xCoord;
		int yCoord;
		int label;	
		string letter=" ";
	};
	
	public:
	int k;
	Point *pointSet;
	int numRow;
	int numCol;
	int **imageArray;
	xyCoord *Kcentroids;
	int numPts;
	int numSet=0;
	int numLoad=0;
	int lab=0;
	K_Mean(int kc, int Pts,int rowCount,int colCount){
		numRow=rowCount;
		numCol=colCount;

		numSet=Pts;
		k=kc;
	
		imageArray = new int*[numRow];
		for(int i=0; i<numRow;i++){
			imageArray[i]=new int [numCol];
		}
		pointSet = new Point [numPts];
		
		Kcentroids =new xyCoord[k];
		mapPoint2Image();
	
	}
	
	void loadPointSet(int lx,int ly){
		pointSet[numLoad].x=lx;
		pointSet[numLoad].y=ly;
		
	}
	void assignLable(){
		pointSet[numLoad].label=lab%4+1;
		numLoad++;
		lab++;
	}
	void printPointSet(){	 
	}
	void mapPoint2Image(){
		for(int i=0 ;i < numSet;i++){
			imageArray[pointSet[i].x][pointSet[i].y]=pointSet[i].label;
		
			
		}
		
	
	}
	void kMeanClustering(ofstream &out){
		
	
		int labelChange=1; //step 5.1
		
		while(labelChange!=0){
		
		mapPoint2Image();
		prettyPrint(out);	
			
		int labelChange=0;
		int x1=0,y1=0,x2=0,y2=0,x3=0,y3=0,x4=0,y4=0;
		int count1=0,count2=0,count3=0,count4=0;

		for(int i=0;i<numSet;i++){ // step 5.2
		
		
			if(pointSet[i].label==1){
				x1+=pointSet[i].x;
				y1+=pointSet[i].y;
				count1++;
		
				
			}else if(pointSet[i].label==2){
				x2+=pointSet[i].x;
				y2+=pointSet[i].y;
				count2++;
			}else if(pointSet[i].label==3){
				x3+=pointSet[i].x;
				y3+=pointSet[i].y;
				count3++;
			}else if(pointSet[i].label==4){
				x4+=pointSet[i].x;
				y4+=pointSet[i].y;
				count4++;
			
			}
		}
			
			Kcentroids[0].xCoord=x1/count1;
			Kcentroids[0].xCoord+=1;
			Kcentroids[0].yCoord=y1/count1;
			Kcentroids[0].label=1;
			Kcentroids[0].yCoord+=1;
			Kcentroids[0].letter="A";

				
			Kcentroids[1].xCoord=x2/count2;
			Kcentroids[1].yCoord=y2/count2;
			Kcentroids[1].label=2;
			Kcentroids[3].letter="B";

				
			Kcentroids[2].xCoord=x3/count3;
			Kcentroids[2].yCoord=y3/count3;
			Kcentroids[2].label=3;
			Kcentroids[3].letter="C";
	
			Kcentroids[3].xCoord=x4/count4;
			Kcentroids[3].yCoord=y4/count4;			
			Kcentroids[3].label=4;
			Kcentroids[3].letter="D";

				
			int minIndex=0;
			double minDist=0.0;
			double minArray[4]={};
			int lbl=1;
		
			double d1=0,d2=0,d3=0,d4=0;
			for(int i=0;i<numSet;i++){ 
					d1=calDistance(pointSet[i],Kcentroids[0]);
					minArray[0]=d1;
					d2=calDistance(pointSet[i],Kcentroids[1]);
					minArray[1]=d2;
					d3=calDistance(pointSet[i],Kcentroids[2]);
					minArray[2]=d3;
					d4=calDistance(pointSet[i],Kcentroids[3]);
					minArray[3]=d4;
					
				for(int j=0;j<4;j++){
					if(minArray[minIndex]>minArray[j]){
						minIndex=j;
					}
					
				}
				if(pointSet[i].label!=Kcentroids[minIndex].label){
					pointSet[i].label=Kcentroids[minIndex].label;
					labelChange++;
				}
			
				
			}
		
		if(labelChange==0){
			break;
			
		}
			

}
}

	void printSet(ofstream &out){
		
	}
	
	void prettyPrint(ofstream &out){

		for(int i =0;i<numRow;i++){
			
			for(int j=0;j<numCol;j++){
		
				if(imageArray[i][j]>0 && imageArray[i][j]<100){
					out<<imageArray[i][j];
					
				}else{
					out<<" ";
				
				}
			}
			out<<endl;
		}
		
		
			
	}
	
	double calDistance(Point a,xyCoord b){
		double distance=0.0;
		double x=0.0;
		double y=0.0;
		x=pow(a.x-b.xCoord,2);
		y=pow(a.y-b.yCoord,2);
		distance =sqrt(x+y);
		return distance;
	}
	
};


int main(int argc ,char** argv){
	
	ifstream inFile;
	ofstream outFile1;
	ofstream outFile2;
	
	inFile.open(argv[1]);
	
	if(!inFile){
		cout<<"No file"<<endl;
		exit(1); 
	}
	
	outFile1.open(argv[2]);
	outFile2.open(argv[3]);
	
	
	int k;
	int numPts;
	int rowCount;
	int colCount;
	inFile>>k>>numPts>>rowCount>>colCount;
	outFile1<<k<<endl;
	outFile1<<numPts<<endl;
	outFile1<<rowCount<<" "<<colCount<<endl;
	
	
	K_Mean myKM (k,numPts,rowCount,colCount);
	
	while(!inFile.eof()){
			int x;
			int y;
			inFile>>x>>y;
			outFile1<<x<<" "<<y<<endl;
			
		
		myKM.loadPointSet(x,y);
		myKM.assignLable();
		if(inFile.eof()){
				break;
			}
			
		}
	myKM.mapPoint2Image();
	myKM.kMeanClustering(outFile2);
	
	


	
	inFile.close();
	outFile1.close();
	outFile2.close();
	

	
	return 0;
	
}
	
		

