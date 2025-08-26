# CMake-Template for static and shared libraries
## Building the template
The template defines several workflows for each architecture which can be listed with
```cmake
cmake --workflow --list-presets
```

To build a preset
```cmake
cmake --workflow --preset <<preset>>
```

CMake only allows to build one architecture in a single call, so if several
architectures have to be built or one architecture depends on the build of another
use several workflow calls.
If e.g. an embedded ARM build depends on x64 artifacts, you would have to handle
it like so
```cmake
cmake --workflow --preset x64-debug
cmake --workflow --preset aarch64-debug
```

