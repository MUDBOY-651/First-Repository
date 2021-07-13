#include<iostream>
#include<cstring>
#include<ctime>
#include<algorithm>
#include<queue>
#include "Team.h"   // 包含了Team类定义以及Match函数的定义
using namespace std;

// 主函数
int main(){
	srand((int)time(0)); // 初始化随机数种子
    char tn1[25],tn2[25];
    // 初始化双方球员姓名，也可采取输入的方式，这样做只是为了简化测试
    char nm1[5][25] = {"斯蒂夫·库里","克莱·汤普森","凯文·杜兰特","安德鲁·伊戈达拉","德莱蒙德·格林"};
    char nm2[5][25] = {"埃尔文·约翰逊","科比·布莱恩特","勒布朗·詹姆斯","安东尼·戴维斯","沙奎尔·奥尼尔"};
    int num1[5],num2[5];
    char op[15];
    printf("请输入BuildTeam进行球队创建:\n"); 
    while(1){
        scanf("%s",&op);
        if(strcmp(op,"BuildTeam") == 0){printf("输入成功！\n");break;}
        else printf("输入失败，请输入BuildTeam再次进行球队创建\n"); 
    }
    printf("现在开始主队创建...\n");
    Inputfun(nm1,num1,tn1);
    printf("现在开始客队创建...\n");
    Inputfun(nm2,num2,tn2);
    // 创建Team实例化对象
    Team team1(tn1,nm1[0],nm1[1],nm1[2],nm1[3],nm1[4],num1[0],num1[1],num1[2],num1[3],num1[4]);
    Team team2(tn2,nm2[0],nm2[1],nm2[2],nm2[3],nm2[4],num2[0],num2[1],num2[2],num2[3],num2[4]);
    // 进入Match函数，进行比赛
    Match(team1,team2);
    return 0;
}