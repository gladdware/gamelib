# Gladdware-Gamelib

_C++ wrapper library for making games with SDL and OpenGL_

I wanted to learn how to use SDL and OpenGL to make a game, so I started by
building this little library that wraps common SDL and OpenGL application tasks
into a collection of re-usable code. This has probably been done before, and
will certainly be done again, but I like to learn by doing :)

## Install

**Note**: I haven't fully tested the 'install' yet, so you probably want to use
a custom prefix during configure for now.

Use autotools to configure, build, and install:

<pre>
$ autoreconf -i 
$ ./configure 
$ make 
# make install 
</pre>

## License

Copyright 2013 Alex Gladd

![LGPL3 Logo](http://www.gnu.org/graphics/lgplv3-147x51.png)

Gladdware-gamelib is free software: you can redistribute it and/or modify
it under the terms of the GNU Lesser General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

Gladdware-gamelib is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU Lesser General Public License for more details.

You should have received a copy of the GNU Lesser General Public License
along with Gladdware-gamelib.  If not, see <http://www.gnu.org/licenses/>.

## Helpful Links

I learned a lot about SDL, OpenGL, etc. through various tutorials:

* http://www.libsdl.org/
* http://www.opengl.org/
* http://www.sdltutorials.com/

