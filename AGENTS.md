# Repository Guidelines

## Project Structure & Module Organization

This is a small C++17 CMake project. Application code lives in `src/`: `main.cpp` builds the `app` executable, while `math_utils.cpp` and `math_utils.h` form the reusable `math_utils` library. Unit tests live in `test/`, currently `test/test_math.cpp`. Build outputs are generated under `build/` and should not be committed.

## Build, Test, and Development Commands

- `cmake -B build -DCMAKE_EXPORT_COMPILE_COMMANDS=ON`: configure the project and generate `build/compile_commands.json` for clang tooling.
- `cmake --build build`: compile the `math_utils` library, `app`, and `unit_tests`.
- `ctest --test-dir build --output-on-failure`: run all CTest-discovered GoogleTest tests with failure details.
- `./build/app`: run the demo executable after building.
- `clang-format --dry-run --Werror src/main.cpp`: check formatting as CI does. Format changed C++ files before submitting.
- `clang-tidy src/main.cpp -p build`: run static analysis using the generated compile database.
- `cmake -B build-coverage -DCMAKE_BUILD_TYPE=Debug -DENABLE_COVERAGE=ON && cmake --build build-coverage --target coverage`: run tests with gcov instrumentation and generate an lcov HTML report in `build-coverage/coverage-report/`.

## Coding Style & Naming Conventions

Use C++17 and keep implementation files in `src/` with matching headers when code is shared. The formatter is based on Google style with 4-space indentation and Allman braces, as defined in `.clang-format`. Prefer clear snake_case names for functions and files, following existing examples such as `math_utils.cpp` and `test_math.cpp`. Keep headers minimal, include only what is needed, and avoid committing generated files from `build/`.

## Testing Guidelines

Tests use GoogleTest, fetched by CMake through `FetchContent`. Add new tests under `test/` and register their source in `CMakeLists.txt` when creating additional test files or executables. Name test files `test_<module>.cpp`, and write focused test cases around observable behavior. Run `cmake --build build` and `ctest --test-dir build --output-on-failure` before opening a pull request.

## Commit & Pull Request Guidelines

Recent commits use short, imperative or descriptive subjects such as `Add CI pipeline` and `Add GoogleTest unit tests`. Keep commit messages concise and focused on one logical change. Pull requests should include a brief summary, the commands run locally, and any relevant issue links. For CI-related changes, describe expected workflow behavior and mention tool or dependency version changes.

## Agent-Specific Instructions

Make scoped edits that match the current CMake layout. Do not commit build artifacts, downloaded dependencies, or local IDE files. If you change CI commands, verify the same commands work locally where possible.
