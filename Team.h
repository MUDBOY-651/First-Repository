#include <iostream>
#include <cstring>
#include <ctime>
#include <algorithm>
#include <queue>
#include <vector>
#include <windows.h>
#include "Person.h"
using namespace std;

// 球队类
class Team
{
private:
    Guard PG, SG;       // PG 控球后卫球员 SG 得分后卫球员
    Forward SF, PF;     // SF 小前锋球员 PF 大前锋球员 
    Center C;       // 中锋球员
    char team_name[25];     // 球队名称
    // PTS 得分 REB 篮板 AST 助攻 BLK 盖帽
    int PTS, REB, AST, BLK;
    // FT 罚球命中数 FG 投篮命中数  FG_2P 两分球命中数 FG_3P 三分球命中数
    int FT, FG, FG_2P, FG_3P;
    //TT_FG 总出手数  TT_2P 两分球出手数 TT_3P 三分球出手数 TT_FT 总罚球出手数
    int TT_FG, TT_2P, TT_3P, TT_FT;
    // FGP 投篮命中率 FTP罚球命中率 FG_2P_Rate两分球命中率 FG_3P_Rate三分球命中率
    double FGP, FTP, FG_2P_Rate, FG_3P_Rate;
public:
    Team(char tn[], char nm1[], char nm2[], char nm3[], char nm4[], char nm5[],
         int num1, int num2, int num3, int num4, int num5);
    char* get_team_name();
    // 获取球队总得分
    int score();
    // 总命中数
    int total_fg();
    // 总出手数
    int total_fg_made();
    // 两分球命中数
    int fg_2p();
    // 三分球命中数
    int fg_3p();
    // 两分球出手数
    int fg_2p_made();
    // 三分球命中数
    int fg_3p_made();
    // 篮板数
    int rebound();
    // 盖帽数
    int block();
    // 助攻
    int assist();
    // 罚球命中数
    int freethrow();
    // 罚球出手数
    int total_freethrow();
    // 返回MVP球员号码
    void ShowMVP();
    // 计算该队球员比赛评价
    void cal_mvp();
    // 显示球队数据
    void Show();
    // 显示球队两双球员数据
    void ShowDD();
    // 显示球队三双球员数据
    void ShowTD();
};

// 执行比赛普通函数
void Match(Team &team1, Team &team2)
{

    int Ball = getrand(0, 1);
    if (Ball == 0)
        cout << team1.get_team_name() << "获得开球球权!\n";
    else
        cout << team2.get_team_name() << "获得开球球权!\n";
    int pt1 = 0, pt2 = 0, home_score = team1.score(), away_score = team2.score();

    // 小节执行
    for (int i = 1; i <= 4; i++)
    {
        cout << "第" << i << "节比赛进行中...\n";
        Sleep(2000);        // Sleep 函数增加趣味
        pt1 += team1.score() / getrand(4, 5);
        pt2 += team2.score() / getrand(4, 5);
        if(pt1 < pt2) pt1 += getrand(2,6);
        else pt2 += getrand(2,6);
        if (pt1 >= team1.score())
            pt1 -= getrand(5, 15);
        if (pt2 >= team2.score())
            pt2 -= getrand(5, 15);

        // 对第四节比赛特殊处理
        if (i != 4)
            printf("第%d节比赛结束,%s-%s: %d-%d\n",i,team1.get_team_name(),team2.get_team_name(),pt1,pt2);
        else{
            Sleep(1000);
            cout << "第" << i << "节比赛结束，全场比赛结束!\n";
        }
    }
    Sleep(1000);
    cout << "主客队比分为:" << team1.score() << '-' << team2.score() << endl;
    Sleep(1000);

    Gethelp();
    // 查询系统执行
    while (1)
    {
        string op;      // 定义操作指令
        op = "";        // 初始化操作指令
        cin >> op;
        Sleep(2000);
        if (op == "/Quit")      // Quit 退出程序
            break;
        else if (op == "/HomeTeamStats")    // 查询主队数据
            team1.Show();
        else if (op == "/AwayTeamStats")    // 查询客队数据
            team2.Show();
        else if (op == "/ShowMVP")      // 显示全场比赛MVP球员信息
        {
            if (home_score > away_score)
            {
                team1.cal_mvp();
                team1.ShowMVP();
            }
            else if (home_score < away_score)
            {
                team2.cal_mvp();
                team2.ShowMVP();
            }
        }
        else if (op == "/DoubleDouble")     // 显示两双球员信息
        {
            if(existdd == false){       // 通过bool检查值，false则表明本场比赛无球员砍下两双，做特殊处理
                printf("本场比赛无球员砍下两双!\n");
                continue;
            }
            printf("===========================================================================================================================\n");
            PrintStandard();
            team1.ShowDD();
            team2.ShowDD();
            printf("===========================================================================================================================\n");
        }
        else if (op == "/TripleDouble")    // 显示三双球员数据
        {
            if(existtd == false){
                printf("本场比赛无球员砍下三双!\n");       // 与上同理
                continue;
            }
            printf("===========================================================================================================================\n");
            PrintStandard();
            team1.ShowTD();
            team2.ShowTD();
            printf("===========================================================================================================================\n");
        }
        else if (op == "/help")     // 获取帮助
            Gethelp();
        else
        {
            printf("指令错误, 请重新输入!\n");      // 执行到此，表明输入指令非法
            continue;
        }
    }
}

