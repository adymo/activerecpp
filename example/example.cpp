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
#include <iostream>
#include <resource.h>

#include <curl/curl.h>

using namespace Restful;

/**The class that corresponds to the books resource in the restful application.*/
class Book: public Resource {
public:
    /**Mandatory argumentless constructor.*/
    Book() :Resource() {}

    //we need to override all abstract methods from Resource
    virtual string resourceName() const { return "Book"; }
    virtual string url() const { return "http://localhost:3000/books"; }
    virtual string username() const { return "adymo"; }
    virtual string password() const { return "pass"; }
};

int main(int argc, char **argv)
{
    //find the book with id=1
    Book *book = Book::find<Book>(1);
    //xml representation of the book is printed here
    cout << book->dump() << endl;
    //title of the book is printed here
    cout << "Title: " << book->attribute("title") << endl;

    //change the title of the book
    book->setAttribute("title", "Rails Agile");

    book->reload();
    cout << "New title: " << book->attribute("title") << endl;

    //change the book title back
    book->setAttribute("title", "PickAxe");

    delete book;
    return 0;
}

/*
# Corresponding Ruby code using ActiveResource would look like:
Book = ActiveResource::Struct.new do |p|
    p.uri = "http://localhost:3000/books"
    p.credentials :name => "adymo", :password => "secret"
end

#GET http://localhost:3000/books/1
#<book>
#    <contents>PickAxe</contents>
#    <created-at type="datetime"></created-at>
#    <id type="integer">1</id>
#</book>
book = Book.find(1)
puts book.title
*/
