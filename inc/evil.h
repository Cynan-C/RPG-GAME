#ifndef __EVIL_H__
#define __EVIL_H__

#include "role.h"

class evil{
public:
    evil(){}
    evil(int hp, int att, int crit):hp(hp), att(att), crit(crit){}
    evil(evil &a){
        this->hp = a.hp;
        this->att = a.att;
        this->crit = a.crit;
        cout << "haha" << endl;
    }
    ~evil(){}
    int attack(int a){
        int b = a + crit * 5;
        return b;
    }
    int hurt(int a){
        int b = this->hp - a;
        this->hp = b;
        return b;
    }
    int get_hp(){
        return this->hp;
    }
    int get_att(){
        return this->att;
    }
    int get_crit(){
        return this->crit;
    }
    void set_msg(int a, int b, float c){
        hp = a;
        att = b;
        crit = c;
    }
private:
    int hp;
    int att;
    float crit;  
};

#endif