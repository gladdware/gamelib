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
 * OpenglErr.cpp
 * Created on: Mar 10, 2013
 */

#include "OpenglErr.h"
#include "log/Logger.h"

#include <GL/glu.h>

namespace gware {

OpenglErr::OpenglErr() {
    // nop
}

OpenglErr::~OpenglErr() {
    // nop
}

void OpenglErr::clear() {
    while(glGetError() != GL_NO_ERROR) {}
}

bool OpenglErr::checkErrs() {
    bool isErr = false;

    GLenum tst = glGetError();
    while(tst != GL_NO_ERROR) {
        // log the error
        LOGF(ERROR, "GL: %s", gluErrorString(tst));
        // set result
        isErr = true;
        // get next flag
        tst = glGetError();
    }

    return isErr;
}

} /* namespace gware */
