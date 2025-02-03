#include "pugixml.hpp"

#include <iostream>



/* 文件加载 节点子节点名字和属性值
   可以设计为子节点为index  判断是否有这个节点， 判断是否有这个属性
*/
int main()
{
// tag::code[]
    pugi::xml_document doc;

    pugi::xml_parse_result result = doc.load_file("tree.xml");
    std::cout << doc.child("mesh").attribute("name") << std::endl;
    std::cout << doc.child("mesh").attribute("mm") << std::endl;
     std::cout << doc.child("mesh") << std::endl;
      std::cout << doc.child("mm") << std::endl;
          std::cout << doc.child("tt").attribute("mm") << std::endl;
    std::cout << "Load result: " << result.description() << ", mesh name: " << doc.child("mesh").attribute("mm").value() << std::endl;
// end::code[]
}

// vim:et
