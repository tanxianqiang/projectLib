if (apiLibDoc)
macro(GEN_DOC INPUT_FILES PROJECT_VERSION PROJECT_DESCRIPTION DOC_LOGO)
    find_package(Doxygen)
    if(DOXYGEN_FOUND)
        find_program(DOT_PATH dot PATH_SUFFIXES graphviz2.38/bin graphviz/bin)
        if(DOT_PATH)
            set(HAVE_DOT "YES")
        else()
            set(HAVE_DOT "NO")
            message(AUTHOR_WARNING "Doxygen: to generate UML diagrams please install graphviz")
        endif()

        # target doc
        add_custom_target(doc
                COMMAND ${DOXYGEN_EXECUTABLE} ${CMAKE_BINARY_DIR}/Doxyfile
                WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR})

        # generate list with spaces as separators
        string(REPLACE ";" " " DOXY_INPUT "${INPUT_FILES}")

        # make other arguments into variables
        set(PROJECT_VERSION ${PROJECT_VERSION})
        set(PROJECT_DESCRIPTION ${PROJECT_DESCRIPTION})
        set(DOC_LOGO ${DOC_LOGO})

        configure_file(Doxyfile.in Doxyfile)
    endif()
endmacro()

file(GLOB SOURCE_HEADERS *.h)

set(LIBAPI_VERSION 0.01)
set(LIBAPI_DESCRIPTION "API lib.")

set(doxy_files ${CMAKE_CURRENT_SOURCE_DIR})
set(DOXYGEN_OUTPUT ${CMAKE_CURRENT_SOURCE_DIR}/doc/apiLibDoc)

gen_doc("${doxy_files}" ${LIBAPI_VERSION} ${LIBAPI_DESCRIPTION} "")

endif()

