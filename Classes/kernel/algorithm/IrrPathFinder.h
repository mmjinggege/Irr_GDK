#ifndef _IRRPATHFINDER_H_
#define _IRRPATHFINDER_H_

#include "IrrMarcos.h"
#include <memory.h> 



#define ASNL_ADDOPEN		0
#define ASNL_STARTOPEN		1
#define ASNL_DELETEOPEN		2
#define ASNL_ADDCLOSED		3

#define ASNC_INITIALADD		0
#define ASNC_OPENADD_UP		1
#define ASNC_OPENADD		2
#define ASNC_CLOSEDADD_UP	3
#define ASNC_CLOSEDADD		4
#define ASNC_NEWADD			5



namespace irr_algorithm
{
	class IrrPathNode
	{
	public:
		IrrPathNode(int a = -1,int b = -1)
			: x(a), y(b), number(0), numchildren(0) 
		{
			parent = next = 0; dataptr = 0;
			memset(children, 0, sizeof(children));
		}

		int				f,g,h;			// Fitness, goal, heuristic.
		int				x,y;			// Coordinate position
		int				numchildren;
		int				number;			// x*m_iRows+y
		IrrPathNode*    parent;
		IrrPathNode*    next;			// For Open and Closed lists
		IrrPathNode*    children[8];	// Assumes square tiles
		void*			dataptr;		// Associated data
	};

	struct IrrAStack 
	{
		IrrPathNode	 *data;
		IrrAStack *next;
	};

	typedef int(*_asFunc)(IrrPathNode *, IrrPathNode *, int, void *);


	typedef std::list<IrrPathNode*> PathNodeList;
	
	class IrrPathFinder {
	public:
		//////////////////////////////////////////////////////////////////////////
		static const char DIRECTION[8][2];
		enum
		{
			DIR_N,//N
			DIR_S,//S
			DIR_W,//W
			DIR_E,//E
			DIR_NW,//NW
			DIR_NE,//NE
			DIR_SW,//SW
			DIR_SE,//SE
			DIR_COUNT
		};
		//////////////////////////////////////////////////////////////////////////
		IrrPathFinder();
		~IrrPathFinder();

		_asFunc	 udCost;			// Called when cost value is need
		_asFunc  udValid;			// Called to check validity of a coordinate
		_asFunc  udNotifyChild;		// Called when child is added/checked (LinkChild)
		_asFunc	 udNotifyList;		// Called when node is added to Open/Closed list

		void	*m_pCBData;			// Data passed back to callback functions
		void	*m_pNCData;			// Data passed back to notify child functions

		bool	GeneratePath(int, int, int, int);
		PathNodeList findPath(int,int,int,int);
		int		Step();
		void	StepInitialize(int, int, int, int);
		void	SetRows(int r)		 { m_iRows = r;    }
		void	Reset() { m_pBest = NULL; }

		IrrPathNode	*GetBestNode() { return m_pBest; }

		static int jugdeDirection(int dx,int dy);

		//default valid and cost function you can replace these functions
		static int AS_Valid(IrrPathNode *, IrrPathNode *, int, void *);
		static int AS_Cost(IrrPathNode *, IrrPathNode *, int, void *);
		//
		//static int AS_Valid_Inner(IrrPathNode *, IrrPathNode *, int, void *);
		
		//normal judge
		static const int ASTAR_ALL = 0x0680;
		//ignore diagonal
		static const int ASTAR_IGNORE_DIAGONAL = 0x0681;
		//ignore sharp turn
		static const int ASTAR_IGNORE_SHARP_TRUN = 0x0682;
		static int ASTAR_MODE;
	protected:
		int		m_iRows;			// Used to calculate node->number
		int		m_iSX, m_iSY, m_iDX, m_iDY, m_iDNum;

		IrrPathNode	*m_pOpen;			// The open list
		IrrPathNode	*m_pClosed;			// The closed list
		IrrPathNode *m_pBest;			// The best node
		IrrAStack*	m_pStack;			// Propagation stack

		// Functions.
		void	AddToOpen(IrrPathNode *);
		void	ClearNodes();
		void	CreateChildren(IrrPathNode *);
		void	LinkChild(IrrPathNode *, IrrPathNode *);
		void	UpdateParents(IrrPathNode *);

		// Stack Functions.
		void	Push(IrrPathNode *);
		IrrPathNode *Pop();

		IrrPathNode *CheckList(IrrPathNode *, int);
		IrrPathNode	*GetBest();

		// Inline functions.
		inline int Coord2Num(int x, int y) { return x * m_iRows + y; }
		inline int udFunc(_asFunc, IrrPathNode *, IrrPathNode *, int, void *);
	};
}

#endif	_IRRPATHFINDER_H_