/* 
 * Name: Assaf Ben Yishay
 * ------------------------
 * Using: sudoku.h
 */ 

#include "sudoku.h"

int ReadSudokuFile(Cell sud[][SIZE],char *input_path)
/*
 *   Description: Read sudoku puzzle from file to array
 */
{
	int i=0,j=0;
	char c;
	FILE *input_file = fopen(input_path,"rt");				
	if(!input_file)											//if failed to load file
	{
		printf("Error reading file");
		exit(1);
	}
	else
	{
		   while ((c = fgetc(input_file)) != EOF)
				{
					if(c=='\n')								//end of line
					{
						i++;								
						j=0;								
					} 
					else if(c>'0'&&c<='9'||c=='.')			//legitimate number or empty cell
					{
						sud[i][j].value = (char) c;			
						InitialPossArray(&sud[i][j]);		//initializ cell's poss array
						j++;								
					}

					else if(c=='-')							//seperatation line
					{
						j=0;								
						while ((c = fgetc(input_file)) != '\n');	//skip line
					}
				}

			fclose(input_file);
	}
	return 0;
}
int WriteSudokuFile(Cell sud[][SIZE],char *output_path,int failed)
{
/*
 *   Description: Write sudoku puzzle from array to file
 */
	int i,j;
	FILE *output_file = fopen(output_path,"w");			//open file to write
	if(!output_file)									//if failed to open file
	{
		printf("Error creating file");
		exit(1);
	}
	else
	{	
		if(!failed)	//only if succeeded solving
		{
			for(i=0;i<SIZE;i++)
			{
				if(i%3==0 && i/3!=0) fprintf(output_file,"-------+-------+-------\n"); //seperation line every third row
				
				for(j=0;j<SIZE;j++)
				{
					if(j%3==0 && j/3!=0) 
						fprintf(output_file," |"); //seperation line every third column
					fprintf(output_file,"%2c",sud[i][j].value);
				}
				fprintf(output_file,"\n");	
			}
		}
		else
		{
			fprintf(output_file,"Sudoku puzzle is too hard for me to solve");
		}
		fclose(output_file);
	}
	return 0;
}

int CheckRow(Cell sud[][SIZE],int n,int m)
{
/*
 *   Description: check row for duplication  
 *	 mark in sud[m][n].poss[] the posibillities left and count them
 */
	int i;
	for(i=0;i<SIZE;i++)														//scan each cell in the row
	{
		if(i==m) continue;													//skip the source cell
		if(sud[n][i].value!='.' && sud[n][m].poss[sud[n][i].value-'0']!=0)	//check if the current cell is a digit and hasn't counted yet
		{	
			if(sud[n][m].value==sud[n][i].value)							
				return i+1;													//return coordination - occurres only when original cell is a digit
			sud[n][m].poss[sud[n][i].value-'0']=0;							//disable possibility in poss array
			sud[n][m].poss[0]--;											//new poss count
		}
	}
	return 0;
}
int CheckCol(Cell sud[][SIZE],int n,int m)
/*
 *   Description: check col for duplication  
 *	 mark in sud[m][n].poss[] the posibillities left and count them
 */
{
	int i;
	for(i=0;i<SIZE;i++)														//scan each cell in the col
	{
		if(i==n) continue;													//check if the current cell is a digit and hasn't counted yet
		if(sud[i][m].value!='.' && sud[n][m].poss[sud[i][m].value-'0']!=0)
		{
			if(sud[n][m].value==sud[i][m].value)
				return i+1;													//return coordination - occurres only when original cell is a digit
			sud[n][m].poss[sud[i][m].value-'0']=0;							//disable possibility in poss array
			sud[n][m].poss[0]--;											//new poss count
		}
	}
	return 0;
}
int CheckSubgrid(Cell sud[][SIZE],int n,int m)
/*
 *   Description: check box for duplication  
 *	 mark in sud[m][n].poss[] the posibillities left and count them
 */
{
	int i,j;	
	for(i=(n/3)*3;i<(n/3+1)*3;i++)
		for(j=(m/3)*3;j<(m/3+1)*3;j++)											//scan each cell in the box
		{
			if(i==n && j==m) continue;
			if(sud[i][j].value!='.' && sud[n][m].poss[sud[i][j].value-'0']!=0) //check if the current cell is a digit and hasn't counted yet
			{
				if(sud[n][m].value==sud[i][j].value)
					return (i+1)*10+(j+1);										//return coordination - occurres only when original cell is a digit	
				sud[n][m].poss[sud[i][j].value-'0']=0;							//disable possibility in poss array
				sud[n][m].poss[0]--;											//new poss count
			}
		}
	return 0;
}

