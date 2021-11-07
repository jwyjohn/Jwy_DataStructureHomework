#ifndef _CART_H__
#define _CART_H__

#include <iostream>
#include <string>
#include <cstring>
#include <vector>
#include <stack>
#include <algorithm>
#include <queue>
#include <map>
#include <set>
#include <assert.h>

using namespace std;

struct dataset
{
    int category_num;
    int feature_num;
    int size = 0;
    vector<int> category;
    vector<vector<float>> feature;
    dataset(){};
    dataset(int feature_num) : feature_num(feature_num)
    {
        feature.resize(feature_num);
    };
    dataset(int size, int feature_num, int category_num) : size(size), feature_num(feature_num), category_num(category_num)
    {
        category.resize(size);
        feature.resize(feature_num);
        for (auto u : feature)
        {
            u.resize(size);
        };
    };
};

struct tree_node
{
    int no;
    int feature;
    float threshold;
    tree_node *lc, *rc;
};

struct feature_split
{
    int no;
    float threshold;
    float gini;
    bool operator<(const feature_split &b) const
    {
        return (gini < b.gini);
    }
};

float calc_gini(const dataset D)
{
    float res = 1.0;
    vector<int> cnt;
    cnt.resize(D.category_num);
    for (auto u : D.category)
    {
        cnt[u]++;
    };
    for (auto i : cnt)
    {
        res -= (float(i) / D.size) * (float(i) / D.size);
    };
    return res;
};

float calc_split_gini(const dataset D, int feature_no, float threshold)
{
    dataset A, B;
    A.category_num = D.category_num;
    A.feature_num = D.feature_num;
    A.feature.resize(D.feature_num);
    B.category_num = D.category_num;
    B.feature_num = D.feature_num;
    B.feature.resize(D.feature_num);
    for (int i = 0; i < D.size; i++)
    {
        // cout << "FOX ! " << i << endl;
        // cout << D.feature[feature_no][i] << endl;
        float tmp = D.feature[feature_no][i];
        // cout << tmp << endl;
        if (tmp <= threshold)
        {
            // cout << "KIT ! " << i << endl;
            A.size++;
            A.category.push_back(D.category[i]);
            for (int j = 0; j < D.feature_num; j++)
            {
                A.feature[j].push_back(D.feature[j][i]);
            };
        }
        else
        {
            B.size++;
            B.category.push_back(D.category[i]);
            // cout << "DOG ! " << i << endl;
            for (int j = 0; j < D.feature_num; j++)
            {
                B.feature[j].push_back(D.feature[j][i]);
                // cout << "WOF ! " << j << endl;
            };
        };
        // cout << "CAT ! " << i << endl;
    };
    float res = 0.0;
    res = float(A.size) / float(D.size) * calc_gini(A) + float(B.size) / float(D.size) * calc_gini(B);
    return res;
};

set<float> gen_split(const dataset D, int feature_no)
{
    vector<float> tmp = D.feature[feature_no];
    set<float> res;
    sort(tmp.begin(), tmp.end());
    for (int i = 1; i < tmp.size(); i++)
    {
        if (tmp[i] != tmp[i - 1])
            res.insert(tmp[i] / 2 + tmp[i - 1] / 2);
    };
    return res;
};

feature_split find_split(dataset D)
{
    feature_split res;
    priority_queue<feature_split> q;
    for (int feature_no = 0; feature_no < D.feature_num; feature_no++)
    {
        set<float> splits = gen_split(D, feature_no);
        for (auto &thres : splits)
        {
            feature_split tmp;
            tmp.no = feature_no;
            tmp.threshold = thres;
            tmp.gini = calc_split_gini(D, feature_no, thres);
            q.push(tmp);
        }
    };
    res = q.top();
    cout << res.no << ": " << res.threshold << " " << res.gini << " " << endl;
    return res;
};

#endif