/******************************************************************************

Welcome to GDB Online.
GDB online is an online compiler and debugger tool for C, C++, Python, PHP, Ruby, 
C#, VB, Perl, Swift, Prolog, Javascript, Pascal, HTML, CSS, JS
Code, Compile, Run and Debug online from anywhere in world.

*******************************************************************************/
#include <iostream>
#include <cmath>
#include <string>
#include <unordered_map>
#include <algorithm>
using namespace std;

#define MAX 100
#define INT_MIN -2147483647

class candidate{
public:
    int points;
    string name;
};

class league{
public:
    int num;
    candidate list[MAX];
    unordered_map<string, int> hash;
    league(){
        num=0;
        k1=1200, k2=40, k3=50;
        hash.clear();
        hash.insert({"Ms. Chanandler Bong",-1});
    }
    bool new_player(string p_name, int x);
    void old_match(string p1, string p2, string p3);
    void disc_action(string p_name);
    void edit(string pass, int k1k, int k2k, int k3k);
    void rank();
private:
    int k1, k2, k3;
    string password="Voldemort";
};

bool league::new_player(string p_name, int x=INT_MIN){
    //strcpy(list[num].name, p_name);
    if (num==100){
        cout<<" Maximum no. of players(in this game) reached."<<endl;
        return 0;
    } 
    hash[p_name]=num;
    list[num].name=p_name;
    if (x==INT_MIN) x=k1;
    list[num].points=x;
    num++;
    return 1;
}

void league::old_match(string p1, string p2, string pw){
    bool b1,b2;
    if (hash.find(p1)==hash.end()) b1=new_player(p1);
    if (hash.find(p2)==hash.end()) b2=new_player(p2);
    if (!b1||!b2) return;
    int i=hash[p1], j=hash[p2];
    int &s1=list[i].points, &s2=list[j].points;
    float e1=1.0*1.0/(1+1.0*pow(10, 1.0*(s1-s2)/400));
    float e2=1-e1;
    //bool d=strcmp(p1,pw);
    if (p1==pw){
        s1+=e2*k2;
        s2-=e2*k2;
    }
    else{
        s1-=e1*k2;
        s2+=e1*k2;
    }
}

void league::disc_action(string p_name){
    bool b;
    if (hash.find(p_name)==hash.end()) b=new_player(p_name);
    if (!b) return;
    list[hash[p_name]].points-=k3;
}

void league::edit(string pass, int k1k, int k2k, int k3k){
    if (pass!=password) return;
    int diff=k1-k1k;
    for (int i=0;i<num;i++) list[i].points-=diff;
    k1=k1k, k2=k2k, k3=k3k;
}

bool cmp(candidate b1, candidate b2){
    return (b1.points<b2.points);
}

void league::rank(){
    candidate temp[num];
    for (int i=0;i<num;i++) temp[i]=list[i];
    sort(temp, temp+num, cmp);
    cout<<temp[0].name;
    for (int i=1;i<num;i++){
        if (temp[i].points==temp[i-1].points){
            cout<<" = "<<temp[i].name;
        }
        else cout<<" < "<<temp[i].name;
    }
    cout<<endl;
}

int main() {
    league contest[6];
    league &ufc=contest[0];
    char opt;
    string name1, name2, winner;
    int s, b, c, id=0;
    cout<<" !!!Welcome to Hogwarts Wizardry Contest!!!\n \n";
    while (1){
        cout<<"Enter your choice \n n for new player entry, m for match score update,";
        cout<<" d for disciplinary action, r for ranking the players in this game,"<<endl;
        cout<<" e if you want to edit score parameters, a if you want to move on to the next game"<<endl;
        cout<<" any other input will terminate the program and reveal the result: ";
        cin>>opt;
        switch (opt){
            case 'a':
                if (id==5) cout<<" Maximum no. of games reached."<<endl;
                else ufc=contest[++id];
                break;
            case 'e':
                cout<<"Enter the master password: ";
                cin>>name1;
                cout<<"Enter initial score: ";
                cin>>s;
                cout<<"Enter a single game's score: ";
                cin>>b;
                cout<<"Enter score lost in a disciplinary action: ";
                cin>>c;
                ufc.edit(name1,s,b,c);
                break;
            case 'n':
                cout<<"Enter the wizard/witch's name: ";
                cin>>name1;
                cout<<"Has he/she played this game before? (1 for yes and 0 for no): ";
                cin>>b;
                if (b){
                    cout<<"Enter his/her current score: ";
                    cin>>s;
                    ufc.new_player(name1, s);
                }
                else ufc.new_player(name1);
                break;
            case 'm':
                cout<<"Enter 1st wizrd/witch's name: ";
                cin>>name1;
                cout<<"Enter 2nd wizrd/witch's name: ";
                cin>>name2;
                do{
                    cout<<"Who won: ";
                    cin>>winner;
                } while (winner!=name1 && winner!=name2);
                ufc.old_match(name1, name2, winner);
                break;
            case 'd':
                cout<<"Enter the wizrd/witch's name: ";
                cin>>name1;
                ufc.disc_action(name1);
                break;
            case 'r':
                ufc.rank();
                break;
            default:
                goto AAA;
                break;
        }
    }
    AAA:unordered_map<string, int> res; 
    for (int i=0;i<=id;i++){
        ufc=contest[i];
        for (int j=0;j<ufc.num;j++){
            res[ufc.list[j].name]+=ufc.list[j].points;
        }
    }
    if (res.size()<3){
        cout<<endl<<" Not enough participants";
        return 0;
    }
    int firstp=INT_MIN, secondp=INT_MIN, thirdp=INT_MIN;
    string firstn, secondn, thirdn;
    for (auto i:res){
        int cur_score=i.second;
        if (cur_score>thirdp){
            if (cur_score>secondp){
                if (cur_score>firstp){
                    firstn=i.first;
                    firstp=cur_score;
                }
                else {
                    secondn=i.first;
                    secondp=cur_score;
                }
            }
            else {
                thirdn=i.first;
                thirdp=cur_score;
            }
        }
    }
    cout<<endl<<endl<<res.size()<<" candidates participated in the tournament.";
    cout<<endl<<thirdn<<" with "<<thirdp<<" points gets the time turner.";
    cout<<endl<<secondn<<" with "<<secondp<<" points gets the resurrection stone.";
    cout<<endl<<"AND FINALLY";
    cout<<endl<<firstn<<" with "<<firstp<<" points gets the invisibility cloak and the elder wand.";
	return 0;
}

