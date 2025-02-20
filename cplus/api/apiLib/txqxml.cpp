#include "txqxml.h"
#include "txqcom.h"
#include "pugixml.hpp"
#include <iostream>






void txq_xml() {
    pugi::xml_document doc;

    pugi::xml_document doc1;

    /* 备份文件 */
    if (!doc.load_file("save_file_output.xml"))  {
        std::cout << "load  xml fail" << std::endl;
    }


    if (!doc1.load_file("save_file_output.xml"))  {
        std::cout << "load  xml fail" << std::endl;
    }

    pugi::xml_parse_result result = doc.load_string("<node attr='value'><child>text<child></node>");
    if (result) {
        std::cout << "XML [" <<  "] parsed without errors, attr value: [" << doc.child("node").attribute("attr").value() << "]\n\n";
    }
    else {
        std::cout << "XML [" << "] parsed with errors, attr value: [" << doc.child("node").attribute("attr").value() << "]\n";
    }

    pugi::xml_node node = doc1.append_child("node");

    // add description node with text child
    pugi::xml_node descr = node.append_child("description");
    descr.append_child(pugi::node_pcdata).set_value("Simple node");

    // add param node before the description
    pugi::xml_node param = node.insert_child_before("param", descr);

    // add attributes to param node
    param.append_attribute("name") = "version";
    param.append_attribute("value") = 1.1;
    param.insert_attribute_after("type", param.attribute("name")) = "float";




    if (!doc.save_file("save_file_output.xml")) {
        std::cout << "save file fail " << std::endl;
    }
}

#if 1
int main(int argc, char* argv[]) {
    START_APP(argv[0]);
    txq_xml();
    END_APP(argv[0]);
}
#endif
