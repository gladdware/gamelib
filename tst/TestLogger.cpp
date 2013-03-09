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
 * TestLogger.cpp
 * Created on: Mar 4, 2013
 */

#include <log/Logger.h>

int main(int argc, char *argv[]) {

    gware::Logger::setLogLevel(gware::Logger::LOG_DUMP);

    LOG(CRIT) << "Test logger";
    LOG(ERROR) << "Foobar";
    LOG(DUMP) << "Dumping test";

    LOGF(ERROR, "Testing #%u, %s", 42, "foobar");

    return 0;
}
