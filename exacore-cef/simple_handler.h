// Copyright (c) 2013 The Chromium Embedded Framework Authors. All rights
// reserved. Use of this source code is governed by a BSD-style license that
// can be found in the LICENSE file.

#ifndef CEF_TESTS_CEFSIMPLE_SIMPLE_HANDLER_H_
#define CEF_TESTS_CEFSIMPLE_SIMPLE_HANDLER_H_

#include "include/cef_client.h"
#include "shm_double_buffer.h"

class SimpleHandler : public CefClient,
                      public CefLifeSpanHandler,
		      public CefRenderHandler {
 public:
  SimpleHandler();
  ~SimpleHandler();

  virtual CefRefPtr<CefLifeSpanHandler> GetLifeSpanHandler() OVERRIDE {
    return this;
  }

  virtual CefRefPtr<CefRenderHandler> GetRenderHandler() OVERRIDE {
    return this;
  }

  // CefLifeSpanHandler methods:
  virtual void OnBeforeClose(CefRefPtr<CefBrowser> browser) OVERRIDE;

  // CefRenderHandler methods:
  virtual bool GetRootScreenRect(CefRefPtr<CefBrowser> browser, CefRect &rect);
  virtual bool GetScreenInfo(
    CefRefPtr<CefBrowser> browser, 
    CefScreenInfo &screen_info
  );
  virtual bool GetScreenPoint(
    CefRefPtr<CefBrowser> browser, 
    int viewX, int viewY,
    int &screenX, int &screenY
  );
  virtual bool GetViewRect(CefRefPtr<CefBrowser> browser, CefRect &rect);
  virtual void OnPaint(
    CefRefPtr<CefBrowser> browser,
    PaintElementType type,
    const RectList &dirtyRects,
    const void *buffer, int width, int height
  );

  void set_shmbuf_fd(int fd);
  
 private:
  // shared memory buffer to write the images to
  ShmDoubleBuffer shmbuf;

  // Include the default reference counting implementation.
  IMPLEMENT_REFCOUNTING(SimpleHandler);
};

#endif  // CEF_TESTS_CEFSIMPLE_SIMPLE_HANDLER_H_
