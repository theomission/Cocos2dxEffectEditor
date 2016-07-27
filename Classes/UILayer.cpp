//
//  UILayer.cpp
//  EffectEditor
//
//  Created by Matrix on 16/7/26.
//
//

#include "UILayer.hpp"
#include "editor-support/cocostudio/CocoStudio.h"
#include "ui/CocosGUI.h"
#include "MainLayer.hpp"
#include "ShaderSprite.hpp"
#include "LinkEffect.hpp"

NS_EE_BEGIN

using namespace cocos2d::ui;

bool UILayer::init(void)
{
    mContainer = CSLoader::createNode("res/main_scene.csb");
    auto size = Director::getInstance()->getWinSize();
    this->addChild(mContainer, (int)SPRITE_ZORDER::UI);
    
    Layout *uiRoot = static_cast<Layout*>(mContainer->getChildByName("root_node"));
    Button *pButton = static_cast<Button*>(ui::Helper::seekWidgetByName(uiRoot, "bt_sprite"));
    pButton->addTouchEventListener(CC_CALLBACK_2(UILayer::onUserTouchEvent, this));
    
    return Layer::init();
}

void UILayer::onUserTouchEvent(cocos2d::Ref *sender, Widget::TouchEventType type)
{
    if(type == Widget::TouchEventType::ENDED)
    {
        auto shaderSprite = MainLayer::getInstance()->getSprite("1");
        shaderSprite->runAction(RepeatForever::create(Sequence::create(MoveBy::create(2.0f, Vec2(200.0f, 0.0f)),
                                                                       MoveBy::create(2.0f, Vec2(-200.0f, 0.0f)), NULL)));
        //shaderSprite->resetTimeUniform();
        
        auto sprite2 = MainLayer::getInstance()->getSprite("2");
        auto link = LinkEffect::create(sprite2, shaderSprite);
        addChild(link);
        
        /*auto test = ParticleSystemQuad::create("res/link_light.plist");
        addChild(test, 99999);
        test->setAnchorPoint(Vec2(0.0f, 0.0f));
        test->setPosition(shaderSprite->getPosition());
        test->setRotation(60);*/
    }
}

NS_EE_END