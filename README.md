"htmlCplusplus" is a C++ library used to create fast html pages by simply writting your own html content via C++!
It is extendable so that the user can use its own implementation on various parts, for example its own Beautify implementation.
It can be used either on the runtime for the creation of html pages (such as for CGIs, html content) or by creating offline 
html pages with complex contents.

The library by default supports wide characters and does not restrict to a specific encoding/locale. The output can be set
either to a "wcout" (by default) or to an wide output stream!

By default "Visual Studio Code" IDE is added into the repository as it was the main IDE during the development. Some default
settings have been defined for debugging.

The repository also include different examples in order to demonstrate the usage of the library, that can be found into the "examples"
folder.


Compiling the library:
----------------------

$ make HtmlClean
$ make Html



Compiling the Examples:
-----------------------
$ cd examples
$ make examples

Currently the library supports the basics for the creation of a Html page with the following features included:

- javascript (as link or as inline javascript body)
- css (as links or as inline css body)
- html head links
- html head metas
- all kind of body tags even custom (since the library doesn't restrict to the basic html tags)
- multi encoding
- multi output streams
- various custom http headers, even custom http headers




The future of this project will mostly focus on:

- Improvements on design
- Performance & Security fixes
- New Features



Enjoy :)
