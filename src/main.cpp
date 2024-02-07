#include <Geode/modify/LevelInfoLayer.hpp>
#include "StatEditor.hpp"

class $modify(LevelInfoLayer) {
	bool init(GJGameLevel* m_level, bool unk) {
		if (!LevelInfoLayer::init(m_level, unk))
			return false;

		auto edit_btn = CCSprite::createWithSpriteFrameName("GJ_editBtn_001.png");
		auto edit_menu = CCMenuItemSpriteExtra::create(edit_btn, this, menu_selector(StatEditor::onOpen));

		StatEditor::m_pLevel = m_level;

		auto menu = CCMenu::create();
		menu->addChild(edit_menu);
		menu->setPosition({-110.0f, -30.0f});
		menu->setScale(0.380f);

		this->addChild(menu);

		return true;
	}
};
