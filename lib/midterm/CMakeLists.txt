set(HEADER_FILES
        inc/inventory_node.h inc/stack.h inc/inventory.h inc/stack_node.h inc/linked_list_m.h)

set(SOURCE_FILES
        src/inventory.cpp src/stack.cpp src/inventory_node.cpp src/linked_list.cpp)
include_directories(inc)
add_library(midterm_lib STATIC ${SOURCE_FILES} ${HEADER_FILES})
