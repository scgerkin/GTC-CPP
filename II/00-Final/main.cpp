#include "Simulator.h"

/**
 * Program entry point.
 */
int main() {
    Simulator simulator;

    try {
        simulator.start();
    }
    catch (const Simulator::QuitException &ex) {
        // do nothing, exiting program
    }

    return 0;
}