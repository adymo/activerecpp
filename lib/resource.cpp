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
#include "resource.h"

#include <iostream>
#include <boost/format.hpp>

#include "restful_locale.h"
#include "http.h"
#include "xmlparser.h"

#define NO_DATA "<no data>"

namespace Restful {

Resource::Resource(ErrorPolicy errorPolicy)
    :m_errorPolicy(errorPolicy), m_id(-1), m_data(NO_DATA)
{
}

Resource::~Resource()
{
}

void Resource::setId(int id)
{
    m_id = id;
    try {
        m_data = Http::get(resourceUrl());
    } catch (Http::GetException) {
        m_data = NO_DATA;
        if (m_errorPolicy == Report)
            throw ResouceInvalidException(_("Can not fetch resource from the service."));
    }
}

int Resource::id() const
{
    return m_id;
}

void Resource::reload()
{
    if (!invalid())
        setId(m_id);
}

bool Resource::invalid() const
{
    return m_id == -1;
}

string Resource::dump() const
{
    return m_data;
}

string Resource::resourceUrl() const
{
    return str(boost::format("%1%/%2%.xml") % url() % id());
}

string Resource::attribute(const string &name) const
{
    if (invalid())
        return NO_DATA;

    return XmlParser::self()->getNodeValue(name, m_data);
}

void Resource::setAttribute(const string &name, const string &value)
{
    string s = str(boost::format("<%1%><%2%>%3%</%2%></%1%>") % resourceName() % name % value);
    try {
        Http::put(resourceUrl(), s);
        reload();
    } catch (Http::PutException) {
        //do nothing here, the object representation did not change
        //just report error if necessary
        if (m_errorPolicy == Report)
            throw ResourceUpdateException(_("Service did not allow to update resource."));
    }
}

}
