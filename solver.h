/* 
 * Name: Assaf Ben Yishay
 */ 

#ifndef _SOLVERH_
#define _SOLVERH_

#include "main.h"
#include "sudoku.h"

/*
 *   Description: Main function of the Solver - Solve sudoku puzzle 
 *	-------------------------------------------------------
 *   input_path: string for the input file path 
 *   output_path: string for the output file path 
 *	-------------------------------------------------------
 *   returns: none 
 */
void Solver(char* input_path,char* output_path);

/*
 *   Solve the sudoku- loop scan cell by cell until solution  
 *	-------------------------------------------------------
 *   sud[][]: array contain the scanned sudoku puzzle cells
 *	-------------------------------------------------------
 *   returns: 0-solve succ eed, 1-solve failed
 */
int Solve(Cell sud[SIZE][SIZE]);



#endif