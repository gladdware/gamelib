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
 * EventHandlerIntf.h
 * Created on: Mar 6, 2013
 */

#ifndef GWARE_EVENTHANDLERINTF_H_
#define GWARE_EVENTHANDLERINTF_H_

#include <SDL/SDL.h>

namespace gware {

/**
 * Pure abstract class interface for an event handler
 */
class EventHandlerIntf {
public:
    virtual ~EventHandlerIntf() {}

    virtual void onEvent(SDL_Event *e) = 0;

protected:
    EventHandlerIntf() {}
};

} /* namespace gware */

#endif /* GWARE_EVENTHANDLERINTF_H_ */
