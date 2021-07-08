#ifndef __1_H_
#define __1_H_

#include <map>
#include <list>
#include "init_key.h"
#include "obj.h"
using namespace std;

class player{
public:
    player(){}
    player(string name):id(name){

    }
    ~player(){}
    int get_ket(){
        kbhit();
        int key_num = readch();
        return key_num;
    }
    int select_ctrl3(int ctrl, map<string,list<obj>> &m1){
        system("clear"); 
        map<string,list<obj>>::iterator pm;
        if(ctrl == 1){
            for(pm = m1.begin(); pm != m1.end(); pm++){
                cout << "\033[34m*************" << pm->first << "*************\033[0m" << endl;
                cout << pm;
                cout << "\033[34m**********************************************\033[0m" << endl;
            }
            cout << "\033[5;1;35m退出\t\t\t\033[0m取物品" << endl;
        }       
        else if(ctrl == 2){
            for(pm = m1.begin(); pm != m1.end(); pm++){
                cout << "\033[34m*************" << pm->first << "*************\033[0m" << endl;
                cout << pm;
                cout << "\033[34m**********************************************\033[0m" << endl;
            }
            cout << "退出\t\t\t\033[5;1;35m取物品\033[0m" << endl;
        }   
        return 0;
    }
    int select_ctrl4(int ctrl, map<string,list<obj>> &m1){
        system("clear"); 
        map<string,list<obj>>::iterator pm;
        if(ctrl == 1){
            cout << "想要打开哪个柜子？" << endl;
            cout << "\033[5;1;35m1、消耗品；\033[0m2、装备" << endl;
        }       
        else if(ctrl == 2){
            cout << "想要打开哪个柜子？" << endl;
            cout << "1、消耗品；\033[5;1;35m2、装备\033[0m" << endl;
        }   
        return 0;
    }
    void show(){
        cout << "\t\tid:" << id << endl;
        cout << "\t\thp:" << hp << endl;
        cout << "\t\tatt:" << att << endl;
        cout << "\t\texp:" << exp << endl;
        cout << "\t\tlev:" << lev << endl;
    }
    void init_obj(map<string,list<obj>> &m1){
        list<obj> l1;
        l1.push_back(obj("红药水",10));
        l1.push_back(obj("蓝药水",1));
        list<obj> l2;
        l2.push_back(obj("尚方宝剑",1));
        l2.push_back(obj("小刀",2));   
        pair<string, list<obj>> p1 = {"消耗品", l1};
        pair<string, list<obj>> p2;
        p2.first = "装备";
        p2.second = l2;   
        map<string,list<obj>>::iterator pm;
        pm = m1.begin();
        pm = m1.insert(pm, p1);
        m1.insert(pm, p2);
    }
    void show_obj(map<string,list<obj>> &m1){
        map<string,list<obj>>::iterator pm;
        int ctrl = 0;
        int k = 0;
        int exit_num = 0;
        while(!exit_num){
            ctrl = 0;
            k = 0;
            system("clear");
            for(pm = m1.begin(); pm != m1.end(); pm++){
                cout << "\033[34m*************" << pm->first << "*************\033[0m" << endl;
                cout << pm;
                cout << "\033[34m**********************************************\033[0m" << endl;
            }
            cout << "退出\t\t\t取物品" << endl;
            while (1){
                k = this->get_ket();
                if(k == 68){                            //key "left"
                    ctrl--;
                    if(ctrl <= 0 )  ctrl=2; 
                    select_ctrl3(ctrl, m1);
                }
                else if(k == 67){                       //key "right"
                    ctrl++; 
                    if(ctrl ==3 )   ctrl=1; 
                    select_ctrl3(ctrl, m1);
                }
                else if(k == 13){                       //key "enter" 
                    if(ctrl == 1)
                        exit_num = 1;                   //choose to exit the object menu
                    else if(ctrl == 2){
                        take_obj(m1);                   //choose to take objects
                        exit_num = 1;
                    }    
                    break;
                } 
            }
        }
    }
    void take_obj(map<string,list<obj>> &m1){
        int v_thing1 = 0;
        int v_thing2 = 0;
        int thing_num = 0;
        int ctrl = 0;
        int k = 0;
        int v_thing11 = 0;
        list<obj>::iterator lp;
        map<string,list<obj>>::iterator pm;
        while(1){
            ctrl = 0;
            k = 0;
            system("clear");
            cout << "想要打开哪个柜子？" << endl;
            cout << "1、消耗品；2、装备" << endl;
            while (1){
                k = this->get_ket();
                if(k == 68){                            //key "left"
                    ctrl--;
                    if(ctrl <= 0 )  ctrl=2; 
                    select_ctrl4(ctrl, m1);
                }
                else if(k == 67){                       //key "right"
                    ctrl++; 
                    if(ctrl == 3 )   ctrl=1; 
                    select_ctrl4(ctrl, m1);
                }
                else if(k == 13){                       //key "enter" 
                    if(ctrl == 1){
                        pm = m1.begin();
                        lp = m1["消耗品"].begin();
                        cout << pm;
                        cout << "想要取出什么？（填数字）:";
                        close_keyboard();
                        cin >> v_thing11;
                        init_keyboard(); 
                        if(v_thing11 > m1["消耗品"].size()){
                            cout << "不存在该物品" << endl;
                            sleep(2);
                            return;
                        }
                        else{
                            for (int i = 0; i < (v_thing11-1) ;i++)
                                ++lp;
                            if(lp->get_num() == 0){
                                cout << lp->get_name() << "已用完,无法取出" << endl;
                                return;
                            }
                            thing_num = lp->get_num() - 1;
                            cout << "已取出" << lp->get_name() << endl;
                            lp->set_num(thing_num);
                            if(v_thing11 == 1){
                                hp += 100;
                                cout << "血量增加了100点，现在的血量为：" << hp << endl;
                            }
                            else if(v_thing11 == 2){
                                att += 10;
                                cout << "攻击力增加了10点，现在的攻击力为：" << att << endl;
                            }
                            sleep(2);
                        }
                    }
                    else if(ctrl == 2){
                        pm = ++(m1.begin());
                        lp = m1["装备"].begin();
                        cout << pm;
                        cout << "想要取出什么？（填数字）:";
                        close_keyboard();
                        cin >> v_thing11;
                        init_keyboard(); 
                        if(v_thing11 > m1["装备"].size()){
                            cout << "不存在该物品" << endl;
                            sleep(2);
                            return;
                        }
                        else{
                            for (int i = 0; i < (v_thing11-1) ;i++)
                                ++lp;
                            if(lp->get_num() == 0){
                                cout << lp->get_name() << "已用完,无法取出" << endl;
                                return;
                            }
                            thing_num = lp->get_num() - 1;
                            cout << "已取出" << lp->get_name() << endl;
                            lp->set_num(thing_num);
                            if(v_thing11 == 1){
                                int tmp = att;
                                tmp += 200;
                                att = tmp;
                                cout << "攻击力增加了200点,现在的攻击力为：" << att << endl;
                            }
                            else if(v_thing11 == 2){
                                int tmp = att;
                                tmp += 20;
                                att = tmp;
                                cout << "攻击力增加了20点，现在的攻击力为：" << att << endl;
                            }
                            sleep(2);
                        }
                    }               
                    return;
                } 
            }
        }
    }
    void set_name(const string &name){
        id = name;
    }
    void set_exp(int a){
        exp = a;
    }
    void set_lev(int a){
        lev = a;
    }
    void set_hp(int a){
        hp = a;
    }
    void set_att(int a){
        att = a;
    }
    void set_hon(string a){
        hon = a;
    }
    int get_hp(){
        return this->hp;
    }
    int get_att(){
        return att;
    }
    int get_exp(){
        return exp;
    }
    int get_lev(){
        return lev;
    }
    string get_hon(){
        return hon;
    }
private:
    string id;          //name
    string hon;         //honor
    int hp = 100;       //blood (hit point)
    int att = 10;       //basic attack
    int exp = 0;        //experience
    int lev = 0;        //level

