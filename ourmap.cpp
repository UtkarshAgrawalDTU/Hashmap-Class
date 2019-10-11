#include<iostream>
#include"hashmap.h"
using namespace std;

int main()
{
    ourmap <int> m;
    m.inserts("utkarsh", 19);
    m.inserts("abc", 53);
    cout<<m.sizes()<<endl;
    cout<<m.getvalue("utkarsh")<<endl;
    m.deletes("utkarsh");
    cout<<m.sizes()<<endl;
    cout<<m.getvalue("utkarsh")<<endl;
    cout<<m.getvalue("abc")<<endl;
    return 0;
}
