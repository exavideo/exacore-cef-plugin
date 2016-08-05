// Copyright (c) 2013 The Chromium Embedded Framework Authors. All rights
// reserved. Use of this source code is governed by a BSD-style license that
// can be found in the LICENSE file.

#include "simple_handler.h"

#include <sstream>
#include <string>

#include "include/base/cef_bind.h"
#include "include/base/cef_logging.h"
#include "include/cef_app.h"
#include "include/views/cef_browser_view.h"
#include "include/views/cef_window.h"
#include "include/wrapper/cef_closure_task.h"
#include "include/wrapper/cef_helpers.h"

#include <unistd.h>
#include <fcntl.h>

#if 0
/* helper for write()-ing big chunks of data */
static ssize_t write_all(int fd, const void *data, size_t size) {
    ssize_t written;
    uint8_t *buf = (uint8_t *) data;

    while (size > 0) {
        written = write(fd, buf, size);
        if (written > 0) {
            size -= written;
            buf += written;
        } else if (written == 0) {
            /* what exactly does this mean? we'll try again */
        } else {
            if (errno == EAGAIN || errno == EINTR) {
                /* don't worry about these */
            } else {
                /* exit (pass errno through to caller) */
                return -1;
            }
        }
    }

    return 1;
}
#endif

SimpleHandler::SimpleHandler( ) {
#if 0
	outfd = open("/tmp/ceftest.tga", O_WRONLY | O_TRUNC | O_CREAT, 0666);
	if (outfd == -1) {
		LOG(WARNING) << "failed to open tga stream";	
	}
#endif
}

SimpleHandler::~SimpleHandler() {

}

void SimpleHandler::OnBeforeClose(CefRefPtr<CefBrowser> browser) {
    // All browser windows have closed. Quit the application message loop.
    CefQuitMessageLoop();
}


bool SimpleHandler::GetRootScreenRect(CefRefPtr<CefBrowser> browser, CefRect &rect) {
	/* static 1920x1080 screen */
	rect.Set(0, 0, 1920, 1080);
	return true;
}

bool SimpleHandler::GetScreenInfo(
  CefRefPtr<CefBrowser> browser, 
  CefScreenInfo &screen_info
) {
	CefRect rect;
	GetViewRect(browser, rect);
	screen_info.Set(1.0f, 32, 8, false, rect, rect);
	return true;
}

bool SimpleHandler::GetScreenPoint(
  CefRefPtr<CefBrowser> browser, 
  int viewX, int viewY,
  int &screenX, int &screenY
) {
	screenX = viewX;
	screenY = viewY;
	return true;
}

bool SimpleHandler::GetViewRect(CefRefPtr<CefBrowser> browser, CefRect &rect) {
	rect.Set(0, 0, 1920, 1080);
	return true;
}

void SimpleHandler::OnPaint(
  CefRefPtr<CefBrowser> browser,
  PaintElementType type,
  const RectList &dirtyRects,
  const void *buffer, int width, int height
) {
	void *outbuf;
	bool flipped;
#if 0
	unsigned char tgahead[] = { 
		0x00,	/* [0] no image ID field */
		0x00,	/* [1] no color map present */
		0x02,	/* [2] true color, uncompressed */
		0x00, 0x00, 0x00, 0x00, 0x00,	/* [3-7] color map spec (not used) */
		0x00, 0x00, 0x00, 0x00,		/* [8-11] X-origin and Y-origin (zero) */
		0x00, 0x00, 0x00, 0x00,		/* [12-15] width, height (we will fill in) */
		32, 0x28			/* [16-17] bits per pixel, flags */
	};
	if (type == PET_VIEW && outfd != -1 && width > 0 && height > 0) {
		/* let's write the image as a TGA to the end of our file */
		tgahead[12] = (unsigned char) (width & 0xff);
		tgahead[13] = (unsigned char) ((width >> 8) & 0xff);
		tgahead[14] = (unsigned char) (height & 0xff);
		tgahead[15] = (unsigned char) ((height >> 8) & 0xff);

		write_all(outfd, tgahead, sizeof(tgahead));
		write_all(outfd, buffer, 4*width*height);
	}
#endif
	if (type == PET_VIEW && width == 1920 && height == 1080) {
		shmbuf.begin_write(outbuf, flipped);
		memcpy(outbuf, buffer, 4*width*height);
		shmbuf.end_write( );
	}
}

void SimpleHandler::set_shmbuf_fd(int fd) {
	shmbuf.init_from_fd(fd);
}
