//Forest Fire program which displays the fire as it propagates across the forest
#include <fstream>
#include <iostream>
#include <cstdlib>
#include <cmath>
#include <ctime>
using namespace std;
	
	#define b 2				//exclude b slots from the boundaries so fire would not propogate across boundaries
	#define m 24			//identify the grid row size
	#define n 24			//identify the grid column size


void fill(double, int[m][n], int[m][n]);
void step(double, int, int, double, int [m][n], int [m][n]);			
void printGrid(int [m][n]);
bool end(int [m][n]);
void ignite(int [m][n], int[m][n]);
void strike(double , int[m][n], int [m][n]);
void grow(double, int[m][n], int[m][n]);
void wind(int, int, int, int, int[m][n], int[m][n]);
void rain(double , int[m][n], int [m][n]);
int Grid[m][n], temp[m][n];


int main()
{
	
	ofstream file("critical.txt");		//create ofstream file critical

	srand(time(NULL));					//random generator




int count=-1;							//number of ticks, starts from -1 in order not to count the initial positions

double  p =  1;							//probability of finding a tree in a slot
double  s =  0.005;						//probability of a tree being struck by lightning
double  g =  0.005;						//probability of an empty space growing
double  r =  0.05;						//probability of extinguishing a burning tree
double  w =  1;							//probability of wind blowing in every tick

fill(p, Grid, temp);					//fill in the grid with trees with probability p

ignite(Grid,temp);						//ignite a random tree to start the fire



while(end(Grid)){						//while fire has not stopped yet

double a = (rand()%100)*0.01;			//generate a random number between 0.00 - 0.99
int dir = (rand()%8)+1;					//randomly choose a wind direction
										//wind direction 1 = N, 2 = NE, 3 = E, 4 = SE, 5 = S, 6 = SW, 7 = W, 8 = NW 
int str = (rand()%3)+2;					//randomly choose wind strength between 2 to 4
int dur = 1;							//set duration of wind to 1
if(w>a)									//if there is wind blowing, then
dur = (rand()%4)+1;						//choose a wind duration between 1 - 4


while(dur >0 && end(Grid)){				//while wind is still blowing and fire has not ended
		
		strike(s,Grid,temp);			//strike the grid with probability s

		grow(g,Grid,temp);				//let trees grow with probability g

		rain(r,Grid,temp);				//let there be rain with probability r

		printGrid(Grid);				//print the grid
		
		step(a, dir, str, w, Grid, temp);			 //fire spreading through the grid with chance of w wind blowing
		
		cout << "duration: " << dur << "\t" << endl;			//print duration of the wind				
		
		count++;						//add one to count
		dur--;							//subtract 1 from the wind duration

}
	}

cout << "p = " << p <<endl;				//print the probability p at the end
cout << endl << "number of ticks: " << count << endl << endl;	//print the number of total ticks

}
//NOTAIONS tree = 1; burning tree = 2; empty slot = 0;
//The double array temp is used as a temporary array to store the values during the step function

//-------------------------------------------------------------------
//fill function to fill the empty grid with trees
void fill(double p, int Grid[m][n], int temp[m][n]){
	
	for(int i=b; i<m-b; i++){			//going through the whole grid except exluded boundaries
	for(int j=b; j<n-b; j++){

	double a=(rand()%100)*0.01;			//generate random number btw 0.00 and 0.99
	

	if (a<=p)	{						//if a <= p fill with the slot with tree
		Grid[i][j] = 1;
		temp[i][j] = 1;
	}
	else {
		Grid[i][j] = 0;					//if a > p leave the slot empty
		temp[i][j] = 0;
		}
	}
}

}
//-------------------------------------------------------------------
//ignite function to start the fire
void ignite(int Grid[m][n], int temp[m][n]){
	
	int a = rand()%(m-(2*b));			//generate random number btw 0  and m-2b
	int c = rand()%(n-(2*b));			//generate random number btw 0  and n-2b
		Grid[a+b][c+b] = 2;				//ignite a random slot according to a and c
		temp[a+b][c+b] = 2;
}
//-------------------------------------------------------------------
//grow function to make trees growing from empty spaces
void grow(double g, int Grid[m][n], int temp[m][n]){
	
	for(int i=b; i<m-b; i++){			//going through the whole grid except exluded boundaries
	for(int j=b; j<n-b; j++){

	double a=(rand()*3.05185*0.00001);  //generate random number between 0.00000 and 0.99999
	

	if (a<g && Grid[i][j] == 0){		//if a < g and the slot is empty
		Grid[i][j] = 1;					//fill the slot with a tree
		temp[i][j] = 1;
			}
		}
	}
}

