#ifndef _IRRGUI_H_
#define _IRRGUI_H_

#include "IrrMarcos.h"
#include "IrrContainer.h"
#include "IrrUIEvent.h"
#include "IrrWidget.h"
namespace irr_core
{
	class IrrGraphic;
}

using namespace irr_core;
using namespace irr_event;

namespace irr_ui
{	
	typedef std::list<IrrWidget*> IrrWidgetTouchableList;
	typedef IrrWidgetTouchableList::iterator pIrrWidgetItor;	
	typedef IrrWidgetTouchableList::reverse_iterator pIrrWidgetReverseItor;

	inline bool sortListByRootDepth( IrrWidget* pWightLeft,  IrrWidget* pWightRight)
	{
		return pWightLeft->getRootDepth() > pWightRight->getRootDepth();
	}


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
		virtual void handleDown( IrrUIEvent& event );
		virtual void handleUp( IrrUIEvent& event );
		virtual void handleClick( IrrUIEvent& event );
		virtual void handleMoveIn( IrrUIEvent& event );
		virtual void handleMove( IrrUIEvent& event );
		virtual void handleMoveOut( IrrUIEvent& event );
//////////////////////////////////////////////////////////////////////////
		virtual void DispatchUIEvent(IrrUIEvent& event); 
//////////////////////////////////////////////////////////////////////////
		void addTouchAbleWight(IrrWidget* pWight);
		void removeTouchAbleWight(IrrWidget* pWight);
		void clearTouchAbleChildren();
		IrrWidgetTouchableList& getTouchAbleChildren();
//////////////////////////////////////////////////////////////////////////
		void selectEventWights();
	private:
		IrrWidget* checkWidget(IrrWidget* pLeft, IrrWidget* pRight);
		IrrWidget* selectCurWidget();
	private:
		IrrGraphic* m_pGraphic;
		IrrVector2D m_DownPos;

		IrrWidgetTouchableList m_TouchableWights;
		IrrWidget* m_pCurrentSelWidget;
		bool m_bIsMoved;

		IrrWidgetTouchableList m_curTouchWights;
	};
}

#endif	//_IRRGUI_H_