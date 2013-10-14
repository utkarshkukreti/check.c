# check.c

check.c is a mini testing framework for C that I built to do Test-Driven
Development in my C projects.

It's highly inspired by RSpec from Ruby, and Mocha from JS/Node.js,
and tries to provide a similar interface using macros, as much as the
C pre-processor allowed me to.

Here's how it looks like:

![Screenshot](https://dl.dropboxusercontent.com/u/2164813/github/utkarshkukreti/check.c/screenshot.png)

## API

The framework exposes 3 main macros: `describe`, `check` and `checkm`,
and two other macros `context` and `it`, which are just aliases to `describe`.

Here's a quick example for those who want to jump in right away:

    describe("My RPN Calculator", {
      context("add", {
        it("adds two positive integers", {
          check(rpn_eval("2 3 +") == 5);
          check(rpn_eval("2 3 4 + +") == 9);
        });

        it("returns -42 if there are not enough operands on the stack", {
          checkm(rpn_eval("2 +") == -42, "This message will appear in the output");
        });
      });

      context("sub", {
        // ...
      });
    });

### describe

`describe` macro expects two parameters: a string and a block (code wrapped
within curly braces; example below), and it prints the string and then executes
the block.

Every nested `describe` call increments the indentation of output of
the assertions made inside its block.

### checkm

`checkm` macro expects 2 parameters, an expression which is
to be asserted as being true, and a message to be used in the test output.

### check

`check` macro expects a single expression, and in turn calls `checkm` macro
with the message being the string representation of the expression, so these two
lines mean the exact same thing:

    check(1 + 2 == 3);
    checkm(1 + 2 == 3, "1 + 2 == 3");

### check_print_stats

Lastly, there's a function `check_print_stats()` which prints some statistics
about the assertions that were run, including total number of assertions, and
the counts of the passed, failed, and skipped assertions.

## Usage

The whole framework is just a single < 60 LOC file `check.h` (inside `include/`
directory in this repository).

You just need to pass the path of the directory containing the file when
compiling your code, like `gcc -Iinclude ...` when `check.h` is in the
`include/` directory.

Micro Example: (check.h is present at `include/check.h`)

    $ cat micro_example.c
    #include <check.h>

    int main() {
      describe("Micro Example", {
        context("Basic Arithmetic", {
          check(1 == 1);
          check(1 < 2);
          // This will fail ->
          check(2 < 1);
          checkm(1, "and this will get skipped");
        });
      });

      check_print_stats();
    }

    $ gcc -Iinclude -std=c99 micro_example.c

    $ ./a.out
    ➔ Micro Example
       ➔ Basic Arithmetic
          ✓ 1 == 1
          ✓ 1 < 2
          ✗ 2 < 1 (build/micro_example.c:12)
          ? and this will get skipped

      ✗ 4 assertions, 2 passed, 1 skipped, 1 failed.

Make sure to use C99 or newer standard when compiling the file, otherwise
the unicode characters in the string will throw some warnings.

## Complete Example

This is the complete code of the screenshot posted above.

    #include <check.h>

    int main() {
      describe("A Test Suite using check.c", {
        describe("check() and checkm()", {
          context("passing tests", {
            it("uses expression as message when using check()", {
              check(1 + 2 == 3);
              check(1);
            });

            it("custom message when using checkm()", {
              checkm(2 * 2 == 4, "two times two equals four");
            });
          });

          context("failing tests", {
            it("shows a message in red color", {
              check(1 > 2);
            });

            it("skips the rest of the tests (in the same block) after one fails", {
              checkm(1, "this passes");
              checkm(0, "this fails");
              checkm(1, "this gets skipped");
            });
          });
        });

        describe("passed, failed, and skipped counters", {
          it("work correctly", {
            check(check_passed == 4);
            check(check_failed == 2);
            check(check_skipped == 1);
          });
        });
      });

      check_print_stats();
    }

You can also run this example by cloning this repository and running

    make

## Tips

`describe` and its aliases `context` and `it` are _meant_ to be nested as much
as required to make the tests, as well as the output easy to read and
understand.


## License

MIT License. (c) 2013 Utkarsh Kukreti.
