-- A solution contains projects, and defines the available configurations
solution "moonstone"
  configurations { "Debug", "Release" }

  project "main"
    kind "ConsoleApp"
    language "C++"
    files {"*.cpp", "utils/*.cpp"}
    includedirs {".", "/usr/include/lua5.2/"}

    links{'lua5.2'}
    buildoptions {"--std=c++11" } ---Wall -Wextra
    configuration "Debug"
      defines { "DEBUG" }
      flags { "Symbols" }

    configuration "Release"
      defines { "NDEBUG" }
      flags { "Optimize" }
