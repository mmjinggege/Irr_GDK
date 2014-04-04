#include "IrrPathFinder.h"

namespace irr_algorithm
{

	int IrrPathFinder::ASTAR_MODE = IrrPathFinder::ASTAR_IGNORE_SHARP_TRUN;

	const char IrrPathFinder::DIRECTION[8][2] = 
	{

		{0,1},//N
		{0,-1},//S
		{-1,0},//W
		{1,0},//E
		{-1,1},//NW
		{1,1},//NE
		{-1,-1},//SW
		{1,-1}//SE	
	};

	IrrPathFinder::IrrPathFinder()
	{
		m_pOpen = m_pClosed = NULL;
		m_pStack = NULL;
		m_pBest = NULL;

		udCost = NULL;
		udValid = NULL;
		udNotifyChild = NULL;
		udNotifyList = NULL;
	}

	IrrPathFinder::~IrrPathFinder()
	{
		ClearNodes();
	}


	PathNodeList IrrPathFinder::findPath( int sx, int sy, int dx, int dy )
	{
		PathNodeList pathList;
		bool ret = GeneratePath(sx,sy,dx,dy);
		if(ret)
		{
 			IrrPathNode * pNode = GetBestNode();
 			if (pNode)
			{
 				while(NULL != pNode)
 				{
					/*ptTemp = m_pMap->getGLPosForTileXY(ccp(pNode->x,pNode->y));*/
 					pathList.push_front(pNode);
					pNode = pNode->parent;
 				}
// 				{//handle back movement if current position is the nearer one
// 					CCPoint ptCurrent = startPt;
// 					CCPoint ptStart   = path.front();
// 					CCPoint ptEnd     = *path.rbegin();
// 					if (ptCurrent.getDistanceSq(ptEnd) < ptStart.getDistanceSq(ptEnd))
// 					{
// 						path.pop_front();
// 						path.push_front(ptCurrent);
// 					}
// 				}
			}
		}
		return pathList;
	}


	bool IrrPathFinder::GeneratePath( int sx, int sy, int dx, int dy )
	{
		StepInitialize(sx, sy, dx, dy);

		int retval = 0;
		while (retval == 0) 
		{
			retval = Step();
		}
		if (retval == -1 || !m_pBest)
		{
			m_pBest = NULL;
			return false;
		}
		return true;
	}

	int IrrPathFinder::Step()
	{
		if (!(m_pBest = GetBest()))
			return -1;
		if (m_pBest->number == m_iDNum) 
			return 1;
		CreateChildren(m_pBest);
		return 0;
	}

	void IrrPathFinder::StepInitialize(int sx, int sy, int dx, int dy)
	{
		ClearNodes();

		m_iSX = sx; m_iSY = sy; m_iDX = dx; m_iDY = dy;
		m_iDNum = Coord2Num(dx,dy);
		IrrPathNode *temp = new IrrPathNode(sx, sy);
		temp->g = 0;
		temp->h = abs(dx-sx) + abs(dy-sy);
		temp->f = temp->g + temp->h;
		temp->number = Coord2Num(sx, sy);

		m_pOpen = temp;

		udFunc(udNotifyList, NULL, m_pOpen, ASNL_STARTOPEN, m_pNCData);
		udFunc(udNotifyChild, NULL, temp, 0, m_pNCData);
	}

	int IrrPathFinder::jugdeDirection( int dx,int dy )
	{
		int ret = DIR_COUNT;
		switch(dx)
		{
		case 0:
			{
				if (dy == 1)
				{
					ret = DIR_N;
				}
				else if (dy == -1)
				{
					ret = DIR_S;
				}
				break;
			}
		case 1:
			{
				if (dy == 0)
				{
					ret = DIR_E;
				}
				else if (dy == 1)
				{
					ret = DIR_NE;
				}
				else if (dy == -1)
				{
					ret = DIR_SE;
				}
				break;
			}
		case -1:
			{
				if (dy == 0)
				{
					ret = DIR_W;
				}
				else if (dy == 1)
				{
					ret = DIR_NW;
				}
				else if (dy == -1)
				{
					ret = DIR_SW;
				}
				break;
			}
		}
		return ret;
	}


	int IrrPathFinder::AS_Valid(IrrPathNode *parent, IrrPathNode *node, int data, void *pointer)
	{
		return 1;
	}

	int IrrPathFinder::AS_Cost( IrrPathNode *parent, IrrPathNode *node, int data, void *pointer)
	{
		int ret = 1;
		//////////////////////////////////////////////////////////////////////////
		int iDir = IrrPathFinder::jugdeDirection(node->x - parent->x,node->y - parent->y);
		if (iDir >= IrrPathFinder::DIR_NW)
		{
			ret = 2;
		}
		return ret;
	}

	void IrrPathFinder::AddToOpen( IrrPathNode * addnode)
	{
		IrrPathNode *node = m_pOpen;
		IrrPathNode *prev = NULL;

		if (!m_pOpen)
		{
			m_pOpen = addnode;
			m_pOpen->next = NULL;

			udFunc(udNotifyList, NULL, addnode, ASNL_STARTOPEN, m_pNCData);

			return;
		}

		while(node) {
			if (addnode->f > node->f)
			{
				prev = node;
				node = node->next;
			} 
			else 
			{
				if (prev)
				{
					prev->next = addnode;
					addnode->next = node;
					udFunc(udNotifyList, prev, addnode, ASNL_ADDOPEN, m_pNCData);
				} 
				else
				{
					IrrPathNode *temp = m_pOpen;
					m_pOpen = addnode;
					m_pOpen->next = temp;
					udFunc(udNotifyList, temp, addnode, ASNL_STARTOPEN, m_pNCData);
				}
				return;
			}
		}

		prev->next = addnode;
		udFunc(udNotifyList, prev, addnode, ASNL_ADDOPEN, m_pNCData);
	}

