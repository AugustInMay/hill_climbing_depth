#include <iostream>
#include <string>
#include <ctime>
#include <math.h>
#include <bitset>
#include <iomanip>
#include <set>
using namespace std;

void neighb_fill(bitset<5> inp, bitset<5> *out){
    for(int i=0; i<5; i++){
        bitset<5> fl=inp;
        out[i]=fl.flip(i);
    }
}

int main() {
    srand(time(0));
    bitset<5> field[32], neighb[5];
    int Q[32], n, cur_p=rand()%32, ran_ch, step=0;
    bool by_neighb=false;
    set<int> used_neighb;
    cin>>n;
    cout<<"The field and landscape are:  "<<endl;
    for(int i=0; i<32; i++){
        field[i]=i;
        Q[i]=pow((i-16), 2);
        cout<<fixed;
        cout<<field[i]<<" - Q = "<<setw(5)<<left<<Q[i]<<" ";
        if((i+1)%5==0){
            cout<<"\n";
        }
    }
    cout<<"\nRandom choice is "<<field[cur_p]<<" - Q = "<<Q[cur_p];
    while(step!=n){
        step++;
        cout<<"\n\n-----\n\nSTEP "<<step<<" -----\nCurrent max is "<<field[cur_p]<<" with max Q = "<<Q[cur_p];
        neighb_fill(field[cur_p], neighb);
        if(used_neighb.size()==5){
            cout<<"\nThere are no neighbours left... Finished with "<<field[cur_p]<<" Q = "<<Q[cur_p]<<" --- in "<<step<<" STEPS";
            by_neighb=true;
            break;
        }
        cout<<"\nHere are the neighbours: ";
        for(int i=0; i<5; i++){
            if(used_neighb.find(i)==used_neighb.end()){
                cout<<neighb[i]<<" Q = "<<Q[(int)(neighb[i].to_ulong())]<<" ; ";
            }
        }
        ran_ch=rand()%5;
        while(used_neighb.find(ran_ch)!=used_neighb.end()){
            ran_ch=rand()%5;
        }
        cout<<"\nRandomly chosen neighbour is "<<neighb[ran_ch]<<" Q = "<<Q[(int)(neighb[ran_ch].to_ulong())];
        if(Q[(int)(neighb[ran_ch].to_ulong())]>Q[cur_p]){
            cur_p=(int)neighb[ran_ch].to_ulong();
            cout<<", and it is a NEW max!\nCurrent max is "<<field[cur_p]<<" with max Q = "<<Q[cur_p];
            used_neighb.clear();
        }
        else{
            cout<<", and there is nothing special in it... Poor guy...";
            used_neighb.insert(ran_ch);
        }
    }
    if(step==n && !by_neighb){
        cout<<"\n\n!The limit of steps is reached!\n\n-----Finished with "<<field[cur_p]<<" Q = "<<Q[cur_p]<<" --- in "<<step<<" STEPS";
    }
    return 0;
}