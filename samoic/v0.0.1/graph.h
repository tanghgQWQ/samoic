//
// Created by Haoge.Tang on 2023/1/2.
//

#ifndef SAMOIC_GRAPH_H
#define SAMOIC_GRAPH_H
#include <iostream>
#include <random>
#include <chrono>
#include <map>
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

    string rand_c(ll len, char type) {
        string s;
        if (type == 'a') {
            for (int i = 0; i < len; ++i) { s += char(rand_l('a', 'z')); }
        } else if (type == 'A') {
            for (int i = 0; i < len; ++i) { s += char(rand_l('A', 'Z')); }
        } else if (type == '0') {
            if (len == 1) {
                s += char(rand_l('0', '9'));
                return s;
            }
            s += char(rand_l('1', '9'));
            for (int i = 1; i < len; ++i) { s += char(rand_l('0', '9')); }
        } else if (type == 'w') {
            s += char(rand_l('A', 'Z'));
            for (int i = 1; i < len; ++i) { s += char(rand_l('a', 'z')); }
        }
        else if (type == 'l') {
            for (int i = 0; i < len; ++i) { s += char(rand_l(33, 'z')); }
        } else {
            for (int i = 0; i < len; ++i) {
                ll t = rand_l(1, 3);
                if (t == 1) { s += char(rand_l('a', 'z')); }
                else if (t == 2) {
                    s += char(rand_l('A', 'Z'));
                }
                else { s += char(rand_l('0', '9')); }
            }
        }
        return s;
    }
}using namespace Rand;
class Graph{
public:
    bool have_weight= false;//有权图或无权图
    struct Edge_node{ll v,weight;};//辅助node使用。
    struct edge{
        ll start,end,weight;
    };
    struct node{
        ll u=0;//当前结点的值
        vector<Edge_node>path;//到达地方（保存的是直接的v而不是point[v]，所以要挪移的话不要直接v了
    };
    vector<node>g;//图本身
    vector<edge>edges;//边的保存
    map<ll,ll>point;//结点指针
    ll n,m;//结点数，边数
    vector<vector<ll>>adjacency_matrix;//邻接矩阵
    void add_edge(ll u,ll v,ll weight=0){
        if(!point.count(u)){
            point[u]=g.size();
            g.push_back({u});
        }
        if(!point.count(v)){
            point[v]=g.size();
            g.push_back({v});
        }
        g[point[u]].path.push_back({v,weight});
    }
    void graph_init(){
        //邻接矩阵的填入，防止RE
        vector<ll>empty;
        adjacency_matrix.push_back(empty);
        for (int i = 1; i <=n ; ++i) {
            vector<ll>h;
            h.push_back(0);
            for (int j = 1; j <=n ; ++j) {
                h.push_back(0);
            }
            adjacency_matrix.push_back(h);
        }
    }
    void graph(ll N,ll M,pair<ll,ll> weight_range={0,0},bool directed= false){
        n=N;m=M;
        graph_init();
        if(weight_range.first!=0||weight_range.second!=0){
            have_weight= true;//有权。
        }
        for (int i = 1; i <=m ; ++i) {
            ll u=rand_l(1,n),v=rand_l(1,n),w= rand_l(weight_range.first,weight_range.second);
            add_edge(u,v,w);
            if(have_weight){
                adjacency_matrix[u][v]=w;//有权图往邻接矩阵里放权值
            }else{
                adjacency_matrix[u][v]=1;//没有放1
            }
            edges.push_back({u,v,w});//记录边
            if(!directed){
                add_edge(v,u,w);
                edges.push_back({v,u,w});
                if(have_weight){
                    adjacency_matrix[v][u]=w;
                }else{
                    adjacency_matrix[v][u]=1;
                }
            }
        }
    }
    void print(){
        printf("%lld %lld\n",n,m);
        for (int i = 0; i <g.size() ; ++i) {
            for (auto v:g[i].path) {
                if(!have_weight){
                    printf("%lld %lld\n",g[i].u,v.v);
                }else{
                    printf("%lld %lld %lld\n",g[i].u,v.v,v.weight);
                }
            }
        }
    }
};
#endif //SAMOIC_GRAPH_H
