print("Moo test");
local lua_system = {}

function lua_system:init()
  --print("Ran init")
  return {"Transform", "lua_component"}
end

function lua_system:update(dt, entity)
  print(dt+1);
  --print(entity.Transform)
  --print(entity.lua_component)
  --print(entity)
  --print("Hello world")
end

--x = 1

return lua_system
