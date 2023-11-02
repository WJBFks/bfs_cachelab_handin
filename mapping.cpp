#include <algorithm>
#include <string>
#include <vector>
#include <map>
#include <iostream>
#include <fstream>
#define err(msg) {cerr << msg << endl; exit(1);}
using namespace std;

class Vertex{
public:
    int index;
    int in;
    Vertex(int id=0, int inDegree=0):index(id), in(inDegree){}
};

class Edge{
public:
    int from;
    int to;
    Edge(int from=0, int to=0):from(from), to(to){}
};

vector<Vertex>list;
map<int,int>in_degree;
map<int,int>mapping;
vector<Edge>edge;

void vertex_mapping(string graph_file, string mapping_file){
    // 打开文件
    ifstream fin;
    fin.open(graph_file, ios::in);
    if (!fin.is_open()) {
        err("输入文件打开失败");
    }
    int v_from, v_to;
    // 计算入度
    while(fin>>v_from>>v_to){
        if(in_degree.count(v_from)==0){
            in_degree[v_from] = 0;
        }
        if(in_degree.count(v_to)==0){
            in_degree[v_to] = 1;
        }else{
            in_degree[v_to]++;
        }
    }
    fin.close();
    // map转vector
    for(const auto& m:in_degree){
        list.emplace_back(m.first, m.second);
    }
    // 入度从大到小排序
    sort(list.begin(), list.end(),  [](const Vertex& a,const Vertex& b){
        return a.in > b.in;
    });
    for(int i = 0; i < list.size(); i++) {
        mapping[list[i].index] = i;
    };
    // 输出结果到文件
    if (!mapping_file.empty()){
        ofstream fout;
        fout.open(mapping_file,ios::out);
        if (!fout.is_open()) {
            err("映射文件打开失败");
        }
        for(int i = 0; i < list.size(); i++) {
            const Vertex& v = list[i];
            fout<<v.index<<" "<<i<<endl;
        };
        fout.close();
        cout<<"已将 "<<graph_file<<" 重映射到 "<<mapping_file<<endl;
    }
}

void graph_resort(string graph_file, string resort_file){
    ifstream fin;
    fin.open(graph_file, ios::in);
    if (!fin.is_open()) {
        err("输入文件打开失败");
    }
    ofstream fout;
    fout.open(resort_file,ios::out);
    if (!fout.is_open()) {
        err("输出文件打开失败");
    }
    int v_from, v_to = 0;
    while(fin>>v_from>>v_to){
        edge.emplace_back(mapping[v_from], mapping[v_to]);
    }
    sort(edge.begin(), edge.end(),  [](const Edge& a,const Edge& b){
        if(a.from == b.from)
            return a.to < b.to;
        return a.from < b.from;
    });
    for(const Edge& e : edge){
        fout<<e.from<<" "<<e.to<<endl;
    }
    fin.close();
    fout.close();
    cout<<"已将 "<<graph_file<<" 重排序到 "<<resort_file<<endl;
}

void help(){
    cout<<"包含2-3个参数："<<endl;
    cout<<"输入文件名：原始的文件路径"<<endl;
    cout<<"输出文件名：经过重排后的文件的输出路径"<<endl; 
    cout<<"映射文件名[可选]：输出映射文件到指定路径"<<endl;
}

int main(int argc, char* argv[]) {
    string graph_file;
    string resort_file;
    string mapping_file;
    if(argc>=2&&string(argv[1])=="help"){
        help();
        return 0;
    } else if(argc <= 2){
        err("参数错误！应至少包含两个参数：输入文件名和输出文件名");
    } else {
        graph_file = argv[1];
        resort_file = argv[2];
        if(argc >= 4){
            mapping_file = argv[3];
        }
    }
    vertex_mapping(graph_file,mapping_file);
    graph_resort(graph_file,resort_file);
    return 0;
}