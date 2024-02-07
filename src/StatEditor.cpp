#include "StatEditor.hpp"

GJGameLevel* StatEditor::m_pLevel = nullptr;

StatEditor* StatEditor::create(GJGameLevel* level) {
    auto editor = new (std::nothrow) StatEditor();
    if (editor && editor->init(level)) {
        editor->autorelease();
        return editor;
    } else {
        delete editor;
        return nullptr;
    }
}

bool StatEditor::init(GJGameLevel* m_level) {
    if (!initWithColor({0, 0, 0, 105})) 
        return false;

    setTouchEnabled(true);
    setKeypadEnabled(true);

    m_mainLayer = CCLayer::create();
    this->addChild(m_mainLayer);

    CCDirector::sharedDirector()->getTouchDispatcher()->addTargetedDelegate(this, cocos2d::kCCMenuHandlerPriority, true);

    m_buttonMenu = CCMenu::create();
    m_mainLayer->addChild(m_buttonMenu, 10);

    createBackground("GJ_square01.png", {287.0f, 155.0f}, {255.0f, 212.0f}, 1.0f, 255, m_mainLayer);
    createLabel("Stats Editor", "goldFont.fnt", {285.0f, 240.0f}, 1.0f, m_mainLayer);

    auto level_name = m_level->m_levelName.size() > 20 ? 0.4f : 0.5f;
    createLabel(m_level->m_levelName, "bigFont.fnt", {280.0f, 210.0f}, level_name, m_mainLayer);

    createBackground("square02_001.png", {226.0f, 175.0f}, {220.0f, 69.0f}, 0.5f, 100, m_mainLayer);
    createBackground("square02_001.png", {345.0f, 175.0f}, {220.0f, 69.0f}, 0.5f, 100, m_mainLayer);
    createBackground("square02_001.png", {226.0f, 135.0f}, {220.0f, 69.0f}, 0.5f, 100, m_mainLayer);
    createBackground("square02_001.png", {345.0f, 135.0f}, {220.0f, 69.0f}, 0.5f, 100, m_mainLayer);

    m_jumps_label = createTextInput("Jumps", m_level->m_jumps, -61.0f, 15.0f, 0.3f, .8);
    m_attempts_label = createTextInput("Attempts", m_level->m_attempts, 60.0f, 15.0f, 0.3f, .8);
    m_normal_percent_label = createTextInput("Normal Percent", m_level->m_normalPercent, -60.0f, -25.0f, 0.3f, .8);
    m_practice_percent_label = createTextInput("Practice Percent", m_level->m_practicePercent, 60.0f, -25.0f, 0.3f, .8);

    createButtonSprite("Apply", menu_selector(StatEditor::setStats), {0.0f, -87.0f}, m_buttonMenu);
    createButton("GJ_closeBtn_001.png", menu_selector(StatEditor::onClose), {-118.0f, 95.0f}, m_buttonMenu, 0.8f);

    return true;
}

void StatEditor::createLabel(gd::string text, gd::string font_file, CCPoint position, float scale, CCNode *parent) {
    auto label = CCLabelBMFont::create(text.c_str(), font_file.c_str());
    label->setPosition(position);
    label->setScale(scale);
    parent->addChild(label);
}

CCTextInputNode* StatEditor::createTextInput(gd::string placeholder, int value, float pos_x, float pos_y, float placeholder_scale, float max_label_scale) {
    auto input_node = CCTextInputNode::create(194.0f, 50.0f, placeholder.c_str(), "bigFont.fnt");
    input_node->setString(std::to_string(value).c_str());
    input_node->setLabelPlaceholderColor({200, 200, 200});
    input_node->setLabelPlaceholderScale(placeholder_scale);
    input_node->setAllowedChars("0123456789");
    input_node->setMaxLabelLength(5);
    input_node->setMaxLabelScale(max_label_scale);
    input_node->setPosition({pos_x, pos_y});
    m_buttonMenu->addChild(input_node);
    return input_node;
}

void StatEditor::createButton(gd::string sprite_name, SEL_MenuHandler callback, CCPoint position, CCMenu *parent_menu, float scale) {
    auto sprite = CCSprite::createWithSpriteFrameName(sprite_name.c_str());
    auto menuItem = CCMenuItemSpriteExtra::create(sprite, this, callback);
    menuItem->setPosition(position);
    menuItem->setScale(scale);
    parent_menu->addChild(menuItem);
}

void StatEditor::createButtonSprite(gd::string button_name, SEL_MenuHandler callback, CCPoint position, CCMenu *parent_menu)
{
    auto menuItem = CCMenuItemSpriteExtra::create(ButtonSprite::create(button_name.c_str()), this, callback);
    menuItem->setPosition(position);
    parent_menu->addChild(menuItem);
}

void StatEditor::createBackground(gd::string sprite_name, CCPoint position, CCSize size, float scale, int opacity, CCNode *parent) {
    auto background = CCScale9Sprite::create(sprite_name.c_str(), {0, 0, 80, 80});
    background->setPosition(position);
    background->setContentSize(size);
    background->setScale(scale);
    background->setOpacity(opacity);
    parent->addChild(background);
}

void StatEditor::onOpen(CCObject *) {
    create(m_pLevel)->show();
}

void StatEditor::onClose(CCObject *) {
    keyBackClicked();
}

void StatEditor::setStats(CCObject *) {
    auto parse_value = [](gd::string str) -> double {
        return std::strtod(str.c_str(), nullptr);
    };

    m_pLevel->m_jumps = parse_value(m_jumps_label->getString());
    m_pLevel->m_attempts = parse_value(m_attempts_label->getString());
    m_pLevel->m_normalPercent = parse_value(m_normal_percent_label->getString());
    m_pLevel->m_practicePercent = parse_value(m_practice_percent_label->getString());

    FLAlertLayer::create("Info", "Everything has been applied", "OK")->show();
    keyBackClicked();
}
