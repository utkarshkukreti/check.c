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

  // Print number of assertions, passed, skipped, and failed counts.
  check_print_stats();

  // Exit successfully if exactly 2 tests failed.
  return check_failed == 2 ? 0 : 1;
}
