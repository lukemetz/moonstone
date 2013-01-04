
local mt = {}

function Quat(x_, y_, z_, w_)
  local q = {x = x_ or 0, y = y_ or 0, z = z_ or 0, w = w_ or 1}
  setmetatable(q, mt)
  return q
end

mt.__tostring = function(q)
  return "Quat(" .. q.x .. ", " .. q.y .. ", " .. q.z .. ", " .. q.w .. ")"
end
