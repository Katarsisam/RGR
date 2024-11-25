#include <bits/stdc++.h>
using namespace std;
 
string op,x,y,z,m;
int N;
 
void encode()
{   for (auto& c     :  m     ) c = 'A' + (c - 'A' + N++)%26;
    for (auto& rotor : {x,y,z})
    for (auto& c     :  m     ) c = rotor[c - 'A'];}

 
void decode()
{   for (auto& rotor : {z,y,x})
    for (auto& c     :  m     ) c = 'A' + distance(begin(rotor), find
                                                  (begin(rotor), end(rotor),c));
    for (auto& c     :  m     ) c = 'A' + (26 + (c - 'A' - N++)%26)%26;
}
 
int main()
{   cin >> op >> N >> x >> y >> z >> m; //?
    op=="ENCODE" ? encode() : decode();
    cout << m << endl;
}