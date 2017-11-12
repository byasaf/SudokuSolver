/* 
 * Name: Assaf Ben Yishay
 */ 
#ifndef _MAINH_
#define _MAINH_

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define SIZE 9
#define ROW_ERR 0
#define COL_ERR 1
#define SUB_ERR 2

typedef struct cells {
   char value;
   char poss[SIZE+1]; //first element [0] is used as counter for the possibilities left
} Cell;

#endif