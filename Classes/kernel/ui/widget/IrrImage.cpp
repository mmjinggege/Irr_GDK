#include "IrrImage.h"
#include "IrrSprite.h"

using namespace irr_display;

namespace irr_ui
{


	IrrImage::IrrImage( void )
	{

	}

	IrrImage::~IrrImage( void )
	{
		removeAllChildrenWithCleanup(true);
	}

	IrrImage* IrrImage::create( const char* texture,bool isPlist /*= false*/ )
	{
		IrrImage* pRet = new IrrImage();
		if(pRet && pRet->init(texture,isPlist))
		{
			pRet->autorelease();
			return pRet;
		}
		IRR_SAFE_DELETE(pRet);
		return NULL;
	}
	
	bool IrrImage::init( const char* texture,bool isPlist /*= false*/ )
	{
		IrrSprite* pTarget = IrrSprite::create(texture,isPlist);
		this->addChild(pTarget);
		return true;
	}
}