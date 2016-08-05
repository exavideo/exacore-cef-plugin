// Copyright (c) 2013 The Chromium Embedded Framework Authors. All rights
// reserved. Use of this source code is governed by a BSD-style license that
// can be found in the LICENSE file.

#include "simple_app.h"

#include <string>

#include "simple_handler.h"
#include "include/cef_browser.h"
#include "include/cef_command_line.h"
#include "include/views/cef_window.h"
#include "include/wrapper/cef_helpers.h"

SimpleApp::SimpleApp() {
}

void SimpleApp::OnContextInitialized() {
  CEF_REQUIRE_UI_THREAD();

  CefRefPtr<CefCommandLine> command_line =
      CefCommandLine::GetGlobalCommandLine();

  // SimpleHandler implements browser-level callbacks.
  CefRefPtr<SimpleHandler> handler(new SimpleHandler);
  handler->set_shmbuf_fd(9);

  // Specify CEF browser settings here.
  CefBrowserSettings browser_settings;
  browser_settings.windowless_frame_rate = 60;

  std::string url;

  // Check if a "--url=" value was provided via the command-line. If so, use
  // that instead of the default URL.
  url = command_line->GetSwitchValue("url");
  if (url.empty())
    url = "http://www.google.com";

  // Information used when creating the native window.
  CefWindowInfo window_info;

  // enable offscreen rendering to our SimpleHandler's OnPaint method
  window_info.SetAsWindowless(0, true);

  // Create the first browser window.
  CefBrowserHost::CreateBrowser(window_info, handler, url, browser_settings,
                                NULL);
  
}
