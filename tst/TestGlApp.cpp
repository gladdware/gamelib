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
 * TestGlApp.cpp
 * Created on: Mar 10, 2013
 */

#include <OpenglApp.h>
#include <evt/EventHandler.h>
#include <img/Surface.h>
#include <log/Logger.h>

using namespace gware;

class TestGlApp : public OpenglApp, public EventHandler {
public:
    TestGlApp(AppContext ctx) : OpenglApp(ctx) { test = NULL; }
    virtual ~TestGlApp() {}

protected:
    bool onInit() {
        test = Surface::load("/home/agladd/alpha-test.png");

        if(test == NULL) return false;
        else return true;
    }
    void onUpdate(const Uint32 elapsedMs) {
//        LOG(DEBUG) << "Update with " << elapsedMs << "ms elapsed";
    }
    void onRender() {
//        Surface::blit(mRootSurface, test, 0, 0);
//
//        SDL_Flip(mRootSurface);
    }
    void onCleanup() {
        if(test != NULL) {
            SDL_FreeSurface(test);
        }
    }
    void onExit() {
        requestShutdown();
    }

private:
    SDL_Surface *test;
};

int main(int argc, char *argv[]) {
    Logger::setLogLevel(Logger::LOG_DEBUG);

    AppContext ctx;
    ctx.width = 800;
    ctx.height = 600;
    ctx.bpp = 32;
    ctx.videoModeFlags = (SDL_HWSURFACE | SDL_OPENGL);

    TestGlApp app(ctx);

    app.setTargetFramerate(60);
    app.setWindowTitle("TestGlApp");
    app.setEventHandler(&app);

    return app.execute();
}
