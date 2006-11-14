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
#ifndef RESTFUL_RESOURCE_H
#define RESTFUL_RESOURCE_H

#include <string>

using namespace std;

namespace Restful {

/**
@short Base class for all resources.
@author Alexander Dymo

Initiates HTTP connections, makes GET's, POST's, UPDATE's and DELETE's
to the server and also handles all type conversions.

Acts as ActiveResource::Struct from activeresource ruby library.

Resource without the id will return nothing in response to all data requests.
Use @ref Resource::find to fetch Resource objects with id from the database
or use @ref Resource::save to assign the id to the newly created object.
*/
class Resource {
public:

    /** @short Generic resource exception with a message.*/
    class ResourceException {
    public:
        ResourceException(const string &message): m_message(message) {}
        /**Returns a message string.*/
        const string &message() const { return m_message; }
    private:
        string m_message;
    };
    /** @short "Resource is invalid" exception.*/
    class ResouceInvalidException: public ResourceException {
    public:
        ResouceInvalidException(const string &message): ResourceException(message) {}
    };
    /** @short "Resource can not be updated" exception.*/
    class ResourceUpdateException: public ResourceException {
    public:
        ResourceUpdateException(const string &message): ResourceException(message) {}
    };

    /**There're two policies for error reporting:*/
    enum ErrorPolicy {
        Silent, /**<Does not report errors, but gives guarantee that the resource is always in a valid state*/
        Report  /**<Reports errors by raising exceptions. Also provides valid state guarantee.*/
    };

    /**Constructs the resource. Please note that all descendants should provide
    the constructor without arguments because @ref Resource::find uses them to
    create new resource objects.*/
    Resource(ErrorPolicy errorPolicy = Resource::Silent);
    virtual ~Resource();

    /**Finds the resource by id and returns it. This function assumes that
    @p ResourceType is the subtype of Resource and automatically performs the type cast.*/
    template <typename ResourceType>
    static ResourceType *find(int id)
    {
        ResourceType *resource = new ResourceType();
        resource->setId(id);
        return resource;
    }

    /**@return the string value of the attribute @p name.*/
    string attribute(const string &name) const;
    /**Sets the string @p value of the attribute @p name.*/
    void setAttribute(const string &name, const string &value);

    /**@return the current error policy.*/
    ErrorPolicy errorPolicy() const { return m_errorPolicy; }
    /**Sets the current error policy.*/
    void setErrorPolicy(ErrorPolicy policy) { m_errorPolicy = policy; }

    /**Reimplement to return the resource name.*/
    virtual string resourceName() const = 0;
    /**Reimplement to return the url of the resource.*/
    virtual string url() const = 0;
    /**Reimplement to return username used for authentication.*/
    virtual string username() const = 0;
    /**Reimplement to return password used for authentication.*/
    virtual string password() const = 0;

    /**Dumps the xml contents of the object. */
    string dump() const;

    /**Reloads the object. Does nothing if the object is invalid.*/
    void reload();

private:
    /**Sets the id. This allows any queries to the resource that otherwise
    would return empty data because of invalid id.*/
    void setId(int id);
    int id() const;
    /** @return true if the resource is invalid, i.e. has incorrect id assigned to it.*/
    bool invalid() const;
    /** @return resource url (with id and .xml extension added).*/
    string resourceUrl() const;

    ErrorPolicy m_errorPolicy;
    int m_id;
    string m_data;
};

}

#endif
