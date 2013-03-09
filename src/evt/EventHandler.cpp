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
 * EventHandler.cpp
 * Created on: Mar 6, 2013
 */

#include "EventHandler.h"

namespace gware {

EventHandler::EventHandler()
    : EventHandlerIntf() {
    // nop
}

EventHandler::~EventHandler() {
    // nop
}

void EventHandler::onEvent(SDL_Event *e) {
    // dispatch based on event type
    switch(e->type) {
    case SDL_ACTIVEEVENT: {
        switch(e->active.state) {
        case SDL_APPMOUSEFOCUS: {
            if ( e->active.gain )   onMouseFocus();
            else                    onMouseBlur();

            break;
        }
        case SDL_APPINPUTFOCUS: {
            if ( e->active.gain )   onInputFocus();
            else                    onInputBlur();

            break;
        }
        case SDL_APPACTIVE:    {
            if ( e->active.gain )   onRestore();
            else                    onMinimize();

            break;
        }
        }
        break;
    }

    case SDL_KEYDOWN: {
        onKeyDown(e->key.keysym.sym,e->key.keysym.mod,e->key.keysym.unicode);
        break;
    }

    case SDL_KEYUP: {
        onKeyUp(e->key.keysym.sym,e->key.keysym.mod,e->key.keysym.unicode);
        break;
    }

    case SDL_MOUSEMOTION: {
        onMouseMove(e->motion.x,e->motion.y,e->motion.xrel,e->motion.yrel,(e->motion.state&SDL_BUTTON(SDL_BUTTON_LEFT))!=0,(e->motion.state&SDL_BUTTON(SDL_BUTTON_RIGHT))!=0,(e->motion.state&SDL_BUTTON(SDL_BUTTON_MIDDLE))!=0);
        break;
    }

    case SDL_MOUSEBUTTONDOWN: {
        switch(e->button.button) {
        case SDL_BUTTON_LEFT: {
            onLButtonDown(e->button.x,e->button.y);
            break;
        }
        case SDL_BUTTON_RIGHT: {
            onRButtonDown(e->button.x,e->button.y);
            break;
        }
        case SDL_BUTTON_MIDDLE: {
            onMButtonDown(e->button.x,e->button.y);
            break;
        }
        }
        break;
    }

    case SDL_MOUSEBUTTONUP: {
        switch(e->button.button) {
        case SDL_BUTTON_LEFT: {
            onLButtonUp(e->button.x,e->button.y);
            break;
        }
        case SDL_BUTTON_RIGHT: {
            onRButtonUp(e->button.x,e->button.y);
            break;
        }
        case SDL_BUTTON_MIDDLE: {
            onMButtonUp(e->button.x,e->button.y);
            break;
        }
        }
        break;
    }

    case SDL_JOYAXISMOTION: {
        onJoyAxis(e->jaxis.which,e->jaxis.axis,e->jaxis.value);
        break;
    }

    case SDL_JOYBALLMOTION: {
        onJoyBall(e->jball.which,e->jball.ball,e->jball.xrel,e->jball.yrel);
        break;
    }

    case SDL_JOYHATMOTION: {
        onJoyHat(e->jhat.which,e->jhat.hat,e->jhat.value);
        break;
    }
    case SDL_JOYBUTTONDOWN: {
        onJoyButtonDown(e->jbutton.which,e->jbutton.button);
        break;
    }

    case SDL_JOYBUTTONUP: {
        onJoyButtonUp(e->jbutton.which,e->jbutton.button);
        break;
    }

    case SDL_QUIT: {
        onExit();
        break;
    }

    case SDL_SYSWMEVENT: {
        //Ignore
        break;
    }

    case SDL_VIDEORESIZE: {
        onResize(e->resize.w,e->resize.h);
        break;
    }

    case SDL_VIDEOEXPOSE: {
        onExpose();
        break;
    }

    default: {
        onUser(e->user.type,e->user.code,e->user.data1,e->user.data2);
        break;
    }
    }
}

void EventHandler::onInputFocus() {}

void EventHandler::onInputBlur() {}

void EventHandler::onKeyDown(SDLKey sym, SDLMod mod, Uint16 unicode) {}

void EventHandler::onKeyUp(SDLKey sym, SDLMod mod, Uint16 unicode) {}

void EventHandler::onMouseFocus() {}

void EventHandler::onMouseBlur() {}

void EventHandler::onMouseMove(int mX, int mY, int relX, int relY, bool mLeft, bool mRight, bool mMiddle) {}

void EventHandler::onMouseWheel(bool mWheelUp, bool mWheelDown) {}

void EventHandler::onLButtonDown(int mX, int mY) {}

void EventHandler::onLButtonUp(int mX, int mY) {}

void EventHandler::onRButtonDown(int mX, int mY) {}

void EventHandler::onRButtonUp(int mX, int mY) {}

void EventHandler::onMButtonDown(int mX, int mY) {}

void EventHandler::onMButtonUp(int mX, int mY) {}

void EventHandler::onJoyAxis(Uint8 which, Uint8 axis, Sint16 value) {}

void EventHandler::onJoyButtonDown(Uint8 which, Uint8 button) {}

void EventHandler::onJoyButtonUp(Uint8 which, Uint8 button) {}

void EventHandler::onJoyHat(Uint8 which, Uint8 hat, Uint8 value) {}

void EventHandler::onJoyBall(Uint8 which, Uint8 ball, Sint16 xrel, Sint16 yrel) {}

void EventHandler::onMinimize() {}

void EventHandler::onRestore() {}

void EventHandler::onResize(int width, int height) {}

void EventHandler::onExpose() {}

void EventHandler::onExit() {}

void EventHandler::onUser(Uint8 type, int code, void *data1, void *data2) {}

} /* namespace gware */
