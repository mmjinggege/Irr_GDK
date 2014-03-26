#include "IrrCamera.h"
#include "IrrNode.h"
#include "IrrGeom.h"
#include "IrrWidget.h"
#include "IrrGui.h"

// static float Correct = Mathutils.cos( -Math.PI / 6) * Math.SQRT2;

namespace irr_core
{
	IrrCamera::IrrCamera(void)
		:m_IrrGui(NULL)
	{
		
	}

	IrrCamera::~IrrCamera( void )
	{
		m_IrrGui->clearAllWidget();
		m_IrrGui->removeFromParentAndCleanup(true);
		IRR_SAFE_DELETE(m_IrrGui);
	}
	
	void IrrCamera::setSceneSize( float width,float height )
	{
		m_SceneSize.setSize(width,height);
		if(m_IrrGui == NULL)
			m_IrrGui = new IrrGui(width,height);
		else
			m_IrrGui->setRect(IrrRect(0,0,width,height));
	}

	float IrrCamera::getSceneWidth() const
	{
		return m_SceneSize.width;
	}

	float IrrCamera::getSceneHeight() const
	{
		return m_SceneSize.height;
	}

	IrrVector2D IrrCamera::convertToSceneViewSpace( IrrVector2D& pt,IrrNode* target /*= NULL */ )
	{
		IrrVector2D pos;
		if(target == NULL)
		{
			pos.X = pt.X;
			pos.Y = getSceneHeight() - pt.Y;
		}
		else
		{
			pos = target->getRect().origin;
			pos.Y = getSceneHeight() - pos.Y;
			target->setPosition(pos);
		}
		return pos;
	}

	IrrRect IrrCamera::convertToSceneView( IrrRect& rect )
	{
		IrrRect newRect;
		newRect = rect;
		newRect.origin.Y = getSceneHeight() -newRect.origin.Y;
		return newRect;
	}


	bool IrrCamera::checkTouchPosInRectAtAnchor( IrrRect& viewRect,IrrVector2D& touchPos,IrrVector2D anchor )
	{
		IrrVector2D tmpPos = touchPos;
		tmpPos.Y = getSceneHeight() - tmpPos.Y;
		IrrRect tmpRec = viewRect;
		viewRect.origin.X -= viewRect.size.width * anchor.X;
		viewRect.origin.Y -= viewRect.size.height * anchor.Y;
		//tmpRect.origin.Y -= viewRect.size.height * anchor.Y;
		return viewRect.containsVector2D(tmpPos);
	}

	IrrGui* IrrCamera::getGUI()
	{
		return m_IrrGui;
	}

	void IrrCamera::appendToGUI( IrrWidget* widget )
	{
		if(widget && m_IrrGui)
		{
			m_IrrGui->addWidget(widget,widget->getOrigin());
		}
	}
	

	void IrrCamera::removeToGUI( IrrWidget* widget,bool isDel /*= true*/ )
	{
		if(widget && m_IrrGui)
		{
			m_IrrGui->removeWidget(widget,isDel);
		}
	}
}