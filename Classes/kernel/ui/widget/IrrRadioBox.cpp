#include "IrrRadioBox.h"
#include "IrrImage.h"

namespace irr_ui
{

	IrrRadioBox::IrrRadioBox( void )
	{
		m_pNormalImage = NULL;
		m_pSelectedImage = NULL;
		setTouchable(true);
	}

	IrrRadioBox::~IrrRadioBox( void )
	{
		removeAllChildrenWithCleanup(true);
	}

	IrrRadioBox* IrrRadioBox::create( const char* normalTexture,const char* selectTexture,const char* groupName,bool isPlist /*= false*/ )
	{
		IrrRadioBox* pRet = new IrrRadioBox();
		if(pRet && pRet->init(normalTexture,selectTexture,groupName,isPlist))
		{
			pRet->autorelease();
			return pRet;
		}
		IRR_SAFE_DELETE(pRet);
		return NULL;
	}

	
	void IrrRadioBox::setSelected( bool selected )
	{
		m_bIsSelected = selected;
		IrrToggleButton::setToggleButtonStatue();
		if(m_bIsSelected)
		{
			IrrToggleButton::clearToggleButton(this);
		}
	}

	bool IrrRadioBox::init( const char* normalTexture,const char* selectTexture,const char* groupName,bool isPlist /*= false*/ )
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