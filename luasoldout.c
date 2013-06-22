/*
 * Copyright (c) 2013 James Turner <james@calminferno.net>
 *
 * Permission to use, copy, modify, and distribute this software for any
 * purpose with or without fee is hereby granted, provided that the above
 * copyright notice and this permission notice appear in all copies.
 *
 * THE SOFTWARE IS PROVIDED "AS IS" AND THE AUTHOR DISCLAIMS ALL WARRANTIES
 * WITH REGARD TO THIS SOFTWARE INCLUDING ALL IMPLIED WARRANTIES OF
 * MERCHANTABILITY AND FITNESS. IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR
 * ANY SPECIAL, DIRECT, INDIRECT, OR CONSEQUENTIAL DAMAGES OR ANY DAMAGES
 * WHATSOEVER RESULTING FROM LOSS OF USE, DATA OR PROFITS, WHETHER IN AN
 * ACTION OF CONTRACT, NEGLIGENCE OR OTHER TORTIOUS ACTION, ARISING OUT OF
 * OR IN CONNECTION WITH THE USE OR PERFORMANCE OF THIS SOFTWARE.
 */

#include <lua.h>
#include <lauxlib.h>
#include <lualib.h>

#include "ext/markdown.h"
#include "ext/renderers.h"

#include <string.h>

#define INPUT_UNIT 1024
#define OUTPUT_UNIT 64

static int l_markdown(lua_State *L)
{
	struct buf *ib, *ob;
	const struct mkd_renderer *hrndr, *xrndr;
	const struct mkd_renderer **prndr;

	const char *mkd = luaL_checkstring(L, 1);
	const char *rndr = luaL_optstring(L, 2, "html");
	const char *ext  = luaL_optstring(L, 3, "markdown");

	hrndr = &mkd_html;
	xrndr = &mkd_xhtml;

	if (strcmp(ext, "discount") == 0) {
		hrndr = &discount_html;
		xrndr = &discount_xhtml;
	}
	else if (strcmp(ext, "natext") == 0) {
		hrndr = &nat_html;
		xrndr = &nat_xhtml;
	}

	if (strcmp(rndr, "xhtml") == 0)
		prndr = &xrndr;
	else
		prndr = &hrndr;

	ib = bufnew(INPUT_UNIT);
	bufgrow(ib, strlen(mkd) + 1);

	ib->size = strlen(mkd);
	strncpy(ib->data, mkd, ib->size);

	ob = bufnew(OUTPUT_UNIT);
	markdown(ob, ib, *prndr);

	lua_pushlstring(L, ob->data, ob->size);

	bufrelease(ib);
	bufrelease(ob);

	return 1;
}

int luaopen_soldout(lua_State *L)
{
	static const struct luaL_Reg methods[] = {
		{ "markdown",	l_markdown },
		{ NULL,		NULL }
	};

	lua_newtable(L);
	luaL_setfuncs(L, methods, 0);
	return 1;
}
