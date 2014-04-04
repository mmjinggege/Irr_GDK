// #ifndef _IRR_RICHTEXT_H_
// #define _IRR_RICHTEXT_H_
// 
// #include "IrrContainer.h"
// using namespace irr_display;
// namespace irr_ui
// {
// 
// 	typedef enum
// 	{
// 		type_no_link,//纯文本
// 		type_link_click,//有下划线，可点击    
// 		type_link,//有下划线，不可点击
// 		type_click//可点击，无下划线
// 	}LinkLabelType;
// 
// 	struct CssData
// 	{
// 		int fontSize;
// 		int lineSpacing;
// 		int leftPadding;//左位置便宜
// 		ccColor3B color3;
// 		bool isNewLine;
// 		LinkLabelType labelType;//0：纯文本    1：有下划线，可点击   2：有下划线，不可点击
// 
// 		CssData()
// 			:fontSize(20),lineSpacing(0),labelType(type_no_link),isNewLine(false),color3(ccc3(255,0,255)),leftPadding(0)
// 		{
// 		}
// 	};
// 
// 	enum RichTextType
// 	{
// 		RichText_Text = 0,
// 		RichText_Image = 1
// 	};
// 	struct RichTextData
// 	{
// 		RichTextType mType;
// 		std::string imgFileName;
// 		bool bImgPlist;
// 		std::string content;
// 		int cmdId;
// 		void* pData;
// 		CssData css_data;
// 
// 		RichTextData():content(""),cmdId(0),pData(NULL),mType(RichText_Text),imgFileName(""),bImgPlist(false)
// 		{
// 		}
// 	};
// 
// 	typedef std::vector<RichTextData> VEC_RICHVIEW_DATA;
// 
// 	class RichTextUtil
// 	{
// 	public:
// 		RichTextUtil();
// 		~RichTextUtil();
// 
// 		static RichTextUtil* sharedTextViewUtil();
// 
// 		CssData getTmpCssData();
// 		RichTextData getTmpRichTextData(const std::string& text, int comandId = 0, void* pData = NULL);
// 		RichTextData getTmpRichTextData(CssData& cssData ,const std::string& text, int comandId = 0, void* pData = NULL);
// 	};
// 
// 	typedef void (CCObject::* RichText_CallBackFun)(int, void*);
// 	#define richtext_callbackfun(_SELECTOR) (RichText_CallBackFun)(&_SELECTOR)
// //////////////////////////////////////////////////////////////////////////
// 
// 	typedef enum 
// 	{
// 		TEXTVIEW_TOP,
// 		TEXTVIEW_CENTER,
// 		TEXTVIEW_BOTTOM,
// 		TEXTVIEW_UNKNOW
// 	}LinkLabelVecAlign;
// 
// 	class CCLinkLabelTTF:public IrrContainer
// 	{
// 	public:
// 		CCLinkLabelTTF();
// 		~CCLinkLabelTTF();
// 		static CCLinkLabelTTF* create(LinkLabelType labelType);
// 		void setCallFunData( int comandId, void* pData){ m_cmdId = comandId; m_pData = pData;}
// 		int getCmdId(){ return m_cmdId; }
// 		void* getData(){ return m_pData; }
// 		void setVerAlignment(LinkLabelVecAlign alignment){verticalAlignment = alignment;}
// 		LinkLabelVecAlign getVerAlignment(){return verticalAlignment;}
// 	private:
// 		bool init( LinkLabelType labelType );
// 	private:
// 		LinkLabelType m_labelType;
// 
// 		void* m_pData;
// 		int m_cmdId;
// 		LinkLabelVecAlign verticalAlignment;//复文本编辑排版用
// 	};
// //////////////////////////////////////////////////////////////////////////
// 	class TextView:public IrrContainer
// 	{
// 	public:
// 		TextView();
// 		~TextView();
// 		static TextView* create(const VEC_RICHVIEW_DATA& vec_data,const CCSize& size, bool bLimitHeight = false);
// 		void setData(const VEC_RICHVIEW_DATA& vec_data,const CCSize& size);
// 		void setCallBackFun(CCObject* pTarget, RichText_CallBackFun callFun){ m_pTarget = pTarget; m_CallFun = callFun; };
// 
// 		CCSize getCurSize(){ return m_curSize;}
// 		int getCurLineCount(){ return m_curLineCount;}
// 	private:
// 		bool init(const VEC_RICHVIEW_DATA& vec_data,const CCSize& size,bool bLimitHeight);
// 		void setLayout();
// 
// 		void setLayoutLabel(std::vector<CCNode*> &vec_nodeList, CCPoint& nowPos, float& maxCurLineLabelH, float& maxCurLinePosY,const VEC_RICHVIEW_DATA& textViewData);
// 		void setLayoutImg( std::vector<CCNode*>& vec_nodeList, CCPoint& nowPos, float& maxCurLineLabelH, float& maxCurLinePosY,const VEC_RICHVIEW_DATA& textViewData);
// 
// 		bool setWrap(std::vector<CCNode*>& vec_nodeList,CCPoint& nowPos, float& maxCurLineLabelH, float& maxCurLinePosY);
// 
// 		//	void visit();
// 		//	void beforeDraw();
// 		//	void afterDraw();
// 		CCRect getViewRect();
// 
// 		void getSingleTextSize(std::string& content, std::string fontName, float fontSize, CCSize& singleSize);
// 
// 		void reSetPosY(std::vector<CCNode*>& vec_nodeList, float maxCurLineLabelH);
// 
// 		std::string splitTxt(std::string txt,int count,int offset=0);
// 		int getTxtLen(const std::string& txt);
// 		void didLinkClick(CCNode* pSender);
// 
// 		bool isEnglish(char txt);
// 	private:
// 		VEC_RICHVIEW_DATA m_vec_data;
// 		CCSize m_size;
// 
// 		RichText_CallBackFun m_CallFun;
// 		CCObject* m_pTarget;
// 		bool m_bLimitHeight;
// 
// 		CCSize m_curSize;
// 		float m_MaxWidth;//文本当前达到的最大宽度
// 		int m_curLineCount;//有几行
// 	};
// 
// 
// }
// #endif