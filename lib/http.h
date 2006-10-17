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
#ifndef RESTFUL_HTTP_H
#define RESTFUL_HTTP_H

#include <string>
using namespace std;

namespace Restful {

/**
@short Performs all communication through HTTP
@author Alexander Dymo

This is a wrapper around curl library that actually performs the communication.
*/
class Http {
public:

    //exception types for GET, PUT, POST and DELETE HTTP requests
    class GetException {};
    class PutException {};
    class PostException {};
    class DeleteException {};

    /**Executes HTTP GET to the @p url and returns the textual
    representation of the result.*/
    static string get(const string &url)
        throw(GetException, PutException, PostException, DeleteException);

    /**Executes HTTP PUT to the @p url with given @p data.*/
    static void put(const string &url, const string &data);

private:
    //CURL specific functions
    /**Captures the data from the remote url to the @p data variable.*/
    static size_t writeData(void *buffer, size_t size, size_t nmemb, string *data);
    static size_t readData(void *buffer, size_t size, size_t nmemb, string *data);

};

}

#endif
