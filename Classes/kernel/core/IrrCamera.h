#ifndef _IRRCAMERA_H_
#define _IRRCAMERA_H_

#include "IrrSingleton.h"
#include "IrrGeom.h"

namespace irr_display
{
	class IrrNode;
}

namespace irr_ui
{
	class IrrWidget;
	class IrrGui;
}

using namespace irr_ui;
using namespace irr_display;

namespace irr_core
{
	class IrrCamera : public irr_base::IrrSingleton<IrrCamera>
	{
	public:
		void setSceneSize(float width,float height);
		float getSceneWidth() const;
		float getSceneHeight() const;
		IrrVector2D convertToSceneViewSpace(IrrVector2D& pt,IrrNode* target = NULL );
		IrrRect convertToSceneView(IrrRect& rect);
		bool checkTouchPosInRectAtAnchor(IrrRect& viewRect,IrrVector2D& touchPos,IrrVector2D anchor);
		IrrGui* getGUI();
		void appendToGUI(IrrWidget* widget);
		void removeToGUI(IrrWidget* widget,bool isDel = true);
	private:
		friend class irr_base::IrrSingleton<IrrCamera>;
		IrrCamera(void);
		~IrrCamera(void);
		IrrSize m_SceneSize;
		IrrGui* m_IrrGui;
	};
}
#define shareCamera IrrCamera::getInstance()
#define shareGui IrrCamera::getInstance()->getGUI()
#endif	//_IRRCAMERA_H_