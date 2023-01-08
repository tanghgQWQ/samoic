/*
 v0.0.1
 Created by Haoge.Tang on 2023/1/3.

 2023/1/6随机数部分初试通过。图论初试通过。
 2023/1/7树部分的多叉树部分和链与菊花图部分初试通过。
 2023/1/8输出部分初式通过，v0.0.1版本开始复试。
 复试流程:
    测试整形随机数和整形输入输出，使用P1001作为测试题目，数据正确。
    测试浮点数随机数和浮点数输入输出，使用P5706作为测试题目，往输入输出中添加了浮点数保留小数位数的功能。
    测试字符串功能，使用P5733作为测试题目，数据正确。
    测试图论功能，由于std较为复杂，不生成输出文件，使用P1339作为测试题目，数据正确。
    测试树功能，由于std较为复杂，不生成输出文件，使用P3379作为测试题目，数据正确。
 测试完毕，所有内容均为正确。
 测试流程：
    1.初试
        在main.cpp中直接进行测试，简单测试是否RE，返回乱码。
    2.复试
        在洛谷网中找一道需要当前被测试函数作为数据生成器的一道题。
        按照真实性写出数据生成器，并在洛谷网中编译和测试。
 初步的功能：
    0.往输入输出文件中写东西。
        放弃原有的va_list思路，太旧了。 还是暂时用vector代替吧。文件输出工具不变，依然使用ofstream。
        之后的版本考虑手写一个文件输入输出的printf。实现cin最好，看难度吧，作者不知道cin的原理。
    1.基础的图论功能
        建有向图，无向图，带权。添加保存的邻接矩阵，和不同边的保存。建边。
        存图方式用链式前向星，由于不确定大小用vector存边。
        A.建边 add_edge(ll from, ll to, ll weight = 0)
        B.建图 graph(ll _n, ll _m, pair<ll, ll> weight_limit = {0, 0},bool directed = false,bool _self_loop = true,bool _double_edge = true)
        C.邻接矩阵 adjacency_matrix
            建图的时候构建邻接矩阵，若无权则m[u][v]=1，有权则m[u][v]=w
        D.保存边 vector<edge_for_save>edges
            与链式前向星类似。from为u，to为v,weight为w。
        输出格式：
            m行，每行三个整数（在之后的版本中考虑给w添加浮点数的版本，现在不考虑）。
            有权图：
                u v w
                u v w
                ...
            无权图：
                u v
                u v
                ...
            n，m由用户自己输入。
    2.基础的树功能
        给出结点和根。
        A.多叉树 tree(ll _n, ll _root, double chain = 0, double flower = 0)
        B.链和菊花图的功能。chain(ll _n, ll _root),flower(ll _n, ll _root)
        输出格式：
            n-1行，每行为u,v代表u，v之间有一条边。
    3.随机namespace Random
        A.整数随机random_integer(l,r)
            肯定要的。
        B.浮点数随机random_float(l,r)
            同上
        C.字符串随机
            所有的字符串均使用string，需要char的自行转换。
            I.高精度 integer_high_precision(ll k, bool negative = false)
                给定一个首为不是0的k-1位数字字符串即在10^k之内
            II.全小写字符串 small_letter_words(ll length)
                实现简单。
            III.大写字符串 capitalized_words(ll length)
                同上
            IV.句子中第一个单词 first_word(ll length)
                I+II即可
            V.标点 punctuation()
                .?!
            VI.句子（给出参数表示是否加标点符号） sentence(ll length,pair<ll,ll>one_word_length,bool have_punctuation= true)
                Iv+II+(V)
*/

#ifndef SAMOIC_SAMOIC_H
#define SAMOIC_SAMOIC_H
#include <iostream>
#include <vector>
#include <map>
#include <random>
#include <fstream>
using namespace std;
typedef long long ll;
namespace Random {
    ll random_integer(ll l, ll r) {
        if(l>r){
            swap(l,r);
        }
        random_device rd;
        mt19937 seed(rd());
        uniform_int_distribution<ll> Rand(l, r);
        return Rand(seed);
    }

    double random_float(double l, double r) {
        if(l>r){
            swap(l,r);
        }
        random_device rd;
        mt19937 seed(rd());
        uniform_real_distribution<double> Rand(l, r);
        return Rand(seed);
    }

