#include "IrrGui.h"

using namespace irr_event;
using namespace irr_ui;

namespace irr_ui
{

	IrrGui::IrrGui( IrrSize size )
		:m_GuiSize(size)
	{
	}

	IrrGui::IrrGui( float width,float height )
	{
		m_GuiSize.width = width;
		m_GuiSize.height = height;
	}

	IrrGui::~IrrGui( void )
	{
	}
	
	void IrrGui::setGuiContentSize( float width,float height )
	{
		m_GuiSize.setSize(width,height);
	}
	

	bool IrrGui::ccTouchBegan( CCTouch *pTouch, CCEvent *pEvent )
	{
		bool ret = false;
		CCPoint pt = pTouch->getLocationInView();
		IrrVector2D touchLocation;
		touchLocation.setVector2D(pt.x,pt.y);
		m_DownPos = touchLocation;
		touchLocation = this->convertToNodeSpace(touchLocation);
		if(this->getChildRect().containsVector2D(touchLocation))
		{
			IrrUIEvent evt(this,IRR_UI_EVENT_DOWN);
			evt.setPos(touchLocation);
			this->DispatchUIEvent(evt);
			ret = true;
		}
		return ret;
	}

	void IrrGui::ccTouchMoved( CCTouch *pTouch, CCEvent *pEvent )
	{
		CCPoint ptCococs2dx = pTouch->getLocationInView();
		IrrVector2D  touchLocation;
		touchLocation.setVector2D(ptCococs2dx.x,ptCococs2dx.y);
		if (tabs(m_DownPos.X - touchLocation.X) >= IrrGui::MIN_MOVE_DISTANCE
			|| tabs(m_DownPos.Y - touchLocation.Y) >= IrrGui::MIN_MOVE_DISTANCE)
		{
			IrrUIEvent evt(this,IRR_UI_EVENT_MOVE);
			evt.setPos(touchLocation);
			this->DispatchUIEvent(evt);
		}
	}

	void IrrGui::ccTouchEnded( CCTouch *pTouch, CCEvent *pEvent )
	{
		CCPoint ptCococs2dx = pTouch->getLocationInView();
		IrrVector2D  touchLocation;
		touchLocation.setVector2D(ptCococs2dx.x,ptCococs2dx.y);
		touchLocation = this->convertToNodeSpace(touchLocation);
		
		IrrUIEvent evt(this,IRR_UI_EVENT_UP);
		evt.setPos(touchLocation);
		this->DispatchUIEvent(evt);
	}

	void IrrGui::ccTouchCancelled( CCTouch *pTouch, CCEvent *pEvent )
	{
		//todo
	}

	void IrrGui::DispatchUIEvent( IrrUIEvent& event )
	{
		switch (event.getEvtType())
		{
		case IRR_UI_EVENT_DOWN:
			{
				this->handleDown(event);
				break;
			}
		case IRR_UI_EVENT_UP:
			{
				this->handleUp(event);
				break;
			}
		case IRR_UI_EVENT_MOVE_IN:
			{
				this->handleMoveIn(event);
				break;
			}
		case IRR_UI_EVENT_MOVE:
			{
				this->handleMove(event);
				break;
			}
		case IRR_UI_EVENT_MOVE_OUT:
			{
				this->handleMoveOut(event);
				break;
			}
		}
	}
}