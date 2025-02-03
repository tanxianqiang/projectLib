#include "pugixml.hpp"

#include <iostream>



/* 有个很好的用法 将流转换为字符串 */
int main()
{
    // get a test document
    pugi::xml_document doc;
    doc.load_string("<foo bar='baz'><call>hey</call></foo>");

    // tag::code[]
    // save document to standard output
    std::cout << "Document:\n";
    doc.save(std::cout);
    // end::code[]
}

// vim:et
