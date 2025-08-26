# CMake-Template for static and shared libraries
## Building the template
The template defines several workflows for each architecture which can be listed with
```bash
cmake --workflow --list-presets
```

To build a preset
```bash
cmake --workflow --preset <<preset>>
```

CMake only allows to build one architecture in a single call, so if several
architectures have to be built or one architecture depends on the build of another
use several workflow calls.
If e.g. an embedded ARM build depends on x64 artifacts, you would have to handle
it like so
```bash
cmake --workflow --preset x64-debug
cmake --workflow --preset aarch64-debug
```

## Coverage

Coverage collection requires that LCOV is installed on the system. Note that MC/DC coverage
requires GCC >=14.2 and LCOV >=2.3.1.

```bash
lcov -c -d . --mcdc-coverage -o coverage.info
genhtml coverage.info --output-directory out
```
