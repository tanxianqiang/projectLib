#include "pugixml.hpp"

#include <iostream>





/* select_nodes 要进行try  catch
  找带有text 文本的节点
  /Profile/Tools/Tool[text()]  有一个xpath 测试工具

  /Profile//Tool[@AllowRemote="true"]
  /Profile//*[@AllowRemote="false"]
/Profile//*[@AllowRemote]
/Profile/Tools/child::* 子节点

/Profile/Tools/Tool/attribute::Filename     filename属性值
/Profile/Tools/child::Tool
/Profile/Tools/Tool/attribute::*   属性值
/Profile/Tools/Tool/child::node()
/Profile/Tools/Tool/Description/ancestor::Tool   先辈节点
/Profile/Tools/Tool[child::Description]
   */
int main()
{
    pugi::xml_document doc;
    if (!doc.load_file("xgconsole.xml")) return -1;

// tag::code[]
    // Exception is thrown for incorrect query syntax
    try
    {
        doc.select_nodes("//text()");
    }
    catch (const pugi::xpath_exception& e)
    {
        std::cout << "Select failed: " << e.what() << std::endl;
    }

    // Exception is thrown for incorrect query semantics
    try
    {
        doc.select_nodes("(123)/next");
    }
    catch (const pugi::xpath_exception& e)
    {
        std::cout << "Select failed: " << e.what() << std::endl;
    }

    // Exception is thrown for query with incorrect return type
    try
    {
        doc.select_nodes("123");
    }
    catch (const pugi::xpath_exception& e)
    {
        std::cout << "Select failed: " << e.what() << std::endl;
    }
// end::code[]
}

// vim:et
