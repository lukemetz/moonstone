system = {}

function system:init()
  return {"single", "Input"}
end

function system:update(dt, entity)
  if (entity.Input.keys[key.P] and entity.single.keydown ) then
    if (entity.single.paused == true) then
      manager:resume()
      entity.single.paused = false
    else
      manager:pause()
      entity.single.paused = true 
    end
    entity.single.keydown = false
  end
  if not entity.Input.keys[key.P] then
    entity.single.keydown = true
  end
end

return system
