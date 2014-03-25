#include "IrrCheckBox.h"
#include "IrrImage.h"

namespace irr_ui
{
	
	IrrCheckBox* IrrCheckBox::create( const char* normalTexture,const char* selectTexture,const char* groupName,bool isPlist /*= false*/ )
	{
		IrrCheckBox* pRet = new IrrCheckBox();
		if(pRet && pRet->init(normalTexture,selectTexture,groupName,isPlist))
		{
			pRet->autorelease();
			return pRet;
		}
		IRR_SAFE_DELETE(pRet);
		return NULL;
	}

	IrrCheckBox::IrrCheckBox( void )
	{
		m_pNormalImage = NULL;
		m_pSelectedImage = NULL;
		setTouchable(true);
	}

	IrrCheckBox::~IrrCheckBox( void )
	{
		removeAllChildrenWithCleanup(true);
	}

	void IrrCheckBox::setSelected( bool selected )
	{
		m_bIsSelected = selected;
		IrrToggleButton::setToggleButtonStatue();
	}
	
	bool IrrCheckBox::init( const char* normalTexture,const char* selectTexture,const char* groupName,bool isPlist /*= false*/ )
	{
		m_pNormalImage = IrrImage::create(normalTexture,isPlist);
		m_pSelectedImage = IrrImage::create(selectTexture,isPlist);

		if(m_pSelectedImage)
			this->addWidget(m_pSelectedImage);
		if(m_pNormalImage)
			addWidget(m_pNormalImage);

		setDimensions(m_pNormalImage->getDimensions());
		m_pSelectedImage->setVisible(false);
		return true;
	}

}