# Luna

Luna is a (attempted) text-editor, inspired by vim, and fully scriptable via the LUA language.

#### A note on compiling

You will need a copy of LUA 5.2.3 & ncurses

If you're on Linux you can run this to install LUA
```bash
curl -R -O http://www.lua.org/ftp/lua-5.2.3.tar.gz
tar zxf lua-5.2.3.tar.gz
cd lua-5.2.3
make linux test
```

If you get errors about missing packages try downloading the `readlines` lib from your package manager

