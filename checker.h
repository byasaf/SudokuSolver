/* 
 * Name: Assaf Ben Yishay
 */ 

#ifndef _CHECKERH_
#define _CHECKERH_

#include "main.h"
#include "sudoku.h"

/*
 *   Description: Main function of the Checker - check existing sudoku solution 
 *	-------------------------------------------------------
 *   input_path: string for the input file path 
 *   output_path: string for the output file path 
 *	-------------------------------------------------------
 *   returns: none 
 */
void Checker(char* input_path,char* output_path);

/*
 *   Description: Log a single error line into output file 
 *	-------------------------------------------------------
 *   type: string for the input file path 
 *   c: the duplicated value 
 *   n: row index of the duplicated value
 *   m: col index of the duplicated value
 *   error: index of the error, produced by CheckRow/CheckCol/CheckSubgrid
 *   output_path: string for the output file path
 *	-------------------------------------------------------
 *   returns: none 
 */
void LogErrorToFile(int type,char c,int n,int m,int error,char *output_path);

#endif