    string integer_high_precision(ll k, bool negative = false) {
        string c;
        if (k == 1) {
            char num = char(random_integer('0', '9'));
            if (negative && num != '0') {
                c += '-';
            }
            c += num;
            return c;
        }
        if (negative) {
            c += '-';
        }
        c += char(random_integer('1', '9'));
        for (int i = 1; i < k; ++i) { c += char(random_integer('0', '9')); }
        c += '\0';
        return c;
    }

    string small_letter_words(ll length) {
        string c;
        for (int i = 1; i <= length; ++i) {
            c += char(random_integer('a', 'z'));
        }
        return c;
    }

    string capitalized_words(ll length) {
        string c;
        for (int i = 1; i <= length; ++i) {
            c += char(random_integer('A', 'Z'));
        }
        return c;
    }

    string first_word(ll length) {
        return capitalized_words(min(ll(1), length)) + small_letter_words(length - 1);
    }

    char punctuation() {
        char p[] = {'.', '?', '!'};
        return p[random_integer(0, 2)];
    }

    string sentence(ll length, pair<ll, ll> one_word_length, bool have_punctuation = true) {
        string c;
        c = first_word(random_integer(one_word_length.first, one_word_length.second));
        for (int i = 1; i <= length - 2; ++i) {
            c += " ";
            c += small_letter_words(random_integer(one_word_length.first, one_word_length.second));
        }
        c += punctuation();
        return c;
    }
}
class Graph {
private:
    struct edge {
        ll from, to, weight, nxt;//链式前向星
    };
    vector<edge> e;//图本身
    ll n, m;//点数，边数
    map<ll, ll> head;//还是一样，为了减少空间。
    bool self_loop, double_edge;//重边和自环
    map<pair<ll, ll>, bool> edge_appeared;//为了防止重边，要记录什么边出现过。
public:
    bool have_weight, have_directed;//在输入建图信息是记录是否带权。第二个是否有方向。
    struct edge_for_save {
        ll from, to, weight;//如名字，只是为了记录
    };
    vector<edge_for_save> edges;//记录边的数组
    vector<vector<ll>> adjacency_matrix;//用来存邻接矩阵

    void add_edge(ll from, ll to, ll weight = 0) {
        edge new_edge = {from, to, weight, head[from]};
        e.push_back(new_edge);
        head[from] = e.size() - 1;//++tot=e.size()-1
        if (have_weight) { adjacency_matrix[from][to] = weight; }//更新邻接矩阵
        else { adjacency_matrix[from][to] = 1; }//同上
    }

    void graph_init() {
        //先往vector的邻接矩阵里填东西，防RE
        vector<ll> h;
        adjacency_matrix.push_back(h);
        for (int j = 1; j <= n + 1; ++j) {
            h.push_back({0});
        }
        for (int i = 1; i <= n; ++i) {
            adjacency_matrix.push_back(h);
        }
        //之后往边的记录里先放一个，这样就可以从1开始了。
        edges.push_back({0, 0, 0});
    }

    void graph(ll _n, ll _m, pair<ll, ll> weight_limit = {0, 0}, bool directed = false,
               bool _self_loop = true, bool _double_edge = true) {
        //导入基本数据
        n = _n;
        m = _m;
        self_loop = _self_loop;
        double_edge = _double_edge;
        have_directed = directed;
        graph_init();//有了数据就可以先init了。
        if (weight_limit.first != 0 || weight_limit.second != 0) { have_weight = true; }
        else { have_weight = false; }
        for (int i = 1; i <= m; ++i) {
            ll u = Random::random_integer(1, n), v = Random::random_integer(1, n), w = Random::random_integer(
                    weight_limit.first, weight_limit.second);
            if (!self_loop) {
                while (u == v) {
                    //如果自环就随机重新刷一边
                    u = Random::random_integer(1, n), v = Random::random_integer(1, n);
                }
            }
            if (!double_edge) {
                if (have_directed) {
                    while (edge_appeared.count({u, v})) {
                        //如果重边就重新刷一遍
                        u = Random::random_integer(1, n), v = Random::random_integer(1, n);
                    }
                } else {
                    while (edge_appeared.count({u, v}) || edge_appeared.count({v, u})) {
                        //同上
                        u = Random::random_integer(1, n), v = Random::random_integer(1, n);
                    }
                }
            }
            add_edge(u, v, w);//先链式前向星记着，之后可能会添加一些功能要遍历。
            edges.push_back({u, v, w});//记录边
            if (!have_directed) {
                add_edge(v, u, w);//模拟建图
            }
        }
    }
};
class Tree {
private:
public:
    ll type;//种类（1为多叉树，2为二叉树）
    ll n, root;//结点个数，根
    map<ll, vector<ll>> t;//多叉树
    map<ll, pair<ll, ll>> bt;//二叉树
    void tree(ll _n, ll _root, double chain = 0, double flower = 0) {
        ll num_chain = _n * chain, num_flower = _n * flower;
        type = 1;
        n = _n;
        root = _root;
        ll father = root;
        map<ll, bool> vis;
        vis[root] = true;
        srand(time(NULL));
        vector<ll> node;
        for (int i = 1; i <= n; ++i) {
            if (i == root) { continue; }
            node.push_back(i);
        }
        std::random_device rd;
        std::mt19937 seed(rd());
        shuffle(node.begin(), node.end(), seed);
        ll key = -Random::random_integer(1 << 18, 1 << 31);
        vector<ll> add_to_root;
        add_to_root.push_back(root);
        for (int i = 0; i < num_chain - 1; ++i) {
            t[father].push_back(node[i]);
            father = node[i];
            add_to_root.push_back(node[i]);
            node[i] = key;
        }
        if (num_chain == 0) { num_chain = 1; }
        for (ll i = num_chain - 1; i < num_flower + num_chain - 2; ++i) {
            t[root].push_back(node[i]);
            add_to_root.push_back(node[i]);
            node[i] = key;
        }
        for (int i = 0; i < node.size(); ++i) {
            if (node[i] != key) {
                t[add_to_root[Random::random_integer(0, add_to_root.size() - 1)]].push_back(node[i]);
                add_to_root.push_back(node[i]);
                node[i] = key;
            }
        }
    }

