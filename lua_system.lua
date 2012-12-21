print("Moo test");
local lua_system = {}

function lua_system:fun_time(dt)
  print("Lawl")
end

function lua_system:update(dt, entity)
  print(dt+1);
end

x = 1

return lua_system