	void IrrPathFinder::ClearNodes()
	{
		IrrPathNode *temp = NULL, *temp2 = NULL;
		if (m_pOpen)
		{
			while (m_pOpen) 
			{
				temp = m_pOpen->next;
				delete m_pOpen;
				m_pOpen = temp;
			}
		}
		if (m_pClosed) 
		{
			while (m_pClosed) 
			{
				temp = m_pClosed->next;
				delete m_pClosed;
				m_pClosed = temp;
			}
		}
	}

	void IrrPathFinder::CreateChildren( IrrPathNode * node)
	{
		IrrPathNode temp;
		int x = node->x, y = node->y;

		for (int i=-1;i<2;i++)
		{
			for (int j=-1;j<2;j++) 
			{
				temp.x = x+i;
				temp.y = y+j;
				if (i == 0 && j == 0 || !udFunc(udValid, node, &temp, 0, m_pCBData)) continue;
				LinkChild(node, &temp);
			}
		}
	}

	void IrrPathFinder::LinkChild( IrrPathNode * node, IrrPathNode *temp )
	{
		int x = temp->x;
		int y = temp->y;
		int g = node->g + udFunc(udCost, node, temp, 0, m_pCBData);
		int num = Coord2Num(x,y);

		IrrPathNode *check = NULL;

		if (check = CheckList(m_pOpen, num), check) 
		{
			node->children[node->numchildren++] = check;
			// A better route found, so update
			// the node and variables accordingly.
			if (g < check->g) 
			{
				check->parent = node;
				check->g = g;
				check->f = g + check->h;
				udFunc(udNotifyChild, node, check, 1, m_pNCData);
			}
			else 
			{
				udFunc(udNotifyChild, node, check, 2, m_pNCData);
			}
		}
		else if (check = CheckList(m_pClosed, num), check) 
		{
			node->children[node->numchildren++] = check;
			if (g < check->g) {
				check->parent = node;
				check->g = g;
				check->f = g + check->h;

				udFunc(udNotifyChild, node, check, 3, m_pNCData);

				// The fun part...
				UpdateParents(check);
			}
			else
			{
				udFunc(udNotifyChild, node, check, 4, m_pNCData);
			}
		} 
		else
		{
			IrrPathNode *newnode = new IrrPathNode(x,y);
			newnode->parent = node;
			newnode->g = g;
			newnode->h = abs(x-m_iDX) + abs(y-m_iDY);
			newnode->f = newnode->g + newnode->h;
			newnode->number = Coord2Num(x,y);

			AddToOpen(newnode);
			node->children[node->numchildren++] = newnode;
			udFunc(udNotifyChild, node, newnode, 5, m_pNCData);
		}
	}

	void IrrPathFinder::UpdateParents( IrrPathNode * node)
	{
		int g = node->g, c = node->numchildren;

		IrrPathNode *kid = NULL;
		for (int i=0;i<c;i++)
		{
			kid = node->children[i];
			if (g+1 < kid->g)
			{
				kid->g = g+1;
				kid->f = kid->g + kid->h;
				kid->parent = node;

				Push(kid);
			}
		}

		IrrPathNode *parent;
		while (m_pStack)
		{
			parent = Pop();
			c = parent->numchildren;
			for (int i=0;i<c;i++) 
			{
				kid = parent->children[i];

				if (parent->g+1 < kid->g)
				{
					kid->g = parent->g + udFunc(udCost, parent, kid, 0, m_pCBData);
					kid->f = kid->g + kid->h;
					kid->parent = parent;

					Push(kid);
				}
			}
		}
	}


	void IrrPathFinder::Push( IrrPathNode * node)
	{
		if (!m_pStack)
		{
			m_pStack = new IrrAStack;
			m_pStack->data = node;
			m_pStack->next = NULL;
		} 
		else
		{
			IrrAStack *temp = new IrrAStack;

			temp->data = node;
			temp->next = m_pStack;
			m_pStack = temp;
		}
	}

	IrrPathNode * IrrPathFinder::Pop()
	{
		IrrPathNode *data = m_pStack->data;
		IrrAStack *temp = m_pStack;

		m_pStack = temp->next;
		delete temp;
		return data;
	}

	IrrPathNode * IrrPathFinder::CheckList( IrrPathNode * node, int num)
	{
		while (node) 
		{
			if (node->number == num)
				return node;
			node = node->next;
		}
		return NULL;
	}


	IrrPathNode	* IrrPathFinder::GetBest()
	{
		if (!m_pOpen) return NULL;

		IrrPathNode *temp = m_pOpen, *temp2 = m_pClosed;
		m_pOpen = temp->next;

		udFunc(udNotifyList, NULL, temp, ASNL_DELETEOPEN, m_pNCData);

		m_pClosed = temp;
		m_pClosed->next = temp2;

		udFunc(udNotifyList, NULL, m_pClosed, ASNL_ADDCLOSED, m_pNCData);

		return temp;
	}


	int IrrPathFinder::udFunc(_asFunc func, IrrPathNode *param1, IrrPathNode *param2, int data, void *cb)
	{
		if (func) return func(param1, param2, data, cb);
		return 1;
	}

}