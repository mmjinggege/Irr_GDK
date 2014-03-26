#ifndef _IRRISO_H_
#define _IRRISO_H_

#include "IrrObject.h"
#include "IrrCommon.h"

using namespace irr_base;
using namespace irr_core;

namespace irr_display
{
	class IrrNode;
}

using namespace irr_display;

namespace irr_extends
{
	
	typedef enum _IrrGridDef
	{
		FLAG_INDEX_NONE = 1,
		FLAG_INDEX_BLOCK,
	} Irr_GridDef;


	struct IrrGridProperty
	{
		IrrFlagIndex gridFlag;
		IrrIntList itemIds;
		IrrGridProperty()
		{
			itemIds.clear();
			gridFlag.reset();
		}
	};


	class IrrISO : public IrrObject
	{
	public:
		IrrISO(short row,short col);
		~IrrISO(void);
		IrrGridProperty* getGridProperty(short gridX,short gridY);
		IrrGridProperty** getGridPropertyList();
		void setGridProperty(short gridX,short gridY,unsigned int flag);
		void setGridProperty(short beginX,short beginY,short endX,short endY,unsigned int flag);
		void resetGridProperty(short gridX,short gridY);
		bool validateGridProperty(short gridX,short gridY,unsigned int flag);
		void setTargetMap(IrrNode* Target);
	protected:
		bool isOverflow(short gridX,short gridY);
		void initGridPropertyArray();
	private:
		short m_gridCol;
		short m_gridRow;
		IrrGridProperty** m_GridArr;
		IrrNode* m_pTarget;
	};
}


#endif	//_IRRISO_H_