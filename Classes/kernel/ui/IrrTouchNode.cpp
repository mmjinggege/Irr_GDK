#include "IrrTouchNode.h"

namespace irr_ui
{
	IrrTouchNode::IrrTouchNode( void )
		:m_bTouchable(false),
		m_iPriority(IRR_TOUCH_PRIORTY_NORMAL),
		m_bSwallowsTouches(false)
	{

	}

	IrrTouchNode::~IrrTouchNode( void )
	{
	}


	void IrrTouchNode::onEnter()
	{
		CCDirector::sharedDirector()->getTouchDispatcher()->addTargetedDelegate(this, m_iPriority, true);
		CCNode::onEnter();
	}

	void IrrTouchNode::onExit()
	{
		CCDirector::sharedDirector()->getTouchDispatcher()->removeDelegate(this);
		CCNode::onExit();
	}

	void IrrTouchNode::setPosition( float x, float y )
	{
		CCNode::setPosition((CCPointMake(x, y)));
	}

	void IrrTouchNode::setPosition( const IrrVector2D &position )
	{
		CCNode::setPosition((CCPointMake(position.X, position.Y)));
	}

	bool IrrTouchNode::containsTouchLocation( CCTouch* touch )
	{
		return this->boundingBox().containsPoint(this->getParent()->convertTouchToNodeSpace(touch));
	}
}