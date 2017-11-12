/* 
 * Name: Assaf Ben Yishay
 * ------------------------
 * Using: solver.h
 */ 

#include "solver.h"

void Solver(char* input_path,char* output_path)
/*
 *   Description: Main function of the Solver - Solve sudoku puzzle
 */
{
	Cell sud[SIZE][SIZE];
	ReadSudokuFile(sud,input_path);
	WriteSudokuFile(sud,output_path,Solve(sud));
}

int Solve(Cell sud[SIZE][SIZE])
/*
 *   Solve the sudoku- loop scan cell by cell until solution  
 */
{
	int i,j,changed=1;
	while(changed==1)
	{
		changed=0;		//flag for every iteration
		for(i=0;i<SIZE;i++)
		{ 
			for(j=0;j<SIZE;j++)
			{	CheckRow(sud,i,j);
				CheckCol(sud,i,j);
				CheckSubgrid(sud,i,j);
				if(sud[i][j].value=='.' && sud[i][j].poss[0]==1){	//check if current cell has only one possibility
						sud[i][j].value=GetLastPoss(&sud[i][j]);	//set its value
						changed=1;									//mark as changed for this while iteration							
				}
			}
		}
		if(changed==0)	//second try, find if there are cells which only them can contain a certain possibilty in their row\col\subgrid
		for(i=0;i<SIZE;i++)
		{ 
			for(j=0;j<SIZE;j++)
			{					
				if(SetIfUniqueInRow(sud,i,j) || SetIfUniqueInCol(sud,i,j) || SetIfUniqueInSubgrid(sud,i,j)) //if found unique bossibility
				{ 
						changed=1; //mark as changed for this while iteration
				}
			}
		}
	}

	for(i=0;i<SIZE;i++){		
		for(j=0;j<SIZE;j++){
			if(sud[i][j].poss[0]!=1) return 1; //if done
		}
	}
	return 0;	//if failed
}