// Team类构造函数定义
Team::Team(char tn[], char nm1[], char nm2[], char nm3[], char nm4[], char nm5[],
           int num1, int num2, int num3, int num4, int num5)
    : PG(nm1, num1, posname[0]), SG(nm2, num2, posname[1]), SF(nm3, num3, posname[2]), PF(nm4, num4, posname[3]),
      C(nm5, num5, posname[4])
{
    strcpy(team_name, tn);
    PTS = PG.score() + SG.score() + SF.score() + PF.score() + C.score();
    REB = PG.rebound() + SG.rebound() + SF.rebound() + PF.rebound() + C.rebound();
    AST = PG.assist() + SG.assist() + SF.assist() + PF.assist() + C.assist();
    BLK = PG.block() + SG.block() + SF.block() + PF.block() + C.block();
    FT = PG.freethrow() + SG.freethrow() + SF.freethrow() + PF.freethrow() + C.freethrow();
    TT_FT = PG.total_freethrow() + SG.total_freethrow() + SF.total_freethrow() + PF.total_freethrow() + C.total_freethrow();
    FG = PG.total_fg() + SG.total_fg() + SF.total_fg() + PF.total_fg() + C.total_fg();
    TT_FG = PG.total_fg_made() + SG.total_fg_made() + SF.total_fg_made() + PF.total_fg_made() + C.total_fg_made();
    FG_2P = PG.fg_2p() + SG.fg_2p() + SF.fg_2p() + PF.fg_2p() + C.fg_2p();
    FG_3P = PG.fg_3p() + SG.fg_3p() + SF.fg_3p() + PF.fg_3p() + C.fg_3p();
    TT_2P = PG.fg_2p_made() + SG.fg_2p_made() + SF.fg_2p_made() + PF.fg_2p_made() + C.fg_2p_made();
    TT_3P = PG.fg_3p_made() + SG.fg_3p_made() + SF.fg_3p_made() + PF.fg_3p_made() + C.fg_3p_made();
    FTP = 100 * divnum(FT, TT_FT);
    FGP = 100 * divnum(FG, TT_FG);
    FG_2P_Rate = 100 * divnum(FG_2P, TT_2P);
    FG_3P_Rate = 100 * divnum(FG_3P, TT_3P);
}
// 获取球队名字
char* Team::get_team_name(){ return team_name; }
// 获取球队得分
int Team::score() { return PTS; }
// 获取球队总出手数
int Team::total_fg() { return FG_2P + FG_3P; }
// 获取球队总命中数
int Team::total_fg_made() { return TT_2P + TT_3P; }
// 获取球队两分球命中数
int Team::fg_2p() { return FG_2P; }
// 获取球队三分球命中数
int Team::fg_3p() { return FG_3P; }
// 获取球队两分球出手数
int Team::fg_2p_made() { return TT_2P; }
// 获取球队三分球出手数
int Team::fg_3p_made() { return TT_3P; }
// 获取球队篮板数
int Team::rebound() { return REB; }
// 获取球队盖帽总数
int Team::block() { return BLK; }
// 获取球队罚球命中数
int Team::freethrow() { return FT; }
// 获取球队罚球出手数
int Team::total_freethrow() { return TT_FT; }
// 计算球队中MVP球员
void Team::ShowMVP()
{
    // 将heap大根堆中，记录的根节点second值，即MVP球员号码提出
    int n = heap.top().second;
    printf("===========================================================================================================================\n");
    // 如果球员号码与MVP球员号码一致则表明该名球员是MVP则打印他的数据
    if (PG.getnum() == n)
        PG.ShowMVP();
    if (SG.getnum() == n)
        SG.ShowMVP();
    if (SF.getnum() == n)
        SF.ShowMVP();
    if (PF.getnum() == n)
        PF.ShowMVP();
    if (C.getnum() == n)
        C.ShowMVP();
    printf("===========================================================================================================================\n");
}
// 计算球队MVP
void Team::cal_mvp()
{
    PG.cal_mvp_rate();
    SG.cal_mvp_rate();
    SF.cal_mvp_rate();
    PF.cal_mvp_rate();
    C.cal_mvp_rate();
}
// 显示球队数据
void Team::Show()
{
    printf("===========================================================================================================================\n");

    printf("%s 赛后数据统计表:\n", team_name);
    printf("Pos Name                 Number  PTS  RB  AST  BLK  FT    2P    3P    FG    FT%%   2P%%   3P%%   FG%%\n");
    printf("PG  ");
    PG.Show();
    printf("SG  ");
    SG.Show();
    printf("SF  ");
    SF.Show();
    printf("PF  ");
    PF.Show();
    printf("C   ");
    C.Show();
    printf("球队总数据统计:                  ");
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
    printf("===========================================================================================================================\n");
}

// 显示球队两双球员数据
void Team::ShowDD(){
    if(PG.get_doubles().first == true) PG.ShowStandard();
    if(SG.get_doubles().first == true) SG.ShowStandard();
    if(SF.get_doubles().first == true) SF.ShowStandard();
    if(PF.get_doubles().first == true) PF.ShowStandard();
    if(C.get_doubles().first == true) C.ShowStandard();
}
// 显示球队三双球员数据
void Team::ShowTD(){
    if(PG.get_doubles().second == true) PG.ShowStandard();
    if(SG.get_doubles().second == true) SG.ShowStandard();
    if(SF.get_doubles().second == true) SF.ShowStandard();
    if(PF.get_doubles().second == true) PF.ShowStandard();
    if(C.get_doubles().second == true) C.ShowStandard();
}
