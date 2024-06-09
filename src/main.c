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

#include <assert.h>
#include <cairo/cairo.h>
#include <cassette/cgui.h>
#include <cassette/cobj.h>
#include <fontconfig/fontconfig.h>
#include <xcb/xcb.h>
#include <stdbool.h>
#include <stdlib.h>

#include "cell.h"
#include "config.h"
#include "env.h"
#include "event.h"
#include "grid.h"
#include "main.h"
#include "mutex.h"
#include "window.h"
#include "util.h"
#include "x11.h"

/************************************************************************************************************/
/************************************************************************************************************/
/************************************************************************************************************/

static bool _is_any_window_activated (void);

/************************************************************************************************************/
/************************************************************************************************************/
/************************************************************************************************************/

/* objects trackers */

static cobj_tracker_t *_cells   = NULL;
static cobj_tracker_t *_grids   = NULL;
static cobj_tracker_t *_windows = NULL;

/* x11 init args */

static xcb_connection_t *_ext_connection = NULL;

static const char *_app_name  = NULL;
static const char *_app_class = NULL;

/* session states */

static bool _init     = false;
static bool _running  = false;
static bool _usr_exit = true;
static bool _failed   = true;

/************************************************************************************************************/
/* PUBLIC ***************************************************************************************************/
/************************************************************************************************************/

void
cgui_allow_user_exit(void)
{
	assert(_init);

	_usr_exit = true;
}

/* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -*/

void
cgui_block_user_exit(void)
{
	assert(_init);

	_usr_exit = false;
}

/* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -*/

void
cgui_exit(void)
{
	assert(_init);

	_running = false;
}

/* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -*/

xcb_connection_t *
cgui_get_xcb_connection(void)
{
	return x11_get_connection();
}

/* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -*/

xcb_window_t
cgui_get_xcb_leader_window(void)
{
	return  x11_get_leader_window();
}

/* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -*/

bool
cgui_has_failed(void)
{
	if (_init)
	{
		_failed |= cobj_tracker_has_failed(main_get_cells());
		_failed |= cobj_tracker_has_failed(main_get_grids());
		_failed |= cobj_tracker_has_failed(main_get_windows());
		_failed |= x11_has_failed();
	}

	return _failed;
}

/* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -*/

void
cgui_init(int argc, char **argv)
{
	assert(!_init);

	if (!_app_class)
	{
		_app_class = argv ? argv[0] : "cgui";
	}

	if (!_app_name)
	{
		_app_name = _app_class;
	}

	_cells   = cobj_tracker_create(1);
	_grids   = cobj_tracker_create(1);
	_windows = cobj_tracker_create(1);

	_failed  = false;
	_failed |= !x11_init(argc, argv, _app_name, _app_class, _ext_connection);
	_failed |= !config_init(_app_name, _app_class);
	_failed |= !config_load();
	_failed |= !mutex_init();

	_init = true;

	cgui_lock();
}

/* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -*/

bool
cgui_is_init(void)
{
	return _init;
}

/* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -*/

bool
cgui_is_running(void)
{
	return _running;
}

/* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -*/

void
cgui_lock(void)
{
	assert(_init);

	assert(mutex_lock());
}

/* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -*/

void
cgui_reconfig(void)
{
	cgui_window_t *window;
//	cgui_grid_t *grid;
//	cgui_grid_t *grid_min;

	assert(_init);

	if (_failed)
	{
		return;
	}

	_failed |= !config_load();

	cobj_tracker_reset_iterator(_windows);
	while (cobj_tracker_increment_iterator(_windows))
	{
		window = (cgui_window_t*)cobj_tracker_get_iteration(_windows);
		if (window->failed)
		{
			continue;
		}

		// TODO
	}
}

/* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -*/

