#ifndef _IRRLAYER_H_
#define _IRRLAYER_H_

#include "IrrNode.h"
#include "IrrUIEvent.h"

using namespace irr_event;

namespace irr_display
{

	class ILayerDelegate
	{
	public:
		virtual void handleMove( IrrLayerEvent& evt) = 0;
		virtual void handleDown( IrrLayerEvent& evt) = 0;
		virtual void handleUp( IrrLayerEvent& evt) = 0;
		virtual void handleClick( IrrLayerEvent& evt) = 0;
	};


	class IrrLayer : public IrrNode,public CCTouchDelegate
	{
	public:
		IrrLayer(void);
		virtual ~IrrLayer(void);
		virtual bool init();
		virtual void onEnter();
		virtual void onExit();
		inline void setDelegate(ILayerDelegate* delegate) {m_pLayerDelegate = delegate;}
		//////////////////////////////////////////////////////////////////////////
		//CCTouchDelegate
		virtual bool ccTouchBegan(CCTouch *pTouch, CCEvent *pEvent);
		virtual void ccTouchMoved(CCTouch *pTouch, CCEvent *pEvent);
		virtual void ccTouchEnded(CCTouch *pTouch, CCEvent *pEvent);
		virtual void ccTouchCancelled(CCTouch *pTouch, CCEvent *pEvent);

	private:
		ILayerDelegate* m_pLayerDelegate;
		bool m_bInit;
	};
}

#endif	//_IRRLAYER_H_