    friend class menu;
    // friend ostream& operator<<(ostream& out, list<obj>::iterator &lp);
};
class swordman:public player{       // swordman
public:
    swordman(){}
    swordman(const string &name):player(name){
    }
    ~swordman(){}
    void show(){
        player::show();
        cout << "\t\tstrength:" << strength << endl;
    }
    swordman *point(){
        return this;
    }
    void set_swordman_name(string name){
        this->set_name(name);
    }
    int attack(){
        int b = this->get_att() + (10 * strength);
        return b;
    }
    int hurt(int a){
        int b = this->get_hp() - a;
        set_hp(b);
        return b;
    }
    int get_strength(){
        return strength;
    }
    void add_exp(int a){
        int v_exp = get_exp() + a;
        int v_lev = get_lev();
        int v_hp = get_hp();
        int v_att = get_att();
        int n = v_exp / 10;
        if(n > 0){                  //level up
            v_exp -= n * 10;
            v_hp += n * 100;        //improve abillity
            v_att += n * 10;
            this->strength += n;   
            for (int i = 0; i < n ;i++)
                ++v_lev;
            set_lev(v_lev);             //update level 
            set_exp(v_exp);         //update exp
            set_hp(v_hp);
            set_att(v_att);
            cout << "我方升级了！现在等级为:LV." << get_lev() << endl;
            if(get_lev() == 1){
                set_hon("初级玩家");
                cout << "恭喜您成为" << get_hon() << endl;
            }
            else if(get_lev() == 5){
                set_hon("中级玩家");
                cout << "恭喜您成为" << get_hon() << endl;
            }
            else if(get_lev() == 10){
                set_hon("高级玩家");
                cout << "恭喜您成为" << get_hon() << endl;
            }
            else if(get_lev() == 20){
                set_hon("终级玩家");
                cout << "恭喜您成为" << get_hon() << endl;
            }
            cout << "血量增加" << n * 10 << "点" << endl;
            cout << "攻击力增加" << n * 10 << "点" << endl;
            cout << "力气增加" << n << "点" << endl;
            cout << "现在的血量值为：" << get_hp() << "\t力量值为：" << strength << "\t基本攻击力为：" << get_att() << endl;
            sleep(3);
    }
        else
            set_exp(v_exp);
    }
private:
    int strength = 1;  
    friend class menu;
};
class archer:public player{        
public: 
    archer(){}
    archer(const string &name):player(name){}
    ~archer(){}
    void show(){
        player::show();
        cout << "\t\tprecision:" << precision << endl;
    }
    void set_archer_name(string name){
        this->set_name(name);
    }
    int attack(){
        int b = this->get_att() + (10 * precision);
        return b;
    }
    int hurt(int a){
        int b = this->get_hp() - a;
        set_hp(b);
        return b;
    }
    int get_strength(){
        return precision;
    }
    void add_exp(int a){
        int v_exp = get_exp() + a;
        int v_lev = get_lev();
        int v_hp = get_hp();
        int v_att = get_att();
        int n = v_exp / 10;
        if(n > 0){                  //level up
            v_exp -= n * 10;
            v_hp += n * 100;        //improve abillity
            v_att += n * 10;
            this->precision += n;   
            for (int i = 0; i < n ;i++)
                ++v_lev;
        set_lev(v_lev);             //update level 
            set_exp(v_exp);         //update exp
            set_hp(v_hp);
            set_att(v_att);
            cout << "我方升级了！现在等级为:LV." << get_lev() << endl;
            if(get_lev() == 1){
                set_hon("初级玩家");
                cout << "恭喜您成为" << get_hon() << endl;
            }
            else if(get_lev() == 5){
                set_hon("中级玩家");
                cout << "恭喜您成为" << get_hon() << endl;
            }
            else if(get_lev() == 10){
                set_hon("高级玩家");
                cout << "恭喜您成为" << get_hon() << endl;
            }
            else if(get_lev() == 20){
                set_hon("终级玩家");
                cout << "恭喜您成为" << get_hon() << endl;
            }
            cout << "血量增加" << n * 10 << "点" << endl;
            cout << "攻击力增加" << n * 10 << "点" << endl;
            cout << "射击精准度增加" << n << "点" << endl;
            cout << "现在的血量值为：" << get_hp() << "\t射击精准度为：" << precision << "\t基本攻击力为：" << get_att() << endl;
            sleep(3);
    }
        else
            set_exp(v_exp);
    }
private:
    int precision = 1;  
    friend class menu;
};
class wizard:public player{         
public: 
    wizard(){}
    wizard(const string &name):player(name){

    }
    ~wizard(){}
    void show(){
        player::show();
        cout << "\t\tmagic:" << magic << endl;
    }
    void set_archer_name(string name){
        this->set_name(name);
    }
    int attack(){
        int b = this->get_att() + (10 * magic);
        return b;
    }
    int hurt(int a){
        int b = this->get_hp() - a;
        set_hp(b);
        return b;
    }
    int get_strength(){
        return magic;
    }
    void add_exp(int a){
        int v_exp = get_exp() + a;
        int v_lev = get_lev();
        int v_hp = get_hp();
        int v_att = get_att();
        int n = v_exp / 10;
        if(n > 0){                  //level up
            v_exp -= n * 10;
            v_hp += n * 100;        //improve abillity
            v_att += n * 10;
            this->magic += n;   
            for (int i = 0; i < n ;i++)
                ++v_lev;
        set_lev(v_lev);             //update level 
            set_exp(v_exp);         //update exp
            set_hp(v_hp);
            set_att(v_att);
            cout << "我方升级了！现在等级为:LV." << get_lev() << endl;
            if(get_lev() == 1){
                set_hon("初级玩家");
                cout << "恭喜您成为" << get_hon() << endl;
            }
            else if(get_lev() == 5){
                set_hon("中级玩家");
                cout << "恭喜您成为" << get_hon() << endl;
            }
            else if(get_lev() == 10){
                set_hon("高级玩家");
                cout << "恭喜您成为" << get_hon() << endl;
            }
            else if(get_lev() == 20){
                set_hon("终级玩家");
                cout << "恭喜您成为" << get_hon() << endl;
            }
            cout << "血量增加" << n * 10 << "点" << endl;
            cout << "攻击力增加" << n * 10 << "点" << endl;
            cout << "法力增加" << n << "点" << endl;
            cout << "现在的血量值为：" << get_hp() << "\t法力值为：" << magic << "\t基本攻击力为：" << get_att() << endl;
            sleep(3);
    }
        else
            set_exp(v_exp);
    }
private:
    int magic = 1;  
    friend class menu;
};

ostream& operator<<(ostream &out, map<string,list<obj>>::iterator &p){
    list<obj>::iterator lp = p->second.begin();
    int i = 1;
    for ( ; lp != p->second.end() ; lp++){
        cout << i << "、" << lp->name << ":" << lp->num << "个" << endl;
        i++;
    }   
}


#endif