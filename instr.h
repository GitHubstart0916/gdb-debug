#ifndef INSTR_H
#define INSTR_H

enum binary_type { Add=1, Sub, Mul, Div, Mod};

class instr
{
private:
    /* data */
public:
    instr(/* args */);
    ~instr();
};

class binary: public instr {
    private:
        enum binary_type type;
    public:
        binary();
        ~binary();
};

#endif