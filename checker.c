/* 
 * Name: Assaf Ben Yishay
 * ------------------------
 * Using: checker.h
 */ 
#include "checker.h"


void Checker(char* input_path,char* output_path)
/*
 *   Description: Main function of the Checker - check existing sudoku solution 
 */
{
	Cell sud[SIZE][SIZE];
	int i,j,error,type;
	int error_occurred=0;
	FILE *output_file=NULL;						
	
	ReadSudokuFile(sud,input_path);					//read sudoku

	output_file = fopen(output_path,"w");
	if(!output_file)									//if failed to open file
	{
		printf("Error creating file");
		exit(1);
	}
	//printf("Found errors in given Sudoku puzzle.\nThe errors are:");
	fprintf(output_file,"Found errors in given Sudoku puzzle.\nThe errors are:");
	fclose(output_file);

	for(type=0;type<3;type++)	//types: row error -> col error-> subgrid error
	{
		int flags[SIZE+1]={0,0,0,0,0,0,0,0,0,0}; //already known errors flags array
		for(i=0;i<SIZE;i++)
		{ 
			for(j=0;j<SIZE;j++)
			{	
				switch(type){
				case ROW_ERR:
					error=CheckRow(sud,i,j);	//save error index returned from function
					break;

				case COL_ERR:
					error=CheckCol(sud,i,j);
					break;		

				case SUB_ERR:
					error=CheckSubgrid(sud,i,j);
				}
				if(error!=0 && flags[sud[i][j].value-'0']!=1)
				{

					LogErrorToFile(type,sud[i][j].value,i,j,error,output_path);
					flags[sud[i][j].value-'0']=1;								//mark as known error
					error_occurred=1;
				}

			}
		}
	}

	if(!error_occurred) //no errors found
		{
			output_file = fopen(output_path,"w");
			if(!output_file)									
			{
				printf("Error creating file");
				exit(1);
			}
			//printf("No errors found in given Sudoku puzzle.");
			fprintf(output_file,"No errors found in given Sudoku puzzle.");
			fclose(output_file);
		}		
}

void LogErrorToFile(int type,char c,int n,int m,int error,char *output_path)

/*
 *   Description: Log a single error line into output file
 */
{	
	FILE* output_file = fopen(output_path,"a+");
	if(!output_file)									//if failed to open file
	{
		printf("Error saving to file");
		exit(1);
	}

		switch(type){
		case ROW_ERR:
			//printf("\nRow error: digit %c appears at (%d,%d) and (%d,%d)",c,m+1,n+1,error,n+1);
			fprintf(output_file,"\nRow error: digit %c appears at (%d,%d) and (%d,%d)",c,m+1,n+1,error,n+1);
			break;

		case COL_ERR:
			//printf("\nColumn error: digit %c appears at (%d,%d) and (%d,%d)",c,m+1,n+1,m+1,error);
			fprintf(output_file,"\nColumn error: digit %c appears at (%d,%d) and (%d,%d)",c,m+1,n+1,m+1,error);
			break;

		case SUB_ERR:
			//printf("\nSubgrid error: digit %c appears at (%d,%d) and (%d,%d)",c,m+1,n+1,error%10,error/10);
			fprintf(output_file,"\nSubgrid error: digit %c appears at (%d,%d) and (%d,%d)",c,m+1,n+1,error%10,error/10);
		}
		fclose(output_file);
}
