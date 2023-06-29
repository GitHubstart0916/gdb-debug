#ifndef VAR_H
#define VAR_H


#include<string>

class var
{
private:
    std::string name;
    int value;
public:
    var(std::string, int value);
    int get_value();
    void set_value(int v);
    //var* clone() const;
    ~var();
};






#endif
