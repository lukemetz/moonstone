print("Moo test");
local lua_system = {}

function lua_system:init()
  --print("Ran init")
  return {"Transform", "lua_component"}
end

function lua_system:update(dt, entity)
  entity.Transform.pos.x = entity.Transform.pos.x + dt*10
  print(__input)
  print(__input["keys"][2])
  print(__input["mouse_dx"])
end

return lua_system
