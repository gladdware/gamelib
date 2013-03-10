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
 * Logger.cpp
 * Created on: Mar 4, 2013
 */

#include "Logger.h"
#include <cmath>
#include <iomanip>
#include <iostream>
#include <string>

#define NUM_LEVELS (LVL2INT(gware::Logger::LOG_DUMP) + 1)
#define DEF_LEVEL (LVL2INT(gware::Logger::LOG_ERROR))

namespace gware {

int Logger::gLogLevel = DEF_LEVEL;

const char *Logger::gLvlStrings[] = {
        "EMERGENCY",
        "CRITICAL",
        "ERROR",
        "WARNING",
        "INFO",
        "DEBUG",
        "DUMP"
};

Logger::Logger(int level) {
    if(level < 0 || level >= NUM_LEVELS) {
        // bad level number; set to default
        mLevel = DEF_LEVEL;
    } else {
        mLevel = level;
    }

    // get timestamp (CPU time)
    clock_gettime(CLOCK_PROCESS_CPUTIME_ID, &mTime);
}

Logger::~Logger() {
    // actual logging happens here
    // TODO: make threadsafe?
    std::cout << mStream.str() << std::endl;
}

std::ostringstream &Logger::get() {
    // setup timestamp
    unsigned seconds = mTime.tv_sec;
//    long uSeconds = long(roundl((long double)mTime.tv_nsec / 1000.0));
    long mSeconds = long(roundl((long double)mTime.tv_nsec / 1000000.0));
    // format timestamp
    std::stringstream ss;
    ss << std::setw(5) << std::setfill(' ') << seconds << '.'
            << std::setw(3) << std::setfill('0') << mSeconds;
    // write timestamp
    mStream << "[" << ss.str() << "]";
    // write level string
    mStream << "[" << gLvlStrings[mLevel] << "]";
    return mStream;
}

int Logger::getLogLevel() {
    return gLogLevel;
}

void Logger::setLogLevel(enum Level lvl) {
    gLogLevel = LVL2INT(lvl);
}

//void Logger::logf(enum Level lvl, const char *format, ...) {
//    va_list args;
//    va_start(args, format);
//    char formatted[FMT_STR_MAX_LEN] = { '\0' };
//
//    vsnprintf(formatted, FMT_STR_MAX_LEN - 1, format, args);
//
//    _LOG(LVL2INT(lvl)) << formatted;
//
//    va_end(args);
//}

} /* namespace gware */
