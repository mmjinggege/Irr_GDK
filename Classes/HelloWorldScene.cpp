#include "HelloWorldScene.h"

using namespace cocos2d;

#include "IrrButton.h"
#include "IrrCamera.h"

using namespace irr_ui;


CCScene* HelloWorld::scene()
{
    CCScene * scene = NULL;
    do 
    {
        // 'scene' is an autorelease object
        scene = CCScene::create();
        CC_BREAK_IF(! scene);

        // 'layer' is an autorelease object
        HelloWorld *layer = HelloWorld::create();
        CC_BREAK_IF(! layer);

        // add layer as a child to scene
        scene->addChild(layer);
    } while (0);
    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool HelloWorld::init()
{
    bool bRet = false;
    do 
    {
        //////////////////////////////////////////////////////////////////////////
        // super init first
        //////////////////////////////////////////////////////////////////////////

        CC_BREAK_IF(! CCLayer::init());

        //////////////////////////////////////////////////////////////////////////
        // add your codes below...
        //////////////////////////////////////////////////////////////////////////

        // 1. Add a menu item with "X" image, which is clicked to quit the program.

        // Create a "close" menu item with close icon, it's an auto release object.
        CCMenuItemImage *pCloseItem = CCMenuItemImage::create(
            "CloseNormal.png",
            "CloseSelected.png",
            this,
            menu_selector(HelloWorld::menuCloseCallback));
        CC_BREAK_IF(! pCloseItem);

        // Place the menu item bottom-right conner.
        pCloseItem->setPosition(ccp(CCDirector::sharedDirector()->getWinSize().width - 20, 20));

        // Create a menu with the "close" menu item, it's an auto release object.
        CCMenu* pMenu = CCMenu::create(pCloseItem, NULL);
        pMenu->setPosition(CCPointZero);
        CC_BREAK_IF(! pMenu);

        // Add the menu to HelloWorld layer as a child layer.
        this->addChild(pMenu, 1);

        // 2. Add a label shows "Hello World".

        // Create a label and initialize with string "Hello World".
        CCLabelTTF* pLabel = CCLabelTTF::create("Hello World", "Arial", 24);
        CC_BREAK_IF(! pLabel);

        // Get window size and place the label upper. 
        CCSize size = CCDirector::sharedDirector()->getWinSize();
        pLabel->setPosition(ccp(size.width / 2, size.height - 50));

        // Add the label to HelloWorld layer as a child layer.
        this->addChild(pLabel, 1);

        // 3. Add add a splash screen, show the cocos2d splash image.
        CCSprite* pSprite = CCSprite::create("HelloWorld.png");
        CC_BREAK_IF(! pSprite);

        // Place the sprite on the center of the screen
        pSprite->setPosition(ccp(size.width/2, size.height/2));

        // Add the sprite to HelloWorld layer as a child layer.
        this->addChild(pSprite, 0);

        bRet = true;
//////////////////////////////////////////////////////////////////////////
		shareCamera->setSceneSize(size.width,size.height);
		this->addChild((CCNode*)(shareCamera->getGUI()));
		
		IrrButton* button = IrrButton::create("CloseNormal.png","CloseSelected.png",false);
		button->setPosition(300,300);
		button->addClickEvent(this,irr_gui_clickselector(HelloWorld::onClickHandler));
		shareCamera->appendToGUI(button);
		std::string name = "btn 0";
		button->setName(name);

		IrrButton* button1 = IrrButton::create("CloseNormal.png","CloseSelected.png",false);
		button1->addClickEvent(this,irr_gui_clickselector(HelloWorld::onClickHandler));
		std::string name1 = "btn 1";
		button1->setName(name1);
		button1->setPosition(300,290);
		shareCamera->appendToGUI(button1);
		CCLabelTTF *pLable = CCLabelTTF::create("中国我唉唉和圣殿", "Marker Felt", 30);
		pLable->setPosition(ccp(200,200));
		this->addChild(pLable);
    } while (0);

    return bRet;
}

void HelloWorld::menuCloseCallback(CCObject* pSender)
{
    // "close" menu item clicked
    CCDirector::sharedDirector()->end();
}

void HelloWorld::onClickHandler( CCObject* sender )
{
	LOG("onClickHandler");
	IrrButton* pBtn = (IrrButton*)sender;
	CCLOG("click:%s",pBtn->getName().c_str());
}


