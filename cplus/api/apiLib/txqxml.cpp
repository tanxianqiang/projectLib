#include "txqxml.h"
#include "txqcom.h"
#include "pugixml.hpp"
#include <iostream>

void txq_xml() {
    pugi::xml_document doc;
    pugi::xml_parse_result result = doc.load_string("<node attr='value'><child>text<child></node>");
    if (result) {
        std::cout << "XML [" <<  "] parsed without errors, attr value: [" << doc.child("node").attribute("attr").value() << "]\n\n";
    }
    else {
        std::cout << "XML [" << "] parsed with errors, attr value: [" << doc.child("node").attribute("attr").value() << "]\n";
    }

}

#if 1
int main(int argc, char* argv[]) {
    START_APP(argv[0]);
    txq_xml();
    END_APP(argv[0]);
}
#endif
