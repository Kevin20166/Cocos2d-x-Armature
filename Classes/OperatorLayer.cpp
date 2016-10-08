//
//  OperatorLayer.cpp
//  TestArmature
//
//  Created by student01 on 16/9/22.
//
//

#include "OperatorLayer.hpp"
OperatorLayer::OperatorLayer():JoyStick(NULL), JoyStickBg(NULL)
{

}
OperatorLayer::~OperatorLayer()
{
    
}
bool OperatorLayer::init()
{
    if (!Layer::init()) {
        return false;
    }
    JoyStick = Sprite::create("Joy.png");
    JoyStick->setScale(0.5);
    JoyStickBg = Sprite::create("JoyStick.png");
    
    this->addChild(JoyStick, 1);
    this->addChild(JoyStickBg);
    
    auto listener = EventListenerTouchOneByOne::create();
    listener->onTouchBegan = CC_CALLBACK_2(OperatorLayer::onTouchBegan, this);
    listener->onTouchMoved = CC_CALLBACK_2(OperatorLayer::onTouchMoved,this);
    listener->onTouchEnded = CC_CALLBACK_2(OperatorLayer::onTouchEnded, this);
    auto dispacher = Director::getInstance()->getEventDispatcher();
    dispacher->addEventListenerWithSceneGraphPriority(listener, this);
    
    return true;
}
bool OperatorLayer::onTouchBegan(Touch *touch, Event *unused_event)
{
    Size winSize = Director::getInstance()->getWinSize();
    Vec2 p = convertToWorldSpace(touch->getLocation());
    if (p.x <= winSize.width/2) {
        this->showJoyStick(p);
        distance = 0;
    }
    return true;
}
void OperatorLayer::onTouchMoved(Touch *touch, Event *unused_event)
{
    Size winSize = Director::getInstance()->getWinSize();
    Vec2 start = touch->getStartLocation();
    
    if (start.x > winSize.width/2) {
        return;
    }
    Vec2 dest = touch->getLocation();
    float dis = start.getDistance(dest);
    Vec2 direct = (dest - start).getNormalized();
    this->updateJoyStick(direct, dis);
}
void OperatorLayer::onTouchEnded(Touch *touch, Event *unused_event)
{
    this->distance = 0.0;
    this->hideJoyStick();
}
void OperatorLayer::showJoyStick(Vec2 pos)
{
    JoyStick->setPosition(pos);
    JoyStickBg->setPosition(pos);
    JoyStick->setVisible(true);
    JoyStickBg->setVisible(true);
}
void OperatorLayer::hideJoyStick()
{
    JoyStick->setPosition(JoyStickBg->getPosition());
    JoyStickBg->setVisible(false);
    JoyStick->setVisible(false);
}
void OperatorLayer::updateJoyStick(Vec2& p, float dis)
{
    Vec2 start = JoyStickBg->getPosition();
    if (dis < 78 ) {
        JoyStick->setPosition(start + (p*dis));
        //小范围(移动速度慢)
        direction = p/1.5;
        distance = dis/1.5;
    }
    else if(dis > 100) {
        JoyStick->setPosition(start + (p*100/2));
        //大范围(移动速度快)
        direction = p/3;
        distance = dis/3;
    }
    else {
        JoyStick->setPosition(start + (p*78/2));
        //中范围(移动中速)
        direction = p/1.5;
        distance = 78/1.5;
    }
}