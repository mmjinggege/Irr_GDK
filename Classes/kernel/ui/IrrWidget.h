#ifndef _IRRWIDGET_H_
#define _IRRWIDGET_H_

#include "IrrObject.h"
#include "IrrTypeDef.h"
#include "IrrUIEvent.h"
#include "IrrGeom.h"

using namespace irr_event;

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
	
	class IrrWidget : public IrrObject,public IHandlerUIEvent
	{
	public:
		IrrWidget(void);
		virtual ~IrrWidget(void);
		virtual void setActivie(bool val);
		bool isActivie() {return m_bIsActive;}
		void setDimensions(const IrrSize& size);
		IrrSize& getDimensions();
		virtual void setLocation(float x,float y);
		IrrRect getChildRect();

		CREATE_PROPERTY_BY_BOOL(m_bIsVisible,Visible);
		CREATE_PROPERTY(IrrUChar,m_Alpha,Alpha);
		CREATE_PROPERTY_BY_REF(IrrString,m_Name,Name);
		CREATE_PROPERTY_UNIMPLEMENT(IrrRect,m_Rect,WidgetRect);
		CREATE_PROPERTY_UNIMPLEMENT(float,m_Scale,Scale);
		CREATE_PROPERTY(IrrWidget*,m_pParent,Parent);

		IrrVector2D convertToNodeSpace(const IrrVector2D& pt);

		//////////////////////////////////////////////////////////////////////////
		virtual void handleDown( IrrUIEvent& event );
		virtual void handleUp( IrrUIEvent& event );
		virtual void handleClick( IrrUIEvent& event );
		virtual void handleMoveIn( IrrUIEvent& event );
		virtual void handleMove( IrrUIEvent& event );
		virtual void handleMoveOut( IrrUIEvent& event );
		//////////////////////////////////////////////////////////////////////////
	private:
		bool m_bIsActive;
		IrrSize m_Dimension;
		IrrVector2D m_Pos;
		bool m_bDirty;
	};
}

#endif	//_IRRWIDGET_H_