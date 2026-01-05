// Emacs style mode select   -*- C -*-
//-----------------------------------------------------------------------------
//
// Copyright(C) 1993-1997 Id Software, Inc.
// Copyright(C) 2007-2012 Samuel Villarreal
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

#ifndef __M_MENU__
#define __M_MENU__

#include "d_event.h"
#include "con_cvar.h"

/* Macros */
#define MENU_VAR(_vName, _name, _prev, _autoPrev) \
	menu_t _vName = { \
		_name, \
		&init, \
		&render, \
		_prev, \
		_autoPrev \
	}

#define MENU_INIT static void init()

#define MENU_RENDER static void render()

#define MENU_EXTERNAL(_vName) \
	extern menu_t _vName

/* Typedef Functions */
typedef void (menuRender)();
typedef void (menuInit)();

/* Structs */
typedef struct menu_s {
	const char *title;
	menuInit *init;
	menuRender *render;
	struct menu_s *previous;
	boolean autoPrev;
} menu_t;

/* Functions */
void m_setCvar(
	cvar_t *cvar,
	float value
);
boolean m_event(event_t *event);
void m_setupMenu(menu_t *next);
void m_render();
void m_init();
void m_startControlPanel(boolean forceNext);
void m_startMainMenu();
void m_clearMenus();

#endif