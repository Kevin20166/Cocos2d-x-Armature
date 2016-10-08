//
//  Hero.cpp
//  TestArmature
//
//  Created by student01 on 16/9/19.
//
//

#include "Hero.hpp"
#include "cocostudio/cocostudio.h"
using namespace cocostudio;
bool Hero::init()
{
    if( !Node::init() )
    {
        return false;
    }
    
    auto hero = Hero::create();
    
    auto armature = Armature::create("K");
    
    return true;
}
void Hero::move(cocos2d::Vec2& p) //移动方法
{

}
void Hero::PlayAnimation()
{
    
}