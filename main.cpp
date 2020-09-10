#ifndef _definition_h_
#include "defs.h"
#define _definition_h_
#endif

//read data from input file to corresponding variables
//return 1 if successfully done, otherwise return 0
int readFile(FILE *f, eventList *&pEvent)
{
	char c = fgetc(f);
	int num, minus;

	eventList *tail = NULL;

	while (c != -1 && !feof(f))
	{
		minus = 0;
		while (c < '0' || c > '9')
		{
			if (c == '-')
				minus = 1;
			c = fgetc(f);
		}

		num = c - '0';
		c = fgetc(f);
		while (c >= '0' && c <= '9')
		{
			num = num * 10 + c - '0';
			c = fgetc(f);
		}

		if (minus)
			num = -num;

		eventList *current_event = new eventList();
		current_event->nEventCode = num;
		current_event->pNext = NULL;

		if (pEvent == NULL)
			pEvent = current_event;
		if (tail != NULL)
			tail->pNext = current_event;
		tail = current_event;
	}
	return 1;
}

// void display(KnightTree* pTree, int n)
// {
// 	cout.flush();
// 	if (pTree)
// 	{
// 		cout << setw(3) << setfill('0')<< pTree->key;
// 		cout << pTree->level;
// 		display(pTree->pLeftChild,++n);
// 		display(pTree->pRightChild,++n);
// 	}
// }

void display(KnightTree *pTree, int n)
{
	if (pTree == NULL)
		cout << "NULL ";
	else
	{
		if (pTree->key == 0)
			cout << "000_" << pTree->level;
		else if (pTree->key < 10)
			cout << "00" << pTree->key << "_" << pTree->level;
		else if (pTree->key < 100)
			cout << "0" << pTree->key << "_" << pTree->level;
		else
			cout << pTree->key << "_" << pTree->level;
		cout << "(";
		display(pTree->pLeftChild, ++n);
		display(pTree->pRightChild, ++n);
		cout << ")";
	}
}
int main(int argc, char *argv[])
{
	if (argc < 2)
		return 1;
	const char *filename = argv[1];
	FILE *f = fopen(filename, "r");
	if (f == NULL) //file not found or cannot read
	{
		printf("File not found \n");
		return 0;
	}

	eventList *pEvent = NULL;
	KnightTree *pFinalTree = NULL;

	ringsignList *pSarumanList = NULL;
	readFile(f, pEvent);
	pFinalTree = siege(pEvent, pSarumanList);
	display(pFinalTree, 0);

	return 0;
}
