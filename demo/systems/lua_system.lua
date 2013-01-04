print("Moo test");
local lua_system = {}

function lua_system:init()
  --print("Ran init")
  return {"Transform", "Mesh", "lua_component", "Input"}
end

function lua_system:update(dt, entity)
  entity.Transform.pos.x = entity.Transform.pos.x + dt*10
  print(entity.Mesh[0].material)
end

return lua_system
