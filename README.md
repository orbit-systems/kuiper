# Kuiper
This repo contains commonly used OS libraries and the orbit-common header folder.

# Orbit Standard

## orbit_da.h
Provides a dynamic array/stretchy buffer system analogous to the std::vector from C++.

## orbit_fs.h
Provides system agnostic FS utilities for opening, closing and manipulating files.

## orbit_ll.h
Provides a doubly-linked list, with a similar interface to orbit_da.h

## orbit_string.h
Provides a wrapper around char* style c-strings, by turning them into slices/fat pointers.
Provides utilities for manipulating strings, with concatenation, searching, printing, equality and conversion utilities.

## orbit_types.h
Provides useful type names used across all OS projects.

## orbit_util.h
Provides debugging, compiler agnostic function attribute and iteration utilities.

## alloc.c/alloc.h
Provides allocation wrappers for mars.

## ptrmap/strmap
Provides a hashmap interface for void* and orbit string types.
Depends on alloc.h and orbit.h

## strbuilder
Provides a string builder interface to allow easier string manipulation with orbit strings.
