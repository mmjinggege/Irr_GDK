#include "IrrContainer.h"
#include "IrrCamera.h"
#include "IrrGui.h"

namespace irr_ui
{
	
	IrrContainer::IrrContainer( void )
	{
	}

	IrrContainer::~IrrContainer( void )
	{
	}

	void IrrContainer::addWidget( IrrWidget* widget)
	{
		//////////////////////////////////////////////////////////////////////////
		//chenjing
		this->addWidget(widget,widget->getOrigin());
		//////////////////////////////////////////////////////////////////////////
		//this->addWidget(widget,IrrVector2D(0,0));
	}

	void IrrContainer::addWidget( IrrWidget* widget,IrrVector2D pos )
	{
		IRR_CHECK_NULL(widget);
		this->addChild(widget);
		widget->setWidgetParent(this);
		widget->setPosition(pos.X,pos.Y);

		if(widget->isTouchable())
		{
 			shareGui->addTouchAbleWidget(widget);
		}

		m_childWidgetList.push_back(widget);
		//////////////////////////////////////////////////////////////////////////
		int rootDepth = this->getRootDepth();
		widget->setRootDepth( ++rootDepth );
		//////////////////////////////////////////////////////////////////////////
	}

	void IrrContainer::removeWidget( IrrWidget* widget,bool isDel /*= true*/ )
	{
		if (widget->isTouchable())
		{
			shareGui->removeTouchAbleWidget(widget);
		}

		widget->setParent(NULL);
		this->removeChild(widget);
	}

	void IrrContainer::clearAllWidget()
	{
// 		pIrrWidgetItor itor = m_TouchableChilds.begin();
// 		while(itor!=m_TouchableChilds.end())
// 		{
// 			itor = m_TouchableChilds.erase(itor);
// 		}
// 		removeAllChildrenWithCleanup(true);

		std::list<IrrWidget*>::iterator pItor = m_childWidgetList.begin();
		IrrWidget* pWidget = NULL;
		while(pItor != m_childWidgetList.end())
		{
			pWidget = *pItor;
			if ( pWidget->isTouchable() )
			{
				shareGui->removeTouchAbleWidget(pWidget);
			}
			pItor ++;
		}

		m_childWidgetList.clear();
		removeAllChildrenWithCleanup(true);
	}

	void IrrContainer::swapWidget( IrrWidget* sour,IrrWidget* desc )
	{
		if(sour == NULL || desc == NULL)
			return;
		int sourZorder = sour->getZOrder();
		int descZorder = desc->getZOrder();
		sour->setZOrder(descZorder);
		desc->setZOrder(sourZorder);
		this->reorderChild(sour,descZorder);
		this->reorderChild(desc,sourZorder);
	}
	

	IrrWidget* IrrContainer::getWidgetByName( const char* name )
	{
		IrrWidget* widget = NULL;
		std::list<IrrWidget*>::iterator pItor = m_childWidgetList.begin();
		for (pItor = m_childWidgetList.begin();pItor!=m_childWidgetList.end();pItor++)
		{
			widget = *pItor;
			if(widget->getName() == name)
			{
				break;
			}
		}
 		return widget;
	} 

	
	IrrWidget* IrrContainer::getWidgetByPos( float x,float y )
	{
		IrrWidget* widget = NULL;
		IrrRect rc = this->getRect();
 		if(rc.containsVector2D(x,y))
 		{
 			std::list<IrrWidget*>::iterator itor = m_childWidgetList.begin();
 			for (itor = m_childWidgetList.begin();itor != m_childWidgetList.end();itor++)
 			{
 				if((*itor)->isVisible() && (*itor)->getRect().containsVector2D(x,y))
 				{
 					widget = *itor;
					break;
 				}
 			}
 		}
		return widget;
	}


	IrrUint IrrContainer::numberOfChildren() const
	{
		return this->getChildrenCount();
	}

