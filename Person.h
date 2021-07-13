#include<iostream>
#include<cstring>
#include<ctime>
#include<algorithm>
#include<vector>
#include<iomanip>
#include<queue>
#include "Function_set.h"   // 载入装有普通函数的头文件
using namespace std;

char posname[5][5] = {"PG","SG","SF","PF","C"};

// 定义Person类
class Person{
protected:
    char name[25];      // 姓名
    char position[15];      // 球员位置
    int age,FG,FG_3P;       // age年龄，FG进球数，FG_3P三分进球数
    int FG_2P,number,AST;   // FG_2P两分进球数，,number球员号码，AST助攻
    int REB,TT_2P,TT_3P;    // REB篮板，TT_2P两分球出手数，TT_3P三分球出手数
    int BLK,PTS;    // BLK盖帽，PTS得分
    int FT,TT_FT,height,weight; // FT罚球命中数，TT_FT罚球出手数，height身高，weight体重
    double FGP,FTP;         // FGP投篮命中率，FTP罚球命中率
    double FG_2P_Rate,FG_3P_Rate;   // FG_2P_Rate两分球命中率，FG_3P_Rate三分球命中率
    PII mvp_rate;       // 存取比赛评价值，用于计算MVP
    Doubles doubles;        // 记录球员是否获得两双
public:
    Person(char *nm);
    // 以下成员函数目的均为获取相应数据成员
    Doubles get_doubles();
    int total_fg(); // 总命中数
    int total_fg_made();    // 总出手数
    int fg_2p();    // 两分球进球数
    int fg_3p();    // 三分球进球数
    int fg_2p_made();       // 两分球出手数
    int fg_3p_made();       // 三分球出手数
    int score();        // 得分
    int rebound();      // 篮板
    int block();        // 盖帽
    int assist();       // 助攻
    int freethrow();    // 罚球命中数
    int total_freethrow();      // 罚球出手数
    int getnum();       // 获取球员号码
    void cal_mvp_rate();        // 获取球员比赛评价
    void Show();        // 展示球员的基本信息1
    void ShowMVP();     // 当球员获得MVP时展示信息
    void ShowStandard();        // 展示球员的基本信息2
};

// 后卫类
class Guard:public Person{
public:
    Guard(char*,int,char*);
};

// 锋线类
class Forward:public Person{
public:
    Forward(char*,int,char*);
}; 

// 中锋类
class Center:public Person{
public:
    Center(char*,int,char*);
};

Person::Person(char nm[])
{
    strcpy(name, nm);
    age = getrand(20, 33);
}

// 球员获得MVP时的展示函数
void Person::ShowMVP()
{
    printf("本场比赛MVP获得者是%s! 比赛评价为%.2f", name,mvp_rate.first);
    printf("(%.2f = %d*0.7 + 0.1*(%d + %d + %d))!\n",mvp_rate.first,REB,BLK,PTS,AST);
    PrintStandard();
    ShowStandard();
}

// 显示球员数据
void Person::Show()
{
    Output(name, 21);
    Output(number, 8);
    Output(PTS, 5);
    Output(REB, 4);
    Output(AST, 5);
    Output(BLK, 5);
    putstats(FT, TT_FT);
    putstats(FG_2P, TT_2P);
    putstats(FG_3P, TT_3P);
    putstats(FG, TT_2P + TT_3P);
    printf("%-6.1f", FTP);
    printf("%-6.1f", FG_2P_Rate);
    printf("%-6.1f", FG_3P_Rate);
    printf("%-6.1f", FGP);
    cout << endl;
}

// 计算球员评价
void Person::cal_mvp_rate()
{
    mvp_rate.first = PTS * 0.7 + 0.1 * (BLK + PTS + AST);
    mvp_rate.second = number;
    heap.push(mvp_rate);
}

// 展示球员基本信息
void Person::ShowStandard(){
    Output(name, 21);
    Output(height, 3); printf("cm  ");
    Output(weight, 3); printf("kg  ");
    Output(age, 4);
    Output(number, 8);
    Output(PTS, 5);
    Output(REB, 4);
    Output(AST, 5);
    Output(BLK, 5);
    putstats(FT, TT_FT);
    putstats(FG_2P, TT_2P);
    putstats(FG_3P, TT_3P);
    putstats(FG, TT_2P + TT_3P);
    printf("%-6.1f", FTP);
    printf("%-6.1f", FG_2P_Rate);
    printf("%-6.1f", FG_3P_Rate);
    printf("%-6.1f", FGP);
    cout << endl;
}

Doubles Person::get_doubles(){ return doubles; }
// 总命中数
int Person::total_fg() { return FG_2P + FG_3P; }
// 总出手数
int Person::total_fg_made() { return TT_2P + TT_3P; }
// 两分球命中数
int Person::fg_2p() { return FG_2P; }
// 三分球命中数
int Person::fg_3p() { return FG_3P; }
// 两分球出手数
int Person::fg_2p_made() { return TT_2P; }
// 三分球出手数
int Person::fg_3p_made() { return TT_3P; }
// 得分
int Person::score() { return PTS; }
// 篮板
int Person::rebound() { return REB; }
// 盖帽
int Person::block() { return BLK; }
// 助攻
int Person::assist() { return AST; }
// 罚球命中数
int Person::freethrow() { return FT; }
// 罚球出手数
int Person::total_freethrow() { return TT_FT; }
// 球衣号码
int Person::getnum() { return number; }

