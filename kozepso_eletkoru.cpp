#include <iostream>
using namespace std;

int x, i, cnt = 0, n, halfn;
int v[151] = {0};
char buf[2];

int main(){
    cin >> n; cin.ignore();
    halfn = n / 2;

    for (i = n; i --> 0;) {
        buf[0] = cin.get();
        if (cin.peek() != '\n') {
            buf[1] = cin.get();
            if (cin.peek() != '\n') {
                x = 100 + (buf[1]-'0')*10 + (cin.get()-'0');
            } else x = (buf[0]-'0')*10 + (buf[1]-'0');
        } else x = (buf[0]-'0');
        cin.ignore();

        ++v[x];
    }

    i = 1;
    while (true) {
        cnt += v[i];
        if (cnt > halfn) break;
        ++i;
    }

    cout << i;

    return 0;
}
