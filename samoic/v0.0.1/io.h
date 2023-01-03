//
// Created by Haoge.Tang on 2023/1/3.
//

#ifndef SAMOIC_IO_H
#define SAMOIC_IO_H
#include <iostream>
#include <iomanip>
#include "graph.h"
using namespace std;
typedef long long ll;
ll Pow(ll b,ll p){
    ll num=1;
    for (int i = 1; i <=p ; ++i) {
        num*=b;
    }
    return num;
}
class Data{
public:
    char file_name_in[10005],file_name_out[10005];
    void build(string File_prefix,ll Id){
        memset(file_name_in,'\0',sizeof(file_name_in));
        memset(file_name_out,'\0',sizeof(file_name_out));
        for (int i = 0; i <File_prefix.size() ; ++i) {
            file_name_in[i]=file_name_out[i]=File_prefix[i];
        }
        ll cut=Id,num=0,sz=File_prefix.size()-1;
        if(cut){while (cut){num++;cut/=10;}}
        else{num=1;}
        while (num){
            cut=Id/ Pow(10,num-1);
            Id%= Pow(10,num-1);num--;sz++;
            file_name_in[sz]=file_name_out[sz]=(cut+'0');
        }
        file_name_in[++sz]='.';file_name_out[sz]='.';
        file_name_in[++sz]='i';file_name_out[sz]='o';
        file_name_in[++sz]='n';file_name_out[sz]='u';
        file_name_out[++sz]='t';
    }
    void input_write_integer(ll number_to_write,...){
        va_list arg;
        va_start(arg,number_to_write);
        freopen(file_name_in,"w",stdout);
        for (int i = 1; i <=number_to_write ; ++i) {
            printf("%lld ", va_arg(arg,ll));
        }
    }
    void input_write_float(ll decimal_digit,ll number_to_write,...){
        va_list arg;
        va_start(arg,number_to_write);
        freopen(file_name_in,"w",stdout);
        for (int i = 1; i <=number_to_write ; ++i) {
            cout<<fixed<<setprecision(decimal_digit)<<va_arg(arg,double)<<" ";
        }
    }
    void input_write_string(ll number_to_write,...){
        va_list arg;
        va_start(arg,number_to_write);
        freopen(file_name_in,"w",stdout);
        for (int i = 1; i <=number_to_write ; ++i) {
            printf("%s ", va_arg(arg,char*));
        }
    }
    void input_write_graph(Graph g){
        freopen(file_name_in,"w",stdout);
        printf("%lld %lld\n",g.n,g.m);
        for (int i = 0; i <g.g.size() ; ++i) {
            for (auto v:g.g[i].path) {
                if(!g.have_weight){
                    printf("%lld %lld\n",g.g[i].u,v.v);
                }else{
                    printf("%lld %lld %lld\n",g.g[i].u,v.v,v.weight);
                }
            }
        }
    }
    void input_write_ln(){
        putchar('\n');
    }
    void output_write_integer(ll number_to_write,...){
        va_list arg;
        va_start(arg,number_to_write);
        freopen(file_name_out,"w",stdout);
        for (int i = 1; i <=number_to_write ; ++i) {
            printf("%lld ", va_arg(arg,ll));
        }
    }
    void output_write_float(ll decimal_digit,ll number_to_write,...){
        va_list arg;
        va_start(arg,number_to_write);
        freopen(file_name_out,"w",stdout);
        for (int i = 1; i <=number_to_write ; ++i) {
            cout<<fixed<<setprecision(decimal_digit)<<va_arg(arg,double)<<" ";
        }
    }
    void output_write_string(ll number_to_write,...){
        va_list arg;
        va_start(arg,number_to_write);
        freopen(file_name_out,"w",stdout);
        for (int i = 1; i <=number_to_write ; ++i) {
            printf("%s ", va_arg(arg,char*));
        }
    }
    void output_write_ln(){
        putchar('\n');
    }
};
#endif //SAMOIC_IO_H
