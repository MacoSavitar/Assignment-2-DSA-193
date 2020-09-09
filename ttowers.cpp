#ifndef _definition_h_
#include "defs.h"
#define _definition_h_
#endif

//your code should be after that directive
//Get key and level
void get(eventList *pEvent, int &key, int &level)
{
	if (pEvent->nEventCode < 0)
	{
		key = abs((pEvent->nEventCode) / 10);
		level = abs(pEvent->nEventCode % 10);
	}
	else
	{
		key = abs((pEvent->nEventCode % 10000) / 10);
		level = abs(pEvent->nEventCode % 10);
	}
}
//Khởi tạo Node mới
KnightTree *initNode(int key, int level)
{
	KnightTree *pKnight = new KnightTree;
	pKnight->key = key;
	pKnight->level = level;
	pKnight->balance = 0;
	pKnight->pLeftChild = NULL;
	pKnight->pRightChild = NULL;
	return pKnight;
}
//Chèn Node vô BST
void insertBST(KnightTree *pKnight, int key, int level)
{
	if (pKnight == NULL)
	{
		pKnight = initNode(key, level);
	}
	else
	{
		KnightTree *parent;
		KnightTree *pWalk = pKnight;
		while (pWalk)
		{
			parent = pWalk;
			if (key < pWalk->key)
				pWalk = pWalk->pLeftChild;
			else
				pWalk = pWalk->pRightChild;
		}
		if (key < parent->key)
			parent->pLeftChild = initNode(key, level);
		else
		{
			parent->pRightChild = initNode(key, level);
		}
	}
}
//Kiểm tra Node có bị trùng key
bool isExistNode(KnightTree *pKnight, int key)
{
	KnightTree *pWalk = pKnight;
	while (pWalk)
	{
		if (pWalk->key == key)
			return true;
		else
		{
			if (pWalk->key < key)
				pWalk = pWalk->pRightChild;
			else
				pWalk = pWalk->pLeftChild;
		}
	}
	return false;
}

