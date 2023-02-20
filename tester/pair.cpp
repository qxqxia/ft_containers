#include <iostream>
#include <utility>

using namespace std;

int main(){
    pair<int, char> p1;
    pair<int, char> p2;
    pair<int, char> p3(1,'a');
    pair<int, char> p4(p3);
    pair<int, int>  p5;

    p5 = make_pair(8.88, 'd'); //implicit conversion from pair<double,char>

    p1.first = 100;
    p1.second = 'G';

    cout << p1.first << "  " << p1.second << '\n';
    cout << p2.first << '\n';
    cout << p3.second << '\n';
    cout << p4.first << '\n';
    cout << p5.first << " " << p5.second << '\n';

    return 0;
}