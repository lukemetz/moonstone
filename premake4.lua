-- A solution contains projects, and defines the available configurations
solution "moonstone"
  configurations { "Debug", "Release" }

  project "moonstone"
    kind "ConsoleApp"
    language "C++"
    includedirs {"src/",
      "src/DeferredShading/include",
      "/usr/include/luajit-2.0/",
      "/usr/include/OGRE",
      "/usr/include/OIS/",
      "/usr/include/bullet"}
    files {"**.cpp", "**.hpp", "**.h", "**.a"}
    excludes {"tests/**"}
    links{'luajit-5.1', 'OgreMain', 'OIS', 
          'BulletCollision', 'BulletDynamics',
          'LinearMath', 'BtOgre', "boost_system"}
    libdirs {"/usr/local/lib", "/usr/lib/x86_64-linux-gnu",
            "src/externals/btogre"}
    buildoptions {"--std=c++11 -g"}
    configuration "Debug"
      defines { "DEBUG" }
      flags { "Symbols" }

    configuration "Release"
      defines { "NDEBUG" }
      flags { "Optimize" }
