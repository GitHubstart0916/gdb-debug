#ifndef ST_H
#define ST_H

#include<vector>
#include<map>
#include "var.h"

class st {

    private:
        std::vector<std::map<std::string, var*>> single_table;
    public:
        st();
        ~st();
        int error_check();
        void init_var(std::string name, int value);
        void init_var(std::string name);
        void set_var(std::string name, int value);
        void print_var(std::string name);

};


#endif