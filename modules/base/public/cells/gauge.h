/**
 * Copyright © 2024 Fraawlen <fraawlen@posteo.net>
 *
 * This file is part of the Derelict Graphics (DG) GUI library.
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

#ifndef DG_BASE_GAUGE_H
#define DG_BASE_GAUGE_H

#include <dg/core/core.h>

#ifdef __cplusplus
extern "C" {
#endif

/************************************************************************************************************/
/************************************************************************************************************/
/************************************************************************************************************/

/**
 * Instantiates a gap-type cell.
 *
 * @return : created cell, NULL in case of failure
 *
 * @error DG_CORE_ERRNO_MEMORY : inherited from dg_core_cell_create()
 * @error DG_CORE_ERRNO_STACK  : inherited from dg_core_cell_create()
 */
dg_core_cell_t *dg_base_gauge_create(void);

/* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -*/

/**
 * TODO description
 */
void dg_base_gauge_hide_label(dg_core_cell_t *c);

/**
 * TODO description
 */
void dg_base_gauge_set_horizontal(dg_core_cell_t *c);

/**
 * TODO description
 */
void dg_base_gauge_set_label_style(dg_core_cell_t *c, int precision, const char *units);

/**
 * TODO description
 */
void dg_base_gauge_set_limits(dg_core_cell_t *c, double min, double max);

/**
 * TODO description
 */
void dg_base_gauge_set_value(dg_core_cell_t *c, double value);

/**
 * TODO description
 */
void dg_base_gauge_set_value_unknown(dg_core_cell_t *c);

/**
 * TODO description
 */
void dg_base_gauge_set_vertical(dg_core_cell_t *c);

/**
 * TODO description
 */
void dg_base_gauge_show_label(dg_core_cell_t *c);

/************************************************************************************************************/
/************************************************************************************************************/
/************************************************************************************************************/

#ifdef __cplusplus
}
#endif

#endif /* DG_BASE_GAUGE_H */

