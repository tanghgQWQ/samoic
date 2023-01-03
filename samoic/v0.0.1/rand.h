//
// Created by Haoge.Tang on 2023/1/3.
//

#ifndef SAMOIC_RAND_H
#define SAMOIC_RAND_H
#include <iostream>
#include <chrono>
#include <random>
using namespace std;
typedef long long ll;
namespace Rand {
    ll aaa;
    double bbb;

    ll rand_l(ll l, ll r, ll t = 1) {
        if(l>r){swap(l,r);}
        mt19937 R(chrono::system_clock::now().time_since_epoch().count());
        uniform_int_distribution<ll> Rand(l, r);
        aaa = Rand(R);
        return aaa * t;
    }

    double rand_d(double l, double r) {
        mt19937 R(chrono::system_clock::now().time_since_epoch().count());
        uniform_real_distribution<double> Rand(l, r);
        bbb = Rand(R);
        return bbb;
    }

    char* rand_c(ll len, char type) {
        char s[1000005];
        ll sz=-1;
        if (type == 'a') {
            for (int i = 0; i < len; ++i) { s[++sz] = char(rand_l('a', 'z')); }
        } else if (type == 'A') {
            for (int i = 0; i < len; ++i) { s[++sz] = char(rand_l('A', 'Z')); }
        } else if (type == '0') {
            if (len == 1) {
                s[++sz] = char(rand_l('0', '9'));
                return s;
            }
            s[++sz] = char(rand_l('1', '9'));
            for (int i = 1; i < len; ++i) { s[++sz] = char(rand_l('0', '9')); }
        } else if (type == 'w') {
            s[++sz] = char(rand_l('A', 'Z'));
            for (int i = 1; i < len; ++i) { s[++sz] = char(rand_l('a', 'z')); }
        }
        else if (type == 'l') {
            for (int i = 0; i < len; ++i) { s[++sz] = char(rand_l(33, 'z')); }
        } else {
            for (int i = 0; i < len; ++i) {
                ll t = rand_l(1, 3);
                if (t == 1) { s[++sz] = char(rand_l('a', 'z')); }
                else if (t == 2) {
                    s[++sz] = char(rand_l('A', 'Z'));
                }
                else { s[++sz]= char(rand_l('0', '9')); }
            }
        }
        return s;
    }
}using namespace Rand;
#endif //SAMOIC_RAND_H
