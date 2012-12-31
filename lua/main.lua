systems = { "lua_system","Ogre_Render_System", "OIS_Input_System"}

function create_camera()
  return {
    Camera = { }
  }
end

function create_ogre()
  return {
    Mesh = {filename = "ogrehead.mesh"},
    Transform = { pos = Vec3f(0,0,0), rot = Vec3f(0,0,0), scale = Vec3f(1,1,1) },
    lua_component = {},
    Input = {}
    }
end

function create_ogre2()
  return {
    Mesh = {filename = "ogrehead.mesh"},
    Transform = { pos = Vec3f(10,0,0), rot = Vec3f(0,0,0), scale = Vec3f(1,2,1) },
    lua_component = {}
    }
end

entities = {
  create_camera(),
  create_ogre(),
  create_ogre2()
}

print("returning")

