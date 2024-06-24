#include <iostream>
#include <stdexcept>

void someFunctionThatMightCrash() {
    std::cerr << "Entering function that might crash.\n";
    // Simulate a crash
    throw std::runtime_error("Simulated crash");
    std::cerr << "This message will not be printed.\n";
}

int main() {
    std::cerr << "Starting the program.\n";
    try {
        someFunctionThatMightCrash();
    } catch (const std::exception &e) {
        std::cerr << "Caught exception: " << e.what() << '\n';
    }
    std::cerr << "Program continues after handling the exception.\n";
    return 0;
}