bool deleteNodeBST(KnightTree *&pKnight, KnightTree *pDlt)
{
	if (pKnight == NULL)
		return false;
	if (pDlt->key < pKnight->key)
		return deleteNodeBST(pKnight->pLeftChild, pDlt);
	else if (pDlt->key > pKnight->key)
		return deleteNodeBST(pKnight->pRightChild, pDlt);
	else
	{
		KnightTree *DltPtr;
		if (pKnight->pLeftChild == NULL)
		{
			DltPtr = pKnight;
			pKnight = pKnight->pRightChild;
			delete DltPtr;
			return true;
		}
		else if (pKnight->pRightChild == NULL)
		{
			DltPtr = pKnight;
			pKnight = pKnight->pLeftChild;
			delete DltPtr;
			return true;
		}
		else
		{
			DltPtr = pKnight->pRightChild;
			while (DltPtr->pLeftChild)
				DltPtr = DltPtr->pLeftChild;
			pKnight->key = DltPtr->key;
			pKnight->level = DltPtr->level;
			return deleteNodeBST(pKnight->pRightChild, DltPtr);
		}
	}
}
void NLR(KnightTree *pTree, int *ListKnight, int &ListCount)
{
	if (pTree)
	{
		ListKnight[ListCount] = pTree->key * 10 + pTree->level;
		ListCount += 1;
		NLR(pTree->pLeftChild, ListKnight, ListCount);
		NLR(pTree->pRightChild, ListKnight, ListCount);
	}
	else
		return;
}
void RNL(KnightTree *pTree, int *ListKnight, int &ListCount)
{
	if (pTree)
	{
		NLR(pTree->pRightChild, ListKnight, ListCount);
		ListKnight[ListCount] = pTree->key * 10 + pTree->level;
		ListCount += 1;
		NLR(pTree->pLeftChild, ListKnight, ListCount);
	}
	else
		return;
}
void LNR(KnightTree *pTree, int *ListKnight, int &ListCount)
{
	if (pTree)
	{
		LNR(pTree->pLeftChild, ListKnight, ListCount);
		ListKnight[ListCount] = pTree->key * 10 + pTree->level;
		ListCount += 1;
		LNR(pTree->pRightChild, ListKnight, ListCount);
	}
	else
		return;
}
int getHeight(KnightTree *pKnight)
{
	if (pKnight == NULL)
		return 0;
	else
	{
		int leftHeight = getHeight(pKnight->pLeftChild);
		int rightHeight = getHeight(pKnight->pRightChild);
		if (leftHeight > rightHeight)
			return (leftHeight + 1);
		else
			return (rightHeight + 1);
	}
}
int getLeaf(KnightTree *pKnight)
{
	if (pKnight == NULL)
		return 0;
	if (pKnight->pLeftChild == NULL && pKnight->pRightChild == NULL)
		return 1;
	else
		return getLeaf(pKnight->pLeftChild) + getLeaf(pKnight->pRightChild);
}
void deleteLeaf(KnightTree *&pKnight)
{
	if (pKnight->pLeftChild == NULL && pKnight->pRightChild == NULL)
	{
		KnightTree *pDlt = pKnight;
		pKnight = NULL;
		delete pDlt;
		return;
	}
	else if (getHeight(pKnight->pLeftChild) > getHeight(pKnight->pRightChild))
		deleteLeaf(pKnight->pLeftChild);
	else
		deleteLeaf(pKnight->pRightChild);
}
int numberOfNode(KnightTree *pKnight)
{
	if (pKnight == NULL)
		return 0;
	else
	{
		return numberOfNode(pKnight->pLeftChild) + numberOfNode(pKnight->pRightChild) + 1;
	}
}
bool isCompleteTree(KnightTree *pKnight)
{

	if (numberOfNode(pKnight) == (int)pow(2, getHeight(pKnight)) - 1)
		return true;
	else
		return false;
}
//For AVL Tree
int max(int a, int b)
{
	if (a > b)
		return a;
	return b;
}
int getBalance(KnightTree *pKnight)
{
	if (pKnight == NULL)
		return 0;
	return getHeight(pKnight->pLeftChild) - getHeight(pKnight->pRightChild);
}
KnightTree *rotateRight(KnightTree *pKnight)
{
	//cout << "Rotate Right\n";
	KnightTree *T1 = pKnight->pLeftChild;
	KnightTree *T2 = T1->pRightChild;
	T1->pRightChild = pKnight;
	pKnight->pLeftChild = T2;
	T1->balance = getBalance(T1);
	pKnight->balance = getBalance(pKnight);
	return T1;
}
KnightTree *rotateLeft(KnightTree *pKnight)
{
	//cout << "Rotate Left\n";
	KnightTree *T1 = pKnight->pLeftChild;
	KnightTree *T2 = T1->pLeftChild;
	T1->pLeftChild = pKnight;
	pKnight->pRightChild = T2;
	pKnight->balance = getBalance(pKnight);
	T1->balance = getBalance(T1);
	return T1;
}
KnightTree *insertAVL(KnightTree *pKnight, int key, int level)
{
	if (pKnight == NULL)
	{
		KnightTree *pNew = new KnightTree;
		pNew->key = key;
		pNew->level = level;
		pNew->balance = 1;
		pNew->pLeftChild = NULL;
		pNew->pRightChild = NULL;
		return pNew;
	}
	if (key < pKnight->key)
		pKnight->pLeftChild = insertAVL(pKnight->pLeftChild, key, level);
	else if (key > pKnight->key)
		pKnight->pRightChild = insertAVL(pKnight->pRightChild, key, level);
	else
		return pKnight;
	pKnight->balance = getBalance(pKnight);
	int balance = pKnight->balance;
	if (balance > 1 && key < pKnight->pLeftChild->key)
		return rotateRight(pKnight);
	if (balance < -1 && key > pKnight->pRightChild->key)
		return rotateLeft(pKnight);
	if (balance > 1 && key > pKnight->pLeftChild->key)
	{
		pKnight->pLeftChild = rotateLeft(pKnight->pLeftChild);
		return rotateRight(pKnight);
	}
	if (balance < -1 && key < pKnight->pRightChild->key)
	{
		pKnight->pRightChild = rotateRight(pKnight->pRightChild);
		return rotateLeft(pKnight);
	}
	return pKnight;
}
void swap(int &a, int &b)
{
	int temp = a;
	a = b;
	b = temp;
}
void sort(int ListKnight[], int ListCount)
{
	for (int i = 0; i < ListCount; i++)
	{
		for (int j = i; j < ListCount; j++)
		{
			if (ListKnight[i] / 10 < ListKnight[j] / 10)
				swap(ListKnight[i], ListKnight[j]);
		}
	}
}
//////////////////
void displayTree(KnightTree *pTree, int n)
{
	if (pTree == NULL)
		cout << "NULL ";
	else
	{
		if (pTree->key == 0)
			cout << "000_" << pTree->level;
		else if (pTree->key < 100)
			cout << "0" << pTree->key << "_" << pTree->level;
		else
			cout << pTree->key << "_" << pTree->level;
		cout << "(";
		displayTree(pTree->pLeftChild, ++n);
		displayTree(pTree->pRightChild, ++n);
		cout << ")";
	}
}
/////////////////
KnightTree *siege(eventList *pEvent, ringsignList *pSarumanList)
{
	KnightTree *pTree = new KnightTree;
	pTree = NULL;
	//let's save the lady
	bool isAragon = false, isLegolas = false, isGandalf = false, isGimli = false;
	bool isLurtz = false, isSaruman = false;
	bool haveNarsil = false, SarumanDefeat = false, isAVL = false;
	int count = 0;
	while (pEvent)
	{
		cout << "Run while: " << ++count << "\n";
		//1XYZL
		if (pEvent->nEventCode / 10000 == 1)
		{
			int key;
			int level;
			get(pEvent, key, level);
			if (key == 777)
				isAragon = true;
			if (key == 888)
				isLegolas = true;
			if (key == 999)
				isGandalf = true;
			if (key == 0)
				isGimli = true;
			if (isAragon)
			{
				int ListKnight[1000], ListCount = 0;
				NLR(pTree, ListKnight, ListCount);
				KnightTree *pNew = new KnightTree;
				pNew->balance = 0;
				pNew->key = key;
				pNew->level = level;
				pNew->pLeftChild = NULL;
				pNew->pRightChild = NULL;
				pTree = pNew;
				for (int i = 0; i < ListCount; i++)
					insertBST(pTree, ListKnight[i] / 10, ListKnight[i] % 10);
				isAragon = false;
			}
			else if (isLegolas)
			{
				int ListKnight[1000], ListCount = 0;
				LNR(pTree, ListKnight, ListCount);
				ListKnight[ListCount] = key * 10 + level;
				ListCount += 1;
				sort(ListKnight, ListCount);
				int midPos = (ListCount - 1) / 2;
				KnightTree *pNew = new KnightTree;
				pNew->key = ListKnight[midPos] / 10;
				pNew->level = ListKnight[midPos] % 10;
				pNew->balance = 0;
				pNew->pLeftChild = NULL;
				pNew->pRightChild = NULL;
				pTree = pNew;
				for (int i = 0; i < midPos; i++)
				{
					insertBST(pTree, ListKnight[i] / 10, ListKnight[i] % 10);
				}
				for (int i = midPos + 1; i < ListCount; i++)
				{
					insertBST(pTree, ListKnight[i] / 10, ListKnight[i] % 10);
				}
				isLegolas = false;
			}
			else
			{
				bool isIncrease = false;
				while (isExistNode(pTree, key))
				{
					isIncrease = true;
					key++;
					if (key == 777 || key == 888)
						key++;
				}
				if (key == 999 && isIncrease)
					break;
				KnightTree *pNew = new KnightTree;
				pNew->balance = 0;
				pNew->key = key;
				pNew->level = level;
				pNew->pLeftChild = NULL;
				pNew->pRightChild = NULL;
				//cout << "run";
				if (isGandalf)
				{
					isAVL = true;
					KnightTree *pWalk = pTree;
					int ListKnight[1000], ListCount = 0;
					RNL(pTree, ListKnight, ListCount);
					//KnightTree *pNew = new KnightTree;
					//delete pTree;
					//KnightTree *pTree=NULL;
					pTree = pNew;
					for (int i = 0; i < ListCount; i++)
					{
						//cout << ListKnight[i] << " ";
						pTree = insertAVL(pTree, ListKnight[i] / 10, ListKnight[i] % 10);
					}
					//cout << "\n";
				}
				else if (isGimli && isCompleteTree(pTree))
					break;
				else if (pTree == NULL)
				{
					pTree = pNew;
				}
				else
				{
					if (isAVL)
						insertAVL(pTree, pNew->key, pNew->level);
					else
						insertBST(pTree, pNew->key, pNew->level);
				}
			}
			if (pTree->key == 777)
				haveNarsil = true;
		}
		//2XYZ
		if (pEvent->nEventCode / 1000 == 2)
		{
			int ballKey = pEvent->nEventCode % 1000;
			KnightTree *pWalk = pTree, *p = pTree;
			int minDistance = abs(pTree->key - ballKey);
			while (pWalk)
			{
				//cout<<"run";
				if (abs(pWalk->key - ballKey) < minDistance)
					p = pWalk;
				if (pWalk->key < ballKey)
					pWalk = pWalk->pRightChild;
				else
					pWalk = pWalk->pLeftChild;
			}
			p->level = p->level + 1;
		}
		//-XYZL
		if (pEvent->nEventCode < 0)
		{
			int monsterKey, monsterLevel;
			get(pEvent, monsterKey, monsterLevel);
			if (isAragon && haveNarsil && monsterLevel == pTree->level)
				haveNarsil = false;
			else
			{
				//cout << "Monster key: " << monsterKey << endl;
				if (monsterKey == 777)
				{
					isLurtz = true;
					//cout << getLeaf(pTree) << endl;
					if (monsterLevel == getLeaf(pTree))
					{
						while (monsterLevel <= getHeight(pTree))
							deleteLeaf(pTree);
					}
				}
				else
				{
					if (monsterKey == 888)
						isSaruman = true;
					if (isSaruman)
					{
						while (pTree && !SarumanDefeat)
						{
							KnightTree *pWalk = pTree, *p = pTree;
							int minDistance = abs(pTree->key - monsterKey);
							while (pWalk)
							{
								//cout<<"run";
								if (abs(pWalk->key - monsterKey) < minDistance)
									p = pWalk;
								if (pWalk->key < monsterKey)
									pWalk = pWalk->pRightChild;
								else
									pWalk = pWalk->pLeftChild;
							}
							if (p->level < monsterLevel)
								deleteNodeBST(pTree, p);
							else
								SarumanDefeat = true;
						}
					}
					else
					{
						KnightTree *pWalk = pTree, *p = pTree;
						int minDistance = abs(pTree->key - monsterKey);
						while (pWalk)
						{
							//cout<<"run";
							if (abs(pWalk->key - monsterKey) < minDistance)
								p = pWalk;
							if (pWalk->key < monsterKey)
								pWalk = pWalk->pRightChild;
							else
								pWalk = pWalk->pLeftChild;
						}
						if (p->level < monsterLevel)
						{
							cout << "lose\n";
							if (isGandalf)
							{
								isGandalf = false;
								isAVL = false;
							}
							deleteNodeBST(pTree, p);
						}
					}
				}
			}
		}
		if (pEvent->nEventCode / 1000 == 3)
		{
			int GaladrielKey = pEvent->nEventCode % 1000;
			KnightTree *pWalk = pTree, *p = pTree;
			int minDistance = abs(pTree->key - GaladrielKey);
			while (pWalk)
			{
				//cout<<"run";
				if (abs(pWalk->key - GaladrielKey) < minDistance)
					p = pWalk;
				if (pWalk->key < GaladrielKey)
					pWalk = pWalk->pRightChild;
				else
					pWalk = pWalk->pLeftChild;
			}
			p->level = 9;
		}
		if (pTree == NULL)
			break;
		// displayTree(pTree, 0);
		// cout << "\n";
		pEvent = pEvent->pNext;
	}
	return pTree;
}

//your code should be before that directive