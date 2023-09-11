#! /bin/sh

CFLAGS="$(cat compile_flags.txt)"

clang $CFLAGS -o count main.c