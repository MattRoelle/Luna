rawset(_G, "keybindings", {}) -- Global keybinding table

function check_keybindings()
  -- I should really rewrite this in C.... sigh TODO
  print("checking keybindings");
  for k,v in pairs(keybindings) do
    local len = string.len(k)
    local state = get_state()
    if string.find(v['mode'], state) and string.sub(input_buffer, 1, len) == k then
      switch_state("E")
      if (v['cb']) then
        v['cb']()
      end
    end
  end
end

function kbind(mode, pattern, cb)
  local mapping = {}
  mapping['mode'] = mode
  mapping['cb'] = cb
  keybindings[pattern] = mapping
end

kbind("n", "h", function() move_cursor(1, 0) end)
kbind("n", "j", function() move_cursor(0, 1) end)
kbind("n", "k", function() move_cursor(0, -1) end)
kbind("n", "l", function() move_cursor(-1, 0) end)
kbind("n", "q", function() switch_state("E") end)
