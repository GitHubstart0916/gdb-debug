#include "st.h"
#include "var.h"

st::st() {
    code = "#include<bits/stdc++.h>\n";
    //code += "struct date {\nint year;\nint month;\nint day;\n};\n";
    code += "struct date {\n"
    "int year;\n"
    "int month;\n"
    "int day;\n"
    "date(int y, int m, int d) {\n"
    "    year = y;\n"
    "    month = m;\n"
    "    day = d;\n"
    "};\n"
    "std::string to_string() {\n"
    "    std::string ret = std::to_string(year) + \"-\" + std::to_string(month) + \"-\" + std::to_string(day);\n"
    "    return ret;\n"
    "};\n"
    "};\n";
}

st::~st() {

}

int st::error_check() {
    return 0;
}

void st::init_var(std::string n, int v) {
    code += "int " + n + " = " + std::to_string(v) + ";\n";
}

void st::init_var(std::string n) {
    code += "int " + n + " = " + std::to_string(0) + ";\n";
}

void st::set_var(std::string name, int value) {
    code += name + " = " + std::to_string(value) + ";\n";
}

void st::print_var(std::string name) {
    code += "printf(\"%d\\n\", " + name + ");\n";
}

void st::def_main() {
    code += "int main() {\n";
}

void st::end_main() {
    code += "return 0;\n}";
}

void st::calc(std::string l, std::string r1, std::string op, std::string r2) {
    std::string ret = l + "=" + r1 + op + r2 + ";\n";
    code += ret;
}

void st::init_date(std::string name, int y, int m, int d) {
    std::string ret = "date " + name + "=" + \
                        "date(" + std::to_string(y) + ", " + \
                        std::to_string(m) + ", " + \
                        std::to_string(d) + ");\n";
    code += ret;
}

void st::print_date(std::string name) {
    std::string ret = "printf(\"%s\\n\", " + \
                    name + ".to_string().c_str());\n";
    code += ret;
}

void st::def_struct(std::string name, int cnt, ...) {
    va_list ap;
    cnt *= 2;
    va_start(ap, cnt);

    std::string ret = "struct " + name + "{\n";  
    //printf("%s\n", ret.c_str());
    for(int i = 0; i < cnt / 2; i++) {
        std::string t = va_arg(ap, char*);
        std::string n = va_arg(ap, char*);
        ret += t + " " + n + ";\n";
    }         
     
    ret += "};\n";
    code += ret;
    va_end(ap);
}

void st::decaler_struct(std::string type, std::string name) {
    code += type + " " + name + ";\n";
}

void st::set_struct_member(std::string var, std::string member, std::string value) {
    code += var + "." + member + "=" + value + ";\n";
}

void st::run() {
    
    const char* ret = code.c_str();
    FILE* out = fopen("trans.cpp", "w");
    //printf("%s\n", ret);
    fprintf(out, "%s", ret);
    fclose(out);
    
    #ifdef _WIN32
        //printf("%s\n", ret);
        system("g++ trans.cpp -o trans");
        system(".\\trans.exe");
        system("del .\\trans.cpp");
        system("del .\\trans.exe");
    #else
        system("g++ trans.cpp -o trans");
        system("./trans.exe");
        system("rm trans.cpp");
        system("rm trans.exe");
    #endif
}



