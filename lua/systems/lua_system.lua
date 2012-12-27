print("Moo test");
local lua_system = {}

function lua_system:init()
  --print("Ran init")
  return {"Transform", "lua_component"}
end

function lua_system:update(dt, entity)
  entity.Transform.pos.x = entity.Transform.pos.x - dt*.1
  entity.Transform.rot.x = 444
end

return lua_system