//-------------------------------------------------------------------
//strike function to strike a tree
void strike(double s, int Grid[m][n], int temp[m][n]){
	
	for(int i=b; i<m-b; i++){			//going through the whole grid except exluded boundaries
	for(int j=b; j<n-b; j++){

	double a=(rand()*3.05185*0.00001);  //generate random number between 0.00000 and 0.99999
	

	if (a<s && Grid[i][j] == 1){		//if a < s and slot is a tree
		Grid[i][j] = 2;					//burn the tree
		temp[i][j] = 2;
			}
		}
	}
}
//-------------------------------------------------------------------
//rain function to extinguish the fire
void rain(double r, int Grid[m][n], int temp[m][n]){
	
	for(int i=b; i<m-b; i++){			//going through the whole grid except exluded boundaries
	for(int j=b; j<n-b; j++){

	double a=(rand()*3.05185*0.00001);  //generate random number between 0.00000 and 0.99999
	

	if (a<r && Grid[i][j] == 2){		//if a < r and the slot is burning
		Grid[i][j] = 0;					//extinguish the fire
		temp[i][j] = 0;
			}
		}
	}
}

//-------------------------------------------------------------------
//function step which spreads the fire across the grid
void step(double a, int dir, int str, double w, int Grid[m][n], int temp[m][n]){

		for(int i=b; i<m-b; i++){					//going through the whole grid except exluded boundaries
		for(int j=b; j<n-b; j++){
			
		if(Grid[i][j] == 1){						//if there is a tree in the slot
		 
			
			if(a>=w){								//if there is no wind and
			if  (Grid[i+1][j]  == 2 ||				//if there is any neighbouring fire to the tree
				 Grid[i-1][j]  == 2 || 
				 Grid[i][j+1]  == 2 || 
				 Grid[i][j-1]  == 2 ||
				 Grid[i+1][j+1]  == 2 ||
				 Grid[i-1][j-1]  == 2 || 
				 Grid[i-1][j+1]  == 2 || 
				 Grid[i+1][j-1]  == 2 )
				temp[i][j] = 2;						//then the tree will catch fire
			}

			if(a<w)									//if there is wind then
			wind(i, j,dir, str, Grid, temp);		//let the trees catch fire according to the wind function
			
	
		}
		else if (Grid[i][j] == 2) temp[i][j] = 0;	//if the grid is a fire, extinguish it
		
		}
}

	if(a<w)											//if there was a wind
	cout << "dir: " << dir << "\t" << "str :" << str << endl;//print its direction and strength

		for(int i=b; i<m-b; i++){					//going through the whole grid except exluded boundaries
		for(int j=b; j<n-b; j++){
          Grid[i][j] = temp[i][j];					//transfer data from Grid to temp
		}
}

}
//--------------------------------------------------------------------
//wind function to allow wind blow over the whole grid with rpobability w
void wind(int i, int j,int dir, int str, int Grid[m][n], int temp[m][n]){

double a = (rand()%100);						//generate random number between 0 and 99
double bw = (6 - str)*(6 - str)*(6 - str);		//let bw variable be probability of fire spreading opposite to	
												//the direction of the wind according to the wind strength
												//for str 2, bw = 64%; str 3, bw = 27%; str 4, bw = 8%


			if  (dir == 1 && 					//if wind is due North and any of the following slots are burning
				 (Grid[i+1][j]  == 2 || 
				 Grid[i][j+1]  == 2 ||				
				 Grid[i][j-1]  == 2 ||
				 Grid[i+1][j+1]  == 2 || 
				 Grid[i+1][j-1]  == 2 ||									
				 Grid[i+str][j]  == 2 ||
				 Grid[i+str-1][j] == 2 ||
				 Grid[i+str-2][j] == 2))
				 temp[i][j] = 2;				//then burn the slot
			
			if (dir == 1 && a < bw &&(Grid[i-1][j]  == 2 || Grid[i-1][j-1]  == 2 ||  Grid[i-1][j+1]  == 2))
				temp[i][j] = 2;	//let the trees opposite to direction of wind to burn with probability bw

			
			if  (dir == 5 && 					//if wind is due South and any of the following slots are burning	
				 (Grid[i-1][j]  == 2 || 
				 Grid[i][j+1]  == 2 ||				
				 Grid[i][j-1]  == 2 ||
				 Grid[i-1][j-1]  == 2 || 
				 Grid[i-1][j+1]  == 2 || 				 								 				
				 Grid[i-str][j]  == 2 ||
				 Grid[i-str+1][j] == 2 ||
				 Grid[i-str+2][j] == 2))
				 temp[i][j] = 2;				//then burn the slot
		
			if (dir == 5 && a < bw && (Grid[i+1][j]  == 2 || Grid[i+1][j-1]  == 2 || Grid[i+1][j+1]  == 2))
				temp[i][j] = 2;	//let the trees opposite to direction of wind to burn with probability bw


			if  (dir == 3 && 					//if wind is due East and any of the following slots are burning 				
				 (Grid[i+1][j]  == 2 ||
				 Grid[i-1][j]  == 2 || 				
				 Grid[i][j-1]  == 2 ||				 
				 Grid[i-1][j-1]  == 2 || 				  
				 Grid[i+1][j-1]  == 2 ||								 				 
				 Grid[i][j-str]  == 2 ||
				 Grid[i][j-str+1] == 2 ||
				 Grid[i][j-str+2] == 2))
				 temp[i][j] = 2;				//then burn the slot
		
			if (dir == 3 && a < bw && (Grid[i][j+1]  == 2 || Grid[i+1][j+1]  == 2 || Grid[i-1][j+1]  == 2))
				temp[i][j] = 2;	//let the trees opposite to direction of wind to burn with probability bw

		
			if  (dir == 7 &&  					//if wind is due West and any of the following slots are burning				
				 (Grid[i+1][j]  == 2 ||
				 Grid[i-1][j]  == 2 || 
				 Grid[i][j+1]  == 2 ||				
				 Grid[i+1][j+1]  == 2 ||				  
				 Grid[i-1][j+1]  == 2 || 												 			
				 Grid[i][j+str]  == 2 ||
				 Grid[i][j+str-1] == 2 ||
				 Grid[i][j+str-2] == 2))
				 temp[i][j] = 2;				//then burn the slot			
			
			if (dir == 7 && a < bw &&  (Grid[i][j-1]  == 2 ||  Grid[i+1][j-1]  == 2 || Grid[i-1][j-1]  == 2))
				temp[i][j] = 2;	//let the trees opposite to direction of wind to burn with probability bw

		
			if  (dir == 2 &&  					//if wind is due North-East and any of the following slots are burning				
				 (Grid[i+1][j]  == 2 ||				
				 Grid[i][j-1]  == 2 ||								
				 Grid[i+1][j+1]  == 2 || 
				 Grid[i-1][j-1]  == 2 || 
				 Grid[i+1][j-1]  == 2 ||								 				 
				 Grid[i+str][j-str]  == 2 ||
				 Grid[i+str-1][j-str+1] == 2 ||
				 Grid[i+str-2][j-str+2] == 2))
				 temp[i][j] = 2;				//then burn the slot
		
			if (dir == 2 && a < bw && (Grid[i-1][j+1]  == 2 ||  Grid[i-1][j]  == 2 || Grid[i][j+1]  == 2))
				temp[i][j] = 2;	//let the trees opposite to direction of wind to burn with probability bw

		
			if  (dir == 6 &&  					//if wind is due South-West and any of the following slots are burning								
				 (Grid[i-1][j]  == 2 || 				
				 Grid[i][j+1]  == 2 ||				
				 Grid[i+1][j+1]  == 2 || 
				 Grid[i-1][j-1]  == 2 || 
				 Grid[i-1][j+1]  == 2 ||								 				
				 Grid[i-str][j+str]  == 2 ||
				 Grid[i-str+1][j+str-1] == 2 ||
				 Grid[i-str+2][j+str-2] == 2))
				 temp[i][j] = 2;					//then burn the slot
			
			if (dir == 6 && a < bw && (Grid[i+1][j-1]  == 2 || Grid[i+1][j]  == 2 || Grid[i][j-1]  == 2))
				temp[i][j] = 2;	//let the trees opposite to direction of wind to burn with probability bw

		
			if  (dir == 4 &&  					//if wind is due South-East and any of the following slots are burning				
				 (Grid[i-1][j]  == 2 || 
				 Grid[i][j-1]  == 2 ||								
				 Grid[i+1][j-1]  == 2 || 
				 Grid[i-1][j-1]  == 2 || 
				 Grid[i-1][j+1]  == 2 ||								 				 
				 Grid[i-str][j-str]  == 2 ||
				 Grid[i-str+1][j-str+1] == 2 ||
				 Grid[i-str+2][j-str+2] == 2))
				 temp[i][j] = 2;				//then burn the slot	
		
			if (dir == 4 && a < bw && (Grid[i+1][j+1]  == 2 || Grid[i][j+1]  == 2 || Grid[i+1][j]  == 2 ))
				temp[i][j] = 2;	//let the trees opposite to direction of wind to burn with probability bw


			if  (dir == 8 &&  					//if wind is due North-West and any of the following slots are burning				
				 (Grid[i+1][j]  == 2 ||
				 Grid[i][j+1]  == 2 ||				
				 Grid[i+1][j-1]  == 2 || 
				 Grid[i+1][j+1]  == 2 || 
				 Grid[i-1][j+1]  == 2 ||								 				 
				 Grid[i+str][j+str]  == 2 ||
				 Grid[i+str-1][j+str-1] == 2 ||
				 Grid[i+str-2][j+str-2] == 2))
				 temp[i][j] = 2;				//then burn the slot
		
			if (dir == 8 && a < bw && (Grid[i-1][j-1]  == 2 || Grid[i][j-1]  == 2 || Grid[i-1][j]  == 2 ))
				temp[i][j] = 2;	//let the trees opposite to direction of wind to burn with probability bw

			}

//--------------------------------------------------------------------
//print function which prints the full Grid
void printGrid(int Grid[m][n]){
	for(int i=b; i<m-b; i++){			//going through the whole grid except exluded boundaries	
	for(int j=b; j<n-b; j++){

	cout << Grid[i][j] << " " ;			//display the final grid
	}
cout << endl;							//skip to the next row after a row is displayed

}
cout << endl;							//skip a line when full grid is printed
}
//---------------------------------------------------------------------
//end function which ends the program when fire does not spread anymore
bool end(int Grid[m][n]){

bool cond=false;						//let cond be false
	for(int i=b; i<m-b; i++){			//going through the whole grid except exluded boundaries	
	for(int j=b; j<n-b; j++){
		
		if (Grid[i][j]==2)				//if there are still trees burning
		cond=true;						//let cond be true
		
	}
}
return cond;							//return the cond
}
//---------------------------------------------------------------------