#include "CMainLayer.h"
#include "IrrISO.h"

using namespace irr_extends;

const char* CMainLayer::MAP_FORMAT_STRING = "Dib%d.png";

CMainLayer::CMainLayer( void )
{
	
}

CMainLayer::~CMainLayer( void )
{

}

bool CMainLayer::init()
{
	if(!IrrLayer::init())
	{
		return false;
	}	
	initMap();
	IrrISO* iso = new IrrISO(CMainLayer::MAP_COL_NUMBER,CMainLayer::MAP_ROW_NUMBER);
	return true;
}


void CMainLayer::initMap()
{
	int mapIndex = 0;
	CCString str = MAP_FORMAT_STRING;
	for (int i= 0; i < MAP_COL_NUMBER;i++)
	{
		for (int j = 0; j < MAP_ROW_NUMBER;j++)
		{
			mapIndex = i * MAP_ROW_NUMBER + j;
			str.initWithFormat(MAP_FORMAT_STRING,mapIndex+1);
			CCSprite* pTempMapBk = CCSprite::create(str.getCString());
			pTempMapBk->setAnchorPoint(ccp(0.0f,0.f));
			pTempMapBk->setPosition(ccp(j  * pTempMapBk->getContentSize().width,i  * pTempMapBk->getContentSize().height));
			this->addChild(pTempMapBk, -2);
		}
	}
	CCSize sizeMap = CCSizeMake(MAP_ROW_NUMBER * SINGLE_MAP_TILE_WIDTH,MAP_COL_NUMBER * SINGLE_MAP_TILE_HEIGHT);
	this->setContentSize(sizeMap);
	//1上，2左，3下，4右，5左上，6左下，7右下，8右上，9无边
	return;
}


IMainLayerDelegate::IMainLayerDelegate( void )
{
}

IMainLayerDelegate::~IMainLayerDelegate( void )
{
}

void IMainLayerDelegate::handleMove( IrrLayerEvent& evt )
{
	ENTERFUNC();
	CCLOG("handleMove");
	CMainLayer* layer = (CMainLayer*)evt.getTarget();
	layer->updateLocation(evt.getDelta());
	LVFUNC();
}

void IMainLayerDelegate::handleDown( IrrLayerEvent& evt )
{
	ENTERFUNC();
	CCLOG("handleDown");
	LVFUNC();
}

void IMainLayerDelegate::handleUp( IrrLayerEvent& evt )
{
	ENTERFUNC();
	CCLOG("handleUp");
	LVFUNC();
}

void IMainLayerDelegate::handleClick( IrrLayerEvent& evt )
{
	ENTERFUNC();
	CCLOG("handleClick");
	LVFUNC();
}
