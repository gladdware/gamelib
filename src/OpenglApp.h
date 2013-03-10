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
 * OpenglApp.h
 * Created on: Mar 10, 2013
 */

#ifndef GWARE_OPENGLAPP_H_
#define GWARE_OPENGLAPP_H_

#include "App.h"
#include <GL/gl.h>
#include <GL/glu.h>

namespace gware {

/**
 * Container for OpenGL setup params
 */
struct OpenglContext {
    int colorBits;          ///< color framebuffer size (for RGB)
    int colorAccumBits;     ///< color accumulation buffer size (for RGB)
    int alphaBits;          ///< alpha channel framebuffer size
    int alphaAccumBits;     ///< alpha channel accumulation buffer size
    int depthBits;          ///< depth buffer size
    int bufferBits;         ///< framebuffer size
    bool doubleBuffer;      ///< use double buffering?
    bool antiAlias;         ///< use anti-aliasing?
    int aaSamples;          ///< anti-aliasing sample size
};

/**
 * A generic SDL+OpenGL application
 */
class OpenglApp : public App {
public:
    /**
     * Default constructor
     * Creates a 640x480 app, with bpp=32 and flags set to
     * (SDL_HWSURFACE | SDL_OPENGL)
     * All OpenGl settings are set to SDL defaults, and GL double buffering is
     * turned on
     */
    OpenglApp();

    /**
     * Constructor
     * Create an app with the given context params
     * All OpenGl settings are set to SDL defaults, and GL double buffering is
     * turned on
     */
    OpenglApp(AppContext appCtx);

    /**
     * Constructor
     * Create an app with the given context params
     */
    OpenglApp(AppContext appCtx, OpenglContext glCtx);

    /**
     * Destructor
     */
    virtual ~OpenglApp();

protected:
    /**
     * Performs basic SDL initialization based on the AppContext and
     * OpenglContext we were constructed with.
     *
     * @return true if initialization was successful
     */
    virtual bool init();

//    /**
//     * Performs basic SDL and OpenGL teardown.
//     */
//    virtual void cleanup();

    /**
     * Perform user initialization. Called after SDL and OpenGL have been
     * initialized and the video mode has been set.
     * Subclasses must implement!
     *
     * @return true if initialization was successful
     */
    virtual bool onInit() = 0;

    /**
     * Called once per frame, immediately prior to rendering the frame.
     * Subclasses must implement!
     *
     * @param elapsedMs Time elapsed since the start of the last frame (milliseconds)
     */
    virtual void onUpdate(const Uint32 elapsedMs) = 0;

    /**
     * Called once per frame to draw the scene to the display.
     * Subclasses must implement!
     */
    virtual void onRender() = 0;

    /**
     * Perform user cleanup. Called immediately before the cleanup
     * function. Teardown anything you set up in onInit.
     */
    virtual void onCleanup() = 0;

    bool mHaveGlContext;        ///< do we have an OpenGl context?
    OpenglContext mGlContext;   ///< the OpenGL context to use
};

} /* namespace gware */
#endif /* GWARE_OPENGLAPP_H_ */
