#ifndef ST_H
#define ST_H

#include<vector>
#include<map>
//#include<initializer_list>
#include <stdarg.h>
#include "var.h"

class st {

    private:
        std::vector<std::map<std::string, var*>> single_table;
        std::string code;
    public:
        st();
        ~st();
        int error_check();
        void init_var(std::string name, int value);
        void init_var(std::string name);
        void set_var(std::string name, int value);
        void init_date(std::string name, int y, int m, int d);
        void print_var(std::string name);
        void print_date(std::string name);
        void def_main();
        void end_main();
        void calc(std::string l, std::string r1, std::string op, std::string r2);
        void def_struct(std::string name, int cnt, ...);
        void decaler_struct(std::string type, std::string name);
        void set_struct_member(std::string var, std::string member, std::string value);
        void run();

};


#endif