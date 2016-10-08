//
//  OperatorLayer.hpp
//  TestArmature
//
//  Created by student01 on 16/9/22.
//
//

#ifndef OperatorLayer_hpp
#define OperatorLayer_hpp

#include "cocos2d.h"
USING_NS_CC;
class OperatorLayer : public cocos2d::Layer
{
public:
    OperatorLayer();
    ~OperatorLayer();
    virtual bool init();
    CREATE_FUNC(OperatorLayer);
    virtual bool onTouchBegan(Touch *touch, Event *unused_event);
    virtual void onTouchMoved(Touch *touch, Event *unused_event);
    virtual void onTouchEnded(Touch *touch, Event *unused_event);
    Vec2 direction;
    float distance;
private:
    void showJoyStick(Vec2 pos);
    void hideJoyStick();
    void updateJoyStick(Vec2& p, float dis);
    Sprite* JoyStick;
    Sprite* JoyStickBg;
    
    
};

#endif /* OperatorLayer_hpp */
