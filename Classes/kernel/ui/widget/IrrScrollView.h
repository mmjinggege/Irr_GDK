#ifndef _IRR_SCROLLVIEW_H_
#define _IRR_SCROLLVIEW_H_
#include "IrrContainer.h"
using namespace irr_display;

namespace irr_ui
{
	typedef enum
	{
		IrrScrollViewTypeHorizontal = 0,
		IrrScrollViewTypeVertical,
		IrrScrollViewBoth,
	}CCScrollViewType;

	class IrrScrollView:public IrrContainer
	{
	public:
		static IrrScrollView* create(IrrSize& dimensions);
		IrrScrollView();
		virtual ~IrrScrollView();
	public:
		//////////////////////////////////////////////////////////////////////////
		//
// 		virtual void setInnerSize(IrrSize size);
// 		IrrSize getInnerSize();
		//////////////////////////////////////////////////////////////////////////
		void setScrollViewType(CCScrollViewType type);
		CCScrollViewType getScrollViewType();
	private:
		bool init(IrrSize& dimensions);

		void handleDown(IrrUIEvent& event); 
		void handleMove(IrrUIEvent& event);
		void handleUp(IrrUIEvent& event);
		void handleClick(IrrUIEvent& event);
		//////////////////////////////////////////////////////////////////////////
		void setClippingToBounds(bool var);
		bool isClippingToBounds();
		//////////////////////////////////////////////////////////////////////////
		void setBounceable(bool var);
		bool getBounceable();
	private:
		IrrContainer* m_pContainer;
		CCScrollViewType m_type;
		//IrrSize m_InnerSize;
		bool m_bClippingToBounds;
		bool m_bBounceable;
		bool m_bIsMoved;
	};
}


#endif