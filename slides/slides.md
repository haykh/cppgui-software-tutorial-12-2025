# intro to `ImGui`

repo for the tutorial: [github.com/haykh/cppgui-software-tutorial-12-2025](https://github.com/haykh/cppgui-software-tutorial-12-2025)

<footer>
  flatiron software tutorial [dec 2025]
</footer>


---


## what is `ImGui`?

[showcase](https://github.com/ocornut/imgui/issues/8942)

[10+ years now](https://github.com/ocornut/imgui/issues/7892)


---


## growing library of [add-ons](https://github.com/ocornut/imgui/wiki/Useful-Extensions)

- plotting: [`ImPlot`](https://github.com/epezent/implot), [`ImPlot3D`](https://github.com/brenocq/implot3d)
- node editors: [`core-nodes`](https://github.com/onurae/core-nodes), [`imnodes`](https://github.com/Nelarius/imnodes)
- [`nnview`](https://github.com/lighttransport/nnview)


---


## other languages

- Python: [`DearPyGui`](https://github.com/hoffstadt/DearPyGui)
- Rust: [`imgui-rs`](https://github.com/imgui-rs/imgui-rs)
- JS/TS: [`imgui-js`](https://github.com/flyover/imgui-js)


---


## [`Oh My Dear ImGui`](https://github.com/haykh/oh-my-dear-imgui)
### why write a wrapper?

- `ImGui` has no explicit `CMake` support
- plotting not natively supported (need, e.g., `ImPlot`)
- mainly relies on software rasterization (`ImPlot` has no native support for shaders)
- needs a bunch of boilerplate code to get up and running (designed for many [`OpenGL` implementations](https://github.com/ocornut/imgui/tree/master/backends))
