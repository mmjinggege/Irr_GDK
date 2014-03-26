#ifndef _IRRTOUCHNODE_H_
#define _IRRTOUCHNODE_H_

#include "IrrMarcos.h"
#include "IrrGeom.h"

using namespace irr_core;

namespace irr_display
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
	//IrrNode
	class IrrNode : public CCNode
	{
	public:
		IrrNode(void);
		virtual ~IrrNode(void);
	public:
		virtual void onEnter();
		virtual void setPosition(float x, float y);
		virtual void setPosition(const IrrVector2D &position);
		IrrVector2D getOrigin();
		virtual void setRect(IrrRect& rect);
		IrrRect getRect() const;

		void updateLocation(float offsetX,float offsetY);
		void updateLocation(IrrVector2D& postion);

		virtual void setDimensions(IrrSize& size);
		virtual void setDimensions(float width,float height);
		IrrSize& getDimensions();

		inline void setSwallowsTouchesFlag(bool bFlag) {m_bSwallowsTouches = bFlag;}
		inline bool getSwallowsTouchesFlag() {return m_bSwallowsTouches;}

	protected:
		IrrRect m_Rect;
	private:
		bool m_bSwallowsTouches;
	};

	typedef void (CCObject::*Irr_GUI_SEL_ClickEvent)(CCObject*);
#define irr_gui_clickselector(_SELECTOR)  (Irr_GUI_SEL_ClickEvent)(&_SELECTOR)

	typedef void (CCObject::*Irr_GUI_SEL_ClickToggleEvent)(CCObject*,int index);
#define irr_gui_clickToggleselector(_SELECTOR)  (Irr_GUI_SEL_ClickToggleEvent)(&_SELECTOR)
}

#endif	//_IRRTOUCHNODE_H_