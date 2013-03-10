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
 * FpsCounter.h
 * Created on: Mar 10, 2013
 */

#ifndef GWARE_FPSCOUNTER_H_
#define GWARE_FPSCOUNTER_H_

#include <list>
#include <SDL/SDL.h>

#define DEF_WINDOW_SIZE 15

namespace gware {

/**
 * Keeps track of a running average of FPS, based on elapsed time per frame.
 *
 * This class tries to save computation time by only calculating the average FPS
 * only once per window size. I.e., if the window size is 10, a new average will
 * only be calculated once per 10 calls to addFrameTime.
 */
class FpsCounter {
public:
    /**
     * Constructor
     *
     * @param avgWindowSize The size of the window over which to average FPS
     *   (optional)
     */
    FpsCounter(unsigned avgWindowSize = DEF_WINDOW_SIZE);
    virtual ~FpsCounter();

    /**
     * Add an elapsed frame time to be considered in the window average
     */
    void addFrameTime(Uint32 frameTime);

    /**
     * Get the average FPS over the accumulated window
     */
    float getAverageFps();

private:
    unsigned mWindowSize;
    std::list<Uint32> mFrameTimes;
    float mLastFps;
};

} /* namespace gware */
#endif /* GWARE_FPSCOUNTER_H_ */
