#include "IrrViewport.h"

namespace irr_ui
{


	IrrViewport::IrrViewport( void )
		:m_isInit(false),
		m_bIsMark(false),
		m_Guid(0)
	{

	}

	IrrViewport::~IrrViewport( void )
	{

	}

	bool IrrViewport::init()
	{
		if(!m_isInit)
		{
			return false;
		}
		m_isInit = true;
		this->setTouchable(true);
		return true;
	}

	void IrrViewport::setGuid( IrrGUID guid )
	{
		m_Guid = guid;
	}

	IrrGUID IrrViewport::getGuid() const
	{
		return m_Guid;
	}

	void IrrViewport::setIsMark( bool val )
	{
		m_bIsMark = val;
	}

	bool IrrViewport::isMark() const
	{
		return m_bIsMark;
	}

	void IrrViewport::onEnter()
	{
		IrrContainer::onEnter();
	}

	void IrrViewport::onExit()
	{
		IrrContainer::onExit();
	}

	void IrrViewport::onInitCallBack()
	{
		;//todo
	}

	void IrrViewport::onRemoveCallBack()
	{
		;//todo
	}
}