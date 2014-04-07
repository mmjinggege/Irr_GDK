#include "IrrGui.h"
#include "IrrGraphic.h"
#include "IrrCamera.h"
using namespace irr_ui;

namespace irr_ui
{

	IrrGui::IrrGui( IrrSize size )
	{
		m_pCurrentSelWidget = NULL;
		m_Rect.size = size;
		m_pGraphic = NULL;
	}

	IrrGui::IrrGui( float width,float height )
	{
		m_Rect.size.setSize(width,height);
		m_pGraphic = IrrGraphic::getInstance();
		m_pGraphic->setGraphicSize(width,height);
	}

	IrrGui::~IrrGui( void )
	{
	}

	bool IrrGui::ccTouchBegan( CCTouch *pTouch, CCEvent *pEvent )
	{
		bool ret = false;
		CCPoint pt = pTouch->getLocationInView();
		IrrVector2D touchLocation;
		touchLocation.setVector2D(pt.x,pt.y);
		touchLocation = this->convertToNodeSpace(touchLocation);
		IrrRect rect = this->getRect();
		if(rect.containsVector2D(touchLocation))
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
		case IRR_UI_EVENT_CLICK:
			{
				this->handleClick(event);
				break;
			}
		}
	}

	void IrrGui::onEnter()
	{
		//////////////////////////////////////////////////////////////////////////
		setRootDepth(0);
		//////////////////////////////////////////////////////////////////////////
		CCDirector::sharedDirector()->getTouchDispatcher()->addTargetedDelegate(this, -1, true);
		CCNode::onEnter();
	}

	void IrrGui::onExit()
	{
		CCNode::onExit();
			 CCDirector::sharedDirector()->getTouchDispatcher()->removeDelegate(this);
	}

	void IrrGui::onRender()
	{
		m_pGraphic->beginDraw();
		m_pGraphic->pushClipArea(this->getRect());
		//draw background
		m_pGraphic->setColor(this->getBackgroundColor());
		m_pGraphic->fillRectangle(this->getChildRect());
		//draw children
		IrrContainer::render(m_pGraphic);
		m_pGraphic->popClipArea();	
		m_pGraphic->endDraw();
	}



