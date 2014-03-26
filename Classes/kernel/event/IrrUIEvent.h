#ifndef _IRRUIEVENT_H_
#define _IRRUIEVENT_H_

#include "IrrNode.h"
#include "IrrGeom.h"

namespace irr_ui
{
	class IrrWidget;
}

using namespace irr_core;
using namespace irr_ui;
using namespace irr_display;
//////////////////////////////////////////////////////////////////////////
namespace irr_event
{
	typedef enum __IrrUIEvent
	{
		IRR_UI_EVENT_DOWN,
		IRR_UI_EVENT_UP,
		IRR_UI_EVENT_CLICK,
		IRR_UI_EVENT_MOVE_IN,
		IRR_UI_EVENT_MOVE,
		IRR_UI_EVENT_MOVE_OUT
	} Irr_UIEvent;

	//////////////////////////////////////////////////////////////////////////
	//ui event
	class IrrUIEvent
	{
	public:
		IrrUIEvent(IrrWidget* target,int evetType)
			:m_pTarget(target),
			m_iEvtType(evetType),
			m_bHandled(false),
			m_bCanceld(false)
		  {}
		~IrrUIEvent(void)
		{
			m_pTarget = 0;
		};
		CREATE_PROPERTY_BY_BOOL(m_bHandled,Handled);
		CREATE_PROPERTY(IrrVector2D,m_pos,Pos);
		CREATE_PROPERTY(int,m_iEvtType,EvtType);
		CREATE_PROPERTY_BY_BOOL(m_bCanceld,Canceled);
		CREATE_PROPERTY(IrrWidget*,m_pTarget,Target);
	};
}


namespace irr_event
{

	typedef enum __IrrLayerEvent
	{
		IRR_LAYER_EVENT_DOWN,
		IRR_LAYER_EVENT_UP,
		IRR_LAYER_EVENT_CLICK,
		IRR_LAYER_EVENT_MOVE_IN,
		IRR_LAYER_EVENT_MOVE,
		IRR_LAYER_EVENT_MOVE_OUT
	} Irr_LayerEvent;


	class IrrLayerEvent
	{
	public:
		IrrLayerEvent(IrrNode* target,int evetType)
			:m_pTarget(target),
			m_iEvtType(evetType),
			m_bHandled(false),
			m_bCanceld(false)
		{}
		~IrrLayerEvent(void){}
		CREATE_PROPERTY_BY_BOOL(m_bHandled,Handled);
		CREATE_PROPERTY(IrrVector2D,m_pos,Pos);
		CREATE_PROPERTY(int,m_iEvtType,EvtType);
		CREATE_PROPERTY_BY_BOOL(m_bCanceld,Canceled);
		CREATE_PROPERTY(IrrNode*,m_pTarget,Target);
		CREATE_PROPERTY(IrrVector2D,m_Delta,Delta);
	};
}

#endif	//_IRRUIEVENT_H_