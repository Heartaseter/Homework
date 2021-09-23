#include <iostream>
#include <string>
#include <fstream>
#include<sstream>

using namespace std;

int keyWordsReturn(string address);

int switchReturn(string address);

void caseReturn(int *p_howMany, int howMany,string address);

int if_Return(string address);

int elseIfReturn(string address);

int main() {
    //string address = "D:\\CLionProjects\\EE308_Lab2\\test.c";
    string address;
    int level;
    cout<< "please enter the file address : "<<endl;
    cin>>address;
    cout <<"please enter the level you want"<<endl;
    cin>>level;
    switch(level){
        case 1:
            cout<<"total num:"<<keyWordsReturn(address)<<endl;
            break;
        case 2:{
            cout<<"total num:"<<keyWordsReturn(address)<<endl;
            int a = switchReturn(address);
            int howMany[a];
            cout<<"switch num:"<<a<<endl;
            caseReturn(howMany,a,address);
            cout<<"case num :";
            for (int i = 0; i < a; ++i) {
                cout <<howMany[i]<<" ";
            }
            break;
        }
        case 3: {
            cout << "total num:" << keyWordsReturn(address) << endl;
            int a = switchReturn(address);
            int howMany[a];
            cout << "switch num:" << a << endl;
            caseReturn(howMany, a, address);
            cout << "case num :";
            for (int i = 0; i < a; ++i) {
                cout << howMany[i] << " ";
            }
            cout<<endl;
            cout<<"if-else num: "<<if_Return(address)-elseIfReturn(address)<<endl;
            break;
        }
        case 4:{
            cout << "total num:" << keyWordsReturn(address) << endl;
            int a = switchReturn(address);
            int howMany[a];
            cout << "switch num:" << a << endl;
            caseReturn(howMany, a, address);
            cout << "case num :";
            for (int i = 0; i < a; ++i) {
                cout << howMany[i] << " ";
            }
            cout<<endl;
            int ElseReturn = elseIfReturn(address);
            cout<<"if-else num: "<<if_Return(address)-ElseReturn<<endl;
            cout<<"if-elseif-if num: "<<ElseReturn<<endl;
            break;
        }

    }

}


int keyWordsReturn(string address) {
    string s1, s2;
    int total;
    string keywords[30] = {"if", "else", "auto", "break", "case", "char", "const", "continue", "default",
                           "do", "enum", "extern", "float", "for", "goto", "int", "long", "register",
                           "return", "short", "signed", "sizeof", "static", "struct", "switch",
                           "typedef", "union", "void", "volatile", "while"};//有do，就不用考虑double关键字，有signed就不用考虑unsigned
    //32个字符串，第一版本便是让他们搜索，接下来可以通过分类索引来改进搜索的速度,有doubule便多了一个do，除此之外保留关键词会不会一行出现相同的两个(可以拆分成一个个单词)，开关次数过多
    for (int i = 0; i < 30; ++i) {
        ifstream fin(address);
        s1 = keywords[i];
        if (!fin) {
            cout << "文件不能打开" << endl;
        }//检测c文件是否打开
        while (getline(fin, s2)) {
            if (s2.find(s1) < 2000) {//一般来说每行不会超过80个词汇，2000个字符宽度足够
                total++;
            }
        }
        fin.close();
    }
    return total;
}

int switchReturn(string address) {
    string s1, s2;
    int total;
    ifstream fin(address);
    s1 = "switch";
    while (getline(fin, s2)) {
        if (s2.find(s1) < 2000) {//一般来说每行不会超过80个词汇，2000个字符宽度足够
            total++;
        }
    }
    return total;
}
//利用指针传递数组来储存每个switch有几个case，以default作为结尾的识别标志，有些switch没有写default 则会出问题。
//而且这段代码无法识别嵌套
void caseReturn(int *p_howMany, int howMany,string address) {
    string s1, s2, s3;
    int i = 0;
    *(p_howMany + i) = 0;
    s1 = "default";
    s3 = "case";
    ifstream fin(address);
    if (howMany > 0) {
        while (getline(fin, s2)) {
            if (s2.find(s3) < 2000) {
                *(p_howMany + i) += 1;
            } else if (s2.find(s1) < 2000) {
                i++;
            }
        }
    }
}
//一级一级读取，做两级
int if_Return(string address) {
    string s1, s2;
    int ifCount = 0;
    ifstream fin(address);
    if (!fin) {
        cout << "文件不能打开" << endl;
    }//检测c文件是否打开
    s1 = "    } else {";
    while (getline(fin, s2)) {
        if (s2.find(s1)<2000){
            ifCount++;
        }
        if (s2.find("        else {")<2000){
            ifCount++;
        }
    }
    return ifCount;
}

int elseIfReturn(string address){
    string s1, s2;
    int elseifCount = 0;
    s1 = "    if";
    ifstream fin(address);
    if (!fin) {
        cout << "文件不能打开" << endl;
    }//检测c文件是否打开
    while (getline(fin, s2)){
        if (s2.find(s1)<2000){
            while (getline(fin,s2)){
                if (s2.find("    } else if")<2000){
                    while (getline(fin,s2)){
                        if (s2.find("    } else")<2000){
                            elseifCount++;
                            break;
                        }
                        continue;
                    }
                }else{
                    continue;
                }
            }
        }
    }
    fin.close();
    ifstream fin1(address);
    if (!fin1) {
        cout << "文件不能打开" << endl;
    }//检测c文件是否打开
    while (getline(fin1, s2)){
        if (s2.find("        if")<2000){
            while (getline(fin1,s2)){
                if (s2.find("        else if")<2000){
                    while (getline(fin1,s2)){
                        if (s2.find("        else")<2000){
                            elseifCount++;
                            break;
                        }
                        continue;
                    }
                }else{
                    continue;
                }
            }
        }
    }
    fin1.close();
    return elseifCount;
}