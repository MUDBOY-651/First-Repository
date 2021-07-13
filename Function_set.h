#include <iostream>
#include <algorithm>
#include <cstring>
#include <vector>
#include <queue>
#include <unordered_map>
using namespace std;

/*该头文件包含了大多数需要用到的普通函数 */

// 表示球员比赛评价和球员号码
typedef pair<double, int> PII;
// 记录是否为两双或三双球员
typedef pair<bool, bool> Doubles;
// 优先队列做成大根堆,方便取出评价最高的球员及号码
priority_queue<PII, vector<PII>, less<PII>> heap;
// 检查存在两双球员
bool existdd = false;
// 检查存在三双球员
bool existtd = false;

// 输入函数
void Inputfun(char nm[][25], int *num, char *tn)
{
    
    printf("输入球队名称:");
    cin >> tn;
    // 定义哈希表来检测输入号码是否有重复
    unordered_map<int,int> hmap;
    while(hmap.size() < 5)
    {
        int i = hmap.size();
        // cout << "输入" << i+1 << "号位球员姓名:"; cin >> nm[i];
        cout << "输入" << i + 1 << "号位球员号码:";
        int number = 0,t = 1;
        string s = "";
        bool flag = true;
        // 输入采用字符串输入，否则scanf("%d")输入字符时会产生bug
        cin >> s;
        for(int i = 0;i < s.size();i++){
            if(s[i] <= '9' && s[i] >= '0'){
                number += number * 10 + s[i] - '0';
            }
            else{
                flag = false;
                break;
            }
        }
        // 检测输入是否为数字
        if(!flag){
            printf("输入不合法,请重新输入!\n");
            continue;
        }
        // 检测输入是否超出范围
        if(number < 0 || number > 99){
            printf("输入号码超出范围(0 ~ 99),请检查输入，输入合法范围，重新输入!\n");
            continue;
        }
        // 检测输入重复
        if(hmap.count(number) == 0){
            num[i] = number;
            printf("录入成功!\n");
            hmap.insert({number,1});
            continue;
        }
        else{
            printf("球员号码输入重复，请检查输入，重新输入!\n");
        }
        number = 0;
    }
    printf("当前球队创建完毕...\n");
    printf("----------------------------------------------------------------------------------------------------------\n");
}

// 获取帮助
void Gethelp()
{
    printf("----------------------------------------------------------------------------------------------------------\n");
    printf("查询系统，请输入以下指令:\n");
    printf("         /ShowMVP      MVP数据                                 /AwayTeamStats 客队数据\n");
    printf("         /Quit         退出                                    /HomeTeamStats 主队数据\n");
    printf("         /TripleDouble 三双球员数据                            /DoubleDouble 两双球员数据\n");
    printf("         /help      显示帮助\n");
    printf("----------------------------------------------------------------------------------------------------------\n");
}

// 获取随机数值
int getrand(int a, int b)
{
    return (rand() % (b - a + 1)) + a;
}

// 计算两双和三双数据
void cal_doubles(int a, int b, int c, Doubles& doubels,bool& existdd, bool& existtd)
{
    int cnt = 0;
    if (a >= 10)
        cnt++;
    if (b >= 10)
        cnt++;
    if (c >= 10)
        cnt++;
    if (cnt >= 2)
    {
        if (cnt == 2)
            doubels.first = true, existdd = true;
        else
            doubels.second = true, existtd = true;
    }
}

// 对两个整数做除法
double divnum(int a, int b)
{
    return double(a) / double(b);
}

// 输出数据函数模板
template <class T>
void Output(T res, int len)
{
    cout << left << setw(len) << res;
}

// 输出数据函数模板
template <class T>
void putstats(T res1, T res2)
{
    cout << res1 << "-";
    int len = 0;
    if (res1 < 10)
        len = 4;
    else
        len = 3;
    cout << left << setw(len) << res2;
}

// 打印球员信息格式
void PrintStandard()
{
    printf("Name                 Height Weight Age Number  PTS  RB  AST  BLK  FT    2P    3P    FG    FT%%   2P%%   3P%%   FG%%\n");
}
