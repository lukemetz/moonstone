local lua_system = {}

function lua_system:init()

  return {"Rigid_Body", "player_movement", "Input"}
end

function lua_system:update(dt, entity)
  print(key.DOWN)
  dx = (entity.Input.keys[key.L] and 1 or 0) - (entity.Input.keys[key.J] and 1 or 0)
  dy = (entity.Input.keys[key.I] and 1 or 0) - (entity.Input.keys[key.K] and 1 or 0)
  entity.Rigid_Body.forces = Vec3f(dx*100,0, dy*100)
end

return lua_system
