//
//  Hero.hpp
//  TestArmature
//
//  Created by student01 on 16/9/19.
//
//

#ifndef Hero_hpp
#define Hero_hpp

#include "cocos2d.h"

class Hero : cocos2d::Node
{
public:
    bool init();
    CREATE_FUNC(Hero);
    void move(cocos2d::Vec2& p); //移动方法
    void PlayAnimation();
    
private:
    int hp;
    int attack; //攻击力

};

#endif /* Hero_hpp */
