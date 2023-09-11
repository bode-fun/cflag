# CFlag ⛳️

CFlag a simple CLI option, aka flag, header-only, stb-style library.
It references the design of the Go *flag* module, but improves on it.

**This library is currently a prototype will have breaking changes until v1.**

## Example

Since this library is in development, it's usage will change.

This is an example how the library currently works.

```c
#include <stdio.h>

#define C_FLAG_IMPL
#include <cflag.h>


int main(int argc, char **argv) {
  // Initialize flag set.
  CFlagSet flags = cflag_from_args(argc, argv);

  // Initialize count to the default value.
  int count = 1;
  // Register count on the flag set on the CLI option "-c".
  cflag_int(&flags, &count, "-c");

  // Parse the CLI options and assign their values.
  int err = cflag_parse(&flags);
  if (err != 0) {
    return err;
  }

  // Use the option's value as if it is a normal variable.
  printf("Counting to %d\n", count);
  for (int idx = 0; idx < count; idx++) {
    printf("  %d\n", idx);
  }

  return 0;
}

```

[Source](./examples/count/main.c).

## TODOs

TODOs and ideas are either references in the source code, starting with *"TODO:"* and *"FIXME:"* or under [this](./TODO.md) file.

## License

This library is licensed under LGPL v3. Please take a look at the [LICENSE](./LICENSE.md) 