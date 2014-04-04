// #ifndef _IRR_UIEVENTDISPATCHER_H_
// #define _IRR_UIEVENTDISPATCHER_H_
// 
// #include "IrrSingleton.h
// #include <vector>
// 
// namespace irr_core
// {	
// 	class IrrUIEventDispatcher: public irr_base::IrrSingleton<IrrUIEventDispatcher>
// 	{
// 	public:
// 		void addTouchAbleChild(IrrWidget* pWight);
// 		void removeTouchAbleChild(IrrWidget* pWight);
// 		void clearTouchAbleChildren();
// 		std::vector<IrrWidget*> getTouchAbleChildren();
// 
// 	private:
// 		IrrUIEventDispatcher();
// 		~IrrUIEventDispatcher();
// 		friend class irr_base::IrrSingleton<IrrUIEventDispatcher>;
// 		std::vector<IrrWidget*> m_vecTouchAbleChildern;
// 	};
// }
// 
// #endif