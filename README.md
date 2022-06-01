# VeritaSTG v0.1.0-WIP <!-- omit in toc -->
A powerful engine for shmups (WIP/Early Development)

- [Quickstart](#quickstart)
- [Features/Roadmap Overview](#featuresroadmap-overview)
- [Design](#design)
- [Dependencies](#dependencies)
- [License](#license)

## Quickstart
```sh
git clone --recursive https://github.com/Tru-Dev/VeritaSTG.git
cd VeritaSTG
./build.sh # .\build.bat if on Windows
# Alternatively, you could use the get_deps script to install the vcpkg dependencies
# and not build VeritaSTG.
```

WIP Note: you will need an ogg file, renamed to `test.ogg`,
to properly test the current version.

## Features/Roadmap Overview
- [ ] Audio
  - [ ] Music playback
  - [ ] Sound effects playback
- [ ] Rendering
- [ ] Input system
- [ ] Callbacks system
- [ ] Extension libraries system
  - [ ] Language bindings system

## Design
VeritaSTG is focused on implementing good design patterns,
for example minimizing global state (including singletons).

Game logic takes place in callbacks, with each callback accepting a context object.
Each context object is an encapsulated view of game state.

In the future, these callbacks will be set by an extension library manager
(which is why Boost.DLL is included in the get_deps script). These extension
libraries will either be native C++ extensions or bindings to other languages,
which will load the scripts and then pass their code to the callbacks.

Individual game objects and individualized contexts/callbacks for said objects are planned.

Miscellaneous:
- The game engine will run on a delta-time basis,
  as opposed to a frame-by-frame basis.
- No exceptions, only recoverable errors and panics.
- Multithreading is planned.

## Dependencies
Dependencies marked with a (v) are installed through [vcpkg](https://vcpkg.io).
Dependencies marked with a (m) are installed through git modules.
Dependencies marked with a (s) are included directly in the source tree.

- [Boost](https://boost.org) (v)
  - DLL
  - Iostreams
  - Locale
- [Boxer](https://github.com/aaronmjacobs/Boxer) (m)
- [{fmt}](https://github.com/fmtlib/fmt) (v)
- [glad](https://github.com/Dav1dde/glad/) (s)
- [GLFW3](https://glfw.org) (v)
- [miniaudio](https://github.com/mackron/miniaudio) (s)

## [License](LICENSE)
This code is under the MIT license.
