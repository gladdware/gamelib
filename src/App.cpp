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
 * App.cpp
 * Created on: Mar 3, 2013
 */

#include "App.h"
#include "log/Logger.h"

#include <cmath>
#include <cstdio>
#include <cstring>

namespace gware {

App::App()
    : mRunFlag(true),
      mLastLoopTimeMs(0),
      mTgtFrameLenMs(DEF_FRAME_LEN_MS),
      mWindowTitle(NULL),
      mRootSurface(NULL),
      mEvtHandler(NULL) {
    // setup default app context
    mContext.width = 640;
    mContext.height = 480;
    mContext.bpp = 32;
    mContext.videoModeFlags = (SDL_HWSURFACE | SDL_DOUBLEBUF);
}

App::App(AppContext ctx)
    : mRunFlag(true),
      mLastLoopTimeMs(0),
      mTgtFrameLenMs(DEF_FRAME_LEN_MS),
      mWindowTitle(NULL),
      mRootSurface(NULL),
      mEvtHandler(NULL),
      mContext(ctx) {
    // nop
}

App::~App() {
    if(mWindowTitle != NULL) {
        delete mWindowTitle;
    }
}

int App::execute() {
    if(!init()) {
        LOG(CRIT) << "Initialization failure; aborting execution";
        return -1;
    } else if(!onInit()) {
        // account for core init success, then user init failure
        LOG(CRIT) << "User initialization failure; aborting execution";
        cleanup();
        return -1;
    }
    // else run exec loop

    SDL_Event evt;

    while(mRunFlag) {
        // pull time
        Uint32 frameStartMs = SDL_GetTicks();
        Uint32 elapsedMs = frameStartMs - mLastLoopTimeMs;

        // check events
        while(SDL_PollEvent(&evt)) {
            handleEvent(&evt);
        }

        // update the scene
        onUpdate(elapsedMs);

        // render the scene
        onRender();

        // TODO get current run flag protected by mutex

        // update last loop time
        mLastLoopTimeMs = frameStartMs;

        // framerate capping
        Uint32 frameTimeMs = SDL_GetTicks() - frameStartMs;
        long targetDiffMs = long(mTgtFrameLenMs) - long(frameTimeMs);
        if(targetDiffMs >= 10) {
            SDL_Delay(Uint32(targetDiffMs));
        }
    }

    // done; cleanup
    onCleanup();
    cleanup();

    return 0;
}

void App::setTargetFramerate(Uint32 fps) {
    if(fps > 0 && fps <= 1000) {
        mTgtFrameLenMs = floor(1000.0 / fps);
        LOG(DEBUG) << "New target frame duration: " << mTgtFrameLenMs << "ms";
    } else {
        LOG(ERROR) << "Target framerate must be between 1 and 1000 (inclusive)";
    }
}

void App::setWindowTitle(char *title) {
    if(title == NULL) {
        return;
    }

    if(mWindowTitle != NULL) {
        delete mWindowTitle;
    }

    mWindowTitle = new char[strlen(title) + 1];
    memset(mWindowTitle, 0, strlen(title) + 1);
    strncpy(mWindowTitle, title, strlen(title));
}

void App::setEventHandler(EventHandlerIntf *evtHdl) {
    // TODO protect with a mutex
    // destroy current handler if we have one
    if(mEvtHandler != NULL && mEvtHandler != dynamic_cast<EventHandlerIntf*>(this)) {
        delete mEvtHandler;
    }

    if(evtHdl == NULL) {
        LOG(INFO) << "Setting NULL event handler";
        mEvtHandler = NULL;
    } else {
        mEvtHandler = evtHdl;
    }
}

void App::requestShutdown() {
    // TODO protect with mutex
    mRunFlag = false;
}

bool App::init() {
    // safety check
    if(mRootSurface != NULL) {
        LOG(WARN) << "Trying to reinitialize App";
        return false;
    }

    // dump version info
    SDL_version v;
    SDL_VERSION(&v);
    LOGF(INFO, "SDL Compilation version: %u.%u.%u", v.major, v.minor, v.patch);
    v = *SDL_Linked_Version();
    LOGF(INFO, "SDL Linked version:      %u.%u.%u", v.major, v.minor, v.patch);

    // init SDL
    if(SDL_Init(SDL_INIT_EVERYTHING) < 0) {
        LOGF(ERROR, "SDL_Init failure: %s", SDL_GetError());
        return false;
    }

    // try to setup root surface
    mRootSurface = SDL_SetVideoMode(mContext.width, mContext.height,
            mContext.bpp, mContext.videoModeFlags);

    if(mRootSurface == NULL) {
        return false;
    } else {
        if(mWindowTitle != NULL) {
            SDL_WM_SetCaption(mWindowTitle, mWindowTitle);
        } else {
            SDL_WM_SetCaption(DEF_CAPTION, DEF_CAPTION);
        }

        return true;
    }
}

void App::cleanup() {
    // standard cleanup
    SDL_FreeSurface(mRootSurface);
    SDL_Quit();
}

void App::handleEvent(SDL_Event *e) {
    // TODO protect with a mutex
    // dispatch through the event handler, if we have one
    if(mEvtHandler != NULL) {
        mEvtHandler->onEvent(e);
    } else {
        LOGF(DEBUG, "Ignoring event type 0x%02x (no event handler)", e->type);
    }
}

} /* namespace gware */