int SetIfUniqueInRow(Cell sud[][SIZE],int n,int m)
{
/*
 *   Description: check if the specific cell in has a unique possibilty
 *   in its row, if so- set its value according to this possibity
 */
	int pi,i,unique=1;
	for(pi=1;pi<SIZE+1 && sud[n][m].poss[0]!=1;pi++)						//scan each cell in source cell's poss[] array and compare it to the poss array of the other cells in the row
	{
		if(sud[n][m].poss[pi]!=0)											//only if this is a valid possibility, than check the rest of the row
		{
			for(i=0;i<SIZE;i++)
			{
				if(i==m) continue;											//skip source cell
				if(sud[n][m].poss[pi]==sud[n][i].poss[pi])					//isn't unique
				{
					unique=0;
				}
			}
			if(unique==1)													//is unique
			{
				sud[n][m].value=sud[n][m].poss[pi];
				sud[n][m].poss[0]=1;
				return 1;
			}
			unique=1;
		}
	}
	return 0;
}
int SetIfUniqueInCol(Cell sud[][SIZE],int n,int m)
/*
 *   Description: check if the specific cell in has a unique possibilty
 *   in its col, if so- set its value according to this possibity
 */
{
	int pi,i,unique=1;
	for(pi=1;pi<SIZE+1 && sud[n][m].poss[0]!=1;pi++)							//scan each cell in source cell's poss[] array and compare it to the poss array of the other cells in the col
	{
		if(sud[n][m].poss[pi]!=0)												//only if this is a valid possibility, than check the rest of the col
		{
			for(i=0;i<SIZE;i++)
			{
				if(i==m) continue;												//skip source cell
				if(sud[n][m].poss[pi]==sud[i][m].poss[pi])						//isn't unique
				{
					unique=0;
				}
			}
			if(unique==1)														//is unique
			{
				sud[n][m].value=sud[n][m].poss[pi];
				sud[n][m].poss[0]=1;
				return 1;
			}
			unique=1;
		}
	}
	return 0;
}
int SetIfUniqueInSubgrid(Cell sud[][SIZE],int n,int m)
/*
 *   Description: check if the specific cell in has a unique possibilty
 *   in its box, if so- set its value according to this possibity
 */
{
	int pi,i,j,unique=1;
	for(pi=1;pi<SIZE+1 && sud[n][m].poss[0]!=1;pi++)							//scan each cell in source cell's poss[] array and compare it to the poss array of the other cells in the box
	{
		if(sud[n][m].poss[pi]!=0)												//only if this is a valid possibility, than check the rest of the col
		{
		for(i=(n/3)*3;i<(n/3+1)*3;i++)
			for(j=(m/3)*3;j<(m/3+1)*3;j++)
			{
				if(i==n && j==m) continue;										//skip source cell
					if(sud[n][m].poss[pi]==sud[i][j].poss[pi])					//isn't unique
					{
						unique=0;
					}
			}
			if(unique==1)														//is unique
			{
				sud[n][m].value=sud[n][m].poss[pi];
				sud[n][m].poss[0]=1;
				return 1;
			}
			unique=1;
		}
	}
	return 0;
}

void InitialPossArray(Cell* cell)
/*
 *   Description: initilize the poss[] array of a Cell object
 *	for an empty cell -  set pos[1-9] as valid possbilties for this cell.
 *	set number of possbilities pos[0]=9
 *	for not an empty cell -  set pos[value] as the only valid possbilty for this cell.
 *	set number of possbilities pos[0]=1
 */
{
	int i;
	if(cell->value=='.'){				//for empty cell all posbilities are valid
		for(i=1;i<SIZE+1;i++)
			cell->poss[i]=i+'0';		//validate all by set each cell to its char value
		cell->poss[0]=SIZE;				//possibillitis count
	}
	else{
		for(i=1;i<SIZE+1;i++)			//for not empty cell only one possibilty is valid
			cell->poss[i]=0;			//disable other possibillties
		cell->poss[0]=1;				//possibillitis count
		cell->poss[cell->value-'0']=cell->value;
	}

}
char GetLastPoss(Cell* cell) 
/*
 *   Description: return char the using cell's poss[] array
 */
{
	int i=0;
	if(cell->poss[0]!=1)			//has more than one possibility
		return 0;
	for(i=1;i<SIZE+1;i++)
		if(cell->poss[i]!=0)
			return cell->poss[i];		
	return 0;
}