 
/*! file="Ravl/GUI/3D/gdkgl.h" */

/* Copyright (C) 1998 Janne L�f <jlof@mail.student.oulu.fi>
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Library General Public
 * License as published by the Free Software Foundation; either
 * version 2 of the License, or (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Library General Public License for more details.
 *
 * You should have received a copy of the GNU Library General Public
 * License along with this library; if not, write to the Free
 * Software Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.
 */

/*! rcsid="$Id$" */
/*! lib=RavlGUI3D */
/*! license=own */
/*! userlevel=Develop */
/*! docentry="Ravl.GUI.3D.Internal" */

#ifndef __GDK_GL_H__
#define __GDK_GL_H__

#include <glib.h>

#ifdef G_OS_WIN32
 /* The GL/gl.h on Windows requires you to include <windows.h>
  * anyway, so we might as well include it here.
  */
 #include <windows.h>
#endif

#include <gdk/gdk.h>

#ifdef __cplusplus
extern "C" {
#endif

/*
 * These definitions are duplicated from GL/glx.h that comes with Mesa.
 * I don't want every program to include GL/glx.h because GtkGLArea
 * supports lecacy systems like Windows. You can still use GLX_xxxx
 * attributes with these, but then you lose portability.
 */
enum _GDK_GL_CONFIGS {
        GDK_GL_NONE             = 0,
	GDK_GL_USE_GL		= 1,
	GDK_GL_BUFFER_SIZE	= 2,
	GDK_GL_LEVEL		= 3,
	GDK_GL_RGBA		= 4,
	GDK_GL_DOUBLEBUFFER	= 5, 
	GDK_GL_STEREO		= 6,
	GDK_GL_AUX_BUFFERS	= 7,
	GDK_GL_RED_SIZE		= 8,
	GDK_GL_GREEN_SIZE	= 9,
	GDK_GL_BLUE_SIZE	= 10,
	GDK_GL_ALPHA_SIZE	= 11,
	GDK_GL_DEPTH_SIZE	= 12,
	GDK_GL_STENCIL_SIZE	= 13,
	GDK_GL_ACCUM_RED_SIZE	= 14,
	GDK_GL_ACCUM_GREEN_SIZE	= 15,
	GDK_GL_ACCUM_BLUE_SIZE	= 16,
	GDK_GL_ACCUM_ALPHA_SIZE	= 17,

	/* GLX_EXT_visual_info extension */
	GDK_GL_X_VISUAL_TYPE_EXT                = 0x22,
	GDK_GL_TRANSPARENT_TYPE_EXT	        = 0x23,
	GDK_GL_TRANSPARENT_INDEX_VALUE_EXT	= 0x24,
	GDK_GL_TRANSPARENT_RED_VALUE_EXT	= 0x25,
	GDK_GL_TRANSPARENT_GREEN_VALUE_EXT	= 0x26,
	GDK_GL_TRANSPARENT_BLUE_VALUE_EXT	= 0x27,
	GDK_GL_TRANSPARENT_ALPHA_VALUE_EXT	= 0x28
};


typedef struct _GdkGLContext GdkGLContext;


gint          gdk_gl_query(void);
gchar        *gdk_gl_get_info(void);

GdkVisual    *gdk_gl_choose_visual(int *attrlist);
int           gdk_gl_get_config(GdkVisual *visual, int attrib);

GdkGLContext *gdk_gl_context_new(GdkVisual *visual);
GdkGLContext *gdk_gl_context_share_new(GdkVisual *visual, GdkGLContext *sharelist, gint direct);
GdkGLContext *gdk_gl_context_attrlist_share_new(int *attrlist, GdkGLContext *sharelist, gint direct);

GdkGLContext *gdk_gl_context_ref(GdkGLContext *context);
void          gdk_gl_context_unref(GdkGLContext *context);

gint          gdk_gl_make_current(GdkDrawable *drawable, GdkGLContext *context);
void          gdk_gl_swap_buffers(GdkDrawable *drawable);


void          gdk_gl_wait_gdk(void);
void          gdk_gl_wait_gl(void);


/* glpixmap stuff */

typedef struct _GdkGLPixmap GdkGLPixmap;

GdkGLPixmap *gdk_gl_pixmap_new(GdkVisual *visual, GdkPixmap *pixmap);
GdkGLPixmap *gdk_gl_pixmap_ref(GdkGLPixmap *glpixmap);
void         gdk_gl_pixmap_unref(GdkGLPixmap *glpixmap);

gint         gdk_gl_pixmap_make_current(GdkGLPixmap *glpixmap, GdkGLContext *context);


/* fonts */
void gdk_gl_use_gdk_font(GdkFont *font, int first, int count, int list_base);


#ifdef __cplusplus
}
#endif


#endif /* __GDK_GL_H__ */

