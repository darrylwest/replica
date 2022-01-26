#include <division.h>
#include <iostream>

using namespace std;

static const char *const HEADER = "\nReplica © 2022 Rain City Software.\n\n";
static const char *const USAGE = "Usage:\n\treplica ...";

int main(int argc, const char *argv[]) {
  Fraction f;

  cout << HEADER;

  // ensure the correct number of parameters are used.
  if (argc > 0) {
    cout << USAGE;
    return 1;
  }

  return 0;
}
