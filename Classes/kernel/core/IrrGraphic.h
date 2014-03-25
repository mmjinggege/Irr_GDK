#ifndef _IRRGRAPHIC_H_
#define _IRRGRAPHIC_H_

#include "IrrMarcos.h"
#include <stack>
#include "IrrGeom.h"
#include "IrrSingleton.h"
#include "IrrColor.h"

namespace irr_core
{
	class IrrGraphic : public irr_base::IrrSingleton<IrrGraphic>
	{
	public:
		 void setGraphicSize(float iWidth,float iHeight);
		 void setColor(IrrColor& color);

		 void drawImage(const CCTexture2D* image,int srcX,int srcY,int dstX,int dstY,int width,int height,unsigned char alpha = 255);

		 void drawPoint(float x, float y);

		 void drawLine(float x1, float y1, float x2, float y2);

		 void drawRectangle(const IrrRect& rectangle);

		 void fillRectangle(const IrrRect& rectangle);
		 //////////////////////////////////////////////////////////////////////////
		 bool pushClipArea(IrrRect area);
		 void popClipArea(void);
		 const IrrClipRect& getCurrentClipArea(void);
		 void reset(void);
	public:	
		void beginDraw();
		void endDraw();
	protected:
	private:
		friend class irr_base::IrrSingleton<IrrGraphic>;
		IrrGraphic(void);
		~IrrGraphic(void);
	private:
		bool pushClipAreaInner(IrrRect area);
		std::stack<IrrClipRect> m_ClipStack;
		float m_Width;
		float m_Height;
		//used for reader image
		CCGLProgram* m_pShader;
		IrrColor  m_Color;
	};
}

#endif	//_IRRGRAPHIC_H_