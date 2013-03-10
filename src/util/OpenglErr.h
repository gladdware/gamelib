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
 * OpenglErr.h
 * Created on: Mar 10, 2013
 */

#ifndef GWARE_OPENGLERR_H_
#define GWARE_OPENGLERR_H_

#include <GL/gl.h>

namespace gware {

/**
 * Simple class for handling OpenGL errors
 */
class OpenglErr {
public:
    virtual ~OpenglErr();

    /**
     * Clear all OpenGL error flags, ignoring any that are set
     */
    static void clear();

    /**
     * Checks for any OpenGL error flags. For each flag that is set, a message
     * is logged and the flag is cleared.
     *
     * @return true if any error flags are set
     */
    static bool checkErrs();

protected:
    // should never be instantiated
    OpenglErr();
};

} /* namespace gware */
#endif /* GWARE_OPENGLERR_H_ */
