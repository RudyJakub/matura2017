#include <string>
#include <fstream>
#include <iostream>
#include <vector>
#include <map>
#include <algorithm> 
#include <cctype>

using namespace std;

string strip(string s) {
    for (char c : s) {
        if (c == ' ' || c == '\t') {
            cout << ";";
        }
        else {
            cout << c;
        }
    }
    cout << endl;
    return "";
}

int main() {
    strip("Iveco Strails	2006	85900	ERA 210 TR	1200655	2015-01-31");
}