// 	void IrrGui::handleDown( IrrUIEvent& event )
// 	{
// 		if(this->getRect().containsVector2D(event.getPos()))
// 		{
// 		 	pIrrWidgetReverseItor rItor = m_TouchableWights.rbegin();
// 		 	IrrWidget* pTemp = NULL;
// 		 	while(rItor != m_TouchableWights.rend())
// 		 	{
// 		 		pTemp = *rItor;
// 		 		IrrVector2D ptTemp = event.getPos();
// 		 		IrrRect rect = pTemp->getRect();
// 		 		if(shareCamera->checkTouchPosInRectAtAnchor(rect,ptTemp,CreateIrrVector2D(0.5,0.5)))
// 		 		{
// 		 			event.setPos(ptTemp);
// 		 			pTemp->handleDown(event);
// 		 			if(event.isHandled())
// 		 			{
// 		 				m_pCurrentSelWidget = pTemp;
// 		 				break;
// 		 			}
// 		 		}
// 		 		rItor++;
// 		 	}
// 		}
// 	}
// 
// 	void IrrGui::handleUp( IrrUIEvent& event )
// 	{
// 		if(m_pCurrentSelWidget)
// 		{
// 		 	pIrrWidgetReverseItor rItor = m_TouchableWights.rbegin();
// 		 	IrrWidget* pTemp = NULL;
// 		 	while(rItor !=m_TouchableWights.rend())
// 		 	{
// 		 		pTemp = *rItor;
// 		 		IrrVector2D ptTemp = event.getPos();
// 		 		IrrRect rect = pTemp->getRect();
// 		 		if(shareCamera->checkTouchPosInRectAtAnchor(rect,ptTemp,CreateIrrVector2D(0.5,0.5)))
// 		 		{
// 		 			break;
// 		 		}
// 		 		rItor++;
// 		 	}
// 		 
// 		 	IrrVector2D ptTemp = event.getPos();
// 		 	m_pCurrentSelWidget->handleUp(event);
// 		 
// 		 	if(pTemp == m_pCurrentSelWidget )
// 		 	{
// 		 		if( !m_bIsMoved )
// 		 		{
// 		 			event.setHandled(false);
// 		 			event.setEvtType(IRR_UI_EVENT_CLICK);
// 		 			m_pCurrentSelWidget->handleClick(event);
// 		 		}
// 		 	}
// 		 
// 		 	m_bIsMoved = false;
// 		 	m_pCurrentSelWidget = NULL;
// 		}
// 	}
// 
// 	void IrrGui::handleClick( IrrUIEvent& event )
// 	{
// 		if (m_pCurrentSelWidget)
// 		{
// 			m_pCurrentSelWidget->handleClick(event);
// 		}
// 	}
	void IrrGui::selectEventWights()
	{
		m_curTouchWights.clear();

	}


	IrrWidget* IrrGui::checkWight()
	{
		m_curTouchWights.sort(sortListByRootDepth);
		pIrrWidgetReverseItor rItor = m_curTouchWights.rbegin();
		IrrWidget* pTemp = NULL;
		while(rItor != m_curTouchWights.rend())
		{

			rItor++;
		}
		return NULL;
	}


	void IrrGui::handleDown( IrrUIEvent& event )
	{
		if(this->getRect().containsVector2D(event.getPos()))
		{
			m_curTouchWights.clear();
			pIrrWidgetReverseItor rItor = m_TouchableWights.rbegin();
			IrrWidget* pTemp = NULL;
			while(rItor != m_TouchableWights.rend())
			{
				pTemp = *rItor;
				IrrVector2D ptTemp = event.getPos();
				IrrRect rect = pTemp->getRect();

				IrrVector2D localVect2D = ((IrrWidget*)pTemp->getParent())->convertToNodeSpace(ptTemp);

				//if(shareCamera->checkTouchPosInRectAtAnchor(rect,localVect2D,CreateIrrVector2D(0.5,0.5)))
				if (rect.containsVector2D(localVect2D))
				{
					
					m_curTouchWights.push_back(pTemp);
// 					event.setPos(ptTemp);
// 					pTemp->handleDown(event);
// 					if(event.isHandled())
// 					{
// 						m_pCurrentSelWidget = pTemp;
// 						break;
// 					}
				}
				rItor++;
			}

			checkWight();
		}
	}

	void IrrGui::handleUp( IrrUIEvent& event )
	{
		if(m_pCurrentSelWidget)
		{
			pIrrWidgetReverseItor rItor = m_TouchableWights.rbegin();
			IrrWidget* pTemp = NULL;
			while(rItor !=m_TouchableWights.rend())
			{
				pTemp = *rItor;
				IrrVector2D ptTemp = event.getPos();
				IrrRect rect = pTemp->getRect();
				if(shareCamera->checkTouchPosInRectAtAnchor(rect,ptTemp,CreateIrrVector2D(0.5,0.5)))
				{
					break;
				}
				rItor++;
			}

			IrrVector2D ptTemp = event.getPos();

			if (m_pCurrentSelWidget)
			{
				m_pCurrentSelWidget->handleUp(event);

			}

			if(pTemp == m_pCurrentSelWidget )
			{
				if( !m_bIsMoved )
				{
					event.setHandled(false);
					event.setEvtType(IRR_UI_EVENT_CLICK);
					m_pCurrentSelWidget->handleClick(event);
				}
			}

			m_bIsMoved = false;
			m_pCurrentSelWidget = NULL;
		}
	}

	void IrrGui::handleClick( IrrUIEvent& event )
	{
		if (m_pCurrentSelWidget)
		{
			m_pCurrentSelWidget->handleClick(event);
		}
	}
	void IrrGui::handleMoveIn( IrrUIEvent& event )
	{

	}

	void IrrGui::handleMove( IrrUIEvent& event )
	{
 		m_bIsMoved = true;
 		if (m_pCurrentSelWidget)
 		{
 			m_pCurrentSelWidget->handleMove(event);
 		}
	}

	void IrrGui::handleMoveOut( IrrUIEvent& event )
	{

	}

	void IrrGui::addTouchAbleWight( IrrWidget* pWight )
	{
		m_TouchableWights.push_back(pWight);
	}

	void IrrGui::removeTouchAbleWight( IrrWidget* pWight )
	{
		pIrrWidgetItor itor;
		for (itor = m_TouchableWights.begin();itor!=m_TouchableWights.end();itor++)
		{
			if(*itor == pWight)
			{
				m_TouchableWights.erase(itor);
				break;
			}
		}
	}

	void IrrGui::clearTouchAbleChildren()
	{
		m_TouchableWights.clear();
	}

	irr_ui::IrrWidgetTouchableList& IrrGui::getTouchAbleChildren()
	{
		return m_TouchableWights;
	}



}