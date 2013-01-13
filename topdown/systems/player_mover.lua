require "math"
local lua_system = {}

function lua_system:init()

  return {"Rigid_Body", "player_movement", "Input"}
end

function clamp(input, low, high)
  if input > high then 
    return high
  elseif input < low then
    return low
  end
  return input
end


function reduce_mag(orig, rate)
  if orig > 0 then
    return -math.min(orig, rate)
  end
  return math.max(orig, rate)
end

function lua_system:try_jump(entity)
  print (entity.Input.keys[key.SPACE])
  if entity.Input.keys[key.SPACE] and not entity.player_movement.has_jumped then
    print "jumpen the styuff"
    entity.player_movement.has_jumped = true
    entity.Rigid_Body.velocity.y = entity.player_movement.jump_vel;
  end

  if not entity.Input.keys[key.SPACE] then
    entity.player_movement.has_jumped = false
  end
end

function lua_system:update(dt, entity)
  dx = (entity.Input.keys[key.L] and 1 or 0) - (entity.Input.keys[key.J] and 1 or 0)
  dy = (entity.Input.keys[key.K] and 1 or 0) - (entity.Input.keys[key.I] and 1 or 0)
  local force_mult = entity.player_movement.force_mult;
  local force_max = entity.player_movement.force_max;
  local vel_reduction= entity.player_movement.vel_reduction;
  entity.Rigid_Body.forces = entity.Rigid_Body.forces + Vec3f(dx*dt*force_mult, 0, dy*dt*force_mult);
  entity.Rigid_Body.forces.x = clamp(entity.Rigid_Body.forces.x, -force_max, force_max)
  entity.Rigid_Body.forces.z = clamp(entity.Rigid_Body.forces.z, -force_max, force_max)
  entity.Rigid_Body.velocity.x = clamp(entity.Rigid_Body.velocity.x , -20, 20);
  entity.Rigid_Body.velocity.z = clamp(entity.Rigid_Body.velocity.z , -20, 20);
  if dx == 0 then
    entity.Rigid_Body.forces.x = 0;
    entity.Rigid_Body.velocity.x = entity.Rigid_Body.velocity.x + reduce_mag(entity.Rigid_Body.velocity.x, vel_reduction*dt);
  end
  if dy == 0 then
    entity.Rigid_Body.velocity.z = entity.Rigid_Body.velocity.z + reduce_mag(entity.Rigid_Body.velocity.z, vel_reduction*dt);
    entity.Rigid_Body.forces.z = 0;
  end
  
  self:try_jump(entity)
end

return lua_system
