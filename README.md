
<h1 align="center">c_utils</h1>

<p align="center">
  <a href="https://github.com/Gabo2447/c_utils/blob/main/LICENSE"><picture><source media="(prefers-color-scheme: dark)" srcset="https://shieldcn.dev/github/Gabo2447/c_utils/license.svg?size=default" /><img alt="license" src="https://shieldcn.dev/github/Gabo2447/c_utils/license.svg?size=default&amp;mode=light" /></picture></a>
  <a href="https://github.com/Gabo2447/c_utils/commits"><picture><source media="(prefers-color-scheme: dark)" srcset="https://shieldcn.dev/github/Gabo2447/c_utils/last-commit.svg?size=default" /><img alt="last commit" src="https://shieldcn.dev/github/Gabo2447/c_utils/last-commit.svg?size=default&amp;mode=light" /></picture></a>
  <a href="https://github.com/gabo2447/c_utils/releases"><picture><source media="(prefers-color-scheme: dark)" srcset="https://shieldcn.dev/github/gabo2447/c_utils/release.svg?size=default" /><img alt="release" src="https://shieldcn.dev/github/gabo2447/c_utils/release.svg?size=default&amp;mode=light" /></picture></a>
</p>

## Overview

`c_utils` is a lightweight, modular C11 library providing generic data structures and POSIX system 
utilities. It delivers clean, type-agnostic abstractions using generic payload pointers (`void*`), 
offering predictable memory behavior for POSIX software.

## Key Principles

* **Explicit Memory Ownership:** Clear separation between container management and payload lifecycle.
* **Strict C11 Compliance:** Built using standard C11 without compiler-specific extensions (`CMAKE_C_EXTENSIONS=OFF`).
* **Developer Ergonomics:** Integrated AddressSanitizer (ASan) support and strict warning flags enabled by default.
* **Modular CMake Setup:** Easy integration as a subdirectory or static library target.

## Requirements

* C11-compliant C compiler (GCC, Clang)
* CMake 3.21 or higher
* POSIX environment (Linux, macOS, BSD)

## Building & Testing

1. Clone the repository
    ```bash
    git clone https://github.com/Gabo2447/c_utils.git
    cd c_utils
    ```

2. Build the project with cmake
    ```bash
    # Configure the build directory
    cmake -B build
    
    # Build the library and test targets
    cmake --build build
    
    # Run unit tests via CTest
    ctest --test-dir build --output-on-failure
    ```