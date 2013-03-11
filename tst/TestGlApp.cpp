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
#include <EventHandler.h>
#include <Surface.h>
#include <Logger.h>

using namespace gware;

class TestGlApp : public OpenglApp, public EventHandler {
public:
    TestGlApp(AppContext ctx, OpenglContext glCtx) : OpenglApp(ctx, glCtx) { test = NULL; }
    virtual ~TestGlApp() {}

protected:
    bool onInit() {
        glGenTextures(1, textures);
        test = Surface::loadGlTexture(textures[0], "/home/agladd/alpha-test.png");

        if(test == NULL) return false;
        else return true;
    }
    void onUpdate(const Uint32 elapsedMs) {
//        LOG(DEBUG) << "Update with " << elapsedMs << "ms elapsed";
    }
    void onRender() {
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        glLoadIdentity();

        Surface::drawQuadTexture(textures[0], 0, 0, test->w, test->h);

        SDL_GL_SwapBuffers();
    }
    void onCleanup() {
        if(test != NULL) {
            SDL_FreeSurface(test);
        }

        glDeleteTextures(1, textures);
    }
    void onExit() {
        requestShutdown();
    }

private:
    SDL_Surface *test;
    GLuint textures[1];
};

int main(int argc, char *argv[]) {
    Logger::setLogLevel(Logger::LOG_DEBUG);

    AppContext ctx;
    ctx.width = 800;
    ctx.height = 600;
    ctx.bpp = 32;
    ctx.videoModeFlags = (SDL_HWSURFACE | SDL_OPENGL);

    OpenglContext glCtx;
    glCtx.colorBits = 8;
    glCtx.colorAccumBits = 8;
    glCtx.alphaBits = 8;
    glCtx.alphaAccumBits = 8;
    glCtx.depthBits = 16;
    glCtx.bufferBits = 32;
    glCtx.doubleBuffer = true;
    glCtx.antiAlias = false;
    glCtx.aaSamples = 2;

    TestGlApp app(ctx, glCtx);

    app.setTargetFramerate(60);
    app.setWindowTitle("TestGlApp");
    app.setEventHandler(&app);

    return app.execute();
}
