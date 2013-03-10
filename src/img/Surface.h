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
#include <GL/gl.h>

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

    /**
     * Attempts to load an image into a new OpenGL texture (represented by the
     * give texture ID). The image is first loaded with SDL, then transformed
     * and bound to the OpenGL texture. If the image has an alpha channel and
     * the current display format supports alpha channels, it will be preserved.
     *
     * Texture IDs must be created with glGenTextures.
     *
     * Users are responsible for freeing OpenGL textures.
     *
     * @param texId The OpenGL texture ID
     * @param filename Path to image file to load
     * @return A new SDL_Surface for the image, or NULL on any errors
     */
    static SDL_Surface *loadGlTexture(GLuint texId, const char *filename);

    /**
     * Shortcut for drawing a texture on an OpenGL quad primitive. Draws an
     * OpenGL quad at the given location with the given size with the texture
     * mapped on top of it. Assumes the given texture ID maps to a texture that
     * has already been created.
     */
    static void drawQuadTexture(GLuint texId, int destX, int destY, int width, int height);

protected:
    // Should never be instantiated
    Surface();
};

} /* namespace gware */
#endif /* GWARE_SURFACE_H_ */
