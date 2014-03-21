#include "IrrWidget.h"

namespace irr_ui
{

	IrrWidget::IrrWidget( void )
		:m_pParent(NULL),
		m_bDirty(false)
	{
	}

	IrrWidget::~IrrWidget( void )
	{
	}
	
	void IrrWidget::setActivie( bool val )
	{
		m_bIsActive  = val;
	}
	
	void IrrWidget::setDimensions( const IrrSize& size )
	{
		m_Dimension = size;
	}

	IrrSize& IrrWidget::getDimensions()
	{
		return m_Dimension;
	}

	void IrrWidget::setWidgetRect(IrrRect var)
	{
		m_Rect = var;
		if( 0 == m_Dimension.width && 0 == m_Dimension.height)
		{
			this->setDimensions(m_Rect.size);
		}
	}

	IrrRect IrrWidget::getWidgetRect()
	{
		//this->updateContentSizeInner();
		IrrRect ret = m_Rect;
		ret.size.width *= m_Scale;
		ret.size.height *= m_Scale;
		return ret;
	}


	IrrVector2D IrrWidget::convertToNodeSpace( const IrrVector2D& pt )
	{
		IrrVector2D ret = pt;
		ret.X -= m_Rect.origin.X;
		ret.Y -= m_Rect.origin.Y;
		return ret;
	}

	void IrrWidget::setScale(float var)
	{
		m_Scale = var;
		m_bDirty = true;
	}

	float IrrWidget::getScale()
	{
		return m_Scale;
	}

	IrrRect IrrWidget::getChildRect()
	{
		IrrRect rc = this->getWidgetRect();
		rc.origin.setVector2D(0,0);
		return rc;
	}


	void IrrWidget::setLocation( float x,float y )
	{
		m_Pos.setVector2D(x,y);
	}
	
	void IrrWidget::handleDown( IrrUIEvent& event )
	{
		//override
	}

	void IrrWidget::handleUp( IrrUIEvent& event )
	{
		//override
	}

	void IrrWidget::handleClick( IrrUIEvent& event )
	{
		//override
	}

	void IrrWidget::handleMoveIn( IrrUIEvent& event )
	{
		//override
	}

	void IrrWidget::handleMove( IrrUIEvent& event )
	{
		//override
	}

	void IrrWidget::handleMoveOut( IrrUIEvent& event )
	{
		//override
	}

}