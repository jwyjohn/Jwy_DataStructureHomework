#ifndef _KMP_H__
#define _KMP_H__

#include <iostream>
#include <string>
#include <vector>

using namespace std;

class text
{

    string raw_text;

public:
    text(string t) : raw_text(t){};
    vector<int> prefixFunction(string s)
    {
        int n = (int)s.length();
        vector<int> pi(n);
        for (int i = 1; i < n; i++)
        {
            int j = pi[i - 1];
            while (j > 0 && s[i] != s[j])
                j = pi[j - 1];
            if (s[i] == s[j])
                j++;
            pi[i] = j;
        }
        return pi;
    };
    int countWord(string s)
    {
        int n = (int)s.length();
        int ans = 0;
        int j = 0;
        string pattern=s+'#';
        pattern+=raw_text;
        cout<<pattern<<endl;
        vector<int> v = prefixFunction(pattern);
        for (auto u:v){
            if(u==n) ans++;
        };
        return ans;
    }
};

#endif