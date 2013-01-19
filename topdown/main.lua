systems = {
  "Ogre_Render_System",
  "OIS_Input_System",
  "Bullet_Debug_Draw_System",
  "player_mover",
  "camera_controller",
  "Pause_System",
  "Bullet_System",
  }

-- helper functions that should be moved
entities = {}
function add_entity(entity)
  assert(type(entity) == "table", "entity must be a table")
  table.insert(entities, entity)
  return #entities
end

function add_entities(entity_array)
  local rets = {}
  for _,entity in ipairs(entity_array) do
    table.insert(rets, add_entity(entity))
  end
  return rets
end

--add camera
camera_entity = {
  Camera = {near_clip = .1},
  Transform = {
    pos = Vec3f(0,50,0),
    -- The quaternion for looking down
    rot = Quat(-math.sqrt(2)/2, 0, 0, math.sqrt(2)/2)
  },
  camera_follower = {following = 0, y_offset = 50},
}

add_entity(camera_entity)

local box_width = 4
local box_vec = Vec3f(box_width, box_width, box_width)

--player
player_id = add_entity{
  Transform = {pos = Vec3f(0,10, 0)},
  Input = {},
  Collider = {type = "box", side = box_vec},
  Rigid_Body = {mass = 3,
    friction=.1, linear_damping = .1,
    torque = Vec3f(0, 0, 0),
    angular_damping = .3,
    angular_factor = Vec3f(0, 1, 0),
  },
  player_movement = {
    force_mult = 5000,
    force_max = 500,
    max_vel = -20,
    vel_reduction = 50,
    jump_vel = 10,
    has_jumped = false
  },
  Mesh = { filename = "Player.mesh" },
}

camera_entity.camera_follower.following = player_id

for x=-5,5 do
  for y=-5,5 do
    add_entity{
      Transform = {pos = Vec3f(x*10, 20, y*10)},
      Collider = {type = "box", side = box_vec},
      Rigid_Body = {mass = 10, friction = .5},
      Mesh = { filename = "Enemy.mesh" },
    }
  end
end

for x=-1,1 do
  for y=-1,1 do
    add_entity{
      Transform = {pos = Vec3f(x*5, 4, y*5) },
      Light = {}
   }
  end
end

--ground
add_entity{
  Transform = {pos = Vec3f(0,-10, 0)},
  Collider = {type = "box", side = Vec3f(200, 4, 200)},
  Rigid_Body = {mass = 0, friction = .65}
}

--Update once per frame
add_entity {
  single = {paused = false, keydown = false},
  Input = {}
}
