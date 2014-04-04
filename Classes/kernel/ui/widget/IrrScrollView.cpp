#include "IrrScrollView.h"

irr_ui::IrrScrollView::IrrScrollView():m_pContainer(NULL),m_type(IrrScrollViewTypeVertical),m_bClippingToBounds(false),m_bBounceable(false),m_bIsMoved(false)
{

}

irr_ui::IrrScrollView::~IrrScrollView()
{

}

IrrScrollView* irr_ui::IrrScrollView::create(IrrSize& dimensions)
{
	IrrScrollView* pScroll = new IrrScrollView();
	if (pScroll->init(dimensions))
	{
		pScroll->autorelease();
		return pScroll;
	}

	IRR_SAFE_DELETE(pScroll);
	return NULL;
}

bool irr_ui::IrrScrollView::init( IrrSize& dimensions )
{
	this->setDimensions(dimensions);
	this->setTouchable(true);
	return true;
}

 
// void irr_ui::IrrScrollView::setInnerSize( IrrSize size )
// {
// 
// }
// 
// irr_core::IrrSize irr_ui::IrrScrollView::getInnerSize()
// {
// 
// }

void irr_ui::IrrScrollView::handleDown( IrrUIEvent& event )
{

}

void irr_ui::IrrScrollView::handleMove( IrrUIEvent& event )
{
	m_bIsMoved = true;
}

void irr_ui::IrrScrollView::handleUp( IrrUIEvent& event )
{

}

void irr_ui::IrrScrollView::handleClick( IrrUIEvent& event )
{

}

void irr_ui::IrrScrollView::setScrollViewType( CCScrollViewType type )
{

}

irr_ui::CCScrollViewType irr_ui::IrrScrollView::getScrollViewType()
{
	return m_type;
}

void irr_ui::IrrScrollView::setClippingToBounds( bool var )
{

}

bool irr_ui::IrrScrollView::isClippingToBounds()
{
	return m_bClippingToBounds;
}

void irr_ui::IrrScrollView::setBounceable( bool var )
{

}

bool irr_ui::IrrScrollView::getBounceable()
{
	return m_bBounceable;
}

