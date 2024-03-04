add_executable (code "12. 模板的全特化与偏特化.cpp")

if (CMAKE_VERSION VERSION_GREATER 3.12)
  set_property(TARGET code PROPERTY CXX_STANDARD 20)
endif()