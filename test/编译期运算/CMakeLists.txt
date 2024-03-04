add_executable (compile "5. 编译期求最大公约数.cpp")

if (CMAKE_VERSION VERSION_GREATER 3.12)
  set_property(TARGET compile PROPERTY CXX_STANDARD 20)
endif()