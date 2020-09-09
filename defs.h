#ifndef _defs_h_
#define _defs_h_

#include <stdio.h>
#include <math.h>
#include <iostream>
#include <iomanip>
using namespace std;

struct ringsignList  
{
	int nRingsign; 
	ringsignList* pNext;
};

struct eventList 
{
	int nEventCode; 
	eventList* pNext;
};

struct KnightTree 
{
	int key;
	int level; 
	int balance;			//will be used in AVL only, and be ignored in other cases.
	KnightTree* pLeftChild;
	KnightTree* pRightChild;
};

KnightTree* siege(eventList* pEvent, ringsignList* pSarumanList);

#endif
