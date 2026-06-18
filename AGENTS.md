# Repository Guidelines

## Project Structure & Module Organization

This is a small C++17 CMake project. Application code lives in `src/`: `main.cpp` builds `app`, while `math_utils.cpp` and `math_utils.h` form the reusable library. Unit tests live in `test/`. Build outputs such as `build/`, `build-coverage/`, and container build directories should not be committed.

## Build, Test, and Development Commands

- `cmake -B build -DCMAKE_EXPORT_COMPILE_COMMANDS=ON`: configure the project and generate `build/compile_commands.json` for clang tooling.
- `cmake --build build`: compile the `math_utils` library, `app`, and `unit_tests`.
- `ctest --test-dir build --output-on-failure`: run all CTest-discovered GoogleTest tests with failure details.
- `./build/app`: run the demo executable after building.
- `clang-format --dry-run --Werror src/main.cpp`: check formatting as CI does. Format changed C++ files before submitting.
- `clang-tidy src/main.cpp -p build`: run static analysis using the generated compile database.
- `cmake -B build-coverage -DCMAKE_BUILD_TYPE=Debug -DENABLE_COVERAGE=ON && cmake --build build-coverage --target coverage`: run tests with gcov instrumentation and generate an lcov HTML report in `build-coverage/coverage-report/`.
- `docker build -t ci-cd-demo-builder .`: build the reusable C++ toolchain container.
- `docker run --rm -v "$PWD":/workspace ci-cd-demo-builder bash -lc "cmake -B build-container && cmake --build build-container && ctest --test-dir build-container"`: build and test inside the container.

## Coding Style & Naming Conventions

Use C++17 and keep shared code in `src/` with matching headers. Formatting follows `.clang-format`: Google style, 4-space indentation, and Allman braces. Prefer clear snake_case names, following examples such as `math_utils.cpp` and `test_math.cpp`. Keep headers minimal and include only what is needed.

## Testing Guidelines

Tests use GoogleTest, fetched by CMake through `FetchContent`. Add new tests under `test/` and register their source in `CMakeLists.txt` when creating additional test files or executables. Name test files `test_<module>.cpp`, and write focused test cases around observable behavior. Run `cmake --build build` and `ctest --test-dir build --output-on-failure` before opening a pull request.

## Commit & Pull Request Guidelines

Recent commits use short, imperative or descriptive subjects such as `Add CI pipeline` and `Add GoogleTest unit tests`. Keep commit messages concise and focused on one logical change. Pull requests should include a brief summary, the commands run locally, and any relevant issue links. For CI-related changes, describe expected workflow behavior and mention tool or dependency version changes.

## Agent-Specific Instructions

Make scoped edits that match the current CMake layout. Do not commit build artifacts, downloaded dependencies, or local IDE files. If you change CI commands, verify the same commands work locally where possible.
