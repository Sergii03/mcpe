/********************************************************************
	Minecraft: Pocket Edition - Decompilation Project
	Copyright (C) 2023 iProgramInCpp
	Copyright (C) 2024 Random (aka Ukrainian) Headcrab

	The following code is licensed under the BSD 1 clause license.
	SPDX-License-Identifier: BSD-1-Clause
 ********************************************************************/

#include "CustomButton.hpp"

void CustomButton::_init()
{
	m_width = 0;
	m_height = 0;
	m_xPos = 0;
	m_yPos = 0;
	m_text = "";
	m_bEnabled = true;
	m_bVisible = true;
	field_36 = false;

	m_lastX = 0;
	m_lastY = 0;

	m_itemIndex = 0;
}

CustomButton::CustomButton(int buttonId, int xPos, int yPos, int btnWidth, int btnHeight, int itemIdToRender, const std::string& text)
{
	_init();

	m_width = btnWidth;
	m_height = btnHeight;
	m_xPos = xPos;
	m_yPos = yPos;
	m_text = text;

	m_itemIndex = itemIdToRender;
}

CustomButton::CustomButton(int buttonId, int xPos, int yPos, int btnWidth, int btnHeight, int itemIdToRender)
{
	_init();

	m_width = btnWidth;
	m_height = btnHeight;
	m_xPos = xPos;
	m_yPos = yPos;
	m_text = "";

	m_itemIndex = itemIdToRender;
}

CustomButton::CustomButton(int buttonId, int xPos, int yPos, const std::string& text)
{
	_init();

	m_width = 32;
	m_height = 32;
	m_xPos = xPos;
	m_yPos = yPos;
	m_text = text;

	m_itemIndex = 0;
}

CustomButton::CustomButton(int buttonId, const std::string& text)
{
	_init();

	m_width = 32;
	m_height = 32;
	m_xPos = 0;
	m_yPos = 0;
	m_text = text;

	m_itemIndex = 0;
}

CustomButton::CustomButton(int buttonId, int itemIdToRender, const std::string& text)
{
	_init();

	m_width = 32;
	m_height = 32;
	m_xPos = 0;
	m_yPos = 0;
	m_text = text;

	m_itemIndex = itemIdToRender;
}

CustomButton::CustomButton(int buttonId, int itemIdToRender)
{
	_init();

	m_width = 32;
	m_height = 32;
	m_xPos = 0;
	m_yPos = 0;
	m_text = "";

	m_itemIndex = itemIdToRender;
}

void CustomButton::renderBg(Minecraft* pMinecraft, int x, int y)
{
	ItemInstance* pItem = pMinecraft->m_pLocalPlayer->m_pInventory->getItem(m_itemIndex);
	if (!pItem)
		return;

	if (!pItem->m_itemID)
		return;

	ItemRenderer::renderGuiItem(pMinecraft->m_pFont, pMinecraft->m_pTextures, pItem, x, y, true);
}

void CustomButton::render(Minecraft* pMinecraft, int xPos, int yPos)
{
	if (!m_bVisible) return;

	//field_36 = clicked(pMinecraft, xPos, yPos);

	Font* pFont = pMinecraft->m_pFont;
	Textures* pTexs = pMinecraft->m_pTextures;

	pTexs->loadAndBindTexture("gui/spritesheet.png");

	glColor4f(1.0f, 1.0f, 1.0f, 1.0f);
	//int iYPos = 20 * getYImage(field_36) + 46;
	int iYPos = 1;

	blit(m_xPos, m_yPos, 0, iYPos, m_width / 2, m_height, 0, 20);
	blit(m_xPos + m_width / 2, m_yPos, 200 - m_width / 2, iYPos, m_width / 2, m_height, 0, 20);

	renderBg(pMinecraft, xPos, yPos);

	int textColor;
	if (!m_bEnabled)
		textColor = int(0xFFA0A0A0U);
	else if (field_36)
		textColor = int(0xFFFFA0U);
	else
		textColor = int(0xE0E0E0U);

	drawCenteredString(pFont, m_text, m_xPos + m_width / 2, m_yPos + (m_height - 8) / 2, textColor);
}
