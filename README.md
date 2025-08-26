# CMake-Template for static and shared libraries
The template should work with both Clang and GCC, however the coverage
presets are only available / will only work with GCC.

## Building the template
The template defines several workflows for each build configuration which can be listed with
```bash
cmake --workflow --list-presets
```

To build a preset
```bash
cmake --workflow --preset <<preset>>
```
## Coverage

Coverage collection requires that LCOV (and genthml) is installed on the system.
Note that MC/DC coverage requires GCC >=14.2 and LCOV >=2.3.1.

Coverage is set up only for the static library build and can be executed via
the coverage preset
```bash
cmake --workflow --preset x64-coverage
```

# Handling different architectures

CMake only allows to build one architecture in a single call, so if several
architectures have to be built or one architecture depends on the build of another
use several workflow calls and separate build directories for each architecture.
If e.g. an embedded ARM build depends on x64 artifacts, you would have to handle
it like so
```bash
cmake --workflow --preset x64-debug
cmake --workflow --preset aarch64-debug
```


