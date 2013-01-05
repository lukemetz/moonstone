systems = {
  "Bullet_System",
  "Ogre_Render_System",
  "OIS_Input_System",
  "Bullet_Debug_Draw_System",
  }


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

--add camera
add_entity{Camera = {}}

--player
add_entity{
  Transform = {pos = Vec3f(0,10, 0)},
  Input = {},
  Collider = {type = "box", side = Vec3f(1,1,1)},
  Rigid_Body = {mass = 3},
  
--  Player_Mover = { },
}

--ground
add_entity{
  Transform = {pos = Vec3f(0,-10, 0)},
  Collider = {type = "box", side = Vec3f(100, 4, 100)},
  Rigid_Body = {mass = 0}
}

add_entity{
  Transform = {scale = Vec3f(.1, .1, .1), pos = Vec3f(0, 5, 0)},
  Mesh = {filename = "ogrehead.mesh"},
  Light = {}
}
