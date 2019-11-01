#include <iostream>
#include "application.h"

int main() {
    application *myapp = new application();
    myapp->run();
    delete myapp;
}