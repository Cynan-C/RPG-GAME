#include "role.h"
#include "menu.h"

int main(){   
    swordman role1;
    archer role2;
    wizard role3;  
    menu m;
    map<string,list<obj>> m1;
    role1.init_obj(m1);            //initialize the objects of player
    int x = m.role_choice(role1, role2, role3);
    if(x == 1)
        m.show_main(role1, m1);
    else if(x == 2)
        m.show_main(role2, m1);
    else if(x == 3)
        m.show_main(role3, m1);
    else
        cout << "输入错误" << endl;
    return 0;
}