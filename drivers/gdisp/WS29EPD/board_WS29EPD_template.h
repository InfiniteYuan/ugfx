/*
 * This file is subject to the terms of the GFX License. If a copy of
 * the license was not distributed with this file, you can obtain one at:
 *
 *              http://ugfx.org/license.html
 */

#ifndef GDISP_LLD_BOARD_H
#define GDISP_LLD_BOARD_H

#include "WS29EPD.h"

static GFXINLINE void init_board(GDisplay *g) {
	(void) g;
}

static GFXINLINE void post_init_board(GDisplay *g) {
	(void) g;
}

static GFXINLINE void setpin_reset(GDisplay *g, gBool state) {
	(void) g;
  (void) state;
}

static GFXINLINE void acquire_bus(GDisplay *g) {
	(void) g;
}

static GFXINLINE void release_bus(GDisplay *g) {
	(void) g;
}

static GFXINLINE void write_data(GDisplay *g, uint8_t data) {
	(void) g;
  (void) data;
}

static GFXINLINE void write_reg(GDisplay *g, uint8_t reg, uint8_t data){
  (void) g;
  (void) reg;
  (void) data;
}

static GFXINLINE void write_cmd(GDisplay *g, uint8_t reg){
  (void) g;
  (void) reg;
}

static GFXINLINE void write_reg_data(GDisplay *g, uint8_t reg, uint8_t *data, uint8_t len) {
  (void) g;
  (void) reg;
  (void) data;
  (void) len;
}

#endif /* GDISP_LLD_BOARD_H */
