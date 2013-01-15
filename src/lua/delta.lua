return function(old_entities, new_entities)
  -- Now check if the tables are the same general shape
  if #old_entities ~= #new_entities then
    return false
  end

  local table_union= function(t1, t2)
    -- returns a dictionary with fields as keys.
    -- The value is either 1, meaning in t2, 2 in t2, or 3 in both
    union = {}
    for k,v in pairs(t1) do
      union[k] = 1
    end

    for k,v in pairs(t2) do
      if union[k] == 1 then 
        union[k] = 3
      else
        union[k] = 2
      end
    end
    return union
  end

  -- does a equality check of tables and any other type
  local is_equal;
  is_equal = function(v1, v2)
    if type(v1) ~= type(v2) then
      return false
    end
    if type(v1) == "table" then
      for k,v in pairs(v1) do
        if is_equal(v1[k], v2[k]) == false then
          return false
        end
      end
    else 
      return v1 == v2
    end
    -- if none return false
    return true
  end
 
  local update_component = function(to_update, old, new)
    keys = table_union(old, new)
    for k,v in pairs(keys) do
      if keys[k] ~= 3 then
        return true
      end
      if not is_equal(old[k], new[k]) then
        print("updating ===>", k, "was", old[k], "==>", new[k])
        to_update[k] = new[k]
      end
    end
  end

  local tabledif = function(current_entity, t1, t2)
    keys = table_union(t1, t2)
    for k,v in pairs(keys) do
      print("             ", k)
      --for now lets remake if there is a different component

      if v ~= 3 then
        return true 
      end
      reset = update_component(current_entity[k], t1[k], t2[k])
      if reset == true then
        return true
      end
    end
    return false
  end

  current_entities = manager:get_all_entities()
  for i = 1,#old_entities do
    print("On entity number in lua", i)
    reset = tabledif(current_entities[i], old_entities[i], new_entities[i])
    if reset then
      return false
    end
  end
  manager:update_all_entities(current_entities)
  return true
end

