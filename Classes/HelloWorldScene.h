#ifndef __HELLOWORLD_SCENE_H__
#define __HELLOWORLD_SCENE_H__

#include "cocos2d.h"
#include "cocostudio/cocostudio.h"
class OperatorLayer;
class HelloWorld : public cocos2d::Layer
{
public:
    // there's no 'id' in cpp, so we recommend returning the class instance pointer
    static cocos2d::Scene* createScene();

    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool init();
    
    // a selector callback
    void menuCloseCallback(cocos2d::Ref* pSender);
    
    // implement the "static create()" method manually
    CREATE_FUNC(HelloWorld);
    cocostudio::Armature* createMount(std::string& name, cocos2d::Vec2& p);
    void move(cocos2d::Vec2 &p);
    void Resetaction();
    void mySchedule(float dt);
    bool onTouchBegan(cocos2d::Touch *touch, cocos2d::Event *unused_event);
    void onTouchMoved(cocos2d::Touch *touch, cocos2d::Event *unused_event);
    void onTouchEnded(cocos2d::Touch *touch, cocos2d::Event *unused_event);
    
    void update(float delta);
private:
    cocos2d::Vec2 p;
    cocos2d::DrawNode* d;
    cocos2d::DrawNode* d2;
    OperatorLayer* operatorLayer;
};

#endif // __HELLOWORLD_SCENE_H__
