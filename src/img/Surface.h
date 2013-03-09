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
 * Surface.h
 * Created on: Mar 7, 2013
 */

#ifndef GWARE_SURFACE_H_
#define GWARE_SURFACE_H_

#include <SDL/SDL.h>

namespace gware {

/**
 * Convenience functions for loading SDL_Surfaces
 */
class Surface {
public:
    virtual ~Surface();

    /**
     * Attempts to load an image into a new SDL_Surface from the given filename.
     * Supports all image formats supported by the SDL_Image library. If the
     * surface is loaded successfully, it's converted to the current display
     * format before being returned. If the loaded image has an alpha channel,
     * it will be preserved.
     *
     * Users are responsible for freeing the returned surface.
     *
     * @param filename Path to image file to load
     * @return A new SDL_Surface for the image, or NULL on any errors
     */
    static SDL_Surface *load(const char *filename);

    // TODO add a version of 'load' that can set COLORKEY for alpha

    /**
     * Shortcut for SDL surface blitting.
     * Blits the source surface onto the destination surface at the given
     * coordinates on the destination.
     */
    static void blit(SDL_Surface *dest, SDL_Surface *src, Sint16 destX, Sint16 destY);

protected:
    // Should never be instantiated
    Surface();
};

} /* namespace gware */
#endif /* GWARE_SURFACE_H_ */