    void chain(ll _n, ll _root) {
        tree(_n, _root, 1, 0);
    }

    void flower(ll _n, ll _root) {
        tree(_n, _root, 0, 1);
    }
};
class Data {
private:
    string in_name, out_name;
public:
    void build(string name_prefix, ll id) {
        in_name = name_prefix + to_string(id) + ".in";
        out_name = name_prefix + to_string(id) + ".out";
        ofstream file_in(in_name, ios::out | ios::trunc);
        ofstream file_out(out_name, ios::out | ios::trunc);
    }

    void input_write_integer(vector<ll> r) {
        ofstream file(in_name, ios::out | ios::app);
        for (int i = 0; i < r.size(); ++i) {
            file << r[i] << " ";
        }
    }

    void input_write_double(vector<double> r, ll con = 6) {
        ofstream file(in_name, ios::out | ios::app);
        for (int i = 0; i < r.size(); ++i) {
            file << setprecision(con) << fixed << r[i] << " ";
        }
    }

    void input_write_string(vector<string> r) {
        ofstream file(in_name, ios::out | ios::app);
        for (int i = 0; i < r.size(); ++i) {
            file << r[i] << " ";
        }
    }

    void input_write_graph(Graph g) {
        ofstream file(in_name, ios::out | ios::app);
        if (g.have_weight) {
            for (int i = 1; i < g.edges.size(); ++i) {
                file << g.edges[i].from << " " << g.edges[i].to << " " << g.edges[i].weight << '\n';
            }
        } else {
            for (int i = 1; i < g.edges.size(); ++i) {
                file << g.edges[i].from << " " << g.edges[i].to << '\n';
            }
        }
    }

    void input_write_tree(Tree t) {
        ofstream file(in_name, ios::out | ios::app);
        for (int i = 1; i <= t.n; ++i) {
            for (int j = 0; j < t.t[i].size(); ++j) {
                file << i << " " << t.t[i][j] << '\n';
            }
        }
    }

    void input_write_ln() {
        ofstream file(in_name, ios::out | ios::app);
        file << '\n';
    }

    void output_write_integer(vector<ll> r) {
        ofstream file(out_name, ios::out | ios::app);
        for (int i = 0; i < r.size(); ++i) {
            file << r[i] << " ";
        }
    }

    void output_write_double(vector<double> r, ll con = 6) {
        ofstream file(out_name, ios::out | ios::app);
        for (int i = 0; i < r.size(); ++i) {
            file << setprecision(con) << fixed << r[i] << " ";
        }
    }

    void output_write_string(vector<string> r) {
        ofstream file(out_name, ios::out | ios::app);
        for (int i = 0; i < r.size(); ++i) {
            file << r[i] << " ";
        }
    }

    void output_write_ln() {
        ofstream file(out_name, ios::out | ios::app);
        file << '\n';
    }
};

#endif //SAMOIC_SAMOIC_H
