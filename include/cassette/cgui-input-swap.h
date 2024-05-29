/**
 * Copyright © 2024 Fraawlen <fraawlen@posteo.net>
 *
 * This file is part of the Cassette Graphics (CGUI) library.
 *
 * This library is free software; you can redistribute it and/or modify it either under the terms of the GNU
 * Lesser General Public License as published by the Free Software Foundation; either version 2.1 of the
 * License or (at your option) any later version.
 *
 * This software is distributed on an "AS IS" basis, WITHOUT WARRANTY OF ANY KIND, either express or implied.
 * See the LGPL for the specific language governing rights and limitations.
 *
 * You should have received a copy of the GNU Lesser General Public License along with this program. If not,
 * see <http://www.gnu.org/licenses/>.
 */

/************************************************************************************************************/
/************************************************************************************************************/
/************************************************************************************************************/

#ifndef CGUI_INPUT_SWAP_H
#define CGUI_INPUT_SWAP_H

#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

/************************************************************************************************************/
/************************************************************************************************************/
/************************************************************************************************************/

enum cgui_input_swap_kind_t
{
	CGUI_INPUT_SWAP_TO_DEFAULT = 0,
	CGUI_INPUT_SWAP_TO_NONE,
	CGUI_INPUT_SWAP_TO_VALUE,
	CGUI_INPUT_SWAP_TO_ACCELERATOR,
	CGUI_INPUT_SWAP_TO_CLIPBOARD_CUT,
	CGUI_INPUT_SWAP_TO_CLIPBOARD_COPY,
	CGUI_INPUT_SWAP_TO_CLIPBOARD_PASTE,
	CGUI_INPUT_SWAP_TO_ACTION_CELL,
	CGUI_INPUT_SWAP_TO_ACTION_FOCUS,
	CGUI_INPUT_SWAP_TO_ACTION_WINDOW,
	CGUI_INPUT_SWAP_TO_ACTION_MISC,
};

typedef uint8_t cgui_input_swap_type_t;

/* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -*/

enum cgui_input_swap_cell_t
{
	CGUI_INPUT_SWAP_CELL_REDRAW,
	CGUI_INPUT_SWAP_CELL_SELECT_LESS,
	CGUI_INPUT_SWAP_CELL_SELECT_MORE,
	CGUI_INPUT_SWAP_CELL_SELECT_NONE,
	CGUI_INPUT_SWAP_CELL_SELECT_ALL,
	CGUI_INPUT_SWAP_CELL_TRIGGER_1,
	CGUI_INPUT_SWAP_CELL_TRIGGER_2,
	CGUI_INPUT_SWAP_CELL_TRIGGER_3,
	CGUI_INPUT_SWAP_CELL_TRIGGER_4,
	CGUI_INPUT_SWAP_CELL_TRIGGER_5,
};

enum cgui_input_swap_focus_t
{
	CGUI_INPUT_SWAP_FOCUS_LEFT,
	CGUI_INPUT_SWAP_FOCUS_RIGHT,
	CGUI_INPUT_SWAP_FOCUS_UP,
	CGUI_INPUT_SWAP_FOCUS_DOWN,
	CGUI_INPUT_SWAP_FOCUS_LEFTMOST,
	CGUI_INPUT_SWAP_FOCUS_RIGHTMOST,
	CGUI_INPUT_SWAP_FOCUS_TOP,
	CGUI_INPUT_SWAP_FOCUS_BOTTOM,
	CGUI_INPUT_SWAP_FOCUS_NEXT,
	CGUI_INPUT_SWAP_FOCUS_PREV,
	CGUI_INPUT_SWAP_FOCUS_FIRST,
	CGUI_INPUT_SWAP_FOCUS_LAST,
	CGUI_INPUT_SWAP_FOCUS_NONE,
};

enum cgui_input_swap_window_t
{
	CGUI_INPUT_SWAP_WINDOW_LOCK_GRID,
	CGUI_INPUT_SWAP_WINDOW_LOCK_FOCUS,
	CGUI_INPUT_SWAP_WINDOW_REDRAW,
};

enum cgui_input_swap_misc_t
{
	CGUI_INPUT_SWAP_RECONFIG,
	CGUI_INPUT_SWAP_EXIT,
};

typedef uint8_t cgui_input_swap_misc_t;
typedef uint8_t cgui_input_swap_window_t;
typedef uint8_t cgui_input_swap_focus_t;
typedef uint8_t cgui_input_swap_cell_t;

/* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -*/

struct cgui_input_swap_t
{
	uint8_t kind;
	uint8_t value;
};

typedef struct cgui_input_swap_t cgui_input_swap_t;

/************************************************************************************************************/
/************************************************************************************************************/
/************************************************************************************************************/

#ifdef __cplusplus
}
#endif

#endif /* CGUI_INPUT_SWAP_H */