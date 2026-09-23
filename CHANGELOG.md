# Changelog

All notable changes to this project will be documented in this file.

The format is based on [Keep a Changelog](https://keepachangelog.com/en/1.1.0/),
and this project adheres to [Semantic Versioning](https://semver.org/spec/v2.0.0.html).

# [Unreleased]

### Added
- new unit test suite for `HashMap` operations, bucket collisions, and dynamic memory cleanup.
- new `linked_list_find` function to `LinkedList` public API to search elements using custom comparators (`CompareFn`)[cite: 1, 2].
- new `linked_list_contains` function to `LinkedList` public API to check element presence[cite: 1, 2].
- new `array_list_contains` function to `ArrayList` public API.

### Changed
- test suites for `ArrayList`, `LinkedList`, and `Queue` with comprehensive coverage for edge cases, boundary limits, and NULL parameter validation.

### Fixed
- logical check in `array_list_contains` that incorrectly restricted search execution based on list capacity.
- missing NULL check for internal list instance in `queue_size`.
- missing NULL check for internal list instance in `queue_clear`.

## [0.2.0] - 2026-09-23

### Added
- new core generic `array_list` implementation.
- unit test suite for `array_list` operations.

## [0.1.0] - 2026-09-22

### Added
- new core generic `linked_list` implementation.
- unit test suite for all `linked_list` operations and edge cases.

[0.1.0]: https://github.com/Gabo2447/c_utils/releases/tag/v0.1.0
[0.2.0]: https://github.com/Gabo2447/c_utils/releases/tag/v0.2.0