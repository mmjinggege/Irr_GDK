#include "IrrWidget.h"
#include "IrrSprite.h"

namespace irr_ui
{
	IrrWidget::IrrWidget( void )
		:m_pWidgetParent(NULL),
		m_bDirty(false),
		m_bIsTouchable(false)
	{
	}

	IrrWidget::~IrrWidget( void )
	{
		removeAllChildrenWithCleanup(true);
	}
	
	void IrrWidget::setActivie( bool val )
	{
		m_bIsActive  = val;
	}
	

	IrrVector2D IrrWidget::convertToNodeSpace( const IrrVector2D& pt )
	{
		CCPoint point = CCNode::convertToNodeSpace(ccp(pt.X,pt.Y));	
		IrrVector2D ret = pt;
// 		ret.X -= m_Rect.origin.X;
// 		ret.Y -= m_Rect.origin.Y;
		ret.X = point.x;
		ret.Y = point.y;
		return ret;
	}
		

	IrrRect IrrWidget::getChildRect()
	{
		IrrRect rc = this->getRect();
		rc.origin.setVector2D(0,0);
		return rc;
	}
	
	//////////////////////////////////////////////////////////////////////////
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

	void IrrWidget::setWidgetParent( IrrWidget* parent)
	{
		m_pWidgetParent = parent;
	}

	IrrWidget* IrrWidget::getWidgetParent()
	{
		return m_pWidgetParent;
	}

	void IrrWidget::setName( IrrString& name )
	{
		m_Name = name;
	}

	IrrString& IrrWidget::getName()
	{
		return m_Name;
	}

	IrrWidget* IrrWidget::create( const char* texture,bool isPlist /*= false*/ )
	{
		IrrWidget* pRet = new IrrWidget();
		if(pRet && pRet->init(texture,isPlist))
		{
			pRet->autorelease();
			return pRet;
		}
		IRR_SAFE_DELETE(pRet);
		return NULL;
	}
	

	bool IrrWidget::init( const char* texture,bool isPlist /*= false*/ )
	{
		IrrSprite* target = IrrSprite::create(texture,isPlist);
		this->addChild(target);
		setDimensions(target->getDimensions());
		return true;
	}

	void IrrWidget::render( IrrGraphic* pGraphic )
	{
		;//todo;
	}

	void IrrWidget::setBackgrondColor( IrrColor Color )
	{
		m_backgroundColor = Color;
	}

	IrrColor& IrrWidget::getBackgroundColor()
	{
		return m_backgroundColor;
	}

	void IrrWidget::setTouchable( bool var )
	{
		m_bIsTouchable = var;
	}

	bool IrrWidget::isTouchable() const
	{
		return m_bIsTouchable;
	}

}