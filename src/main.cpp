#include "Example.hpp"

int main() {
    Example e = Example();
    e.helloWorld();

    Example* e2 = new Example();
    e2->helloWorld();
}