#include "Demonstration.h"

/**
 * Entry point for program.
 */
int main() {
    Demonstration demonstration;
    try {
        demonstration.start();
    }
    catch (const Demonstration::QuitException &ex) {
        // do nothing.
    }
    return 0;
}