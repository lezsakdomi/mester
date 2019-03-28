#!/bin/bash

jam akadalyverseny >&2

cat >>akadalyverseny-gen.cpp <<CPP
#include <bits/stdc++.h>

using namespace std;

int main() {
    int n;
    cin >> n;

    switch (n) {
CPP

for i in {1..23}; do
    echo "Generating $i..." >&2
    cat >>akadalyverseny-gen.cpp <<CPP
        case $i:
            cout << `echo $i | ./akadalyverseny 2>/dev/null` << endl;
            return 0;

CPP
done

cat >>akadalyverseny-gen.cpp <<CPP
        default:
            cerr << "Out of range :(" << endl;
            return 1;
    }
}
CPP

make akadalyverseny-gen
