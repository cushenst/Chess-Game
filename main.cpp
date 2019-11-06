#include <iostream>
#include "application.h"
int main() {
    application *myapp = new application();
    if (myapp->test() == 0) {
        std::cout << "All tests Passed\n";
        myapp->run();
    }
    delete myapp;
}