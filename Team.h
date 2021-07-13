#include <iostream>
#include <cstring>
#include <ctime>
#include <algorithm>
#include <queue>
#include <vector>
#include <windows.h>
#include "Person.h"
using namespace std;

// �����
class Team
{
private:
    Guard PG, SG;       // PG ���������Ա SG �÷ֺ�����Ա
    Forward SF, PF;     // SF Сǰ����Ա PF ��ǰ����Ա 
    Center C;       // �з���Ա
    char team_name[25];     // �������
    // PTS �÷� REB ���� AST ���� BLK ��ñ
    int PTS, REB, AST, BLK;
    // FT ���������� FG Ͷ��������  FG_2P ������������ FG_3P ������������
    int FT, FG, FG_2P, FG_3P;
    //TT_FG �ܳ�����  TT_2P ����������� TT_3P ����������� TT_FT �ܷ��������
    int TT_FG, TT_2P, TT_3P, TT_FT;
    // FGP Ͷ�������� FTP���������� FG_2P_Rate������������ FG_3P_Rate������������
    double FGP, FTP, FG_2P_Rate, FG_3P_Rate;
public:
    Team(char tn[], char nm1[], char nm2[], char nm3[], char nm4[], char nm5[],
         int num1, int num2, int num3, int num4, int num5);
    char* get_team_name();
    // ��ȡ����ܵ÷�
    int score();
    // ��������
    int total_fg();
    // �ܳ�����
    int total_fg_made();
    // ������������
    int fg_2p();
    // ������������
    int fg_3p();
    // �����������
    int fg_2p_made();
    // ������������
    int fg_3p_made();
    // ������
    int rebound();
    // ��ñ��
    int block();
    // ����
    int assist();
    // ����������
    int freethrow();
    // ���������
    int total_freethrow();
    // ����MVP��Ա����
    void ShowMVP();
    // ����ö���Ա��������
    void cal_mvp();
    // ��ʾ�������
    void Show();
    // ��ʾ�����˫��Ա����
    void ShowDD();
    // ��ʾ�����˫��Ա����
    void ShowTD();
};

// ִ�б�����ͨ����
void Match(Team &team1, Team &team2)
{

    int Ball = getrand(0, 1);
    if (Ball == 0)
        cout << team1.get_team_name() << "��ÿ�����Ȩ!\n";
    else
        cout << team2.get_team_name() << "��ÿ�����Ȩ!\n";
    int pt1 = 0, pt2 = 0, home_score = team1.score(), away_score = team2.score();

    // С��ִ��
    for (int i = 1; i <= 4; i++)
    {
        cout << "��" << i << "�ڱ���������...\n";
        Sleep(2000);        // Sleep ��������Ȥζ
        pt1 += team1.score() / getrand(4, 5);
        pt2 += team2.score() / getrand(4, 5);
        if(pt1 < pt2) pt1 += getrand(2,6);
        else pt2 += getrand(2,6);
        if (pt1 >= team1.score())
            pt1 -= getrand(5, 15);
        if (pt2 >= team2.score())
            pt2 -= getrand(5, 15);

        // �Ե��Ľڱ������⴦��
        if (i != 4)
            printf("��%d�ڱ�������,%s-%s: %d-%d\n",i,team1.get_team_name(),team2.get_team_name(),pt1,pt2);
        else{
            Sleep(1000);
            cout << "��" << i << "�ڱ���������ȫ����������!\n";
        }
    }
    Sleep(1000);
    cout << "���Ͷӱȷ�Ϊ:" << team1.score() << '-' << team2.score() << endl;
    Sleep(1000);

    Gethelp();
    // ��ѯϵͳִ��
    while (1)
    {
        string op;      // �������ָ��
        op = "";        // ��ʼ������ָ��
        cin >> op;
        Sleep(2000);
        if (op == "/Quit")      // Quit �˳�����
            break;
        else if (op == "/HomeTeamStats")    // ��ѯ��������
            team1.Show();
        else if (op == "/AwayTeamStats")    // ��ѯ�Ͷ�����
            team2.Show();
        else if (op == "/ShowMVP")      // ��ʾȫ������MVP��Ա��Ϣ
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
        else if (op == "/DoubleDouble")     // ��ʾ��˫��Ա��Ϣ
        {
            if(existdd == false){       // ͨ��bool���ֵ��false�����������������Ա������˫�������⴦��
                printf("������������Ա������˫!\n");
                continue;
            }
            printf("===========================================================================================================================\n");
            PrintStandard();
            team1.ShowDD();
            team2.ShowDD();
            printf("===========================================================================================================================\n");
        }
        else if (op == "/TripleDouble")    // ��ʾ��˫��Ա����
        {
            if(existtd == false){
                printf("������������Ա������˫!\n");       // ����ͬ��
                continue;
            }
            printf("===========================================================================================================================\n");
            PrintStandard();
            team1.ShowTD();
            team2.ShowTD();
            printf("===========================================================================================================================\n");
        }
        else if (op == "/help")     // ��ȡ����
            Gethelp();
        else
        {
            printf("ָ�����, ����������!\n");      // ִ�е��ˣ���������ָ��Ƿ�
            continue;
        }
    }
}

