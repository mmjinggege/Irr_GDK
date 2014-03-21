#ifndef _IRRGUI_H_
#define _IRRGUI_H_

#include "IrrMarcos.h"
#include "IrrContainer.h"
#include "IrrUIEvent.h"

using namespace irr_event;

namespace irr_ui
{	

	class IrrGui : public IrrContainer,public CCTouchDelegate
	{
	public:
		static const int MIN_MOVE_DISTANCE = 30;
	public:
		IrrGui(IrrSize size);
		IrrGui(float width,float height);
		~IrrGui(void);
		void setGuiContentSize(float width,float height);
	public:
		//////////////////////////////////////////////////////////////////////////
		//CCTouchDelegate
		bool ccTouchBegan(CCTouch *pTouch, CCEvent *pEvent);
		void ccTouchMoved(CCTouch *pTouch, CCEvent *pEvent);
		void ccTouchEnded(CCTouch *pTouch, CCEvent *pEvent);
		void ccTouchCancelled(CCTouch *pTouch, CCEvent *pEvent);
		//////////////////////////////////////////////////////////////////////////
		virtual void DispatchUIEvent(IrrUIEvent& event); 
	private:
		IrrVector2D m_DownPos;
		IrrSize m_GuiSize;
	};
}

#endif	//_IRRGUI_H_