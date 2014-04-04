#ifndef _IRRGUI_H_
#define _IRRGUI_H_

#include "IrrMarcos.h"
#include "IrrContainer.h"
#include "IrrUIEvent.h"

namespace irr_core
{
	class IrrGraphic;
}

using namespace irr_core;
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
		virtual void onEnter();
		virtual void onExit();
		virtual void onRender();
	public:
		//////////////////////////////////////////////////////////////////////////
		//CCTouchDelegate
		bool ccTouchBegan(CCTouch *pTouch, CCEvent *pEvent);
		void ccTouchMoved(CCTouch *pTouch, CCEvent *pEvent);
		void ccTouchEnded(CCTouch *pTouch, CCEvent *pEvent);
		void ccTouchCancelled(CCTouch *pTouch, CCEvent *pEvent);
//////////////////////////////////////////////////////////////////////////
		virtual void DispatchUIEvent(IrrUIEvent& event); 
//////////////////////////////////////////////////////////////////////////
		void addTouchAbleChild(IrrWidget* pWight);
		void removeTouchAbleChild(IrrWidget* pWight);
		void clearTouchAbleChildren();
		std::vector<IrrWidget*> getTouchAbleChildren();
	private:
		IrrGraphic* m_pGraphic;
		IrrVector2D m_DownPos;
		std::vector<IrrWidget*> m_vecTouchAbleChildern;
	};
}

#endif	//_IRRGUI_H_