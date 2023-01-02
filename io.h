//
// Created by Haoge.Tang on 2023/1/2.
//

#ifndef SAMOIC_IO_H
#define SAMOIC_IO_H
#include <iostream>
using namespace std;
typedef long long ll;
ll Pow(ll A,ll B){
    ll num=1;
    for (int i = 1; i <=B ; ++i) {
        num*=A;
    }
    return num;
}
void print_char(char c){
    printf("%c",c);
}
ll Print(char *format,...){
    if(format==NULL){
        return -1;
    }
    ll ele_num=0;
    char *c=(char*)format;
    int arg_int_value=0;
    ll arg_long_long_value=0;
    unsigned long long arg_hex_value=0;
    char* arg_string_value= NULL;
    double arg_dou_value=0;
    unsigned long long cut;
    unsigned long long temp;
    ll cnt=0;
    ll i=0;
    va_list arg;
    va_start(arg,format);
    while (*c!='\0'){
        switch (*c) {
            case ' ':print_char(*c);ele_num++;break;
            case '\t':print_char(*c);ele_num+=4;break;
            case '\r':print_char(*c);ele_num++;break;
            case '\n':print_char(*c);ele_num++;break;
            case '%':
                c++;
                switch (*c) {
                    case '%':
                        print_char(*c);
                        ele_num++;
                        c++;
                        continue;
                    case 'c':
                        arg_int_value= va_arg(arg,int );
                        print_char(char(arg_int_value));
                        ele_num++;
                        c++;
                        continue;
                    case 'd':
                        arg_int_value= va_arg(arg,int);
                        if(arg_int_value<0){
                            print_char('-');
                            arg_int_value=-arg_int_value;
                            ele_num++;
                        }
                        cut=arg_int_value;
                        if(cut){
                            while (cut){++cnt;cut/=10;}
                        }else{cnt=1;}
                        ele_num+=cnt;
                        while (cnt){
                            cut=arg_int_value/ Pow(10,cnt-1);
                            arg_int_value%=int(Pow(10,cnt-1));
                            print_char(char(cut+'0'));
                            cnt--;
                        }c++;
                        continue;
                    case 'o':
                        arg_int_value= va_arg(arg,int);
                        if(arg_int_value<0){
                            print_char('-');
                            arg_int_value=-arg_int_value;
                            ele_num++;
                        }
                        cut=arg_int_value;
                        if(cut){
                            while (cut){++cnt;cut/=8;}
                        }else{cnt=1;}
                        ele_num+=cnt;
                        while (cnt){
                            cut=arg_int_value/ Pow(8,cnt-1);
                            arg_int_value%=int(Pow(8,cnt-1));
                            print_char(char(cut+'0'));
                            cnt--;
                        }c++;
                        continue;
                    case 'x':
                        arg_hex_value= va_arg(arg,unsigned long );
                        cut=arg_hex_value;
                        if(cut){
                            while (cut){++cnt;cut/=16;}
                        }else{cnt=1;}
                        ele_num+=cnt;
                        while (cnt){
                            cut=arg_hex_value/ Pow(16,cnt-1);
                            arg_hex_value%=ll(Pow(16,cnt-1));
                            if(cut<=9){
                                print_char(char(cut+'0'));
                            }else{
                                print_char(char(cut-10+'A'));
                            }
                            cnt--;
                        }c++;
                        continue;
                    case 'b':
                        arg_int_value= va_arg(arg,int);
                        if(arg_int_value<0){
                            print_char('-');
                            arg_int_value=-arg_int_value;
                            ele_num++;
                        }
                        cut=arg_int_value;
                        if(cut){
                            while (cut){++cnt;cut/=2;}
                        }else{cnt=1;}
                        ele_num+=cnt;
                        while (cnt){
                            cut=arg_int_value/ Pow(2,cnt-1);
                            arg_int_value%=int(Pow(2,cnt-1));
                            print_char(char(cut+'0'));
                            cnt--;
                        }c++;
                        continue;
                    case 's':
                        arg_string_value= va_arg(arg,char*);
                        ele_num+= strlen(arg_string_value);
                        while (*arg_string_value){
                            print_char(*arg_string_value);
                            arg_string_value++;
                        }
                        c++;
                        continue;
                    case 'f':
                        arg_dou_value= va_arg(arg,double );
                        cut=ll(arg_dou_value);
                        temp=cut;arg_dou_value-=cut;
                        if(cut){while (cut){++cnt;cut/=10;}
                        }else{cnt=1;}ele_num+=cnt;
                        while (cnt){
                            cut=arg_int_value/ Pow(10,cnt-1);
                            arg_int_value%=int(Pow(10,cnt-1));
                            print_char(char(cut+'0'));cnt--;
                        }
                        print_char('.');ele_num++;
                        arg_dou_value*=1e6;cnt=6;
                        temp=ll(arg_dou_value);
                        while (cnt){
                           cut=temp/ Pow(10,cnt-1);
                           temp%= Pow(10,cnt-1);
                            print_char(char(cut+'0'));
                            cnt--;
                        }ele_num+=6;c++;continue;
                    default:
                        print_char(' ');
                        ele_num++;
                        continue;
                }
            default:
                print_char(*c);
                ele_num++;
                break;
        }
        ++c;
    }
    return ele_num;
}
#endif //SAMOIC_IO_H
