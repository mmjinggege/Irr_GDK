#include "HelloWorldScene.h"

using namespace cocos2d;

#include "IrrButton.h"
#include "IrrCamera.h"
#include "IrrPngLabel.h"
#include "IrrTextFieldTTF.h"
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
<<<<<<< HEAD

         bRet = true;
// //////////////////////////////////////////////////////////////////////////
=======
		 
        bRet = true;
		bRet = true;
//////////////////////////////////////////////////////////////////////////
>>>>>>> a3b7a3c37ef805fa1138aae12cc1d400d1208495
		shareCamera->setSceneSize(size.width,size.height);
		this->addChild((CCNode*)(shareCamera->getGUI()));
	
		IrrButton* button = IrrButton::create("CloseNormal.png","CloseSelected.png",false);
		button->setPosition(300,100);
		button->addClickEvent(this,irr_gui_clickselector(HelloWorld::onClickHandler));
	//	shareCamera->appendToGUI(button);
		std::string name = "btn 0";
		button->setName(name);

		IrrButton* button1 = IrrButton::create("CloseNormal.png","CloseSelected.png",false);
		button1->addClickEvent(this,irr_gui_clickselector(HelloWorld::onClickHandler));
		std::string name1 = "btn 1";
		button1->setName(name1);
		button1->setPosition(300,310);
		shareCamera->appendToGUI(button1);

		IrrButton* button2 = IrrButton::create("CloseNormal.png","CloseSelected.png",false);
		button2->addClickEvent(this,irr_gui_clickselector(HelloWorld::onClickHandler));
		std::string name2 = "btn 2";
		button2->setName(name2);
		//button2->setPosition(310,300);
		button1->addWidget(button2);
		//shareCamera->appendToGUI(button2);
// 		IrrPngLabel* pPngLabel = IrrPngLabel::create("123123sfdgfgsf2");
// 		pPngLabel->setPosition(300,300);
// 		pPngLabel->setDimensions(30,300);
// 
// 		//pPngLabel->setFontSize(18);
// 		//pPngLabel->setVerticalTextAlign(kCCVerticalTextAlignmentBottom);
// 		pPngLabel->setTextAlign(kCCTextAlignmentCenter);
// 		pPngLabel->setTouchable(true);
// 		shareCamera->appendToGUI(pPngLabel);
		
		//pPngLabel->setDimensions(300,200);

		IrrTextFieldTTF* pLabelTTF = IrrTextFieldTTF::create();
		pLabelTTF->setString("123123123123123sfds");
		shareCamera->appendToGUI(pLabelTTF);
		pLabelTTF->setPosition(200,200);

		CCNode* pChild1 = CCNode::create();
		CCNode* pChild2 = CCNode::create();
		this->addChild(pChild1);
		this->addChild(pChild2);

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


