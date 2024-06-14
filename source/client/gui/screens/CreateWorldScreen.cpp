/********************************************************************
	Minecraft: Pocket Edition - Decompilation Project
	Copyright (C) 2023 iProgramInCpp

	The following code is licensed under the BSD 1 clause license.
	SPDX-License-Identifier: BSD-1-Clause
 ********************************************************************/

#include "CreateWorldScreen.hpp"
#include "SelectWorldScreen.hpp"
#include "ProgressScreen.hpp"
#ifndef ORIGINAL_CODE
#include "world/gamemode/CreativeMode.hpp"
#include "world/gamemode/SurvivalMode.hpp"
#endif
#include "common/Util.hpp"

CreateWorldScreen::CreateWorldScreen() :
	m_textName(this, 1, 0, 0, 0, 0, "", "New world"),
	m_textSeed(this, 2, 0, 0, 0, 0, ""),
	m_btnBack(3, "Cancel"),
	m_btnCreate(4, "Create New World"),
#ifndef ORIGINAL_CODE
	m_btnGameMode(5, "Survival"),
	m_gameType(GAME_TYPE_SURVIVAL)
#endif
{
}

#define CRAMPED() (100 + 32 + 58 > m_height)

void CreateWorldScreen::init()
{
	m_textName.m_width  = m_textSeed.m_width  = 200;
	m_textName.m_height = m_textSeed.m_height = 20;
	m_textName.m_xPos   = m_textSeed.m_xPos   = (m_width - 200) / 2;
	m_textName.m_yPos = 60;
	m_textSeed.m_yPos = 100;

	m_btnCreate.m_yPos  = m_height - 56;
	m_btnBack.m_yPos    = m_height - 30;
	m_btnBack.m_width   = m_btnCreate.m_width  = 200;
	m_btnBack.m_height  = m_btnCreate.m_height = 20;
	
	m_btnBack.m_xPos   = m_width / 2 - 200 / 2;
	m_btnCreate.m_xPos = m_width / 2 - 200 / 2;

#ifndef ORIGINAL_CODE
	m_btnGameMode.m_yPos = m_height - 90;
	m_btnGameMode.m_width = 70;
	m_btnGameMode.m_height = 20;

	m_btnGameMode.m_xPos = (m_width - 200) / 2;
#endif

	m_textInputs.push_back(&m_textName);
	m_textInputs.push_back(&m_textSeed);
	m_buttons.push_back(&m_btnBack);
	m_buttons.push_back(&m_btnCreate);
#ifndef ORIGINAL_CODE
	m_buttons.push_back(&m_btnGameMode);
#endif
	m_buttonTabList.push_back(&m_btnBack);
	m_buttonTabList.push_back(&m_btnCreate);
#ifndef ORIGINAL_CODE
	m_buttonTabList.push_back(&m_btnGameMode);
#endif
	m_textName.init(m_pFont);
	m_textSeed.init(m_pFont);

	// 100 - yPos of textSeed
	// 32  - offset + height of "Leave blank for random" text
	// 58  - approximately the Y position of the create button
	bool crampedMode = CRAMPED();
	if (crampedMode)
	{
		// crush everything down as much as we can
		m_textName.m_yPos = 40;
		m_textSeed.m_yPos = 80;
#ifndef ORIGINAL_CODE
		m_btnGameMode.m_yPos += 20;
#endif
		m_btnCreate.m_yPos += 10;
		m_btnBack.m_yPos += 5;
	}
}

static char g_CreateWorldFilterArray[] = { '/','\n','\r','\x09','\0','\xC','`','?','*','\\','<','>','|','"',':' };

static std::string GetUniqueLevelName(LevelStorageSource* pSource, const std::string& in)
{
	std::set<std::string> maps;

	std::vector<LevelSummary> vls;
	pSource->getLevelList(vls);

	for (int i = 0; i < int(vls.size()); i++)
	{
		const LevelSummary& ls = vls[i];
		maps.insert(ls.field_0);
	}

	std::string out = in;
	while (maps.find(out) != maps.end())
		out += "-";

	return out;
}

void CreateWorldScreen::buttonClicked(Button* pButton)
{
#ifndef ORIGINAL_CODE
	if (pButton->m_buttonId == m_btnGameMode.m_buttonId)
	{
		if (m_gameType == GAME_TYPE_CREATIVE)
		{
			m_btnGameMode.m_text = "Survival";
			m_gameType = GAME_TYPE_SURVIVAL;
			m_pMinecraft->setGameMode(m_gameType);
		}
		else
		{
			m_btnGameMode.m_text = "Creative";
			m_gameType = GAME_TYPE_CREATIVE;
			m_pMinecraft->setGameMode(m_gameType);
		}
	}
#endif

	if (pButton->m_buttonId == m_btnBack.m_buttonId)
	{
		m_pMinecraft->setScreen(new SelectWorldScreen);
	}

	if (pButton->m_buttonId == m_btnCreate.m_buttonId)
	{
		std::string nameStr = m_textName.m_text; 
		std::string seedStr = m_textSeed.m_text;

		std::string levelNickname = Util::stringTrim(nameStr);
		std::string levelUniqueName = levelNickname;

		for (int i = 0; i < sizeof(g_CreateWorldFilterArray); i++)
		{
			std::string str;
			str.push_back(g_CreateWorldFilterArray[i]);
			Util::stringReplace(levelUniqueName, str, "");
		}

		levelUniqueName = GetUniqueLevelName(m_pMinecraft->m_pLevelStorageSource, levelUniqueName);

		int seed = int(getEpochTimeS());

		std::string seedThing = Util::stringTrim(seedStr);
		if (!seedThing.empty())
		{
			int num;
			if (sscanf(seedThing.c_str(), "%d", &num) > 0)
				seed = num;
			else
				seed = Util::hashCode(seedThing);
		}

		m_pMinecraft->selectLevel(levelUniqueName, levelNickname, seed, m_gameType);
		m_pMinecraft->hostMultiplayer();
		m_pMinecraft->setScreen(new ProgressScreen);
	}
}

void CreateWorldScreen::render(int mouseX, int mouseY, float f)
{
	renderBackground();
	Screen::render(mouseX, mouseY, f);

	drawCenteredString(m_pFont, "Create New World", m_width / 2, CRAMPED() ? 10 : 30, 0xFFFFFF);
	drawString(m_pFont, "World name",                    m_textName.m_xPos, m_textName.m_yPos - 10, 0xDDDDDD);
	drawString(m_pFont, "Seed for the World Generator",  m_textSeed.m_xPos, m_textSeed.m_yPos - 10, 0xDDDDDD);
	drawString(m_pFont, "Leave blank for a random seed", m_textSeed.m_xPos, m_textSeed.m_yPos + 22, 0x999999);
#ifndef ORIGINAL_CODE
	drawString(m_pFont, "Game Mode", m_textSeed.m_xPos, m_btnGameMode.m_yPos - 10, 0x999999);
#endif
}
