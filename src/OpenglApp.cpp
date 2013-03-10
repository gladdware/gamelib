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
 * OpenglApp.cpp
 * Created on: Mar 10, 2013
 */

#include "OpenglApp.h"

#include "log/Logger.h"

namespace gware {

OpenglApp::OpenglApp()
    : App(),
      mHaveGlContext(false) {
    // set opengl flags
    mContext.videoModeFlags = (SDL_HWSURFACE | SDL_OPENGL);
}

OpenglApp::OpenglApp(AppContext appCtx)
    : App(appCtx),
      mHaveGlContext(false) {
    // nop
}

OpenglApp::OpenglApp(AppContext appCtx, OpenglContext glCtx)
    : App(appCtx),
      mHaveGlContext(true),
      mGlContext(glCtx) {
    // nop
}

OpenglApp::~OpenglApp() {
    // TODO Auto-generated destructor stub
}

bool OpenglApp::init() {
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

    // OpenGL settings
    if(mHaveGlContext) {
        // use values from glCtx
        SDL_GL_SetAttribute(SDL_GL_RED_SIZE, mGlContext.colorBits);
        SDL_GL_SetAttribute(SDL_GL_GREEN_SIZE, mGlContext.colorBits);
        SDL_GL_SetAttribute(SDL_GL_BLUE_SIZE, mGlContext.colorBits);
        SDL_GL_SetAttribute(SDL_GL_ALPHA_SIZE, mGlContext.alphaBits);

        SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, mGlContext.depthBits);
        SDL_GL_SetAttribute(SDL_GL_BUFFER_SIZE, mGlContext.bufferBits);

        SDL_GL_SetAttribute(SDL_GL_ACCUM_RED_SIZE, mGlContext.colorAccumBits);
        SDL_GL_SetAttribute(SDL_GL_ACCUM_GREEN_SIZE, mGlContext.colorAccumBits);
        SDL_GL_SetAttribute(SDL_GL_ACCUM_BLUE_SIZE, mGlContext.colorAccumBits);
        SDL_GL_SetAttribute(SDL_GL_ACCUM_ALPHA_SIZE, mGlContext.alphaAccumBits);

        SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER,  (mGlContext.doubleBuffer?1:0));

        if(mGlContext.antiAlias) {
            SDL_GL_SetAttribute(SDL_GL_MULTISAMPLEBUFFERS, 1);
            SDL_GL_SetAttribute(SDL_GL_MULTISAMPLESAMPLES, mGlContext.aaSamples);
        }
    } else {
        // use defaults
        SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER,  1);
    }

    // try to setup root surface
    mRootSurface = SDL_SetVideoMode(mContext.width, mContext.height,
            mContext.bpp, mContext.videoModeFlags);

    if(mRootSurface == NULL) {
        LOGF(ERROR, "SDL_SetVideoMode failure: %s", SDL_GetError());
        return false;
    } else {
        if(mWindowTitle != NULL) {
            SDL_WM_SetCaption(mWindowTitle, mWindowTitle);
        } else {
            SDL_WM_SetCaption(DEF_CAPTION, DEF_CAPTION);
        }

        // print OpenGL info
        LOG(INFO) << "OpenGL Info:";
        LOGF(INFO, "  Vendor:   %s", glGetString(GL_VENDOR));
        LOGF(INFO, "  Renderer: %s", glGetString(GL_RENDERER));
        LOGF(INFO, "  Version:  %s", glGetString(GL_VERSION));

        // OpenGL init
        glClearColor(0.0, 0.0, 0.0, 0.0);

        glViewport(0, 0, mContext.width, mContext.height);

        glMatrixMode(GL_PROJECTION);
        glLoadIdentity();

        glOrtho(0.0, mContext.width, mContext.height, 0.0, 1.0, -1.0);

        glMatrixMode(GL_MODELVIEW);

        glEnable(GL_TEXTURE_2D);

        glLoadIdentity();

        return true;
    }
}

//void OpenglApp::cleanup() {
//
//}

} /* namespace gware */
