#include "var.h"


var::var(std::string n, int v) {
    name = n;
    value = v;
}

int var::get_value() {
    //printf("value addr: %p\n", &(this->value));
    return value;
}

void var::set_value(int v) {
    this->value = v;
    //printf("value addr: %p\n", &(this->value));
}

/*var* var::clone() const {
    return new var(*this);
}*/


var::~var() {

}