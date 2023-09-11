#include <stdio.h>

#define C_FLAG_IMPL
#define C_FLAG_DEBUG
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
