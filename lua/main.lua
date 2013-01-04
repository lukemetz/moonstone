systems = { "lua_system", "Ogre_Render_System", "OIS_Input_System"}


entities = {}
function add_entity(entity)
  assert(type(entity) == "table", "entity must be a table")
  table.insert(entities, entity)
  return #entities - 1
end

function add_entities(entity_array)
  local rets = {}
  for _,entity in ipairs(entity_array) do
    table.insert(rets, add_entity(entity))
  end
  return rets
end

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
    Input = {},
    Collider = {type = "sphere", radius=3},
    Rigid_Body = {mass = 2, offset = Vec3f(0,0,0)} 
    }
end

function create_ogre2()
  return {
    Mesh = {filename = "penguin.mesh"},
    Transform = { pos = Vec3f(10,0,0), rot = Vec3f(0,0,0), scale = Vec3f(1,1,1) },
    lua_component = {}
    }
end

val1, val2 = add_entities{
  create_camera(), create_ogre(), create_ogre2()}
print (val1, val2)

local val2 = add_entity(create_ogre())
local val2 = add_entity(create_ogre2())

