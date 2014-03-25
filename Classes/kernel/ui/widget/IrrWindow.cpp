#include "IrrWindow.h"
#include "IrrImage.h"
#include "IrrPattern.h"

namespace irr_ui
{
	
	IrrWindow::IrrWindow( void )
		:m_pTitleImage(NULL),
		m_pFrame(NULL)
	{

	}

	IrrWindow::~IrrWindow( void )
	{

	}

	IrrWindow* IrrWindow::create( const char* texture,bool isPlist /*= false*/ )
	{
		IrrWindow* pRet = new IrrWindow();
		if(pRet &&pRet->init(texture,isPlist))
		{
			pRet->autorelease();
			return pRet;
		}
		IRR_SAFE_DELETE(pRet);
		return NULL;
	}


	bool IrrWindow::init( const char* texture,bool isPlist /*= false*/ )
	{

		return true;
	}
}