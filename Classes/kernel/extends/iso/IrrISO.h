#ifndef _IRRISO_H_
#define _IRRISO_H_

#include "IrrLayer.h"
#include "IrrCommon.h"

using namespace irr_base;
using namespace irr_core;
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

	
	class IrrISODelegate : public ILayerDelegate
	{
	public:
		void handleMove( IrrLayerEvent& evt );
		void handleDown( IrrLayerEvent& evt );
		void handleUp( IrrLayerEvent& evt );
		void handleClick( IrrLayerEvent& evt );
	};
	

	class IrrISO : public IrrLayer
	{
	public:
		static IrrVector3D ScreenToIso(IrrVector2D& pos);
		static IrrVector2D IsoToScreen(IrrVector3D& pos);
	public:
		IrrISO(short isoWidth,short isoHeight,short row,short col);
		~IrrISO(void);

		virtual bool init();

		IrrGridProperty* getGridProperty(short gridX,short gridY);
		IrrGridProperty** getGridPropertyList();
		void setGridProperty(short gridX,short gridY,unsigned int flag);
		void setGridProperty(short beginX,short beginY,short endX,short endY,unsigned int flag);
		void resetGridProperty(short gridX,short gridY);
		bool validateGridProperty(short gridX,short gridY,unsigned int flag);
		void setTargetMap(IrrNode* Target);
		IrrVector3D calcVector3D(IrrVector2D& pos);
		void draw();
	protected:
		//////////////////////////////////////////////////////////////////////////
		void __drawLineBorder();
		void __drawLineGrids();
		void __drawTxt();
		//////////////////////////////////////////////////////////////////////////
		bool isOverflow(short gridX,short gridY);
		void initGridPropertyArray();

		
	private:
		short m_gridCol;
		short m_gridRow;
		short m_isoWidth;
		short m_isoHeight;
		IrrGridProperty** m_GridArr;
		IrrNode* m_pTarget;
		
		IrrVector2D m_leftPoint;
		IrrVector2D m_topPoint;
		IrrVector2D m_BottomPoint;
	public:
		IrrVector3D postion3D;
		float offsetX;
		float offsetY;
	};
}


#endif	//_IRRISO_H_