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
 * Surface.cpp
 * Created on: Mar 7, 2013
 */

#include "Surface.h"
#include "log/Logger.h"
#include "util/OpenglErr.h"

#include <SDL/SDL_image.h>

namespace gware {

Surface::Surface() {
    // mop
}

Surface::~Surface() {
    // nop
}

SDL_Surface *Surface::load(const char *filename) {
    // quick check
    if(filename == NULL || strlen(filename) == 0) {
        LOG(WARN) << "Trying to load surface with NULL or empty filename";
        return NULL;
    }

    SDL_Surface *tmp = NULL, *ret = NULL;

    // try to load the image
    tmp = IMG_Load(filename);
    if(tmp == NULL) {
        LOG(ERROR) << "IMG_Load failed to load image " << filename;
        return NULL;
    } else if(tmp->format->BytesPerPixel == 3) {
        // no alpha channel
        ret = SDL_DisplayFormat(tmp);
    } else if(tmp->format->BytesPerPixel == 4) {
        // has alpha channel
        ret = SDL_DisplayFormatAlpha(tmp);
    } else {
        // umm... bad?
        LOG(ERROR) << "Unknown bytes-per-pixel (" << tmp->format->BytesPerPixel << ") in image " << filename;
        ret = NULL;
    }

    SDL_FreeSurface(tmp);
    return ret;
}

void Surface::blit(SDL_Surface *dest, SDL_Surface *src, Sint16 destX, Sint16 destY) {
    if(dest == NULL || src == NULL) {
        LOG(ERROR) << "Can't blit NULL surfaces";
        return;
    } else {
        SDL_Rect r;
        r.x = destX;
        r.y = destY;

        SDL_BlitSurface(src, NULL, dest, &r);
    }
}

SDL_Surface *Surface::loadGlTexture(GLuint texId, const char *filename) {
    SDL_Surface *tmp = load(filename);

    if(tmp == NULL) {
        return false;
    }

    // check if we have alpha
    int mode;
    if(tmp->format->BytesPerPixel == 4) {
        mode = GL_RGBA;
    } else {
        mode = GL_RGB;
    }

    // clear error state
    OpenglErr::clear();

    // create the texture
    glBindTexture(GL_TEXTURE_2D, texId);
    glTexImage2D(GL_TEXTURE_2D, 0, mode, tmp->w, tmp->h, 0, mode, GL_UNSIGNED_BYTE, tmp->pixels);
    // set texture params
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    // check for errors
    if(OpenglErr::checkErrs()) {
        LOG(ERROR) << "Failed to create OpenGL texture";
        SDL_FreeSurface(tmp);
        return NULL;
    } else {
        return tmp;
    }
}

void Surface::drawQuadTexture(GLuint texId, int destX, int destY, int width, int height) {
    // clear error state
    OpenglErr::clear();

    glBindTexture(GL_TEXTURE_2D, texId);

    glBegin(GL_QUADS);

    // 4 vertices
    glTexCoord2f(0.0, 0.0); glVertex3i(destX, destY, 0);
    glTexCoord2f(1.0, 0.0); glVertex3i(destX+width, destY, 0);
    glTexCoord2f(1.0, 1.0); glVertex3i(destX+width, destY+height, 0);
    glTexCoord2f(0.0, 1.0); glVertex3i(destX, destY+height, 0);

    glEnd();

    // print any errors
    OpenglErr::checkErrs();
}

} /* namespace gware */
