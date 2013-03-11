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
 * App.h
 * Created on: Mar 3, 2013
 */

#ifndef GWARE_APP_H_
#define GWARE_APP_H_

#include "EventHandlerIntf.h"
#include <SDL/SDL.h>

#define DEF_FRAME_LEN_MS 33
#define DEF_CAPTION "SDL App"

namespace gware {

/**
 * Container for App setup params
 */
struct AppContext {
    int width;              ///< App window resolution width in pixels
    int height;             ///< App window resolution height in pixels
    int bpp;                ///< Bits per pixel
    Uint32 videoModeFlags;  ///< SDL video mode flags
};

/**
 * A generic SDL application
 */
class App {
public:
    /**
     * Default constructor
     * Creates a 640x480 app, with bpp=32 and flags set to
     * (SDL_HWSURFACE | SDL_DOUBLEBUF)
     */
    App();

    /**
     * Constructor
     * Create an app with the give context params
     */
    App(AppContext ctx);

    /**
     * Destructor
     */
    virtual ~App();

    /**
     * Start the main loop of the app.
     * Should never be overridden by sublasses!
     */
    int execute();

    /**
     * Set the app's target framerate (attempt to save HW resources)
     */
    void setTargetFramerate(Uint32 fps);

    /**
     * Set the app window title; should be set before init.
     */
    void setWindowTitle(char *title);

    /**
     * Set the event handler for the app.
     */
    void setEventHandler(EventHandlerIntf *evtHdl);

    /**
     * Request that the app shutdown.
     */
    void requestShutdown();

protected:
    /**
     * Performs basic SDL initialization based on the AppContext we were
     * constructed with.
     *
     * @return true if initialization was successful
     */
    virtual bool init();

    /**
     * Performs basic SDL teardown.
     */
    virtual void cleanup();

    /**
     * Perform user initialization. Called after SDL has been initialized and
     * the video mode has been set. If you want to use OpenGL, this is where
     * you'd want to initialize it.
     * Subclasses must implement!
     *
     * @return true if initialization was successful
     */
    virtual bool onInit() = 0;

    /**
     * Called once per frame, immediately prior to rendering the frame.
     * Subclasses must implement!
     *
     * @param elapsedMs Time elapsed since the last frame (milliseconds)
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


    /** Root scene surface */
    SDL_Surface *mRootSurface;

    bool mRunFlag;              ///< is the app currently running?
    Uint32 mLastLoopTimeMs;     ///< last exec time of the main loop (ms)
    Uint32 mTgtFrameLenMs;      ///< target frame duration (ms)
    char *mWindowTitle;         ///< desired window title
    EventHandlerIntf *mEvtHandler;  ///< the current event handler
    AppContext mContext;        ///< app creation context

private:
    /**
     * Thread-safe event dispatcher
     */
    void handleEvent(SDL_Event *e);
};

} /* namespace gware */
#endif /* GWARE_APP_H_ */
