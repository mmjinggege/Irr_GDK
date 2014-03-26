#ifndef _CMAINLAYER_H_
#define _CMAINLAYER_H_

#include "IrrLayer.h"

using namespace irr_display;


class IMainLayerDelegate : public ILayerDelegate
{
public:
	IMainLayerDelegate(void);
	~IMainLayerDelegate(void);

	virtual void handleMove( IrrLayerEvent& evt );
	virtual void handleDown( IrrLayerEvent& evt );
	virtual void handleUp( IrrLayerEvent& evt );
	virtual void handleClick( IrrLayerEvent& evt );
};


class CMainLayer : public IrrLayer
{
public:
	static const int MAP_ROW_NUMBER = 4; //4
	static const int MAP_COL_NUMBER = 3; //3
	static const int SINGLE_MAP_TILE_WIDTH = 720;
	static const int SINGLE_MAP_TILE_HEIGHT = 660;
	static const char* MAP_FORMAT_STRING;
public:
	CMainLayer(void);
	~CMainLayer(void);

	STATIC_CREATE_CONSTRUCTION(CMainLayer);

	bool init();

	void initMap();
};

#endif	//_CMAINLAYER_H_
