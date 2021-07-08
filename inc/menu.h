#ifndef __MENU_H__
#define __MENU_H__

#include "role.h"
#include "evil.h"

class menu{
public: 
    menu(){
        init_keyboard();     //initilize the keyboard  (please use Ubuntu!!!!!!)
    }
   ~menu(){
    close_keyboard();       //cancel the change of the keyboard 
   }
    int get_ket(){          //get the value of key
        kbhit();
        int key_num = readch();
        return key_num;
    }
    int select_ctrl1(int ctrl){     //change word type
        system("clear");            //clear the screen
        if(ctrl == 1)        cout << "\033[5;1;35m1.查看角色属性\033[0m\t2.查看装备栏\t3.进入地图\t4.退出" << endl;
        else if(ctrl == 2)   cout << "1.查看角色属性\t\033[5;1;35m2.查看装备栏\033[0m\t3.进入地图\t4.退出" << endl;
        else if(ctrl == 3)   cout << "1.查看角色属性\t2.查看装备栏\t\033[5;1;35m3.进入地图\033[0m\t4.退出" << endl;
        else if(ctrl == 4)   cout << "1.查看角色属性\t2.查看装备栏\t3.进入地图\t\033[5;1;35m4.退出\033[0m" << endl;
        return 0;
    }
    int select_ctrl2(int ctrl){
        system("clear"); 
        if(ctrl == 1)        cout << "\033[5;1;35m1.沼泽（简单）\033[0m\t2.黑暗森林（中等）\t3.魔塔（困难）\t4.离开" << endl;
        else if(ctrl == 2)   cout << "1.沼泽（简单）\033[5;1;35m\t2.黑暗森林（中等）\t\033[0m3.魔塔（困难）\t4.离开" << endl;
        else if(ctrl == 3)   cout << "1.沼泽（简单）\t2.黑暗森林（中等）\033[5;1;35m\t3.魔塔（困难）\t\033[0m4.离开" << endl;
        else if(ctrl == 4)   cout << "1.沼泽（简单）\t2.黑暗森林（中等）\t3.魔塔（困难）\t\033[5;1;35m4.离开\033[0m" << endl;
        return 0;
    }
    template<class T>
    int m_map(T &a){
        int ctrl=0;
        int out_symbol = 0;
        int exit_num = 0;
        int k = 0;
        while(!exit_num){
            ctrl = 0;
            k = 0;
            system("clear");
            cout << "1.沼泽（简单）\t2.黑暗森林（中等）\t3.魔塔（困难）\t4、离开"<< endl;
            while (1){
                k = this->get_ket();
                if(k == 68){                            //key "left"
                    ctrl--;
                    if(ctrl <= 0 )  ctrl=4; 
                    select_ctrl2(ctrl);
                }
                else if(k == 67){                       //key "right"
                    ctrl++; 
                    if(ctrl >=5 )   ctrl=1; 
                    select_ctrl2(ctrl);
                }
                else if(k==13){                         //key enter 
                    if(ctrl == 1)
                        marsh_fig(a);                   //fight around the marsh
                    else if(ctrl == 2)
                        dark_forest_fig(a);             //fight in dark forest
                    else if(ctrl == 3)
                        out_symbol = mag_tower_fig(a);  //fight in magic tower
                    else
                        exit_num = 1;
                    break;
                }
                if(out_symbol == 1)
                    return 1;            
            }
        }
    }
    template<class T1, class T2>
    void show_main(T1 &a, T2 &m1){
        int ctrl=0;
        int exit_num = 0;
        int k = 0;
        int out_symbol = 0;
        cout << endl;
        cout << "                 欢迎来到《挑战魔塔》"  << endl; 
        sleep(1);
        while(!exit_num){
            system("clear");
            cout << "1.查看角色属性\t2.查看装备栏\t3.进入地图\t4.退出"<< endl;
            ctrl = 0;
            k = 0;
            while (1){
                k=this->get_ket();              //get the key from keyboard
                if(k == 68){                    //key "left"
                    ctrl--;
                    if(ctrl <= 0 )  ctrl=4; 
                    select_ctrl1(ctrl);         //choose the function 
                }
                else if(k == 67){               //key "right"
                    ctrl++; 
                    if(ctrl >=5 )   ctrl=1; 
                    select_ctrl1(ctrl);
                }
                else if(k==13){                 //key "enter" 
                    if(ctrl == 1){
                        cout << "\033[34m=================角色属性=================\033[0m" << endl;
                        a.show();
                        cout << "\033[34m==========================================\033[0m" << endl;
                        sleep(2);
                    }
                    else if(ctrl == 2){
                        a.show_obj(m1);
                        sleep(1);
                    }
                    else if(ctrl == 3){
                        out_symbol = m_map(a); 
                        if(out_symbol == 1)
                            return;
                        sleep(1);
                    }
                    else{
                        cout << "退出" << endl;
                        sleep(1);
                        exit_num = 1;
                    }
                    break;
                }          
            }
        }
    }
    int role_choice(swordman &a,archer &b,wizard &c){
        string name;
        int role;
        close_keyboard();
        cout << "请输入您的用户名：";
        cin >> name;
        cout << "\
############游戏角色##############\n\
1、剑士\t2、弓箭手\t3、法师\n\
###################################\n\
您想选择的角色是(请输入数字)：";
        cin >> role;
        init_keyboard();
        if(role == 1){
            a.set_swordman_name(name);
            return 1;
        }
        else if(role == 2){
            b.set_archer_name(name);
            return 2;
        }
        else if(role == 3){
            c.set_archer_name(name);
            return 3;
        }
    }
    template<class T1, class T2>
    void solo(T1 &role1, T2 &evil1){    // role fight with evil
        int a, b;
        while(1){
            a = role1.attack();
            cout << "敌方受到" << a << "点伤害，还剩余" << evil1.hurt(a) << "点血量" << endl;
            if(evil1.get_hp() <= 0){
                int a = rand()%10 + 1;          //get the experience according to the difficulty
                if(evil1.get_crit() > 0)
                    a = a + 20 * evil1.get_crit();
                cout << "我方击败敌方，获胜，获得" << a << "点经验" <<endl;
                sleep(1);
                role1.add_exp(a);
                break;
            }
            b = (rand()%3 + 1);         //random value
            b = evil1.attack(b);
            cout << "我方受到" << b << "点伤害，还剩余" << role1.hurt(b) << "点血量" << endl;
            if(role1.get_hp() <= 0){
                cout << "我方阵亡，闯关失败" << endl;
                sleep(2);
                break;
            }
        }
    }
    template<class T>
    int marsh_fig(T &a){
        evil ee;
        int e_hp = 0;
        int e_att = 0;
        int e_crit = 0;
        int in = 0;
        int ran_meet = 0;
        close_keyboard();
        while(1){
            ran_meet = rand() % 10;
            e_hp = rand()%10;
            e_att = rand()%10;
            ee.set_msg(e_hp, e_att, e_crit);
            if(ran_meet < 3)
                cout << "正面遇到了一只野生小怪，是否与它对战？(1:是；2：否）" << endl;
            else if(ran_meet >= 3 && ran_meet < 5)
                cout << "出现了一只变异的小鳄鱼，是否与它对战？(1:是；2：否）" << endl;
            else
                cout << "出现了一群变异的未知昆虫，是否与它对战？(1:是；2：否）" << endl;
            cout << "我方等级：" << a.lev << "\t血量：" << a.hp << endl;
            cout << "敌方血量：" << ee.get_hp() << "\t攻击力：" << ee.get_att() << "暴击率：" << ee.get_crit() << endl;
            cin >> in;
            if(in == 1)
                solo(a, ee);
            else{
                cout << "逃离沼泽地" << endl;
                sleep(1);
                break;
            }
        }
        init_keyboard();  
    }
    template<class T>
    int dark_forest_fig(T &a){
        evil ee;
        int e_hp = 0;
        int e_att = 0;
        float e_crit = 0.3;
        int in;
        int ran_meet;
        close_keyboard();
        while(1){
            ran_meet = rand() % 4;
            e_hp = rand()%10 + 50;
            e_att = rand()%10 * 3;
            ee.set_msg(e_hp, e_att, e_crit);
            if(ran_meet < 2)
                cout << "身旁的一颗老橡树闪出一只暴走的鬣狗，是否与它对战？(1:是；2：否）" << endl;
            else
                cout << "听到“嘶嘶嘶”声，发现身后有一条散发糜肉味的巨蟒的在悄悄靠近，是否与它对战？(1:是；2：否）" << endl;
            cout << "我方等级：" << a.lev << "\t血量：" << a.hp << endl;
            cout << "敌方血量：" << ee.get_hp() << "\t攻击力：" << ee.get_att() << "暴击率：" << ee.get_crit() << endl;
            cin >> in;
            if(in == 1)
                solo(a, ee);
            else{
                cout << "逃离黑暗森林" << endl;
                sleep(1);
                break;
            }
        } 
        init_keyboard();  
    }
    template<class T>
    int mag_tower_fig(T &role1){
        evil evil1;
        int e_hp = 500;
        int e_att = 10;
        float e_crit = 0.5;
        int in;
        int ran_skill;
        int a, b;
        close_keyboard();
        evil1.set_msg(e_hp, e_att, e_crit);
        cout << "来到了毫无生机的魔塔，这里是所有玩家的噩梦，周围散布着挑战失败的玩家的骷髅，决定要进入这片禁地吗？(1:是；2：否）" << endl;
        cin >> in;
        if(in == 1){
            cout << "推开布满蜘蛛丝的大门，古老的大门发出低沉的响声，走了进去，看到五十米处有一 六米高、 披着破旧黑斗篷、 手拿十米镰刀的黑衣魔漂浮在半空中\n\t身后的大门已自动合上，你无路可退，只能选择在五秒后进入战斗" << endl;
            sleep(5);
        }
        else{
            cout << "逃离魔塔" << endl;
            close_keyboard();
            sleep(1);
            return 0;
        }
        while(1){
            a = role1.attack();
            cout << "敌方受到" << a << "点伤害，还剩余" << evil1.hurt(a) << "点血量" << endl;
            if(evil1.get_hp() <= 0){
                cout << "我方击败黑衣魔，获得胜利，闯关成功！游戏圆满结束！！！" <<endl;
                init_keyboard();
                sleep(3);
                return 1;   //the symbol of game over
            }
            ran_skill = rand()%10;
            if(ran_skill < 2){
                cout << "黑衣魔挥动镰刀发动普通攻击" << endl;
                b = e_att * e_crit * 4;
                cout << "我方受到" << b << "点伤害，还剩余" << role1.hurt(b) << "点血量" << endl;
            }
            else if(ran_skill >=2 && ran_skill < 7){
                cout << "黑衣魔隐身发动法术攻击" << endl;
                b = e_att * e_crit * 6;
                cout << "我方受到" << b << "点伤害，还剩余" << role1.hurt(b) << "点血量" << endl;
            }
            else if(ran_skill < 10){
                cout << "黑衣魔甩出五颗鬼火球发动绝招" << endl;
                b = e_att * e_crit * 10;
                cout << "我方受到" << b << "点伤害，还剩余" << role1.hurt(b) << "点血量" << endl;
            }
            if(role1.get_hp() <= 0){
                cout << "我方阵亡，闯关失败" << endl;
                sleep(2);
                init_keyboard();
                return 0;
            }   
        }
    }
};

#endif