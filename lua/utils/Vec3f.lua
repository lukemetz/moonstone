local mt = {}

function Vec3f(x_, y_, z_)
  local v = {x = (x_ or 0), y = y_ or 0, z = z_ or 0}
  setmetatable(v, mt)
  return v
end

mt.__add = function(v1, v2)
  return Vec3f(v1.x + v2.x, v1.y + v2.y, v1.z + v2.z)
end

mt.__sub = function(v1, v2)
  return Vec3f(v1.x - v2.x, v1.y - v2.y, v1.z - v2.z)
end

mt.__tostring = function(v1)
  return "Vec3f(" .. v1.x .. ", " .. v1.y .. ", " .. v1.z .. ")"
end
