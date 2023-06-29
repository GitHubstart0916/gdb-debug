#include "st.h"
#include "var.h"
int main() {
    //var a = var();
    //string str;

    //method 1
    /* st a = st();
    a.init_var("num", 10);
    a.print_var("num");
    a.init_var("num1", 111);
    a.print_var("num1");
    a.set_var("num", 20);
    a.print_var("num"); */

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

    //method 2
    st code = st();
    code.def_struct("node", 2, "int", "a", "int", "b");
    code.def_main();
    code.init_var("a", 1);
    code.init_var("b", 2);
    code.init_var("c");
    code.calc("c", "a", "+", "b");
    code.print_var("c");
    code.init_date("d", 2020, 1, 1);
    code.print_date("d");
    code.decaler_struct("node", "my_node");
    code.set_struct_member("my_node", "a", "10");
    code.print_var("my_node.a");
    code.set_struct_member("my_node", "b", "20");
    code.print_var("my_node.b");
    code.end_main();
    code.run();
    return 0;
}