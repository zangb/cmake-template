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

# Building Documentation with Doxygen
To build the documentation a CMake target `doxygen` is provided, outside of workflows.
First, configure the project for an architecture of your choice
or run a workflow as shown above. Then call the below command for the generated
build directory, e.g. `build/release`.
```bash
cmake --build <build_dir> --target doxygen
```
The Doxyfile is configured to make doxygen return with a non-zero value if it encounters
undocumented or wrongly documented code which can be used to fail a step in your
build pipeline.

To configure the look of your doxygen output or any doxygen settings at all, look
at the Doxyfile in the `docs/` folder. The output will be generated in
`docs/doxygen`. Note that relative paths will be resolved against the location
where doxygen was called from. In this template it is the root folder.

Make sure that any source file / header file you add has a doxygen file description,
otherwise doxygen will not pick it up in its evaluation. An example is provided below
(the exact syntax depends on the doxygen comment flavour you prefer):
```cpp
/*! \file template.hpp
 *  \brief The template header
 *
 *  Provides the template header
 */
```

