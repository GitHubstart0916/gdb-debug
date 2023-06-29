#include<bits/stdc++.h>
struct date {
    int year;
    int month;
    int day;
    date(int y, int m, int d) {
        year = y;
        month = m;
        day = d;
    };
    std::string to_string() {
        std::string ret = std::to_string(year) + "-" + std::to_string(month) + "-" + std::to_string(day);
        return ret;
    };
};

int main() {
    date a = date(2020, 1, 2);
    printf("%s\n", a.to_string().c_str());
}