#include <stdio.h>

char player = 'x';  //定义棋子类型,x与o

char gamelist[3][3] = { {'-','-','-'},
                        {'-','-','-'},
                        {'-','-','-'} };    //定义井字棋二维数组

int print_vector2_list(int listlen1, int listlen2, char list[listlen1][listlen2]) {
    for (int i = 0; i < listlen1; i++) {
        for (int j = 0; j < listlen2; j++) {
            if (j != listlen2 - 1) {
                printf("%c ",list[i][j]);
            }
            if (j == listlen2 - 1) {
                printf("%c\n",list[i][j]);
            }
        }
    }
    return 1;
}   //打印数组[3][3]函数,成功则返回1

int compare_strings(const char* str1, const char* str2) {
    int if_ended = 0;
    int i = 0;

    while (if_ended == 0) {
        if (str1[i] != str2[i]) {
            return 0;
        }
        if (str1[i] == '\0') {
            if_ended = 1;
        }
        i += 1;
    }
    return 1;
}   //字符串对比函数,到\0空白符停止,相等返回1,不相等返回0

int change_list(int listlen1, int listlen2, int listnum1, int listnum2, char list[listlen1][listlen2], char code) {
    if (list[listnum1][listnum2] != '-') {
        return -1;
    } else if (code != 'x') {
        if (code != 'o') {
            return 0;
        }
    }

    list[listnum1][listnum2] = code;
    return 1;
}   //落子函数,若该地已落子则返回-1,未知棋子返回0,成功返回1

int checkwin_3_3(char list[3][3]) {
    if (list[0][0] == list[0][1] && list[0][1] == list[0][1] && list[1][1] != '-') {
        return 1;
    } else if (list[1][0] == list[1][1] && list[1][1] == list[1][2] && list[1][1] != '-') {
        return 1;
    } else if (list[2][0] == list[2][1] && list[2][1] == list[2][2] && list[2][1] != '-') {
        return 1;
    } else if (list[0][0] == list[1][0] && list[1][0] == list[2][0] && list[1][0] != '-') {
        return 1;
    } else if (list[0][1] == list[1][1] && list[1][1] == list[2][1] && list[1][1] != '-') {
        return 1;
    } else if (list[0][2] == list[1][2] && list[1][2] == list[2][2] && list[1][2] != '-') {
        return 1;
    } else if (list[0][0] == list[1][1] && list[1][1] == list[2][2] && list[1][1] != '-') {
        return 1;
    } else if (list[0][2] == list[1][1] && list[1][1] == list[2][0] && list[1][1] != '-') {
        return 1;
    }
    return 0;
}   //检查是否胜利函数,胜利返回1,失败返回零

int main() {    //main函数游戏主要逻辑
    while (1) {
        char input_string[20];  //用一个长20字节的char数组存储输入,目前找不到更好解决办法
        printf("& ");
        fflush(stdout);
        scanf("%s",input_string);

        if (compare_strings(input_string, "show") == 1) {    //判断输入字符串并执行相应操作
            print_vector2_list(3,3,gamelist);
        } else if (compare_strings(input_string, "exit") == 1) {
            return 0;
        } else if (compare_strings(input_string, "down") == 1) {    //落子部分
            int posnum1,posnum2;    //输入坐标
            printf("Posite(line column) -> ");
            scanf("%d %d",&posnum1,&posnum2);
            if ((posnum1 <= 3) && (posnum2 <= 3) && (posnum1 > 0) && (posnum2 > 0)) {   //防止越界
            int changetype = change_list(3, 3, posnum1 - 1, posnum2 - 1, gamelist, player);
            if (changetype == -1) {     //判断函数异常状况
                printf("alredy have that\n");
                fflush(stdout);
            } else if (changetype == 0) {
                printf("unknown chess\n");
                fflush(stdout);
            } else {
                printf("success\n");
                fflush(stdout);
                if (player == 'x') {
                    player = 'o';
                } else {
                    player = 'x';
                }
            }
            print_vector2_list(3,3,gamelist);   //打印确认
            }else {     //越界提示
                printf("unknown pos\n");
                fflush(stdout);
            }
            if (checkwin_3_3(gamelist) == 1) {  //这里检查完结是否胜利,若胜利就输出胜利者
                if (player == 'x') {
                    printf("O wins\n");
                    return 0;
                } else {
                    printf("X win\n");
                    return 0;
                }
            }
        } else if (compare_strings(input_string, "player")) {   //玩家棋子提示部分
            printf("next player is %c\n",player);
            fflush(stdout);
        } else {    //未知操作提示
            printf("unknown arg\n");
            fflush(stdout);
        }
    }
}