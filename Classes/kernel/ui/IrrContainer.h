#ifndef _IRRCONTAINER_H_
#define _IRRCONTAINER_H_

#include "IrrWidget.h"

namespace irr_ui
{
	class IrrContainer : public IrrWidget
	{
	public:
		IrrContainer(void);
		virtual ~IrrContainer(void);

		virtual void render(IrrGraphic* pGraphic);
		virtual void addWidget(IrrWidget* widget);
		virtual void addWidget(IrrWidget* widget,IrrVector2D pos);
		virtual void removeWidget(IrrWidget* widget,bool isDel = true);
		virtual void clearAllWidget();
		void swapWidget(IrrWidget* sour,IrrWidget* desc);

		IrrWidget* getWidgetByName(const char* name);
		IrrWidget* getWidgetByPos(float x,float y);
		IrrUint numberOfChildren() const;

		//////////////////////////////////////////////////////////////////////////
		virtual void handleDown( IrrUIEvent& event );
		virtual void handleUp( IrrUIEvent& event );
		virtual void handleClick( IrrUIEvent& event );
		virtual void handleMoveIn( IrrUIEvent& event );
		virtual void handleMove( IrrUIEvent& event );
		virtual void handleMoveOut( IrrUIEvent& event );
		//////////////////////////////////////////////////////////////////////////
	protected:
		std::list<IrrWidget*> m_childWidgetList;
	};
}




#endif	//_IRRCONTAINER_H_