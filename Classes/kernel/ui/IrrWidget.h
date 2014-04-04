#ifndef _IRRWIDGET_H_
#define _IRRWIDGET_H_

#include "IrrNode.h"
#include "IrrTypeDef.h"
#include "IrrUIEvent.h"
#include "IrrGeom.h"
#include "IrrGraphic.h"

using namespace irr_core;
using namespace irr_event;
using namespace irr_display;

namespace irr_ui
{
	class IHandlerUIEvent
	{
	public:
		virtual void handleDown(IrrUIEvent& event) = 0;
		virtual void handleUp(IrrUIEvent& event) = 0;
		virtual void handleClick(IrrUIEvent& event) = 0;
		virtual void handleMoveIn(IrrUIEvent& event) = 0;
		virtual void handleMove(IrrUIEvent& event) = 0;
		virtual void handleMoveOut(IrrUIEvent& event) = 0;
	};
	

	class IrrWidget : public IrrNode,public IHandlerUIEvent
	{
	public:
		static IrrWidget* create(const char* texture,bool isPlist = false);
	public:
		IrrWidget(void);
		virtual ~IrrWidget(void);
		virtual void setActivie(bool val);
		bool isActivie() {return m_bIsActive;}
		IrrRect getChildRect();
		
		void setWidgetParent(IrrWidget* parent);
		IrrWidget* getWidgetParent();
		void setName(IrrString& name);
		IrrString& getName();

		void setBackgrondColor(IrrColor Color);
		IrrColor& getBackgroundColor();

		virtual void setTouchable(bool var);
		bool isTouchable() const;

		IrrVector2D convertToNodeSpace(const IrrVector2D& pt);
//////////////////////////////////////////////////////////////////////////
		virtual void handleDown( IrrUIEvent& event );
		virtual void handleUp( IrrUIEvent& event );
		virtual void handleClick( IrrUIEvent& event );
		virtual void handleMoveIn( IrrUIEvent& event );
		virtual void handleMove( IrrUIEvent& event );
		virtual void handleMoveOut( IrrUIEvent& event );
		
		//draw function
		virtual void render(IrrGraphic* pGraphic);
	private:		
		bool init(const char* texture,bool isPlist = false);
	protected:
		bool m_bIsActive;
		IrrVector2D m_Pos;
		bool m_bDirty;
		IrrWidget* m_pWidgetParent;
		IrrString m_Name;
		IrrColor m_backgroundColor;

		bool m_bIsTouchable;
		bool m_bSwallowsTouches;
	};
}

#endif	//_IRRWIDGET_H_