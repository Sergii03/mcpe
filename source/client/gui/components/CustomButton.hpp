/********************************************************************
	Minecraft: Pocket Edition - Decompilation Project
	Copyright (C) 2023 iProgramInCpp
	Copyright (C) 2024 Random (aka Ukrainian) Headcrab

	The following code is licensed under the BSD 1 clause license.
	SPDX-License-Identifier: BSD-1-Clause
 ********************************************************************/

#pragma once

#include "Button.hpp"

class CustomButton : public Button
{
private:
	void _init();
public:
	CustomButton(int, int x, int y, int width, int height, int, const std::string&);
	CustomButton(int, int x, int y, int width, int height, int);
	CustomButton(int, int x, int y, const std::string&);
	CustomButton(int, const std::string&);
	CustomButton(int, int, const std::string&);
	CustomButton(int, int);

	void renderBg(Minecraft*, int, int);
	void render(Minecraft*, int xPos, int yPos);

public:
	int m_width;
	int m_height;
	int m_xPos;
	int m_yPos;
	std::string m_text;
	bool m_bEnabled;
	bool m_bVisible;
	bool field_36;

	int m_lastX;
	int m_lastY;

	int m_itemIndex;
};