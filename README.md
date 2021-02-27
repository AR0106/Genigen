# Genigen

Genigen is an Open Source 2D Game Engine, that I work on in my Spare Time.

## Prerequisites

1. [Box2d](https://github.com/erincatto/box2d)
2. [GLEW](https://github.com/nigels-com/glew)
3. [GLFW](https://github.com/glfw/glfw)
4. [GLM](https://github.com/g-truc/glm)
5. [ImGUI](https://github.com/ocornut/imgui)
6. [STB](https://github.com/nothings/stb)
7. [FMOD Core](https://www.fmod.com/core)

## Setup

### Static Libraries

Drag The 'Lib' and 'Include' folders of Box2D, FModCore, GLEW, GLFW, Like:

```bash
Dependencies
│   ├───Dependency
│   │   ├───include
│   │   └───lib
```

### Header Libraries

Drag the Header Libraries into the Vendor Folder in Source Like:

```bash
Vendor
    ├───HeaderLib1
    │   └───HeaderLib1_SubFolder
    ├───HeaderLib2
    └───HeaderLib3
```

## Contributing

Pull requests are welcome. For major changes, please open an issue first to discuss what you would like to change.

Please make sure to update tests as appropriate.

## License

[MIT](https://choosealicense.com/licenses/mit/)

## Notes

This is a work in progress, very early engine.
