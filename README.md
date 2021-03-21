# Gladiat0rs ![face](assets/ui_face.png)

![gif](assets/gladiat0rs.gif)  
*Small arcady gladiator game!*

## Controls
- `w` , `a` , `s`, `d` - Move in game and menu
- `↑`, `↓` , `←`, `→` - Shoot in game and move in menu
- `ESC` - Pause game

## Download
- [Windows 64bit](https://github.com/nikoka12345/gladiat0rs/releases/download/v1.0-beta/gladiat0rs-v1.0-Windows-x86_64.zip)
- [Linux 64bit](https://github.com/nikoka12345/gladiat0rs/releases/download/v1.0-beta/gladiat0rs-v1.0-Linux-x86_64.zip)

## Credits

- Art [Guan Qi 🌟 关琪](https://www.instagram.com/qi.draws)
- Music [IXentimenTI](https://www.instagram.com/xentiment/)

## Dependencies

- [SDL2](https://www.libsdl.org/)
- [SDL2_image](https://www.libsdl.org/projects/SDL_image/)
- [SDL2_ttf](https://www.libsdl.org/projects/SDL_ttf/)
- [SDL2_mixer](https://www.libsdl.org/projects/SDL_mixer/)

### For Debian
```console
$ apt install libsdl2-dev libsdl2-image-dev libsdl2-mixer-dev libsdl2-ttf-dev
```

## Building

- Windows
```console
$ pushd build
$ cl -nologo -O2 ../src/main.c /I <path_t0>\SDL2\include /I <path_t0>\SDL2_image\include /I <path_t0>\SDL2_mixer\include /I <path_t0>\SDL2_ttf\include /link /LIBPATH:<path_t0>\SDL2\lib\x64 /LIBPATH:<path_t0>\SDL2_image\lib\x64  /LIBPATH:<path_t0>\SDL2_mixer\lib\x64 /LIBPATH:<path_t0>\SDL2_ttf\lib\x64 SDL2.lib SDL2main.lib SDL2_image.lib SDL2_mixer.lib SDL2_ttf.lib  /SUBSYSTEM:CONSOLE /out:gladiat0rs.exe
$ popd
```

- Linux
```console
$ gcc -c src/main.c -m64 -O3 -Wall && gcc *.o -o build/gladiat0rs -s -lm -lSDL2main -lSDL2 -lSDL2_image -lSDL2_mixer -lSDL2_ttf && rm *.o
```

## License
[MIT](./LICENSE)
