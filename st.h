#ifndef ST_H
#define ST_H

#include<vector>
#include<map>
#include "var.h"

class st {
    public:
        std::vector<std::map<std::string, var>> single_table;
        int error_check();
};

int st::error_check(void) {
    return 0;
}


#endif