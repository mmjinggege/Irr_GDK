//  #ifndef _IRRPNGLABEL_H_
 //  #define _IRRPNGLABEL_H_
 //  
 //  #include "IrrContainer.h"
 //  
 //  using namespace irr_display;
 //  
 //  namespace irr_ui
 //  {
 //  	//////////////////////////////////////////////////////////////////////////
 //  	class IrrPngLabel : public IrrContainer
 //  	{
 //  	public:
 //  		static IrrPngLabel* create(const char* label);
 //  	public:
 //  		IrrPngLabel(void);
 //  		virtual ~IrrPngLabel(void);
 //  
 //  		void handleDown(IrrUIEvent& event);
 //  		void handleUp(IrrUIEvent& event);
 //  		void handleClick(IrrUIEvent& event);
 //  		void addClickEvent(CCObject* target,Irr_GUI_SEL_ClickEvent selector);
 //  		virtual void setTouchable(bool var);
 //  
 //  		CCLabelBMFont* getLabel() {return m_pFontLabel;}
 //  		const char* getFontName();
 //  		float getFontSize();
 //  		void setFontSize(float size);
 //  		void setColor(const cocos2d::ccColor3B &_value);
 //  		const cocos2d::ccColor3B getColor();
 //  
 //  		void setTextAlign(cocos2d::CCTextAlignment align);
 //  		void setVerticalTextAlign(cocos2d::CCVerticalTextAlignment align);
 //  		cocos2d::CCTextAlignment getTextAlignment();
 //  		cocos2d::CCVerticalTextAlignment getVerticalTextAlignment();
 //  
 //  		void setDimensions( IrrSize& size );
 // 		void setDimensions( float width,float height );
 // 	
 //  		CCSize getCharSize(unsigned int index);
 //  	protected:
 //  		bool initWithString(const char* label);
 //  	private:
 //  		CCObject* m_pEventTarget;
 //  		Irr_GUI_SEL_ClickEvent m_pClickSelector;
 //  
 //  		CCLabelBMFont* m_pFontLabel;
 //  		std::string m_baseContent;//原始字符，不可修改
 //  		CCTextAlignment m_Align;
 //  		CCVerticalTextAlignment m_vectorAlign;
 //  		float m_fSize;
 //  		float m_Scale;
 //  	};
 //  }
 //  
 //  #endif	//_IRRBUTTON_H_