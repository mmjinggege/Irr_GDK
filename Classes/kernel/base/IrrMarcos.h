#ifndef _IRRMARCOS_H_
#define _IRRMARCOS_H_

//////////////////////////////////////////////////////////////////////////
#include "cocos2d.h"
#include "cocos-ext.h"
USING_NS_CC;
USING_NS_CC_EXT;

#ifndef LOG
#define LOG		cocos2d::CCLog
#endif
#define  ENTERFUNC()    LOG("enter func %s in %s",__FUNCTION__, __FILE__)
#define  LVFUNC()       LOG("leave func %s in %s",__FUNCTION__, __FILE__)


#define CREATE_PROPERTY(varType,varName,funName)\
protected:varType varName;\
public: inline varType get##funName(void) {return varName;}\
public: inline void set##funName(varType var) {varName = var;}

#define CREATE_PROPERTY_UNIMPLEMENT(varType,varName,funName)\
protected:varType varName;\
public: varType get##funName(void);\
public: virtual void set##funName(varType var);\

//未实现函数定义
#define CREATE_PROPERTY_BY_BOOL_UNIMPLEMENT(varType,varName,funName)\
protected:bool varName;\
public: virtual bool is##funName(void);\
public: virtual void set##funName(bool var);

#define CREATE_PROPERTY_BY_BOOL(varName,funName)\
protected:bool varName;\
public: virtual bool is##funName(void) {return varName;}\
public: virtual void set##funName(bool var) {varName = var;}

#define CREATE_PROPERTY_BY_REF(varType, varName, funName)\
protected: varType varName;\
public: virtual const varType& get##funName(void) {return varName;}\
public: virtual void set##funName(const varType& var) {varName = var;}

#define CREATE_PROPERTY_READONLY(varType, varName, funName)\
protected: varType varName;\
public: virtual varType get##funName(void) const { return varName; }

#define CREATE_PROPERTY_READONLY_BY_REF(varType, varName, funName)\
protected: varType varName;\
public: virtual const varType& get##funName(void) const { return varName; }

#define STATIC_CREATE_CONSTRUCTION(__TYPE__) \
	static __TYPE__* create() \
{ \
	__TYPE__ *pRet = new __TYPE__(); \
	if (pRet && pRet->init()) \
	{ \
		pRet->autorelease(); \
		return pRet; \
	} \
	else \
	{ \
		delete pRet; \
		pRet = NULL; \
		return NULL; \
	} \
}



// 增加CC只是为了统一命名，使用时方便
#define IRR_RETURN_IF(cond)						if(cond) return
#define IRR_CHECK_NULL(instance)				if(instance == 0) return
#define IRR_SAFE_DELETE_ARRAY(p)				do { if(p) { delete[] (p); (p) = 0; } } while(0)
#define IRR_SAFE_DELETE(p)						do {if(p) {delete(p);(p)=0;	}} while(0)

#define IRR_SAFE_RELEASE(p)            do { if(p) { (p)->release(); } } while(0)

#define IRR_SAFE_RETAIN(p)            do { if(p) { (p)->retain(); } } while(0)

//abs
#define  tabs(a)  (((a) > 0)?(a):(-(a)))
//max
#define  tmax(a,b) (((a) >= (b))?(a):(b))
//min
#define  tmin(a,b) (((a) <= (b))?(a):(b))
/* Define NULL pointer value */
#ifndef NULL
#define NULL    0
#endif

#define irr_cos(angle) cos(angle)

#if defined(_USRDLL)
#define IRR_DLL     __declspec(dllexport)
#else         /* use a DLL library */
#define IRR_DLL     __declspec(dllimport)
#endif

#include <assert.h>

#if CC_DISABLE_ASSERT > 0
#define IRR_ASSERT(cond)
#else
#define IRR_ASSERT(cond)    assert(cond)
#endif
#define CC_UNUSED_PARAM(unusedparam) (void)unusedparam

#define GET_START_TIME\
	cc_timeval timeA;\
	CCTime::gettimeofdayCocos2d(&timeA,NULL);

#define GET_END_TIME\
	cc_timeval timeB;\
	CCTime::gettimeofdayCocos2d(&timeB,NULL);

#if (CC_TARGET_PLATFORM == CC_PLATFORM_WIN32)
#define LOG_TIME(tag)\
	double dt = CCTime::timersubCocos2d(&timeA,&timeB);\
	LOG(tag##"using time [%lf] ms",dt);
#else
#define LOG_TIME(tag)
#endif


// 读取常量值，结果 = 值/10000
#define INIT_CONST_INFO(name) \
	float f##name = 0.f; \
	float Get##name() \
{ \
	if (f##name == 0.f) \
{ \
	f##name = shareConstReader->getConstInfoByName(#name).value/10000; \
} \
	return f##name; \
}


#define USING_IRR_BASE						  using namespace irr_base
#define USING_IRR_MANAGER                     using namespace irr_manager
#define USING_IRR_CORE                        using namespace irr_core
#define USING_IRR_UTILS                       using namespace irr_utils
#define USING_IRR_UI                          using namespace irr_ui
#define USING_IRR_EVENT                       using namespace irr_event
#endif //_IRRMARCOS_H_