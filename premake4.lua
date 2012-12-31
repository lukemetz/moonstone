-- A solution contains projects, and defines the available configurations
solution "moonstone"
  configurations { "Debug", "Release" }

  project "main"
    kind "ConsoleApp"
    language "C++"
    includedirs {"src/",
      "/usr/include/lua5.2/",
      "/usr/local/include/OGRE",
      "/usr/include/OIS/"}
    
    files {"**.cpp", "**.hpp"}
    excludes {"tests/**"}
    links{'lua5.2', 'OgreMain', 'OIS'}
    libdirs {"/usr/local/lib", "/usr/lib/x86_64-linux-gnu"}
    buildoptions {"--std=c++11 -g"}
    configuration "Debug"
      defines { "DEBUG" }
      flags { "Symbols" }

    configuration "Release"
      defines { "NDEBUG" }
      flags { "Optimize" }
