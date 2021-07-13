#include <iostream>
#include <algorithm>
#include <cstring>
#include <vector>
#include <queue>
#include <unordered_map>
using namespace std;

/*��ͷ�ļ������˴������Ҫ�õ�����ͨ���� */

// ��ʾ��Ա�������ۺ���Ա����
typedef pair<double, int> PII;
// ��¼�Ƿ�Ϊ��˫����˫��Ա
typedef pair<bool, bool> Doubles;
// ���ȶ������ɴ����,����ȡ��������ߵ���Ա������
priority_queue<PII, vector<PII>, less<PII>> heap;
// ��������˫��Ա
bool existdd = false;
// ��������˫��Ա
bool existtd = false;

// ���뺯��
void Inputfun(char nm[][25], int *num, char *tn)
{
    
    printf("�����������:");
    cin >> tn;
    // �����ϣ���������������Ƿ����ظ�
    unordered_map<int,int> hmap;
    while(hmap.size() < 5)
    {
        int i = hmap.size();
        // cout << "����" << i+1 << "��λ��Ա����:"; cin >> nm[i];
        cout << "����" << i + 1 << "��λ��Ա����:";
        int number = 0,t = 1;
        string s = "";
        bool flag = true;
        // ��������ַ������룬����scanf("%d")�����ַ�ʱ�����bug
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
        // ��������Ƿ�Ϊ����
        if(!flag){
            printf("���벻�Ϸ�,����������!\n");
            continue;
        }
        // ��������Ƿ񳬳���Χ
        if(number < 0 || number > 99){
            printf("������볬����Χ(0 ~ 99),�������룬����Ϸ���Χ����������!\n");
            continue;
        }
        // ��������ظ�
        if(hmap.count(number) == 0){
            num[i] = number;
            printf("¼��ɹ�!\n");
            hmap.insert({number,1});
            continue;
        }
        else{
            printf("��Ա���������ظ����������룬��������!\n");
        }
        number = 0;
    }
    printf("��ǰ��Ӵ������...\n");
    printf("----------------------------------------------------------------------------------------------------------\n");
}

// ��ȡ����
void Gethelp()
{
    printf("----------------------------------------------------------------------------------------------------------\n");
    printf("��ѯϵͳ������������ָ��:\n");
    printf("         /ShowMVP      MVP����                                 /AwayTeamStats �Ͷ�����\n");
    printf("         /Quit         �˳�                                    /HomeTeamStats ��������\n");
    printf("         /TripleDouble ��˫��Ա����                            /DoubleDouble ��˫��Ա����\n");
    printf("         /help      ��ʾ����\n");
    printf("----------------------------------------------------------------------------------------------------------\n");
}

// ��ȡ�����ֵ
int getrand(int a, int b)
{
    return (rand() % (b - a + 1)) + a;
}

// ������˫����˫����
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

// ����������������
double divnum(int a, int b)
{
    return double(a) / double(b);
}

// ������ݺ���ģ��
template <class T>
void Output(T res, int len)
{
    cout << left << setw(len) << res;
}

// ������ݺ���ģ��
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

// ��ӡ��Ա��Ϣ��ʽ
void PrintStandard()
{
    printf("Name                 Height Weight Age Number  PTS  RB  AST  BLK  FT    2P    3P    FG    FT%%   2P%%   3P%%   FG%%\n");
}
