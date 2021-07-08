#ifndef __OBJ_H__
#define __OBJ_H__

#include "role.h"

class obj{
public:
    obj(){}
    obj(string name, int num):name(name),num(num){}
    string get_name(){
        return name;
    }
    int get_num(){
        return num;
    }
    void set_num(int a){
        num = a;
    }
    ~obj(){}
private:
    string name;
    int num;
    friend ostream& operator<<(ostream &out, map<string,list<obj>>::iterator &p);
};

#endif