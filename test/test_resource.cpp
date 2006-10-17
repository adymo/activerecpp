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
#include <boost/test/unit_test.hpp>
#include <boost/lexical_cast.hpp>

#include <resource.h>

using boost::unit_test::test_suite;
using boost::unit_test::test_case;
using namespace Restful;

class Book: public Resource {
public:
    Book() :Resource() {}

    virtual string resourceName() const { return "Book"; }
    virtual string url() const { return "http://localhost:3000/books"; }
    virtual string username() const { return "adymo"; }
    virtual string password() const { return "pass"; }
};

struct resource_test {
    resource_test()
    {
        book = Book::find<Book>(1);
    }

    void test_get_attribute()
    {
        BOOST_CHECK_EQUAL(book->attribute("title"), "PickAxe");
    }

    Book *book;
};

struct resource_test_suite: public test_suite {
    resource_test_suite(): test_suite("resource_test_suite")
    {
        // add member function test cases to a test suite
        boost::shared_ptr<resource_test> instance(new resource_test());

        test_case *get_attribute_test_case =
            BOOST_CLASS_TEST_CASE(&resource_test::test_get_attribute, instance);

        add(get_attribute_test_case, 1);
    }
};

test_suite* init_unit_test_suite(int argc, char **argv)
{
    test_suite* test = BOOST_TEST_SUITE("Resource Test");
    test->add(new resource_test_suite());
    return test;
}
