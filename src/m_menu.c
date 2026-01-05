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
#define CIMGUI_USE_SDL3
#define CIMGUI_USE_OPENGL3
#include <cimgui/cimgui.h>
#include <cimgui_impl.h>
#include <stdlib.h>
#include <SDL3/SDL_platform_defines.h>

#include "tools.h"
#include "m_menu.h"
#include "sounds.h"
#include "g_game.h"
#include "m_misc.h"
#include "doomdef.h"
#include "s_sound.h"
#include "m_shift.h"
#include "con_cvar.h"
#include "doomstat.h"
#include "i_system.h"
#include "i_sdlinput.h"

/* Macros */
// #define MENU_MOUSELOOK
#define SIZE_MENUSTRING 32
#define HEIGHT_LINE 18
#define HEIGHT_TEXTLINE 18
#define QUICKSAVE_SLOT 7
#define FILE_QUICKSAVE "doomsav7.dsg"

/* Variables */
boolean allowMenu = true;
boolean menuActive = false;
boolean mainMenuActive = false;
boolean allowClearMenu = true;

int map = 1;

static menu_t *currentMenu = NULL;
static menu_t *previousMenu = NULL;

/* Menu Externals */
MENU_EXTERNAL(menu_mainMenu);

/* Functions */
void m_setCvar(
	cvar_t *cvar,
	float value
) {
	/* Taken and modified from the original menu code */
	if (cvar->value == value) {
		return;
	}

	CON_CvarSetValue(cvar->name, value);
	return;
}

boolean m_event(event_t *event) {
	if (currentMenu != NULL) {
		// return currentMenu->event(event);
	}
	return false;
}

void m_setupMenu(menu_t *newMenu) {
	if (newMenu != NULL) {
		if (currentMenu != NULL) {
			previousMenu = currentMenu;
		}
		
		if (newMenu->init != NULL) {
			newMenu->init();
		}
		
		currentMenu = newMenu;
	}
	return;
}

void m_quickSave() {
	if (!usergame) {
		S_StartSound(NULL, sfx_oof);
		return;
	}
	
	if (gamestate != GS_LEVEL) {
		return;
	}
	
	G_SaveGame(QUICKSAVE_SLOT, "quicksave");
	return;
}

void m_quickLoad() {
	char *filepath = I_GetUserFile(FILE_QUICKSAVE);
	
	if (M_FileExists(filepath)) {
		G_LoadGame(filepath);
	}
	
	free(filepath);
	return;
}

void m_startControlPanel(boolean forceNext) {
	STUB();
	return;
}

void m_startMainMenu() {
	menuActive = true;
	m_setupMenu(&menu_mainMenu);
	return;
}

void m_render() {
	if (currentMenu != NULL) {
		igSetNextWindowPos(
			(ImVec2){ 0.0f, 0.0f },
			ImGuiCond_FirstUseEver,
			(ImVec2){ 0.0f, 0.0f }
		);
		igSetNextWindowSize(
			igGetIO_Nil()->DisplaySize,
			ImGuiCond_FirstUseEver
		);
		
		igBegin(
			currentMenu->title,
			NULL,
			ImGuiWindowFlags_NoMove |
			ImGuiWindowFlags_NoResize |
			ImGuiWindowFlags_NoTitleBar |
			ImGuiWindowFlags_NoBackground
		);
		
		igText("%s", currentMenu->title);
		
		if (
			currentMenu->previous != NULL ||
			currentMenu->autoPrev
		) {
			if (igButton("<- Back", (ImVec2){ 0.0f, 0.0f })) {
				if (!currentMenu->autoPrev) {
					previousMenu = currentMenu->previous;
				}
				
				m_setupMenu(previousMenu);
			}
		}
		
		currentMenu->render();
		
		igEnd();
	}
	return;
}

void m_clearMenus() {
	/* Taken and modified from the original menu code */
	if (!allowClearMenu) {
		return;
	}
	
	/*
		center mouse before clearing menu
		so the input code won't try to
		re-center the mouse; which can
		cause the player's view to warp
	*/
	if (gamestate == GS_LEVEL) {
		I_CenterMouse();
	}
	
	currentMenu = NULL;
	previousMenu = NULL;
	
	menuActive = false;
	
	S_ResumeSound();
	return;
}

void m_init() {
	m_clearMenus();
	m_setupMenu(&menu_mainMenu);
	menuActive = true;
	
	M_InitShiftXForm();
	return;
}