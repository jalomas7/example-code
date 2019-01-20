#include <iostream>
#include <string>
#include <sstream>
#include <map>

using namespace std;

int main() {
    map<string, int> count;
    string word;

    while(cin >> word) {
        count[word]++;
    }

    for (map<string,int>::iterator it=count.begin(); it!=count.end(); ++it)
            cout << it->first << " : " << it->second << '\n';

}
