#include<iostream>
#include<cstring>
#include<ctime>
#include<algorithm>
#include<queue>
#include "Team.h"   // ������Team�ඨ���Լ�Match�����Ķ���
using namespace std;

// ������
int main(){
	srand((int)time(0)); // ��ʼ�����������
    char tn1[25],tn2[25];
    // ��ʼ��˫����Ա������Ҳ�ɲ�ȡ����ķ�ʽ��������ֻ��Ϊ�˼򻯲���
    char nm1[5][25] = {"˹�ٷ򡤿���","����������ɭ","���ġ�������","����³���������","�����ɵ¡�����"};
    char nm2[5][25] = {"�����ġ�Լ��ѷ","�Ʊȡ���������","�ղ��ʡ�ղķ˹","�����ᡤ��ά˹","ɳ�����������"};
    int num1[5],num2[5];
    char op[15];
    printf("������BuildTeam������Ӵ���:\n"); 
    while(1){
        scanf("%s",&op);
        if(strcmp(op,"BuildTeam") == 0){printf("����ɹ���\n");break;}
        else printf("����ʧ�ܣ�������BuildTeam�ٴν�����Ӵ���\n"); 
    }
    printf("���ڿ�ʼ���Ӵ���...\n");
    Inputfun(nm1,num1,tn1);
    printf("���ڿ�ʼ�ͶӴ���...\n");
    Inputfun(nm2,num2,tn2);
    // ����Teamʵ��������
    Team team1(tn1,nm1[0],nm1[1],nm1[2],nm1[3],nm1[4],num1[0],num1[1],num1[2],num1[3],num1[4]);
    Team team2(tn2,nm2[0],nm2[1],nm2[2],nm2[3],nm2[4],num2[0],num2[1],num2[2],num2[3],num2[4]);
    // ����Match���������б���
    Match(team1,team2);
    return 0;
}