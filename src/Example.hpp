#ifndef CANDIDATE_HPP
#define CANDIDATE_HPP

#include <iostream>
using namespace std;

class Example {
    public:
        Example() {cout << "in constructor\n";}
        ~Example() {cout << "in destructor\n";}
        void helloWorld();
};

#endif