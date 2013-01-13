systems = {
  "Bullet_System",
  "Ogre_Render_System",
  "OIS_Input_System",
  "Bullet_Debug_Draw_System",
  "player_mover",
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
add_entity{Camera = {near_clip = .1}}

local box_width = 4
local box_vec = Vec3f(box_width, box_width, box_width)
--player
add_entity{
  Transform = {pos = Vec3f(0,10, 0)},
  Input = {},
  Collider = {type = "box", side = box_vec},
  Rigid_Body = {mass = 3,
    friction=.1, linear_damping = .1,
    angular_damping = 1},
  player_movement = {
    force_mult = 5000, 
    force_max = 500,
    max_vel = -20,
    vel_reduction = 50,
    jump_vel = 10,
    has_jumped = false,
  },
  Mesh = { filename = "Player.mesh" },
}

for i=1,10 do
  add_entity{
    Transform = {pos = Vec3f(0, 10+i*4, 0)},
    Collider = {type = "box", side = box_vec},
    Rigid_Body = {mass = 1, friction = .5},
    Mesh = { filename = "Enemy.mesh" },
    Light = { },
  }
end

--ground
add_entity{
  Transform = {pos = Vec3f(0,-10, 0)},
  Collider = {type = "box", side = Vec3f(100, 4, 100)},
  Rigid_Body = {mass = 0, friction = .65}
}

