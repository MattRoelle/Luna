rawset(_G, "keybindings", {}) -- Global keybinding table

function check_keybindings()
  -- I should really rewrite this in C.... sigh TODO
  print("checking keybindings");
  for k,v in pairs(keybindings) do
    local len = string.len(k)
    local state = get_state()
    if string.find(v['mode'], state) and string.sub(input_buffer, 1, len) == k then
      if (v['cb']) then v['cb']() end
    end
  end
end

function kbind(mode, pattern, cb)
  local mapping = {}
  mapping['mode'] = mode
  mapping['cb'] = cb
  keybindings[pattern] = mapping
end

-- Default keybindings, can be overwritten
kbind("n", "i", function() switch_state("e") end) -- Switch to Edit state
kbind("neEc", "", function() switch_state("E") end) -- Force switch to Exit state

-- VI Keys
kbind("n", "h", function() move_cursor(1, 0) end) -- left
kbind("n", "j", function() move_cursor(0, 1) end) -- down
kbind("n", "k", function() move_cursor(0, -1) end) -- up
kbind("n", "l", function() move_cursor(-1, 0) end) -- right
