#include "var.h"


var::var(std::string name, int value) {
    var::name = name;
    var::value = value;
}

int var::get_value() {
    return var::value;
}

void var::set_value(int value) {
    var::value = value;
}

var::~var() {

}