/*
    MapDoorWindow
    Window that displays the current map and door name
*/
#pragma once

#include "mod_ui_base/window.h"

namespace mod {

class MapDoorWindow final : public Window
{
protected:
    virtual void disp() override;
    char mMapMsg[40];
    char mDoorMsg[40];
    wii::RGBA mColour;
    f32 mScale;

    MapDoorWindow();
    
public:
    // Window::mPosX/Y are used for top left corner of window

    static MapDoorWindow * sInstance;

    static void init();
};

}
