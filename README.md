This is a research of connecting JavaScript and C++ inside Emscripten Web application.

It is similar to [Lua and C++ example][lua-cpp] I did before.


This code:
* uses [MOTOR][motor]'s first stage as the base to render empty window
* is released under [CC0][cc0] license (public domain).
* declares C++ functions that accept vector of strings and return them
* uses JS to call those C++ functions
* declares C++ function to call JS function that in turn calls C++ again

Overall, this was a research to find out if [MUROM][murom] can use JavaScript
to script games. The answer is YES.

[lua-cpp]: http://github.com/kornerr/cpp-callback-script
[motor]: http://bitbucket.com/ogstudio/motor
[murom]: http://opengamestudio.org/murom
[cc0]: https://creativecommons.org/share-your-work/public-domain/cc0/
