#include<iostream>
#include<cstring>
#include<ctime>
#include<algorithm>
#include<vector>
#include<iomanip>
#include<queue>
#include "Function_set.h"   // ����װ����ͨ������ͷ�ļ�
using namespace std;

char posname[5][5] = {"PG","SG","SF","PF","C"};

// ����Person��
class Person{
protected:
    char name[25];      // ����
    char position[15];      // ��Աλ��
    int age,FG,FG_3P;       // age���䣬FG��������FG_3P���ֽ�����
    int FG_2P,number,AST;   // FG_2P���ֽ�������,number��Ա���룬AST����
    int REB,TT_2P,TT_3P;    // REB���壬TT_2P�������������TT_3P�����������
    int BLK,PTS;    // BLK��ñ��PTS�÷�
    int FT,TT_FT,height,weight; // FT������������TT_FT�����������height��ߣ�weight����
    double FGP,FTP;         // FGPͶ�������ʣ�FTP����������
    double FG_2P_Rate,FG_3P_Rate;   // FG_2P_Rate�����������ʣ�FG_3P_Rate������������
    PII mvp_rate;       // ��ȡ��������ֵ�����ڼ���MVP
    Doubles doubles;        // ��¼��Ա�Ƿ�����˫
public:
    Person(char *nm);
    // ���³�Ա����Ŀ�ľ�Ϊ��ȡ��Ӧ���ݳ�Ա
    Doubles get_doubles();
    int total_fg(); // ��������
    int total_fg_made();    // �ܳ�����
    int fg_2p();    // �����������
    int fg_3p();    // �����������
    int fg_2p_made();       // �����������
    int fg_3p_made();       // �����������
    int score();        // �÷�
    int rebound();      // ����
    int block();        // ��ñ
    int assist();       // ����
    int freethrow();    // ����������
    int total_freethrow();      // ���������
    int getnum();       // ��ȡ��Ա����
    void cal_mvp_rate();        // ��ȡ��Ա��������
    void Show();        // չʾ��Ա�Ļ�����Ϣ1
    void ShowMVP();     // ����Ա���MVPʱչʾ��Ϣ
    void ShowStandard();        // չʾ��Ա�Ļ�����Ϣ2
};

// ������
class Guard:public Person{
public:
    Guard(char*,int,char*);
};

// ������
class Forward:public Person{
public:
    Forward(char*,int,char*);
}; 

// �з���
class Center:public Person{
public:
    Center(char*,int,char*);
};

Person::Person(char nm[])
{
    strcpy(name, nm);
    age = getrand(20, 33);
}

// ��Ա���MVPʱ��չʾ����
void Person::ShowMVP()
{
    printf("��������MVP�������%s! ��������Ϊ%.2f", name,mvp_rate.first);
    printf("(%.2f = %d*0.7 + 0.1*(%d + %d + %d))!\n",mvp_rate.first,REB,BLK,PTS,AST);
    PrintStandard();
    ShowStandard();
}

// ��ʾ��Ա����
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

// ������Ա����
void Person::cal_mvp_rate()
{
    mvp_rate.first = PTS * 0.7 + 0.1 * (BLK + PTS + AST);
    mvp_rate.second = number;
    heap.push(mvp_rate);
}

// չʾ��Ա������Ϣ
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
// ��������
int Person::total_fg() { return FG_2P + FG_3P; }
// �ܳ�����
int Person::total_fg_made() { return TT_2P + TT_3P; }
// ������������
int Person::fg_2p() { return FG_2P; }
// ������������
int Person::fg_3p() { return FG_3P; }
// �����������
int Person::fg_2p_made() { return TT_2P; }
// �����������
int Person::fg_3p_made() { return TT_3P; }
// �÷�
int Person::score() { return PTS; }
// ����
int Person::rebound() { return REB; }
// ��ñ
int Person::block() { return BLK; }
// ����
int Person::assist() { return AST; }
// ����������
int Person::freethrow() { return FT; }
// ���������
int Person::total_freethrow() { return TT_FT; }
// ���º���
int Person::getnum() { return number; }

//
//  ��������һ�������ע�ͣ���������ṹ���ƣ�ֻ���������Χ��ͬ~
//

// Guard�๹�캯��
Guard::Guard(char nm[], int num, char pos[15]) : Person(nm)
{
    number = num;
    strcpy(position, pos);
    // ��������if�ж���Ա����PG����SG
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
    // �Ը�������������Աλ�ò�ͬ���и��Ի���ֵ
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
    // �����ǶԵ�������Ϊ0�������ʼ���ʱ����ĸΪ0ʱ����һЩ���⴦��
    if ((TT_2P + TT_3P) == 0)// ���ܳ�����= ���ֳ�����+���ֳ����� = 0ʱ����������ֱ�Ӹ�ֵ0�������˳�0�����
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

// Forward���캯��
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
    // �Ը�������������Աλ�ò�ͬ���и��Ի���ֵ
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
    // �����ǶԵ�������Ϊ0�������ʼ���ʱ����ĸΪ0ʱ����һЩ���⴦��
    if ((TT_2P + TT_3P) == 0)   // ���ܳ�����= ���ֳ�����+���ֳ����� = 0ʱ����������ֱ�Ӹ�ֵ0�������˳�0�����
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

// Center�๹�캯��
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
