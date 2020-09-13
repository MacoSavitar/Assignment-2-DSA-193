#ifndef _definition_h_
#include "defs.h"
#define _definition_h_
#endif

//your code should be after that directive
//Get key and level
//////////////////
struct Trunk
{
	Trunk *prev;
	string str;
	Trunk(Trunk *prev, string str)
	{
		this->prev = prev;
		this->str = str;
	}
};
void showTrunks(Trunk *p)
{
	if (p == NULL)
		return;
	showTrunks(p->prev);
	cout << p->str;
}
void displayTree(KnightTree *pTree, Trunk *prev, bool isLeft)
{
	if (pTree == NULL)
		return;
	string prev_str = "	";
	Trunk *trunk = new Trunk(prev, prev_str);
	displayTree(pTree->pLeftChild, trunk, true);
	if (!prev)
		trunk->str = "---";
	else if (isLeft)
	{
		trunk->str = ".---";
		prev_str = "	|";
	}
	else
	{
		trunk->str = "`---";
		prev->str = prev_str;
	}
	showTrunks(trunk);
	cout << pTree->key << "_" << pTree->level << endl;
	if (prev)
		prev->str = prev_str;
	trunk->str = "	|";
	displayTree(pTree->pRightChild, trunk, false);
}
// void displayTree(KnightTree *pTree, int n)
// {
// 	if (pTree == NULL)
// 		cout << "NULL ";
// 	else
// 	{
// 		if (pTree->key == 0)
// 			cout << "000_" << pTree->level;
// 		else if (pTree->key < 10)
// 			cout << "00" << pTree->key << "_" << pTree->level;
// 		else if (pTree->key < 100)
// 			cout << "0" << pTree->key << "_" << pTree->level;
// 		else
// 			cout << pTree->key << "_" << pTree->level;
// 		cout << "(";
// 		displayTree(pTree->pLeftChild, ++n);
// 		displayTree(pTree->pRightChild, ++n);
// 		cout << ")";
// 	}
// }
/////////////////
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
		cout << "Insert to BST success!\n";
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
//Xóa node trong cây BST
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
			cout << "Delete from BST success!\n";
			DltPtr = pKnight;
			pKnight = pKnight->pRightChild;
			delete DltPtr;
			return true;
		}
		else if (pKnight->pRightChild == NULL)
		{
			cout << "Delete from BST success!\n";
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
//Duyệt NLR
void NLR(KnightTree *pTree, int *ListKnight, int &ListCount)
{
	if (pTree)
	{
		ListKnight[ListCount] = pTree->key * 10 + pTree->level;
		ListCount += 1;
		NLR(pTree->pLeftChild, ListKnight, ListCount);
		NLR(pTree->pRightChild, ListKnight, ListCount);
	}
}
//Duyệt LNR
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
//Duyệt RNL
void RNL(KnightTree *pTree, int *ListKnight, int &ListCount)
{
	if (pTree != NULL)
	{
		RNL(pTree->pRightChild, ListKnight, ListCount);
		ListKnight[ListCount] = pTree->key * 10 + pTree->level;
		ListCount += 1;
		RNL(pTree->pLeftChild, ListKnight, ListCount);
	}
}
//Lấy chiều cao của cây
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
//Lấy số lượng node lá
int getLeaf(KnightTree *pKnight)
{
	if (pKnight == NULL)
		return 0;
	if (pKnight->pLeftChild == NULL && pKnight->pRightChild == NULL)
		return 1;
	else
		return getLeaf(pKnight->pLeftChild) + getLeaf(pKnight->pRightChild);
}
//Xóa node lá
void deleteLeaf(KnightTree *&pKnight)
{
	if (pKnight->pLeftChild == NULL && pKnight->pRightChild == NULL)
	{
		cout << "Delete leaf success!\n";
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
//Đếm số node của cây
int numberOfNode(KnightTree *pKnight)
{
	if (pKnight == NULL)
		return 0;
	else
	{
		return numberOfNode(pKnight->pLeftChild) + numberOfNode(pKnight->pRightChild) + 1;
	}
}
//Kiểm tra cây hoàn thiện
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
	int l = getHeight(pKnight->pLeftChild);
	int r = getHeight(pKnight->pRightChild);
	return l - r;
}
KnightTree *rrRotate(KnightTree *pKnight)
{
	cout << "Rotate Right\n";
	KnightTree *T1;
	T1 = pKnight->pRightChild;
	pKnight->pRightChild = T1->pLeftChild;
	T1->pLeftChild = pKnight;
	return (T1);
}

KnightTree *llRotate(KnightTree *pKnight)
{
	cout << "Rotate Left\n";
	// KnightTree *T1;
	// T1 = pKnight->pLeftChild;
	// pKnight->pLeftChild = T1->pRightChild;
	// T1->pRightChild = pKnight;
	KnightTree *T1 = pKnight->pLeftChild;
	KnightTree *T2 = T1->pRightChild;
	T1->pRightChild = pKnight;
	pKnight->pLeftChild = T2;
	return T1;
}

KnightTree *rlRotate(KnightTree *pKnight)
{
	KnightTree *T1;
	T1 = pKnight->pRightChild;
	pKnight->pRightChild = llRotate(T1);
	return (rrRotate(pKnight));
}

KnightTree *lrRotate(KnightTree *pKnight)
{
	KnightTree *T1;
	T1 = pKnight->pLeftChild;
	pKnight->pLeftChild = rrRotate(T1);
	return (llRotate(pKnight));
}

KnightTree *autoBalance(KnightTree *pKnight)
{
	int balance = getBalance(pKnight);
	if (balance > 1)
	{
		if (getBalance(pKnight->pLeftChild) > 0)
			pKnight = llRotate(pKnight);
		else
			pKnight = lrRotate(pKnight);
	}
	else if (balance < -1)
	{
		if (getBalance(pKnight->pRightChild) > 0)
			pKnight = rlRotate(pKnight);
		else
			pKnight = rrRotate(pKnight);
	}
	return pKnight;
}

KnightTree *insertAVL(KnightTree *pKnight, int key, int level)
{
	if (pKnight == NULL)
	{
		pKnight = initNode(key, level);
		cout << "Insert " << key << " to AVL success!\n";
		return pKnight;
	}
	else if (key < pKnight->key)
	{
		pKnight->pLeftChild = insertAVL(pKnight->pLeftChild, key, level);
		pKnight = autoBalance(pKnight);
	}
	else if (key > pKnight->key)
	{
		pKnight->pRightChild = insertAVL(pKnight->pRightChild, key, level);
		pKnight = autoBalance(pKnight);
	}
	return pKnight;
}

KnightTree *deleteAVL(KnightTree *pKnight, int key)
{
	if (pKnight == NULL)
		return pKnight;
	if (key < pKnight->key)
		pKnight->pLeftChild = deleteAVL(pKnight->pLeftChild, key);
	else if (key > pKnight->key)
		pKnight->pRightChild = deleteAVL(pKnight->pRightChild, key);
	else
	{
		if (pKnight->pLeftChild == NULL || pKnight->pRightChild == NULL)
		{
			KnightTree *temp = pKnight->pLeftChild ? pKnight->pLeftChild : pKnight->pRightChild;
			if (temp == NULL)
			{
				temp = pKnight;
				pKnight = NULL;
			}
			else
				*pKnight = *temp;
			delete temp;
		}
		else
		{
			KnightTree *pWalk = pKnight->pRightChild;
			while (pWalk->pLeftChild)
				pWalk = pWalk->pLeftChild;
			pKnight->key = pWalk->key;
			pKnight->level = pWalk->level;
			pKnight->pRightChild = deleteAVL(pKnight->pRightChild, pWalk->key);
		}
	}
	if (pKnight == NULL)
		return pKnight;
	int balance = getBalance(pKnight);
	if (balance > 1 && getBalance(pKnight->pLeftChild) < 0)
	{
		return llRotate(pKnight);
	}

	if (balance < -1 && getBalance(pKnight->pLeftChild) <= 0)
	{
		return rrRotate(pKnight);
	}

	if (balance > 1 && getBalance(pKnight) < 0)
	{
		return lrRotate(pKnight);
	}

	if (balance < -1 && getBalance(pKnight->pRightChild) <= 0)
	{
		return rlRotate(pKnight);
	}
	pKnight = autoBalance(pKnight);
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
			if (ListKnight[j] / 10 < ListKnight[i] / 10)
				swap(ListKnight[j], ListKnight[i]);
		}
	}
	cout << "Sort called\n";
}
KnightTree *siege(eventList *pEvent, ringsignList *pSarumanList)
{
	KnightTree *pTree = new KnightTree;
	pTree = NULL;
	//let's save the lady
	bool isAragon = false, isLegolas = false, isGandalf = false, isGimli = false;
	bool isLurtz = false, isSaruman = false;
	bool haveNarsil, SarumanDefeat = false, isAVL = false, isBST = false, isRareKnight;
	int count = 0;
	while (pEvent)
	{
		isRareKnight = false;
		if (pTree != NULL)
			if (pTree->key == 777)
				haveNarsil = true;
			else
				haveNarsil = false;
		cout << "Run while: " << ++count << "\n";
		//1XYZL
		if (pEvent->nEventCode / 10000 == 1)
		{
			int key;
			int level;
			get(pEvent, key, level);
			if (key == 777)
			{
				isAragon = true;
				isLegolas = false;
				isGandalf = false;
				isRareKnight = true;
			}
			if (key == 888)
			{
				isAragon = false;
				isLegolas = true;
				isGandalf = false;
				isRareKnight = true;
			}
			if (key == 999)
			{
				isAragon = false;
				isLegolas = false;
				isGandalf = true;
				isRareKnight = true;
			}
			if (key == 000)
			{
				isGimli = true;
			}
			if (isAragon && isRareKnight)
			{
				cout << "Aragon is Leader----List is NLR\n";
				int ListKnight[1000], ListCount = 0;
				NLR(pTree, ListKnight, ListCount);
				for (int i = 0; i < ListCount; i++)
					cout << ListKnight[i] / 10 << " ";
				cout << endl;
				KnightTree *pNew = new KnightTree;
				pNew = initNode(key, level);
				pTree = pNew;
				for (int i = 0; i < ListCount; i++)
					insertBST(pTree, ListKnight[i] / 10, ListKnight[i] % 10);
				isBST = true;
				isAVL = false;
				//
				displayTree(pTree, NULL, false);
				cout << "\n";
			}
			if (isLegolas && isRareKnight)
			{
				cout << "Legolas is Leader----List is LNR\n";
				int ListKnight[1000], ListCount = 0;
				LNR(pTree, ListKnight, ListCount);
				ListKnight[ListCount] = key * 10 + level;
				ListCount += 1;
				sort(ListKnight, ListCount);
				for (int i = 0; i < ListCount; i++)
					cout << ListKnight[i] / 10 << " ";
				cout << endl;
				// for (int i = 0; i < ListCount; i++)
				// {
				// 	cout << ListKnight[i] << " ";
				// 	cout << endl;
				// }
				int midPos = (ListCount - 1) / 2;
				KnightTree *pNew = new KnightTree;
				pNew = initNode(ListKnight[midPos] / 10, ListKnight[midPos] % 10);
				pTree = pNew;
				for (int i = 0; i < midPos; i++)
				{
					insertBST(pTree, ListKnight[i] / 10, ListKnight[i] % 10);
				}
				for (int i = midPos + 1; i < ListCount; i++)
				{
					insertBST(pTree, ListKnight[i] / 10, ListKnight[i] % 10);
				}
				//
				displayTree(pTree, NULL, false);
				cout << "\n";
			}
			if (isGandalf && isRareKnight)
			{
				cout << "Gandalf is Leader----List is RNL\n";
				int ListKnight[1000], ListCount = 0;
				RNL(pTree, ListKnight, ListCount);
				for (int i = 0; i < ListCount; i++)
					cout << ListKnight[i] / 10 << " ";
				cout << endl;
				KnightTree *pNew = new KnightTree;
				pNew = initNode(key, level);
				pTree = pNew;
				for (int i = 0; i < ListCount; i++)
				{
					cout << "Insert " << ListKnight[i] / 10 << " to AVL" << endl;
					pTree = insertAVL(pTree, ListKnight[i] / 10, ListKnight[i] % 10);
					cout << endl;
				}
				isAVL = true;
				isBST = false;
				//
				displayTree(pTree, NULL, false);
				cout << "\n";
			}
			if (isGimli && isRareKnight)
			{
				if (!isCompleteTree(pTree))
				{
					bool isIncrease = false;
					while (isExistNode(pTree, key))
					{
						isIncrease = true;
						key++;
						if (key == 777 || key == 888)
							key++;
					}
					if (!(key == 999 && isIncrease))
					{
						KnightTree *pNew = new KnightTree;
						pNew = initNode(key, level);
						if (pTree == NULL)
							pTree = pNew;
						else
						{
							if (isAVL)
								insertAVL(pTree, pNew->key, pNew->level);
							else
								insertBST(pTree, pNew->key, pNew->level);
						}
					}
				}
			}
			if (!isRareKnight)
			{
				bool isIncrease = false;
				while (isExistNode(pTree, key))
				{
					isIncrease = true;
					key++;
					if (key == 777 || key == 888)
						key++;
				}
				if (!(key == 999 && isIncrease))
				{
					KnightTree *pNew = new KnightTree;
					pNew = initNode(key, level);
					if (pTree == NULL)
						pTree = pNew;
					else
					{
						if (isAVL)
							insertAVL(pTree, pNew->key, pNew->level);
						else
							insertBST(pTree, pNew->key, pNew->level);
					}
				}
			}
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
			if (p->level < 9)
				p->level = p->level + 1;
		}
		//-XYZL
		if (pEvent->nEventCode < 0)
		{
			int monsterKey, monsterLevel;
			get(pEvent, monsterKey, monsterLevel);
			cout << "Fight with " << monsterKey << endl;

			if (!(monsterLevel == pTree->level && isAragon && haveNarsil))
			{
				if (monsterKey == 777)
				{
					isLurtz = true;
					if (monsterLevel == getLeaf(pTree))
					{
						cout << "Horse!\n";
						while (monsterLevel <= getHeight(pTree))
							deleteLeaf(pTree);
						break;
					}
				}
				if (monsterKey == 888)
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
							if (isAVL)
								deleteAVL(pTree, p->key);
							else
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
						{
							p = pWalk;
							minDistance = abs(p->key - monsterKey);
						}
						if (pWalk->key < monsterKey)
							pWalk = pWalk->pRightChild;
						else
							pWalk = pWalk->pLeftChild;
					}
					cout << p->key << " Fight\n";
					if (p->level < monsterLevel)
					{
						cout << "lose\n";
						if (p->key == 999)
						{
							isGandalf = false;
							isAVL = false;
						}
						if (isAVL)
							deleteAVL(pTree, p->key);
						else
							deleteNodeBST(pTree, p);
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
		cout << "Final Tree: \n";
		displayTree(pTree, NULL, false);
		cout << "\n";
		if (isAVL)
			cout << "Is AVL tree\n";
		else
			cout << "Is BST tree\n";
		pEvent = pEvent->pNext;
	}
	return pTree;
}

//your code should be before that directive