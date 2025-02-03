#include "pugixml.hpp"

#include <iostream>




/* 迭代的范围循环  迭代器 */
int main()
{
    pugi::xml_document doc;
    if (!doc.load_file("xgconsole.xml")) return -1;

    pugi::xml_node tools = doc.child("Profile").child("Tools");

    // tag::code[]
    for (pugi::xml_node tool: tools.children())
    {
        std::cout << "Tool:";

        for (pugi::xml_attribute attr: tool.attributes())
        {
            std::cout << " " << attr.name() << "=" << attr.value();
        }

        for (pugi::xml_node child: tool.children())
        {
            std::cout << ", child " << child.name();
        }

        std::cout << std::endl;
    }
    // end::code[]
}

// vim:et
