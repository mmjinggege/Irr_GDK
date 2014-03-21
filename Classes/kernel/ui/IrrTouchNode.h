#ifndef _IRRTOUCHNODE_H_
#define _IRRTOUCHNODE_H_

#include "IrrMarcos.h"
#include "IrrGeom.h"

using namespace irr_core;

namespace irr_ui
{

	typedef enum __IrrUIPriority
	{
		IRR_TOUCH_PRIORTY_LOWEST = -1000,
		IRR_TOUCH_PRIORTY_LOW = -1200,
		IRR_TOUCH_PRIORTY_NORMAL = -1500,
		IRR_TOUCH_PRIORTY_HIGH = -1800,
		IRR_TOUCH_PRIORTY_HIGHEST = -2000
	} irr_UIPriority;
	//////////////////////////////////////////////////////////////////////////
	//IrrTouchNode
	//基于可点击可视化节点
	class IrrTouchNode : public CCNodeRGBA,public CCTargetedTouchDelegate
	{
	public:
		IrrTouchNode(void);
		virtual ~IrrTouchNode(void);
		
	public:
		virtual void onEnter();
		virtual void onExit();
		virtual bool ccTouchBegan(CCTouch *pTouch, CCEvent *pEvent) = 0;
		virtual void ccTouchMoved(CCTouch *pTouch, CCEvent *pEvent) = 0;
		virtual void ccTouchEnded(CCTouch *pTouch, CCEvent *pEvent) = 0;
		virtual void ccTouchCancelled(CCTouch *pTouch, CCEvent *pEvent) = 0;

		virtual void setPosition(float x, float y);
		virtual void setPosition(const IrrVector2D &position);

		inline void setSwallowsTouchesFlag(bool bFlag) {m_bSwallowsTouches = bFlag;}
		inline bool getSwallowsTouchesFlag() {return m_bSwallowsTouches;}
		
		CREATE_PROPERTY(int,m_iPriority,Priorty);
		CREATE_PROPERTY_BY_BOOL(m_bTouchable,Touchable);
	protected:
		bool containsTouchLocation(CCTouch* touch);
	private:
		bool m_bSwallowsTouches;
	};
}

#endif	//_IRRTOUCHNODE_H_