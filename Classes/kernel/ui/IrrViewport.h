#ifndef _IRRVIEWPORT_H_
#define _IRRVIEWPORT_H_

#include "IrrContainer.h"

namespace irr_ui
{
	/************************************************************************/
	/*
		@Desc¬ﬂº≠ ”Õº≤„
	*/
	/************************************************************************/
	class IrrViewport : public IrrContainer
	{
	public:
		IrrViewport(void);
		~IrrViewport(void);

		virtual bool init();
		virtual void onInitCallBack();
		virtual void onRemoveCallBack();

		void setGuid(IrrGUID guid);
		IrrGUID getGuid() const;

		void setIsMark(bool val);
		bool isMark() const;
	public:
		virtual void onEnter();
		virtual void onExit();

	private:
		IrrGUID m_Guid;
		bool m_isInit;
		bool m_bIsMark;
	};
}
#endif	//_IRRVIEWPORT_H_