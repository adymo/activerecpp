/*
Copyright (c) 2006 Pluron Inc.

Permission is hereby granted, free of charge, to any person obtaining
a copy of this software and associated documentation files (the
"Software"), to deal in the Software without restriction, including
without limitation the rights to use, copy, modify, merge, publish,
distribute, sublicense, and/or sell copies of the Software, and to
permit persons to whom the Software is furnished to do so, subject to
the following conditions:

The above copyright notice and this permission notice shall be
included in all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE
LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION
OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION
WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
*/
#ifndef RESTFUL_XMLPARSER_H
#define RESTFUL_XMLPARSER_H

#include <string>
#include <xercesc/util/XercesDefs.hpp>

using namespace std;

XERCES_CPP_NAMESPACE_BEGIN
class XercesDOMParser;
XERCES_CPP_NAMESPACE_END

namespace Restful {

/**
@short XML parser specific for recppful library.
@author Alexander Dymo

Provides a high-level frontend to Xerces-C++ xml parser.

Use as sigleton with @ref XmlParser::self() method.
*/
class XmlParser {
public:
    /** @return the XmlParser object to be used.*/
    static XmlParser *self();
    /** @todo adymo: take care about termination.*/
    ~XmlParser();

    XERCES_CPP_NAMESPACE::XercesDOMParser *parser();
    /** @return the textual value of the node.*/
    string getNodeValue(const string &nodeName, const string &data);

private:
    XmlParser();
    static XmlParser *m_instance;
    XERCES_CPP_NAMESPACE::XercesDOMParser *m_parser;

};

}

#endif