	//////////////////////////////////////////////////////////////////////////
	void IrrContainer::handleDown( IrrUIEvent& event )
	{
// 		if(this->getRect().containsVector2D(event.getPos()))
// 		{
// 			pIrrWidgetReverseItor rItor = m_TouchableChilds.rbegin();
// 			IrrWidget* pTemp = NULL;
// 			while(rItor !=m_TouchableChilds.rend())
// 			{
// 				pTemp = *rItor;
// 				IrrVector2D ptTemp = event.getPos();
// 				//ptTemp = pTemp->convertToNodeSpace(ptTemp);
// 				//ptTemp = shareCamera->convertToSceneViewSpace(ptTemp);
// 				IrrRect rect = pTemp->getRect();
// 				if(shareCamera->checkTouchPosInRectAtAnchor(rect,ptTemp,CreateIrrVector2D(0.5,0.5)))
// 				{
// 					event.setPos(ptTemp);
// 					pTemp->handleDown(event);
// 					if(event.isHandled())
// 					{
// 						m_pCurrentSelWidget = pTemp;
// 						break;
// 					}
// 				}
// 				rItor++;
// 			}
// 		}
	}

	void IrrContainer::handleUp( IrrUIEvent& event )
	{
// 		if(m_pCurrentSelWidget)
// 		{
// 			pIrrWidgetReverseItor rItor = m_TouchableChilds.rbegin();
// 			IrrWidget* pTemp = NULL;
// 			while(rItor !=m_TouchableChilds.rend())
// 			{
// 				pTemp = *rItor;
// 				IrrVector2D ptTemp = event.getPos();
// 				//ptTemp = pTemp->convertToNodeSpace(ptTemp);
// 				IrrRect rect = pTemp->getRect();
// 				if(shareCamera->checkTouchPosInRectAtAnchor(rect,ptTemp,CreateIrrVector2D(0.5,0.5)))
// 				{
// 					break;
// 				}
// 				rItor++;
// 			}
// 
// 			IrrVector2D ptTemp = event.getPos();
// 			m_pCurrentSelWidget->handleUp(event);
// 
// 			if(pTemp == m_pCurrentSelWidget )
// 			{
// 				if( !m_bIsMoved )
// 				{
// 					event.setHandled(false);
// 					event.setEvtType(IRR_UI_EVENT_CLICK);
// 					m_pCurrentSelWidget->handleClick(event);
// 				}
// 			}
// 
// 			m_bIsMoved = false;
// 			m_pCurrentSelWidget = NULL;
// 		}
	}

	void IrrContainer::handleClick( IrrUIEvent& event )
	{
// 		if (m_pCurrentSelWidget)
// 		{
// 			m_pCurrentSelWidget->handleClick(event);
// 		}
	}

	void IrrContainer::handleMoveIn( IrrUIEvent& event )
	{
		;//TODO
	}

	void IrrContainer::handleMove( IrrUIEvent& event )
	{
// 		m_bIsMoved = true;
// 		if (m_pCurrentSelWidget)
// 		{
// 			m_pCurrentSelWidget->handleMove(event);
// 		}
	}

	void IrrContainer::handleMoveOut( IrrUIEvent& event )
	{
		;//TODO
	}
	
	void IrrContainer::render( IrrGraphic* pGraphic )
	{
#if 0
		IRR_ASSERT(pGraphic != NULL,"in function draw pGraphic can not be null");
		pGraphic->pushClipArea(this->getChildRect());
		pIrrWidgetItor iter;
		IrrRect rc;
		for (iter = m_TouchableChilds.begin(); iter != m_TouchableChilds.end(); iter++)
		{
			kmGLPushMatrix();
			if ((*iter)->isVisible())
			{
				rc = (*iter)->getRect();
				//if can not been seen just continue
				if (rc.size.height + rc.origin.Y <= 0)
				{
					continue;
				}

				if (rc.origin.Y >= this->getRect().size.height)
				{
					continue;
				}
				
				pGraphic->pushClipArea((*iter)->getRect());
				(*iter)->render(pGraphic);
				pGraphic->popClipArea();	
			}
			kmGLPopMatrix();
		}
		pGraphic->popClipArea();
#endif
	}
	//////////////////////////////////////////////////////////////////////////
}