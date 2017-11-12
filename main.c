/* 
 * Ex1: Easy Sudoku puzzle solver and checker
 * -------------------------
 * Name: Assaf Ben Yishay
 * ------------------------
 * Using: main.h , solver.h , checker.h
 */ 

#include "main.h"
#include "solver.h"
#include "checker.h"

int main(int argc, char *argv[])
{
	char* output_path=NULL;
	int i,allocated=0;
	char suffix[]="_sol.txt";

	if(argc==3) //no output file name from user
	{
		output_path=(char*)malloc(sizeof(char)*(strlen(argv[2])+strlen(suffix))); //allocate memory for output path string
		if(output_path == NULL)                     
		{
			printf("Memory allocation failed\n");
			return 1;
		}
		allocated=1;	//mark that output_path was dynamically allocated, used when trying to free allocation
		for(i=0;i<(int)strlen(argv[2])-4;i++)
		{
			output_path[i]=argv[2][i];		//copy input path, not intcluding the ".txt" suffix
		}
		output_path[i]='\0';
		strcat(output_path,suffix);			//copy new suufix
	}
	else if(argc==4)						//existing file name from user
	{
		output_path=argv[3];
	}
	else
	{
		printf("Unkonwn arguments\n");
		return 1;
	}
	
	if(argv[1][0]=='0')
		Solver(argv[2],output_path);
	if(argv[1][0]=='1')
		Checker(argv[2],output_path);

	
	if(allocated) free(output_path);
	return 0;
}