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
 * Tile.cpp
 * Created on: Mar 11, 2013
 */

#include "Tile.h"

#include "log/Logger.h"
#include "img/Surface.h"

namespace gware {

Tile::Tile(SDL_Surface *tex)
    : mSurface(tex) {
    // sanity check
    if(mSurface == NULL) {
        LOG(WARN) << "Create tile with NULL surface";
    }
}

Tile::~Tile() {
    if(mSurface != NULL) {
        delete mSurface;
        mSurface = NULL;
    }
}

void Tile::render(SDL_Surface *dest, Sint16 destX, Sint16 destY) {
    if(mSurface == NULL) {
        return;
    }

    Surface::blit(dest, mSurface, destX, destY);
}

GlTile::GlTile(SDL_Surface *tex)
    : Tile(tex) {
    if(mSurface != NULL) {
        // bind the gl texture
        glGenTextures(1, &mGlTextureId);

        if(!Surface::bindGlTexture(mGlTextureId, mSurface)) {
            // destroy everything so we don't use
            glDeleteTextures(1, &mGlTextureId);
            delete mSurface;
            mSurface = NULL;
        }
    }
}

GlTile::~GlTile() {
    if(mSurface != NULL) {
        glDeleteTextures(1, &mGlTextureId);
        delete mSurface;
        mSurface = NULL;
    }
}

void GlTile::render(int destX, int destY) {
    if(mSurface == NULL) {
        return;
    }

    Surface::drawQuadTexture(mGlTextureId, destX, destY, mSurface->w, mSurface->h);
}

} /* namespace gware */
