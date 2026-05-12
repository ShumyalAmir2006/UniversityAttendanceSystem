#pragma once
#include <string>
using namespace std;

class Login {
public:
    string username, password;
    bool   authenticated = false;
};
