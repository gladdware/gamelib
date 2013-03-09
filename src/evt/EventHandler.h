/*
 * Copyright 2013 Alex Gladd
 *
 * This file is part of Gladdware-gamelib.
 *
 * Gladdware-gamelib is free software: you can redistribute it and/or modify
 * it under the terms of the GNU Lesser General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * Gladdware-gamelib is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public License
 * along with Gladdware-gamelib.  If not, see <http://www.gnu.org/licenses/>.
 *
 * EventHandler.h
 * Created on: Mar 6, 2013
 */

#ifndef GWARE_EVENTHANDLER_H_
#define GWARE_EVENTHANDLER_H_

#include "EventHandlerIntf.h"

namespace gware {

/**
 * A basic SDL event handler implementation
 *
 * Adapted from sdltutorials.com (http://www.sdltutorials.com/sdl-events)
 */
class EventHandler : public EventHandlerIntf {
public:
    EventHandler();
    virtual ~EventHandler();

    virtual void onEvent(SDL_Event *e);

    virtual void onInputFocus();

    virtual void onInputBlur();

    virtual void onKeyDown(SDLKey sym, SDLMod mod, Uint16 unicode);

    virtual void onKeyUp(SDLKey sym, SDLMod mod, Uint16 unicode);

    virtual void onMouseFocus();

    virtual void onMouseBlur();

    virtual void onMouseMove(int mX, int mY, int relX, int relY, bool mLeft, bool mRight, bool mMiddle);

    virtual void onMouseWheel(bool mWheelUp, bool mWheelDown);

    virtual void onLButtonDown(int mX, int mY);

    virtual void onLButtonUp(int mX, int mY);

    virtual void onRButtonDown(int mX, int mY);

    virtual void onRButtonUp(int mX, int mY);

    virtual void onMButtonDown(int mX, int mY);

    virtual void onMButtonUp(int mX, int mY);

    virtual void onJoyAxis(Uint8 which, Uint8 axis, Sint16 value);

    virtual void onJoyButtonDown(Uint8 which, Uint8 button);

    virtual void onJoyButtonUp(Uint8 which, Uint8 button);

    virtual void onJoyHat(Uint8 which, Uint8 hat, Uint8 value);

    virtual void onJoyBall(Uint8 which, Uint8 ball, Sint16 xrel, Sint16 yrel);

    virtual void onMinimize();

    virtual void onRestore();

    virtual void onResize(int width, int height);

    virtual void onExpose();

    virtual void onExit();

    virtual void onUser(Uint8 type, int code, void *data1, void *data2);
};

} /* namespace gware */
#endif /* EVENTHANDLER_H_ */
