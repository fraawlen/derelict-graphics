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

#ifndef CELL_H
#define CELL_H

#include <stdbool.h>
#include <stdlib.h>

/************************************************************************************************************/
/************************************************************************************************************/
/************************************************************************************************************/

struct cell_t
{
	size_t id;
	void *data;

	/* states */

	bool to_destroy;
	bool enabled;
	bool failed;

	/* callbacks */

	void (*fn_destroy) (cgui_cell_t *cell);
	void (*fn_draw)    (cgui_cell_t *cell, cgui_cell_drawing_context_t *dc);
	void (*fn_event)   (cgui_cell_t *cell, cgui_cell_event_t *ev);
};

/* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -*/

void cell_destroy(cgui_cell_t *cell);

bool cell_send_windowless_event(cgui_cell_t *cell, cgui_cell_event_t *event);

/************************************************************************************************************/
/************************************************************************************************************/
/************************************************************************************************************/

#endif /* CELL_H */