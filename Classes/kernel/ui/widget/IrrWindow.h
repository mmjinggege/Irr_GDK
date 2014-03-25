#ifndef _IRRWINDOW_H_
#define _IRRWINDOW_H_

#include "IrrContainer.h"

namespace irr_ui
{

	class IrrImage;
	class IrrPanel;

	class IrrWindow : public IrrContainer
	{
	public:
		static IrrWindow* create(const char* texture,bool isPlist = false);
	public:
		IrrWindow(void);
		~IrrWindow(void);
	private:
		bool init(const char* texture,bool isPlist = false);
	protected:
		IrrImage* m_pTitleImage;
		IrrPanel* m_pFrame;
	};
}

#endif	//_IRRWINDOW_H_