print("Moo test");
local lua_system = {}

function lua_system:init()
  --print("Ran init")
  return {"Transform",  "lua_component", "Input"}
end

function lua_system:update(dt, entity)
  entity.Transform.pos.x = entity.Transform.pos.x + dt*10
  print(entity.Input.keys[2])
end

return lua_system