// Team�๹�캯������
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
// ��ȡ�������
char* Team::get_team_name(){ return team_name; }
// ��ȡ��ӵ÷�
int Team::score() { return PTS; }
// ��ȡ����ܳ�����
int Team::total_fg() { return FG_2P + FG_3P; }
// ��ȡ�����������
int Team::total_fg_made() { return TT_2P + TT_3P; }
// ��ȡ���������������
int Team::fg_2p() { return FG_2P; }
// ��ȡ���������������
int Team::fg_3p() { return FG_3P; }
// ��ȡ��������������
int Team::fg_2p_made() { return TT_2P; }
// ��ȡ��������������
int Team::fg_3p_made() { return TT_3P; }
// ��ȡ���������
int Team::rebound() { return REB; }
// ��ȡ��Ӹ�ñ����
int Team::block() { return BLK; }
// ��ȡ��ӷ���������
int Team::freethrow() { return FT; }
// ��ȡ��ӷ��������
int Team::total_freethrow() { return TT_FT; }
// ���������MVP��Ա
void Team::ShowMVP()
{
    // ��heap������У���¼�ĸ��ڵ�secondֵ����MVP��Ա�������
    int n = heap.top().second;
    printf("===========================================================================================================================\n");
    // �����Ա������MVP��Ա����һ�������������Ա��MVP���ӡ��������
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
// �������MVP
void Team::cal_mvp()
{
    PG.cal_mvp_rate();
    SG.cal_mvp_rate();
    SF.cal_mvp_rate();
    PF.cal_mvp_rate();
    C.cal_mvp_rate();
}
// ��ʾ�������
void Team::Show()
{
    printf("===========================================================================================================================\n");

    printf("%s ��������ͳ�Ʊ�:\n", team_name);
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
    printf("���������ͳ��:                  ");
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

// ��ʾ�����˫��Ա����
void Team::ShowDD(){
    if(PG.get_doubles().first == true) PG.ShowStandard();
    if(SG.get_doubles().first == true) SG.ShowStandard();
    if(SF.get_doubles().first == true) SF.ShowStandard();
    if(PF.get_doubles().first == true) PF.ShowStandard();
    if(C.get_doubles().first == true) C.ShowStandard();
}
// ��ʾ�����˫��Ա����
void Team::ShowTD(){
    if(PG.get_doubles().second == true) PG.ShowStandard();
    if(SG.get_doubles().second == true) SG.ShowStandard();
    if(SF.get_doubles().second == true) SF.ShowStandard();
    if(PF.get_doubles().second == true) PF.ShowStandard();
    if(C.get_doubles().second == true) C.ShowStandard();
}