//
//  仅对以下一个类进行注释，其他的类结构相似，只是随机数范围不同~
//

// Guard类构造函数
Guard::Guard(char nm[], int num, char pos[15]) : Person(nm)
{
    number = num;
    strcpy(position, pos);
    // 以下两个if判断球员属于PG还是SG
    if (strcmp(position, "PG") == 0)
    {
        height = getrand(185, 195);
        weight = getrand(82, 91);
    }
    if (strcmp(position, "SG") == 0)
    {
        height = getrand(191, 201);
        weight = getrand(92, 99);
    }
    // 对各个数据依靠球员位置不同进行个性化赋值
    FG_2P = getrand(0, 7);
    FG_3P = getrand(0, 7);
    FG = FG_2P + FG_3P;
    TT_2P = getrand(FG_2P, 13);
    TT_3P = getrand(FG_3P, 9);
    FT = getrand(0, 8);
    TT_FT = getrand(FT, FT + 2);
    AST = getrand(4, 14);
    REB = getrand(1, 11);
    BLK = getrand(0, 2);
    PTS = 2 * FG_2P + 3 * FG_3P + FT;
    cal_doubles(PTS, AST, REB, doubles,existdd,existtd);
    // 以下是对当出手数为0（命中率计算时，分母为0时）的一些特殊处理
    if ((TT_2P + TT_3P) == 0)// 如总出手数= 三分出手数+两分出手数 = 0时，将命中率直接赋值0，避免了除0的情况
        FGP = 0;
    else
        FGP = 100 * divnum(FG, TT_2P + TT_3P);
    if (TT_FT == 0)
        FTP = 0;
    else
        FTP = 100 * divnum(FT, TT_FT);
    if (TT_2P == 0)
        FG_2P_Rate = 0;
    else
        FG_2P_Rate = 100 * divnum(FG_2P, TT_2P);
    if (TT_3P == 0)
        FG_3P_Rate = 0;
    else
        FG_3P_Rate = 100 * divnum(FG_3P, TT_3P);
}

// Forward构造函数
Forward::Forward(char nm[], int num, char pos[15]) : Person(nm)
{
    number = num;
    strcpy(position, pos);
    if (strcmp(position, "SF") == 0)
    {
        height = getrand(201, 206);
        weight = getrand(102, 105);
    }
    if (strcmp(position, "PF") == 0)
    {
        height = getrand(205, 210);
        weight = getrand(106, 110);
    }
    // 对各个数据依靠球员位置不同进行个性化赋值
    FG_2P = getrand(0, 9);
    FG_3P = getrand(0, 5);
    FG = FG_2P + FG_3P;
    TT_2P = getrand(FG_2P, 14);
    TT_3P = getrand(FG_3P, 5);
    FT = getrand(0, 8);
    TT_FT = getrand(FT, FT + 3);
    AST = getrand(1, 12);
    REB = getrand(2, 14);
    BLK = getrand(0, 3);
    PTS = 2 * FG_2P + 3 * FG_3P + FT;
    cal_doubles(PTS, AST, REB, doubles,existdd,existtd);
    // 以下是对当出手数为0（命中率计算时，分母为0时）的一些特殊处理
    if ((TT_2P + TT_3P) == 0)   // 如总出手数= 三分出手数+两分出手数 = 0时，将命中率直接赋值0，避免了除0的情况
        FGP = 0;
    else
        FGP = 100 * divnum(FG, TT_2P + TT_3P);
    if (TT_FT == 0)
        FTP = 0;
    else
        FTP = 100 * divnum(FT, TT_FT);
    if (TT_2P == 0)
        FG_2P_Rate = 0;
    else
        FG_2P_Rate = 100 * divnum(FG_2P, TT_2P);
    if (TT_3P == 0)
        FG_3P_Rate = 0;
    else
        FG_3P_Rate = 100 * divnum(FG_3P, TT_3P);
}

// Center类构造函数
Center::Center(char nm[], int num, char pos[15]) : Person(nm)
{
    int cnt = 0;
    number = num;
    strcpy(position, pos);
    height = getrand(210, 220);
    weight = getrand(110, 125);
    FG_2P = getrand(2, 10);
    FG_3P = getrand(0, 3);
    FG = FG_2P + FG_3P;
    TT_2P = getrand(FG_2P, 14);
    TT_3P = getrand(FG_3P + 1, 4);
    FT = getrand(4, 8);
    TT_FT = getrand(FT, FT + 4);
    AST = getrand(2, 10);
    REB = getrand(4, 16);
    BLK = getrand(0, 4);
    PTS = 2 * FG_2P + 3 * FG_3P + FT;
    cal_doubles(PTS, AST, REB, doubles,existdd,existtd);
    if ((TT_2P + TT_3P) == 0)
        FGP = 0;
    else
        FGP = 100 * divnum(FG, TT_2P + TT_3P);
    if (TT_FT == 0)
        FTP = 0;
    else
        FTP = 100 * divnum(FT, TT_FT);
    if (TT_2P == 0)
        FG_2P_Rate = 0;
    else
        FG_2P_Rate = 100 * divnum(FG_2P, TT_2P);
    if (TT_3P == 0)
        FG_3P_Rate = 0;
    else
        FG_3P_Rate = 100 * divnum(FG_3P, TT_3P);
}
