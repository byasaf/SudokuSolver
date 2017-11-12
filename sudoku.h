/* 
 * Name: Assaf Ben Yishay
 */ 

#ifndef _SUDH_
#define _SUDH_

#include "main.h"

/*
 *   Description: Read sudoku puzzle from file to array
 *	-------------------------------------------------------
 *   sud[][]: 2-dim array contains the scanned from file sudoku puzzle 
 *   path: string for the input file path
 *	-------------------------------------------------------
 *   returns: 0- read file succeed, 1- read file failed
 */
int ReadSudokuFile(Cell sud[][SIZE],char *path); 

/*
 *   Description: Write sudoku puzzle from array to file 
 *	-------------------------------------------------------
 *   sud[][]: 2-dim array contains the sudoku puzzle to be saved
 *   path: string for the output file path
 *	-------------------------------------------------------
 *   returns: 0- read file succeed, 1- read file failed
 */
int WriteSudokuFile(Cell sud[][SIZE],char *output_path,int failed);

/*
 *   Description: check row for duplication  
 *	 mark in sud[m][n].poss[] the posibillities left and count them
 *	-------------------------------------------------------
 *   sud[][]: 2-dim array contains the sudoku puzzle
 *   n: row index to check
 *   m: col index to check
 *	-------------------------------------------------------
 *   returns: index of the first error in the row, return 0 of there is none
 */
int CheckRow(Cell sud[][SIZE],int n,int m);

/*
 *   Description: check col for duplication  
 *	 mark in sud[m][n].poss[] the posibillities left and count them
 *	-------------------------------------------------------
 *   sud[][]: 2-dim array contains the sudoku puzzle
 *   n: row index to check
 *   m: col index to check
 *	-------------------------------------------------------
 *   returns: index of the first error in the c, return 0 of there is none
 */
int CheckCol(Cell sud[][SIZE],int n,int m);

/*
 *   Description: check box for duplication  
 *	 mark in sud[m][n].poss[] the posibillities left and count them
 *	-------------------------------------------------------
 *   sud[][]: 2-dim array contains the sudoku puzzle
 *   n: row index to check
 *   m: col index to check
 *	-------------------------------------------------------
 *   returns: two digits num-
 *	 first digit - x coordintaion of error
 *   second digit - y coordination of error
 *   0 if there is none
 */
int CheckSubgrid(Cell sud[][SIZE],int n,int m);

/*
 *   Description: check if the specific cell in has a unique possibilty
 *   in its row, if so- set its value according to this possibity
 *	-------------------------------------------------------
 *   sud[][]: 2-dim array contains the sudoku puzzle
 *   n: row index to check
 *   m: col index to check
 *	-------------------------------------------------------
 *   returns: 1 if cell's value has been changed, 0 if not
 */
int SetIfUniqueInRow(Cell sud[][SIZE],int n,int m);

/*
 *   Description: check if the specific cell in has a unique possibilty
 *   in its col, if so- set its value according to this possibity
 *	-------------------------------------------------------
 *   sud[][]: 2-dim array contains the sudoku puzzle
 *   n: row index to check
 *   m: col index to check
 *	-------------------------------------------------------
 *   returns: 1 if cell's value has been changed, 0 if not
 */
int SetIfUniqueInCol(Cell sud[][SIZE],int n,int m);

/*
 *   Description: check if the specific cell in has a unique possibilty
 *   in its box, if so- set its value according to this possibity
 *	-------------------------------------------------------
 *   sud[][]: 2-dim array contains the sudoku puzzle
 *   n: row index to check
 *   m: col index to check
 *	-------------------------------------------------------
 *   returns: 1 if cell's value has been changed, 0 if not
 */
int SetIfUniqueInSubgrid(Cell sud[][SIZE],int n,int m);

/*
 *   Description: initilize the poss[] array of a Cell object
 *	for an empty cell -  set pos[1-9] as valid possbilties for this cell.
 *	set number of possbilities pos[0]=9
 *	for not an empty cell -  set pos[value] as the only valid possbilty for this cell.
 *	set number of possbilities pos[0]=1
 *	-------------------------------------------------------
 *   cell: pointer of the Cell type object
 *	-------------------------------------------------------
 *   returns: none
 */
void InitialPossArray(Cell* poss);

/*
 *   Description: return char the using cell's poss[] array
 *	-------------------------------------------------------
 *   cell: pointer of the Cell type object
 *	-------------------------------------------------------
 *   returns: char
 */
char GetLastPoss(Cell* cell);

#endif
