#include "IrrNode.h"

namespace irr_display
{
	IrrNode::IrrNode( void )
	{
		m_iRootDepth = 0;
		m_bSwallowsTouches = false;
		setAnchorPoint(ccp(0.5f,0.5f));
	}

	IrrNode::~IrrNode( void )
	{
	}
	
	void IrrNode::onEnter()
	{
		CCNode::onEnter();
	}
	
	void IrrNode::setPosition( float x, float y )
	{
		m_Rect.origin.setVector2D(x,y);
		CCNode::setPosition((CCPointMake(m_Rect.getOriginX(), m_Rect.getOriginY())));
	}

	void IrrNode::setPosition( const IrrVector2D &position )
	{
		this->setPosition(position.X,position.Y);
	}

	void IrrNode::setDimensions( IrrSize& size )
	{
		m_Rect.size = size;
		/*this->setContentSize(CCSizeMake(size.width,size.height));*/
	}

	void IrrNode::setDimensions( float width,float height )
	{
		m_Rect.size.setSize(width,height);
	}


	IrrSize& IrrNode::getDimensions()
	{
		//CCSize size= this->getContentSize();
		//IrrSize(size.width,size.height);
		return m_Rect.size;
	}

	void IrrNode::setRect( IrrRect& rect )
	{
		m_Rect = rect;
		if( 0 == this->getContentSize().width && 0 == this->getContentSize().height)
		{
			this->setDimensions(m_Rect.size);
		}
	}

	IrrRect IrrNode::getRect() const
	{
		IrrRect ret = m_Rect;
		ret.size.width  *= CC_CONTENT_SCALE_FACTOR();
		ret.size.height *= CC_CONTENT_SCALE_FACTOR();
		return ret;
	}

	IrrVector2D IrrNode::getOrigin()
	{
		return m_Rect.origin;
	}

	void IrrNode::updateLocation( float offsetX,float offsetY )
	{
		setPosition(m_Rect.origin.X+offsetX, m_Rect.origin.Y+offsetY);
	}

	void IrrNode::updateLocation( IrrVector2D& postion )
	{
		setPosition(m_Rect.origin.X+postion.X, m_Rect.origin.Y+postion.Y);
	}
}