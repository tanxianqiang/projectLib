#include "pugixml.hpp"

#include <new>
#include <cstdio>
#include <cstring>

char * p = nullptr;
// tag::decl[]
void* custom_allocate(size_t size)
{
    p = new (std::nothrow) char[size];
    memset (p, 0, size);
    return p ;
}

void custom_deallocate(void* ptr)
{
    delete[] static_cast<char*>(ptr);
}
// end::decl[]


/* tanxianqiang 创建用户自己定义的内存  通过gdb调试可以知道申请两次并释放两次  怎么个申请和释放的 ？*/
int main()
{
// tag::call[]
    pugi::set_memory_management_functions(custom_allocate, custom_deallocate);
// end::call[]
    pugi::xml_document doc;
    doc.load_string("<node/>");

    printf ("%s  \n", p );
}

// vim:et
