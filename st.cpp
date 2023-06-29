#include "st.h"
#include "var.h"

st::st() {
    single_table.clear();
    std::map<std::string, var*> main_table;
    single_table.push_back(main_table);
}

st::~st() {

}

int st::error_check() {
    return 0;
}

void st::init_var(std::string n, int v) {
    var *ret = new var(n, v);
    //printf("%p\n", ret);
    single_table[single_table.size() - 1].insert(std::pair<std::string, var*>(n, ret));
}

void st::init_var(std::string n) {
    var *ret = new var(n, 0);
    single_table[single_table.size() - 1].insert(std::pair<std::string, var*>(n, ret));

}

void st::set_var(std::string name, int value) {
    std::map<std::string, var*> table = single_table[single_table.size() - 1];
    std::map<std::string, var*>::iterator iter;
    iter = table.find(name);
    //iter is temp value
    //
    if (iter == table.end()) {
        printf("error: var undefine\n");
    } else {
        table[name];
        iter->second->set_value(value);
        //var *t = &(iter->second);
        //t->set_value(value);
        //table.erase(iter);
        //table.insert()
        //printf("%p %d\n", iter->second, iter->second->get_value());
        //t.set_value(value);
        //table[name] = t;
    }
}

void st::print_var(std::string name) {
    std::map<std::string, var*> table = single_table[single_table.size() - 1];
    std::map<std::string, var*>::iterator iter;
    iter = table.find(name);
    if (iter == table.end()) {
        printf("error: var undefine\n");
    } else {
        printf("%d\n", iter->second->get_value());
    }
    
}

