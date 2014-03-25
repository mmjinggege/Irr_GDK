#include "IrrSprite.h"

namespace irr_display
{
	IrrSprite* IrrSprite::create( const char* texture,bool isPlist /*= false*/ )
	{
		IrrSprite* pRet = new IrrSprite();
		if(pRet && pRet->init(texture,isPlist))
		{
			return pRet;
		}
		IRR_SAFE_DELETE(pRet);
		return NULL;
	}

	IrrSprite::IrrSprite( void )
	{
	}

	IrrSprite::~IrrSprite( void )
	{
		removeAllChildrenWithCleanup(true);	
	}


	bool irr_display::IrrSprite::init( const char* texture,bool isPlist /*= false*/ )
	{
		CCSprite* m_pSprite = NULL;
		if(isPlist)
		{
			m_pSprite = CCSprite::createWithSpriteFrameName(texture);
		}
		else
		{
			m_pSprite = CCSprite::create(texture);
		}
		this->addChild(m_pSprite);
		this->setDimensions(m_pSprite->getContentSize().width,m_pSprite->getContentSize().height);
		return true;
	}
}