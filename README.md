luasoldout
==========

A simple lua binding to
[libsoldout](http://fossil.instinctive.eu/libsoldout/), a lightweight C
library that can parse
[Markdown](http://daringfireball.net/projects/markdown/).

Usage
-----

    local soldout = require("soldout")
    local markdown_string = [[
    This is an
    example [Markdown](http://daringfireball.net/projects/markdown/)
    paragraph.
    ]]
    local html_string = soldout.markdown(markdown_string [, output, extension]);

output can be one of "html" (default) or "xhtml".  
extension can be one of "markdown" (default), "discount" or "natext".
