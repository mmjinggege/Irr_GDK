#include "IrrPanel.h"
#include "IrrGeom.h"
#include "IrrMarcos.h"

USING_NS_CC_EXT;

using namespace irr_core;

namespace irr_ui
{

	IrrPanel::IrrPanel( void )
	{
	}

	IrrPanel::~IrrPanel( void )
	{
	}

	IrrPanel* IrrPanel::create( const char* texture,IrrSize size,bool isPlist /*= false*/ )
	{
		IrrPanel* pRet = new IrrPanel();
		if(pRet && pRet->init(texture,size,isPlist))
		{
			pRet->autorelease();
			return pRet;
		}
		IRR_SAFE_DELETE(pRet);
		return NULL;
	}


	bool IrrPanel::init( const char* texture,IrrSize size,bool isPlist /*= false*/ )
	{
		CCScale9Sprite* pBackground = NULL;
		if(isPlist)
		{
			CCScale9Sprite* pBackground = CCScale9Sprite::createWithSpriteFrameName(texture);
		}
		else
		{
			CCScale9Sprite* pBackground = CCScale9Sprite::create(texture);
		}
		pBackground->setAnchorPoint(ccp(0,0));
		pBackground->setContentSize(CCSize(size.width,size.height));
		this->addChild(pBackground);
		return true;
	}
}