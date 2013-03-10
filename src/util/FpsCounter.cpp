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
 * FpsCounter.cpp
 * Created on: Mar 10, 2013
 */

#include "FpsCounter.h"

#include "log/Logger.h"
#include <numeric>

namespace gware {

FpsCounter::FpsCounter(unsigned avgWindowSize)
    : mWindowSize(avgWindowSize),
      mLastFps(0.0) {
    // make sure window size is sane
    if(mWindowSize < 1) {
        LOG(ERROR) << "Window size must be >= 1; setting to default: " << unsigned(DEF_WINDOW_SIZE);
        mWindowSize = DEF_WINDOW_SIZE;
    }
}

FpsCounter::~FpsCounter() {
    // nop
}

void FpsCounter::addFrameTime(Uint32 frameTime) {
    mFrameTimes.push_back(frameTime);

    // see if we need to calc new fps
    if(mFrameTimes.size() >= mWindowSize) {
        // TODO lock before new fps
        Uint32 sum = std::accumulate(mFrameTimes.begin(), mFrameTimes.end(), 0);
        mLastFps = float(sum) / float(mFrameTimes.size());

        mFrameTimes.clear();
    }
}

float FpsCounter::getAverageFps() {
    // TODO use a scope lock here
    return mLastFps;
}

} /* namespace gware */
