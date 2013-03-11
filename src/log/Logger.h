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
 * Logger.h
 * Created on: Mar 4, 2013
 */

#ifndef GWARE_LOGGER_H_
#define GWARE_LOGGER_H_

#include <cstdio>
#include <ctime>
#include <sstream>

// logging defines
#define LVL2INT(lvl) (int(lvl))
#define FMT_STR_MAX_LEN 1024

// could also add __FUNCTION__ in here
// TODO: log thread ID
#define _LOG(level) \
    gware::Logger(level).get() << " " __FILE__  ":"  << __LINE__ << ": "

// Simple logging macro
#define LOG(level) \
    if(gware::Logger::getLogLevel() >= LVL2INT(gware::Logger::LOG_##level)) _LOG(LVL2INT(gware::Logger::LOG_##level))

// Simple format logging macro
#define LOGF(level, fmt, ...) \
    if(gware::Logger::getLogLevel() >= LVL2INT(gware::Logger::LOG_##level)) {\
        char _logf_formatted[FMT_STR_MAX_LEN] = {'\0'}; \
        snprintf(_logf_formatted, FMT_STR_MAX_LEN - 1, fmt, __VA_ARGS__); \
        _LOG(LVL2INT(gware::Logger::LOG_##level)) <<  _logf_formatted;\
    }

namespace gware {

class Logger {
public:
    enum Level {
        LOG_EMERG = 0,
        LOG_CRIT = 1,
        LOG_ERROR = 2,
        LOG_WARN = 3,
        LOG_INFO = 4,
        LOG_DEBUG = 5,
        LOG_DUMP = 6
    };

    /** Constructor */
    Logger(int level);

    /**
     * The destructor actually does the real logging
     */
    ~Logger();

    /**
     * Get the output string stream associated with this logger
     */
    std::ostringstream &get();

    /**
     * Get the global log level (as an int)
     */
    static int getLogLevel();

    /**
     * Set the global log level
     */
    static void setLogLevel(enum Level lvl);
private:
    std::ostringstream mStream;
    int mLevel;
    timespec mTime;

    static int gLogLevel;               ///< the global log level
    static const char *gLvlStrings[];   ///< level strings

    // TODO need static mutexes
};

} /* namespace gware */
#endif /* GWARE_LOGGER_H_ */
