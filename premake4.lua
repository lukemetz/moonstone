-- A solution contains projects, and defines the available configurations
solution "moonstone"
  configurations { "Debug", "Release" }

  project "main"
    kind "ConsoleApp"
    language "C++"
    includedirs {"src/",
      "src/DeferredShading/include",
      "/usr/local/include/luajit-2.0/",
      "/usr/local/include/OGRE",
      "/usr/include/OIS/",
      "/usr/include/bullet"}
    files {"**.cpp", "**.hpp", "**.h", "**.a"}
    excludes {"tests/**"}
    links{'luajit-5.1', 'OgreMain', 'OIS', 
          'BulletCollision', 'BulletDynamics', 'LinearMath', 'BtOgre'}
    libdirs {"/usr/local/lib", "/usr/lib/x86_64-linux-gnu",
            "src/externals/btogre"}
    buildoptions {"--std=c++11 -g"}
    configuration "Debug"
      defines { "DEBUG" }
      flags { "Symbols" }

    configuration "Release"
      defines { "NDEBUG" }
      flags { "Optimize" }
