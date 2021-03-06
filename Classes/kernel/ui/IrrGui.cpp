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
		m_bIsMoved = false;
	}

	IrrGui::IrrGui( float width,float height )
	{
		m_Rect.size.setSize(width,height);
		m_pGraphic = IrrGraphic::getInstance();
		m_pGraphic->setGraphicSize(width,height);
		m_pCurrentSelWidget = NULL;
		m_bIsMoved = false;
	}

	IrrGui::~IrrGui( void )
	{
	}

	bool IrrGui::ccTouchBegan( CCTouch *pTouch, CCEvent *pEvent )
	{
		bool ret = false;
		CCPoint pt = pTouch->getLocation();
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
	//	CCPoint ptCococs2dx = pTouch->getLocationInView();
		CCPoint ptCococs2dx = pTouch->getLocation();
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
	void IrrGui::selectEventWidgets()
	{
		m_curTouchWidgets.clear();
	}


// 	IrrWidget* IrrGui::checkWight()
// 	{
// 		m_curTouchWights.sort(sortListByRootDepth);
// 		pIrrWidgetReverseItor rItor = m_curTouchWights.rbegin();
// 		IrrWidget* pTemp = NULL;
// 		while(rItor != m_curTouchWights.rend())
// 		{
// 			pTemp = *rItor;
// 			rItor++;
// 		}
// 		return NULL;
// 	}

	IrrWidget* IrrGui::checkWidget( IrrWidget* pLeft, IrrWidget* pRight )
	{
		if (pLeft == NULL && pRight == NULL)
		{
			return NULL;
		}
	
		if (pLeft == NULL)
		{
			return pRight;
		}

		if (pRight == NULL)
		{
			return pLeft;
		}

		if (pLeft == pRight)
		{
			return pLeft;
		}

		int difRootDepth = pLeft->getRootDepth() - pRight->getRootDepth();
		IrrWidget* pLeftParent = pLeft->getWidgetParent();
		IrrWidget* pRightParent = pRight->getWidgetParent();

		IrrWidget* pTmpLeft = NULL;
		IrrWidget* pTmpRight = NULL;

		if (difRootDepth > 0)
		{
			for(int i = 0; i < difRootDepth; i++)
			{
				pTmpLeft = pLeftParent;
				pLeftParent = pLeftParent->getWidgetParent();
			}
		}else if(difRootDepth < 0)
		{
			int absDif = tabs(difRootDepth);
			for(int i = 0; i < absDif; i++)
			{
				pTmpRight = pRightParent;
				pRightParent = pRightParent->getWidgetParent();
			}
		}

		while( pLeftParent != pRightParent )
		{
			pTmpLeft = pLeftParent;
			pTmpRight = pRightParent;
			pLeftParent = pLeftParent->getWidgetParent();
			pRightParent = pRightParent->getWidgetParent();
		}

 		if (pTmpLeft == NULL && pTmpRight == NULL)
		{
			if ( pLeft->getZOrder() == pRight->getZOrder())
			{
				if(pLeftParent->getChildren()->indexOfObject(pLeft) > pRightParent->getChildren()->indexOfObject(pRight))
				{
					return pLeft;
				}
			}else if ( pLeft->getZOrder() > pRight->getZOrder())
			{
				return pLeft;
			}

			return pRight;
		}

		if (pTmpLeft == NULL)
		{
			if (pLeft->getZOrder() == pTmpRight->getZOrder())
			{
				if(pLeftParent->getChildren()->indexOfObject(pLeft) > pRightParent->getChildren()->indexOfObject(pTmpRight))
				{
					return pLeft;
				}
			}
			else if (pLeft->getZOrder() > pTmpRight->getZOrder())
			{
				return pLeft;
			}

			return pRight;
		}
		else if(pTmpRight == NULL)
		{
			if (pRight->getZOrder() == pTmpLeft->getZOrder())
			{
				if(pRightParent->getChildren()->indexOfObject(pRight) > pLeftParent->getChildren()->indexOfObject(pTmpLeft))
				{
					return pRight;
				}
			}
			else if (pRight->getZOrder() > pTmpLeft->getZOrder())
			{
				return pRight;
			}

			return pLeft;
		}
		
		if ( pTmpLeft->getZOrder() == pTmpRight->getZOrder())
		{
			if(pLeftParent->getChildren()->indexOfObject(pLeft) > pRightParent->getChildren()->indexOfObject(pRight))
			{
				return pLeft;
			}
		}
		else if ( pTmpLeft->getZOrder() > pTmpRight->getZOrder())
		{
			return pLeft;
		}

		return pRight;
	}

	IrrWidget* IrrGui::selectCurWidget()
	{
		if (m_curTouchWidgets.size() == 0)
		{
			return NULL;
		}

		if (m_curTouchWidgets.size() == 1)
		{
			IrrWidget* pWigdet = m_curTouchWidgets.front();
			m_curTouchWidgets.pop_front();
			return pWigdet;
		}

		m_curTouchWidgets.sort(sortListByRootDepth);

		IrrWidget* pTmp = NULL;

		IrrWidget* pLeft = m_curTouchWidgets.front();
		m_curTouchWidgets.pop_front();
		IrrWidget* pRight = m_curTouchWidgets.front();;
		m_curTouchWidgets.pop_front();

		pTmp = checkWidget(pLeft,pRight);

		while(!m_curTouchWidgets.empty())
		{
			IrrWidget* pLeft = m_curTouchWidgets.front();
			m_curTouchWidgets.pop_front();
			pTmp = checkWidget(pLeft,pTmp);
		}

		return pTmp;
	}

	void IrrGui::handleDown( IrrUIEvent& event )
	{
		ENTERFUNC();
		GET_START_TIME;
		if(this->getRect().containsVector2D(event.getPos()))
		{
			m_curTouchWidgets.clear();
			pIrrWidgetReverseItor rItor = m_TouchableWidgets.rbegin();
			IrrWidget* pTemp = NULL;
			while(rItor != m_TouchableWidgets.rend())
			{
				pTemp = *rItor;
				IrrVector2D ptTemp = event.getPos();
				IrrRect rect = pTemp->getRect();

				IrrVector2D localVect2D = ((IrrWidget*)pTemp->getParent())->convertToNodeSpaceAR(ptTemp);
				rect.origin.X -= pTemp->getRect().size.width * 0.5f;
				rect.origin.Y -= pTemp->getRect().size.height * 0.5f;
				if (rect.containsVector2D(localVect2D))
				{
					m_curTouchWidgets.push_back(pTemp);
				}
				rItor++;
			}

			//CCLOG("touch down widget size:%d",m_curTouchWights.size());

			m_pCurrentSelWidget = selectCurWidget();

			if (m_pCurrentSelWidget)
			{
				m_pCurrentSelWidget->handleDown(event);
			}
		}
		GET_END_TIME;
		LOG_TIME("handleDown");
		LVFUNC();
	}

	void IrrGui::handleUp( IrrUIEvent& event )
	{
		ENTERFUNC();
		GET_START_TIME;
		if(m_pCurrentSelWidget)
		{
			m_curTouchWidgets.clear();

			pIrrWidgetReverseItor rItor = m_TouchableWidgets.rbegin();
			IrrWidget* pTemp = NULL;
			while(rItor != m_TouchableWidgets.rend())
			{
				pTemp = *rItor;
				IrrVector2D ptTemp = event.getPos();
				IrrRect rect = pTemp->getRect();

				IrrVector2D localVect2D = ((IrrWidget*)pTemp->getParent())->convertToNodeSpaceAR(ptTemp);
				rect.origin.X -= pTemp->getRect().size.width * 0.5f;
				rect.origin.Y -= pTemp->getRect().size.height * 0.5f;
				if (rect.containsVector2D(localVect2D))
				{
					m_curTouchWidgets.push_back(pTemp);
				}
				rItor++;
			}

			//CCLOG("touch widget up size:%d",m_curTouchWights.size());
			pTemp = selectCurWidget();

			//CCLOG("click up:tmpname = [%s] curname = [%s]",pTemp->getName().c_str(),m_pCurrentSelWidget->getName().c_str());

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
		GET_END_TIME;
		LOG_TIME("handleUp");
		LVFUNC();
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

	void IrrGui::addTouchAbleWidget( IrrWidget* pWidget )
	{
		if (! isInTouchaleList(pWidget))
		{
			m_TouchableWidgets.push_back(pWidget);
		}
	}

	void IrrGui::removeTouchAbleWidget( IrrWidget* pWight )
	{
		pIrrWidgetItor itor;
		for (itor = m_TouchableWidgets.begin();itor != m_TouchableWidgets.end();itor++)
		{
			if(*itor == pWight)
			{
				m_TouchableWidgets.erase(itor);
				break;
			}
		}
	}

	void IrrGui::clearTouchAbleChildren()
	{
		m_TouchableWidgets.clear();
	}

	irr_ui::IrrWidgetTouchableList& IrrGui::getTouchAbleChildren()
	{
		return m_TouchableWidgets;
	}

	bool IrrGui::isInTouchaleList( IrrWidget* pWidget )
	{
		pIrrWidgetItor itor;
		for (itor = m_TouchableWidgets.begin();itor != m_TouchableWidgets.end();itor++)
		{
			if(*itor == pWidget)
			{
				return true;
			}
		}
		return false;
	}
}