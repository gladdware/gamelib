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
 * Tile.h
 * Created on: Mar 11, 2013
 */

#ifndef GWARE_TILE_H_
#define GWARE_TILE_H_

#include <SDL/SDL.h>
#include <GL/gl.h>

namespace gware {

/**
 * Very simple SDL tile texture container
 */
class Tile {
public:
    /**
     * Constructor
     * Takes ownership of the given texture
     */
    Tile(SDL_Surface *tex);

    /**
     * Destructor
     */
    virtual ~Tile();

    /**
     * Render the tile on the given surface at the given location
     */
    void render(SDL_Surface *dest, Sint16 destX, Sint16 destY);

protected:
    SDL_Surface *mSurface;
};

/**
 * Very simple OpenGl tile texture container
 */
class GlTile : public Tile {
public:
    /**
     * Constructor
     * Takes ownership of the given texture
     */
    GlTile(SDL_Surface *tex);

    /**
     * Destructor
     */
    virtual ~GlTile();

    /**
     * Renders the tile as an OpenGL texture at the given location
     */
    void render(int destX, int destY);

protected:
    GLuint mGlTextureId;
};

} /* namespace gware */
#endif /* GWARE_TILE_H_ */
