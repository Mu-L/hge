/*-----------------------------------------------------------------------------
 * Haaf's Game Engine 1.9
 * Copyright (C) 2003-2007, Relish Games
 * Maintained 2012-2021 by dmytro.lytovchenko@gmail.com (github @kvakvs)
 * Github -- https://github.com/kvakvs/hge | Discord -- https://discord.gg/TdjamHt
 *
 * Old website: http://hge.relishgames.com; Old forum: http://relishgames.com/forum
 *-----------------------------------------------------------------------------*/
//
// hge_tut01 - Minimal HGE application
//


#include <hge.h>

HGE *hge = nullptr;

// This function will be called by HGE once per frame.
// Put your game loop code here. In this example we
// just check whether ESC key has been pressed.
bool frame_func() {
  // By returning "true" we tell HGE
  // to stop running the application.
  if (hge->Input_GetKeyState(HGEK_ESCAPE)) return true;

  // Continue execution
  return false;
}

int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int) {
  // Here we use global pointer to HGE interface.
  // Instead you may use hgeCreate() every
  // time you need access to HGE. Just be sure to
  // have a corresponding hge->Release()
  // for each call to hgeCreate()
  hge = hgeCreate(HGE_VERSION);

  // Set our frame function
  hge->System_SetState(HGE_FRAMEFUNC, frame_func);

  // Set the window title
  hge->System_SetState(HGE_TITLE, "HGE Tutorial 01 - Minimal HGE application");

  // Run in windowed mode
  // Default window size is 800x600
  hge->System_SetState(HGE_WINDOWED, true);

  // Don't use BASS for sound
  hge->System_SetState(HGE_USESOUND, false);

  // Tries to initiate HGE with the states set.
  // If something goes wrong, "false" is returned
  // and more specific description of what have
  // happened can be read with System_GetErrorMessage().
  if (hge->System_Initiate()) {
    // Starts running FrameFunc().
    // Note that the execution "stops" here
    // until "true" is returned from FrameFunc().
    hge->System_Start();
  } else {
    // If HGE initialization failed show error message
    MessageBox(nullptr, hge->System_GetErrorMessage(), "Error",
               MB_OK | MB_ICONERROR | MB_APPLMODAL);
  }

  // Now ESC has been pressed or the user
  // has closed the window by other means.

  // Restore video mode and free
  // all allocated resources
  hge->System_Shutdown();

  // Release the HGE interface.
  // If there are no more references,
  // the HGE object will be deleted.
  hge->Release();

  return 0;
}
