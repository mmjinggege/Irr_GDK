#ifndef _IRR_TEXTFIELDTTF_H_
#define _IRR_TEXTFIELDTTF_H_

//#include "CCLabelTTF.h"
#include "IrrWidget.h"

using namespace irr_display;

namespace irr_ui
{
	class IrrTextFieldTTF:public IrrWidget
	{
	public:
		IrrTextFieldTTF();
		virtual ~IrrTextFieldTTF();
	public:
		static IrrTextFieldTTF* create(const char *string, const char *fontName, float fontSize);
		static IrrTextFieldTTF* create(const char *string, const char *fontName, float fontSize, const CCSize& dimensions, CCTextAlignment hAlignment);
		static IrrTextFieldTTF* create(const char *string, const char *fontName, float fontSize, const CCSize& dimensions, CCTextAlignment hAlignment, CCVerticalTextAlignment vAlignment);
		static IrrTextFieldTTF* create();
		//////////////////////////////////////////////////////////////////////////
		virtual void setString(const char *label);
		virtual const char* getString(void);
		//////////////////////////////////////////////////////////////////////////
		CCTextAlignment getHorizontalAlignment();
		void setHorizontalAlignment(CCTextAlignment alignment);
		CCVerticalTextAlignment getVerticalAlignment();
		void setVerticalAlignment(CCVerticalTextAlignment verticalAlignment);
		//////////////////////////////////////////////////////////////////////////
		void setDimensions( IrrSize& size );
		void setDimensions( float width,float height );
		void setLabelDimensions( float width,float height );
		CCSize getLabelDimensions();
		//////////////////////////////////////////////////////////////////////////
		float getFontSize();
		void setFontSize(float fontSize);
		//////////////////////////////////////////////////////////////////////////
		const char* getFontName();
		void setFontName(const char *fontName);
		//////////////////////////////////////////////////////////////////////////
		void enableShadow(const CCSize &shadowOffset, float shadowOpacity, float shadowBlur, bool mustUpdateTexture = true);
		void disableShadow(bool mustUpdateTexture = true);
		//////////////////////////////////////////////////////////////////////////
		void enableStroke(const ccColor3B &strokeColor, float strokeSize, bool mustUpdateTexture = true);
		void disableStroke(bool mustUpdateTexture = true);
		//////////////////////////////////////////////////////////////////////////
		void setFontFillColor(const ccColor3B &tintColor, bool mustUpdateTexture = true);
	private:
		bool init(const char *string, const char *fontName, float fontSize);
		bool init(const char *string, const char *fontName, float fontSize, const CCSize& dimensions, CCTextAlignment hAlignment);
		bool init(const char *string, const char *fontName, float fontSize, const CCSize& dimensions, CCTextAlignment hAlignment, CCVerticalTextAlignment vAlignment);
		bool init();
	private:
		CCLabelTTF* m_pLabel;
	};
}



#endif