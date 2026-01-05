// Emacs style mode select   -*- C -*-
//-----------------------------------------------------------------------------
//
// Copyright(C) 2026 StevenSYS
//
// This source is available for distribution and/or modification
// only under the terms of the DOOM Source Code License as
// published by id Software. All rights reserved.
//
// The source is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// FITNESS FOR A PARTICULAR PURPOSE. See the DOOM Source Code License
// for more details.
//
//-----------------------------------------------------------------------------

#define CIMGUI_DEFINE_ENUMS_AND_STRUCTS
#include <cimgui/cimgui.h>

#include "tools.h"
#include "m_menu.h"

MENU_EXTERNAL(menu_episode);
MENU_EXTERNAL(menu_loadGame);
MENU_EXTERNAL(menu_options);
MENU_EXTERNAL(menu_quitGame);

MENU_INIT {
	return;
}

MENU_RENDER {
	if (igButton("New Game", (ImVec2){ 0.0f, 0.0f })) {
		m_setupMenu(&menu_episode);
	}
	
	if (igButton("Load Game", (ImVec2){ 0.0f, 0.0f })) {
		m_setupMenu(&menu_loadGame);
	}
	
	if (igButton("Options", (ImVec2){ 0.0f, 0.0f })) {
		m_setupMenu(&menu_options);
	}
	
	if (igButton("Quit Game", (ImVec2){ 0.0f, 0.0f })) {
		m_setupMenu(&menu_quitGame);
	}
	return;
}

MENU_VAR(menu_mainMenu, "Main Menu", NULL, false);