void
cgui_reset(void)
{
	assert(_init);

	cobj_tracker_reset_iterator(_windows);
	while (cobj_tracker_increment_iterator(_windows))
	{
		((cgui_window_t*)cobj_tracker_get_iteration(_windows))->failed = true;
	}

	cobj_tracker_reset_iterator(_grids);
	while (cobj_tracker_increment_iterator(_grids))
	{
		((cgui_grid_t*)cobj_tracker_get_iteration(_grids))->failed = true;
	}

	cobj_tracker_reset_iterator(_cells);
	while (cobj_tracker_increment_iterator(_cells))
	{
		((cgui_cell_t*)cobj_tracker_get_iteration(_cells))->failed = true;
	}

	if (!_ext_connection || util_env_exists(ENV_FORCE_CLEAN))
	{
		cairo_debug_reset_static_data();
		FcFini();
	}

	cobj_tracker_destroy(&_cells);
	cobj_tracker_destroy(&_grids);
	cobj_tracker_destroy(&_windows);

	x11_reset(!_ext_connection);
	config_reset();
	mutex_reset();

	_ext_connection = NULL;
	_app_class      = NULL;
	_app_name       = NULL;
	_usr_exit       = true;
	_failed         = true;
	_running        = false;

	cgui_unlock();
	
	_init = false;
}

/* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -*/

void
cgui_run(void)
{
	bool fail = false;

	assert(_init);

	if (_failed || _running)
	{
		return;
	}

	_running = true;

	while (_init && _running && _is_any_window_activated() && !fail)
	{
		cgui_unlock();

		fail = !x11_update();

		cgui_lock();
	}

	_failed |= fail;
	_running = false;
}

/* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -*/

void
cgui_setup_app_class(const char *class_name)
{
	assert(!_init);

	_app_class = class_name;
}

/* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -*/

void
cgui_setup_app_name(const char *name)
{
	assert(!_init);

	_app_name = name;
}

/* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -*/

void
cgui_setup_x11_connection(xcb_connection_t *connection)
{
	assert(!_init);

	_ext_connection = connection;
}

/* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -*/

void
cgui_unlock(void)
{
	assert(_init);

	assert(mutex_unlock());
}

/************************************************************************************************************/
/* PRIVATE **************************************************************************************************/
/************************************************************************************************************/

cobj_tracker_t *
main_get_cells(void)
{
	return _cells ? _cells : cobj_tracker_get_placeholder();
}

/* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -*/

cobj_tracker_t *
main_get_grids(void)
{
	return _grids ? _grids : cobj_tracker_get_placeholder();
}

/* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -*/

cobj_tracker_t *
main_get_windows(void)
{
	return _windows ? _windows : cobj_tracker_get_placeholder();
}

/* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -*/

void
main_update(cgui_event_t *event)
{
	cgui_lock();

	event_process(event);

	cobj_tracker_reset_iterator(_windows);
	while (cobj_tracker_increment_iterator(_windows))
	{
		window_present((cgui_window_t*)cobj_tracker_get_iteration(_windows));
		window_destroy((cgui_window_t*)cobj_tracker_get_iteration(_windows));
	}

	cobj_tracker_reset_iterator(_grids);
	while (cobj_tracker_increment_iterator(_grids))
	{
		grid_destroy((cgui_grid_t*)cobj_tracker_get_iteration(_grids));
	}

	cobj_tracker_reset_iterator(_cells);
	while (cobj_tracker_increment_iterator(_cells))
	{
		cell_destroy((cgui_cell_t*)cobj_tracker_get_iteration(_cells));
	}
	
	cgui_unlock();
}

/************************************************************************************************************/
/* _ ********************************************************************************************************/
/************************************************************************************************************/

static bool
_is_any_window_activated(void)
{
	cobj_tracker_reset_iterator(_windows);
	while (cobj_tracker_increment_iterator(_windows))
	{
		if (((cgui_window_t*)cobj_tracker_get_iteration(_windows))->state & CGUI_WINDOW_STATE_ACTIVE)
		{
			return true;
		}
	}

	return false;
}
