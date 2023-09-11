#ifndef C_FLAG_H_INCLUDE
#define C_FLAG_H_INCLUDE

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

enum CFlagType { FlagTypeInt };

typedef struct {
  void *value_ref;

  void *default_value;
  enum CFlagType flag_type;

  const char *short_name;
} CFlag;

typedef struct {
  int _argc;
  char **_argv;

  CFlag *_flags;
  int _flagsc;

  char *program_name;
} CFlagSet;

CFlagSet cflag_from_args(int argc, char **argv);

int cflag_parse(CFlagSet *flags);

void cflag_int(CFlagSet *flags, int *value, const char *short_name);

#endif // C_FLAG_H_INCLUDE

CFlagSet cflag_from_args(int argc, char **argv) {
  CFlagSet flags = {
      ._argc = argc,
      ._argv = argv,
      0,
  };

  return flags;
}

void cflag_int(CFlagSet *flags, int *value, const char *short_name) {
  // Dereference the value pointer, so it's value can't be changed during
  // parsing.
  int default_value = *value;

  CFlag flag = {
      .flag_type = FlagTypeInt,
      .short_name = short_name,
      .value_ref = value,
      // Take a reference to the default value, so it fits into a void*
      .default_value = &default_value,
  };

  // Add flag to FlagSet
  flags->_flagsc += 1;

  CFlag *resized_flags = realloc(flags->_flags, sizeof(CFlag) * flags->_flagsc);
  if (resized_flags == NULL) {
    assert(0 && "Memory allocation failed. I have to handle realloc failure, "
                "which might set errno.");
  }

  flags->_flags = resized_flags;
  flags->_flags[flags->_flagsc - 1] = flag;
}

int cflag_parse(CFlagSet *flags) {
  if (flags->_argv[0] == NULL) {
    return 0;
  }

  // If the argument count is at least one, the first argument is the program
  // name.
  // https://www.open-std.org/jtc1/sc22/wg14/www/docs/n2310.pdf  5.1.2.2.1
  // Program startup
  flags->program_name = flags->_argv[0];

  // No arguments to parse
  if (flags->_argv[1] == NULL) {
    return 0;
  }

  for (int argIdx = 1; argIdx < flags->_argc; argIdx++) {
    char *arg = flags->_argv[argIdx];

    for (int flagIdx = 0; flagIdx < flags->_flagsc; flagIdx++) {
      CFlag flag = flags->_flags[flagIdx];
      if (strcmp(arg, flag.short_name) == 0) {
        // FIXME: Check if there is a next argument for every type except bool.
        // Save to void* and cast in switch.

#ifdef C_FLAG_DEBUG
        printf("Found %s\n", arg);
        int val_before = *(int *)flag.value_ref;
#endif

        // TODO: Don't assume data type.
        int val = atoi(flags->_argv[argIdx + 1]);
        *(int *)flag.value_ref = val;

#ifdef C_FLAG_DEBUG
        printf("  %d => %d\n", val_before, *(int *)flag.value_ref);
#endif
        break;
      }
    }
  }

  return 0;
}
