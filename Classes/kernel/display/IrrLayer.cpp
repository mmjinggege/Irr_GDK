#include "IrrLayer.h"

namespace irr_display
{
	
	IrrLayer::IrrLayer( void )
		:m_pLayerDelegate(NULL),
		m_bInit(false)
	{
	}

	IrrLayer::~IrrLayer( void )
	{
		IRR_SAFE_DELETE(m_pLayerDelegate);
	}

	bool IrrLayer::init()
	{
		if(m_bInit)
		{
			return false;
		}
		m_bInit = true;
		return true;
	}
	
	void IrrLayer::onEnter()
	{
		CCDirector::sharedDirector()->getTouchDispatcher()->addTargetedDelegate(this,-1,true);
		IrrNode::onEnter();
	}
	
	void IrrLayer::onExit()
	{
		CCDirector::sharedDirector()->getTouchDispatcher()->removeDelegate(this);
		IrrNode::onExit();
	}


	bool IrrLayer::ccTouchBegan( CCTouch *pTouch, CCEvent *pEvent )
	{
		if(m_pLayerDelegate)
		{
			IrrLayerEvent evt(this,IRR_LAYER_EVENT_DOWN);
			evt.setDelta(CreateIrrVector2D(pTouch->getDelta().x,pTouch->getDelta().y));
			evt.setPos(CreateIrrVector2D(pTouch->getLocation().x,pTouch->getLocation().y));
			m_pLayerDelegate->handleDown(evt);
		}
		return true;
	}

	void IrrLayer::ccTouchMoved( CCTouch *pTouch, CCEvent *pEvent )
	{
		if(m_pLayerDelegate)
		{
			IrrLayerEvent evt(this,IRR_LAYER_EVENT_MOVE);
			evt.setDelta(CreateIrrVector2D(pTouch->getDelta().x,pTouch->getDelta().y));
			evt.setPos(CreateIrrVector2D(pTouch->getLocation().x,pTouch->getLocation().y));
			m_pLayerDelegate->handleMove(evt);
		}
	}

	void IrrLayer::ccTouchEnded( CCTouch *pTouch, CCEvent *pEvent )
	{
		if(m_pLayerDelegate)
		{ 
			IrrLayerEvent evt(this,IRR_LAYER_EVENT_UP);
			evt.setDelta(CreateIrrVector2D(pTouch->getDelta().x,pTouch->getDelta().y));
			evt.setPos(CreateIrrVector2D(pTouch->getLocation().x,pTouch->getLocation().y));
			m_pLayerDelegate->handleUp(evt);
		}
	}

	void IrrLayer::ccTouchCancelled( CCTouch *pTouch, CCEvent *pEvent )
	{
		;//TODO
	}


}