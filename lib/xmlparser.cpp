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
#include "xmlparser.h"

#include <cstring>

#include <xercesc/util/PlatformUtils.hpp>
#include <xercesc/util/XMLString.hpp>

#include <xercesc/framework/MemBufInputSource.hpp>

#include <xercesc/dom/DOM.hpp>
#include <xercesc/dom/DOMImplementation.hpp>
#include <xercesc/dom/DOMImplementationLS.hpp>
#include <xercesc/dom/DOMWriter.hpp>

#include <xercesc/parsers/XercesDOMParser.hpp>

XERCES_CPP_NAMESPACE_USE

#define X(str) XMLString::transcode(str)

///BEGIN debug
#include <iostream>
using namespace std;
#include "DOMTreeErrorReporter.hpp"
///END debug

namespace Restful {

XmlParser *XmlParser::m_instance = 0;

XmlParser *XmlParser::self()
{
    if (!m_instance)
        m_instance = new XmlParser();
    return m_instance;
}

XmlParser::XmlParser()
{
    XMLPlatformUtils::Initialize();
    m_parser = new XercesDOMParser;
    m_parser->setValidationScheme(XercesDOMParser::Val_Auto);
    m_parser->setDoNamespaces(false);
    m_parser->setDoSchema(false);
    m_parser->setCreateEntityReferenceNodes(false);
    m_parser->setDisableDefaultEntityResolution(false);

    ///BEGIN debug
    DOMTreeErrorReporter *errReporter = new DOMTreeErrorReporter();
    m_parser->setErrorHandler(errReporter);
    ///END debug
}

XmlParser::~XmlParser()
{
    XMLPlatformUtils::Terminate();
}

string XmlParser::getNodeValue(const string &nodeName, const string &data)
{
    try {
        m_parser->reset();
        const char *c_data = data.c_str();
        MemBufInputSource source((const XMLByte*)c_data, strlen(c_data), "nodebuffer", false);
        m_parser->parse(source);
        if (m_parser->getErrorCount() > 0)
            return "";
        DOMDocument *doc = m_parser->getDocument();
        const char *n = nodeName.c_str();
        DOMNodeList *list = doc->getElementsByTagName(X(nodeName.c_str()));
        if (list->getLength() == 1)
            return X(list->item(0)->getFirstChild()->getNodeValue());
        return "";
    } catch (...) {
        return "";
    }
}

}
