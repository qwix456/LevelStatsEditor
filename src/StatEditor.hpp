#pragma once

#include <Geode/Geode.hpp>
#include <Geode/binding/FLAlertLayer.hpp>
#include <Geode/binding/CCTextInputNode.hpp>
#include <Geode/binding/GameManager.hpp>
using namespace geode::prelude;

class StatEditor : public FLAlertLayer {
public:
    static StatEditor* create(GJGameLevel* m_level);
    bool init(GJGameLevel* m_level);
    void createLabel(gd::string text, gd::string font_file, CCPoint position, float scale, CCNode* parent);
    CCTextInputNode* createTextInput(gd::string placeholder, int value, float pos_x, float pos_y, float placeholder_scale, float max_label_scale);
    void createButton(gd::string sprite_name, SEL_MenuHandler callback, CCPoint position, CCMenu* parent_menu, float scale);
    void createButtonSprite(gd::string button_name, SEL_MenuHandler callback, CCPoint position, CCMenu* parent_menu);
    void createBackground(gd::string sprite_name, CCPoint position, CCSize size, float scale, int opacity, CCNode* parent);
    void onOpen(CCObject*);
    void onClose(CCObject*);
    void setStats(CCObject*);
    static GJGameLevel* m_pLevel;
private:
    CCTextInputNode* m_jumps_label;
    CCTextInputNode* m_attempts_label;
    CCTextInputNode* m_normal_percent_label;
    CCTextInputNode* m_practice_percent_label;
};