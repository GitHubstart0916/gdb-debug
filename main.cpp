#include "st.h"
#include "var.h"
int main() {
    //var a = var();
    //string str;
    st a = st();
    a.init_var("num", 10);
    a.print_var("num");
    a.init_var("num1", 111);
    a.print_var("num1");
    a.set_var("num", 20);
    a.print_var("num");

    /*std::vector<var> v;
    v.push_back(var("name1", 10));
    v.push_back(var("name2", 20));

    printf("%d %d\n", v[0].get_value(), v[1].get_value());
    v[0].set_value(1);
    v[1].set_value(2);
    
    printf("%d %d\n", v[0].get_value(), v[1].get_value());*/
    

    /*var a = var("num", 10);
    printf("%d\n", a.get_value());
    a.set_value(20);
    printf("%d\n", a.get_value());*/
    return 0;
}