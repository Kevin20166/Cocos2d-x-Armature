#include "HelloWorldScene.h"
#include "OperatorLayer.hpp"
using namespace cocostudio;
USING_NS_CC;

Scene* HelloWorld::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::create();
    
    // 'layer' is an autorelease object
    auto layer = HelloWorld::create();

    // add layer as a child to scene
    scene->addChild(layer);

    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool HelloWorld::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !Layer::init() )
    {
        return false;
    }
    
    auto winSize = Director::getInstance()->getVisibleSize();
    
    //加载背景图片
    auto bgSprite = Sprite::create("bg.jpg");
    bgSprite->setPosition(0, 0);
    bgSprite->setAnchorPoint(Vec2(0,0));
    
    d = DrawNode::create();
    addChild(d);
    d2 = DrawNode::create();
    addChild(d2);
    
    this->addChild(bgSprite);
    //加载骨骼动画的文件
    cocostudio::ArmatureDataManager::getInstance()->addArmatureFileInfo("knight.png", "knight.plist", "knight.xml");
    cocostudio::ArmatureDataManager::getInstance()->addArmatureFileInfo("weapon.png", "weapon.plist", "weapon.xml");
    cocostudio::ArmatureDataManager::getInstance()->addArmatureFileInfo("horse.ExportJson");

    
    auto pArmature = Armature::create("Knight_f/Knight");
    pArmature->getAnimation()->playWithIndex(0);//播放第一个动作
    pArmature->setPosition(Vec2(winSize.width/2-50, winSize.height/2+3));

    pArmature->setScale(1.6);
    pArmature->setTag(122);
    this->addChild(pArmature);
    
    
    pArmature->getBoundingBox();
  
    
    auto horse = Armature::create("horse");
    horse->getAnimation()->playWithIndex(0);
    horse->setPosition(Vec2(winSize.width/2, winSize.height/2 - 100));
    this->addChild(horse);
    
//    auto bone = horse->getBone("hero");
//    bone->addDisplay(horse, 0);
//    bone->changeDisplayWithIndex(0, true);
//    bone->setIgnoreMovementBoneData(true);
    
    
    std::string WeaponName[] = {"weapon_f-sword.png",
        "weapon_f-sword2.png",
        "weapon_f-sword3.png",
        "weapon_f-sword4.png",
        "weapon_f-sword5.png",
        "weapon_f-knife.png",
        "weapon_f-hammer.png",};
    
    
    
    for (int i = 0; i < sizeof(WeaponName)/sizeof(WeaponName[0]); i++) {
        auto skin = Skin::createWithSpriteFrameName(WeaponName[i]);
        pArmature->getBone("weapon")->addDisplay(skin, i);
    }
    
    
    //虚拟摇杆初始化
    operatorLayer = OperatorLayer::create();
//    operatorLayer->setPosition(Vec2(200, winSize.height/2 + 100));
    this->addChild(operatorLayer);
    
    
    
    auto listener = EventListenerTouchOneByOne::create();
    listener->onTouchBegan = CC_CALLBACK_2(HelloWorld::onTouchBegan, this);
    listener->onTouchMoved = CC_CALLBACK_2(HelloWorld::onTouchMoved, this);
    listener->onTouchEnded = CC_CALLBACK_2(HelloWorld::onTouchEnded, this);
    
//    auto dispacher = Director::getInstance()->getEventDispatcher();
//    dispacher->addEventListenerWithSceneGraphPriority(listener, this);
    
    
    auto item = MenuItemImage::create("CloseNormal.png", "CloseSelected.png", CC_CALLBACK_1(HelloWorld::menuCloseCallback, this));
    
    auto menu = Menu::create();
    menu->addChild(item);
    menu->setPosition(Vec2(50,50));
    menu->setAnchorPoint(Vec2::ZERO);
    menu->setScale(1.5);
    this->addChild(menu);
    
    this->scheduleUpdate();
    return true;
}
void HelloWorld::move(cocos2d::Vec2 &p)
{
    auto hero = dynamic_cast<Armature*>(this->getChildByTag(122));

}

bool HelloWorld::onTouchBegan(Touch *touch, Event *unused_event)
{
    return true;
}

void HelloWorld::update(float delta)
{
    auto hero = dynamic_cast<Armature*>(this->getChildByTag(122));
    hero->getBone("wepon");
    d->removeFromParent();
    d2->removeFromParent();
    d = DrawNode::create();
    d2 = DrawNode::create();
    CCLog("%f", hero->getBone("weapon")->getDisplayManager()->getBoundingBox().origin.x);
    d->drawRect(Vec2(hero->getPosition().x-hero->getContentSize().width/2, hero->getPosition().y+hero->getContentSize().height), Vec2(hero->getPosition().x+hero->getContentSize().width/2, hero->getPosition().y-hero->getContentSize().height/2), Color4F(46,54,54,1));
    
//    log("%f, %f", hero->getBone("weapon")->getPosition().x,hero->getBone("weapon")->getPosition().y);
    
    
    d2->drawRect(Vec2(hero->getBone("weapon")->getPosition().x-hero->getBone("weapon")->getContentSize().width/2, hero->getBone("weapon")->getPosition().y+hero->getBone("weapon")->getContentSize().height), Vec2(hero->getBone("weapon")->getPosition().x+hero->getBone("weapon")->getContentSize().width/2, hero->getBone("weapon")->getPosition().y-hero->getBone("weapon")->getContentSize().height/2), Color4F(46,54,54,1));
    
    addChild(d);
    addChild(d2);
    hero->stopAllActions();
    if (operatorLayer->direction.x <= 0) {
        hero->setScaleX(-1.6);
    }else if(operatorLayer->direction.x >= 0){
        hero->setScaleX(1.6);
    }
    
    
    
    
    hero->setPosition(hero->getPosition() + (operatorLayer->direction*(operatorLayer->distance/10)));
//    auto move = MoveTo::create(duration, locate);
//    
//    auto callBack = [hero]{
//        hero->getAnimation()->playWithIndex(0);
//    };
//    
//    hero->getAnimation()->playWithIndex(1);
//    hero->runAction(Sequence::create(move, CallFunc::create(callBack), NULL));
    

}

void HelloWorld::mySchedule(float dt)
{

}
void HelloWorld::onTouchMoved(Touch *touch, Event *unused_event)
{
    
}
void HelloWorld::onTouchEnded(Touch *touch, Event *unused_event)
{
    
}

Armature* HelloWorld::createMount(std::string &name, cocos2d::Vec2 &p )
{
    auto armature = Armature::create(name);
    armature->getAnimation()->playWithIndex(0);
    armature->setPosition(p);
    this->addChild(armature);
    return armature;
    
}


void HelloWorld::menuCloseCallback(Ref* pSender)
{
    static int DisplayIndex = -1;
    ++DisplayIndex;
    DisplayIndex = (DisplayIndex)%5;
    auto pArmature = dynamic_cast<Armature*>(this->getChildByTag(122));
    pArmature->getBone("weapon")->changeDisplayByIndex(DisplayIndex,true);

}
