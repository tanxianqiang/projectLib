#include "pugixml.hpp"

#include <iostream>





/* 格式输出
  子节点输出， 还是node_to_string()
 */
int main()
{
    // tag::code[]
    // get a test document
    pugi::xml_document doc;
    doc.load_string("<foo bar='baz'><call>hey</call></foo>");

    // print document to standard output (prints <?xml version="1.0"?><foo bar="baz"><call>hey</call></foo>)
    doc.save(std::cout, "", pugi::format_raw);
    std::cout << std::endl;

    // print document to standard output as a regular node (prints <foo bar="baz"><call>hey</call></foo>)
    doc.print(std::cout, "", pugi::format_raw);
    std::cout << std::endl;

    // print a subtree to standard output (prints <call>hey</call>)
    doc.child("foo").child("call").print(std::cout, "", pugi::format_raw);
    std::cout << std::endl;
    // end::code[]
}

// vim:et
