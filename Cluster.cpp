//Cluster program which finds the largest cluster of trees in a forest
#include <fstream>
#include <iostream>
#include <cstdlib>
#include <cmath>
#include <ctime>
using namespace std;
	#define b 2			//exclude b slots from the boundaries so fire would not propogate across boundaries
	#define m 302		//identify the largest grid dimensions 


void printGrid(int, int [m][m]);
int check(int, int, int [m][m]);
void conback(int [m][m]);

int main()
{
	
	ofstream file("cluster.txt");	//create ofstream file cluster

	srand(time(NULL));				//random generator	


double p = 0.35;					//choose a probability p

int Grid[m][m];						//define the double array Grid


for(int L=2*b+1; L<=m; L++){		//let grid size go through 2b+1 to m where L is grid dimension
							
					
//----------------------------------
//filling the grid with trees with probability p

	for(int i=b; i<L-b; i++){		//going through the whole grid except exluded boundaries
	for(int j=b; j<L-b; j++){

	double a=(rand()%100)*0.01;		//generate random number btw 0.00 and 0.99
	

	if (a<=p)	{					//if a <= p
		Grid[i][j] = 1;				//fill the grid with tree

	}
	else {
		Grid[i][j] = 0;				//if a  >p leave the slot empty

		}
	}
}

//---------------------------------

//cout << endl;						//skip a line
printGrid(L,Grid);				//print the grid

int temp = 0;						//temp will be any cluster size 
int final = 0;						//final stores the largest temp


	for(int i=b; i<L-b; i++){		//going through the whole grid except exluded boundaries
	for(int j=b; j<L-b; j++){


		
		if(Grid[i][j] == 1){			//if the slot is a tree
			temp = check(i, j, Grid);	//temp will be the size of the cluster checked
		if (temp == 0) temp++;			//if the slot is a single tree without any neighbouring tree, add 1 to temp
		}

		if(temp > final) final = temp;	//store temp to final if it is larger than final
			
			}
		}

	cout << L-2*b << "\t" << final << endl;		//print the grid size and the largest cluster size
	file << L-2*b << "\t" << final << endl;		//file the grid size and the largest cluster size
}
}
//-----------------------------------------------
//check function which is a recursive function, checking a slot for a tree and checking the neighbouring trees
//where again each neghbouring tree is checked for further neighbouring trees and so on. At the end, the cluster
//size corresponding to the initial slot is returned
int check(int i, int j, int Grid[m][m]){
		
	int count = 0;					//let count, the cluster size be 0


//after checking each tree, it is made to be 5 to avoid double counting

	if(Grid[i][j+1]  == 1){				//if there is a tree to the East	
		Grid[i][j+1]  = 5;				//let it be 5 
		count += check(i, j+1, Grid);	//check this tree
		count++;						//increment cluster size by 1
		
	}

	if(Grid[i+1][j]  == 1){				//if there is a tree to the South	
		Grid[i+1][j]  = 5;				//let it be 5 
		count += check(i+1, j, Grid);	//check this tree
		count++;						//increment cluster size by 1
		
	}

	

	if(Grid[i][j-1]  ==  1){			//if there is a tree to the West	
		Grid[i][j-1]  = 5;				//let it be 5 
		count += check(i, j-1, Grid);	//check this tree
		count++;						//increment cluster size by 1

	}

	if(Grid[i-1][j]  == 1){				//if there is a tree to the North	
		Grid[i-1][j]  = 5;				//let it be 5 
		count += check(i-1, j, Grid);	//check this tree
		count++;						//increment cluster size by 1

	}


	if(Grid[i+1][j+1]  == 1){			//if there is a tree to the South-East	
		Grid[i+1][j+1]  = 5;			//let it be 5 
		count += check(i+1, j+1, Grid);	//check this tree
		count++;						//increment cluster size by 1
		
	}

	if(Grid[i+1][j-1]  == 1){			//if there is a tree to the South-West	
		Grid[i+1][j-1]  = 5;			//let it be 5 
		count += check(i+1, j-1, Grid);	//check this tree
		count++;						//increment cluster size by 1
		
	}

	if(Grid[i-1][j+1]  == 1){			//if there is a tree to the North-East	
		Grid[i-1][j+1]  = 5;			//let it be 5 
		count += check(i-1, j+1, Grid);	//check this tree
		count++;						//increment cluster size by 1
		
	}

	if(Grid[i-1][j-1]  == 1){			//if there is a tree to the North-West	
		Grid[i-1][j-1]  = 5;			//let it be 5 
		count += check(i-1, j-1, Grid);	//check this tree
		count++;						//increment cluster size by 1
		
	}
	return count;						//return the culster size
	

}

//---------------------------------------------------------------------------
//print function which prints the full Grid
void printGrid(int L, int Grid[m][m]){
	for(int i=b; i<L-b; i++){		//going through the whole grid except exluded boundaries			
	for(int j=b; j<L-b; j++){

	cout << Grid[i][j] << " " ;		//display the final grid
	}
cout << endl;						//skip to the next row after a row is displayed

}
cout << endl;						//skip a line when full grid is printed
}

//---------------------------------------------------------------------------