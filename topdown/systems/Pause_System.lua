system = {}

function system:init()
  return {"single", "Input"}
end

function system:update(dt, entity)
  local do_resume = false
  if (entity.Input.keys[key.P] and entity.single.keydown ) then
    if (entity.single.paused == true) then
      entity.single.paused = false
      do_resume = true
    else
      entity.single.paused = true
      manager:pause()
    end
    entity.single.keydown = false
  end
  if not entity.Input.keys[key.P] then
    entity.single.keydown = true
  end

  if (do_resume) then
    manager:resume()
  end
end
return system
