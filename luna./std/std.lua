function dofile(fname)
  return assert(loadfile(fname))()
end

dofile('/home/matt/code/Luna/luna./std/keybindings.lua') -- Relative paths seem to break... not good not good
