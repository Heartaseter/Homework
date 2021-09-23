 # The second homework for this course

| The Link Your Class                        | https://bbs.csdn.net/forums/MUEE308FZ?category=0             |
| ------------------------------------------ | ------------------------------------------------------------ |
| The Link of Requirement of This Assignment | https://bbs.csdn.net/topics/600798588                        |
| The Aim of This Assignment                 | A program extract keywords of different levels from the C or C++ code files that are read in. |
| MU STU ID and FZU STU ID                   | 19105169_831901316                                           |




| GIthub link                                         |
| --------------------------------------------------- |
| https://github.com/Heartaseter/Homework/tree/master |

-------------

# PSP FORM


| Personal Software Process Stages | Estimated Time/minutes | Completed Time/minutes |
| -------------------------------- | ---------------------- | ---------------------- |
| Planning                         | 20                     | 60                     |
| Estimate                         | -                      | -                      |
| Development                      | 30                     | 30                     |
| Analysis                         | 20                     | 20                     |
| Design Spec                      | 30                     | 30                     |
| Design Review                    | 50                     | 50                     |
| Coding Standard                  | 50                     | 50                     |
| Design                           | 60                     | 60                     |
| Coding                           | 500                    | 1000                   |
| Code ReviewPlanning              | 20                     | 20                     |
| Test                             | 30                     | 40                     |
| Reporting                        | 40                     | 40                     |
| Test Report                      | 30                     | 60                     |
| Size Measurement                 | 10                     | 10                     |
| Postmortem&Process Improvement   | 20                     | 20                     |
| total                            | 910                    | 1490                   |

## problem-solving ideas

Question: search keywords in 4 levels

Analysis: when searching for keywords, we should use the comparison method. This time, we compare 32 keywords, store the keywords in an array, and then compare the text with the array.

Since there is only one switch in each switch structure, whether nested or not, you can only count the number of switch keywords

I have a wonderful idea about if and if-else-if structures，If a structure such as if () {} else {} is detected，add one to the if-num，If the else if {} else {} structure is detected, record the if-elseif-else once，use if-num -if-elseif-else num. You can get the number of if-else structures.

If-elseif-else structures num is if-elseif-else num itself.


## keywords

| auto   | break  | case     | char   | const    | continue | default  | do     |
| ------ | ------ | -------- | ------ | -------- | -------- | -------- | ------ |
| double | else   | enum     | extern | float    | for      | goto     | if     |
| int    | long   | register | return | short    | signed   | sizeof   | static |
| struct | switch | typedef  | union  | unsigned | void     | volatile | while  |

-------------

# Design and implementation process

![img](https://img-community.csdnimg.cn/images/5476b0d0c9514e12bbea012f561e1382.png "=600 #center")

Design the infrastructure, select different identification features, test the identification features, and think about new features if there is an error

## keyfunctions flowchart

### keyWordsReturn（）

This function is used to read the number of keywords

![img](https://img-community.csdnimg.cn/images/94c93db0ee2449749555992d4f74e771.png "=300 #center")

### elseIfReturn（）

This function is used to read the number of else if structures

![img](https://img-community.csdnimg.cn/images/7dc4d9c692134cb9af796dec3392ce84.png "=600 #left")

Function if_Return()，I also use a similar method. Because I read by line and convert the file into a string, the spaces are not ignored, so I use indentation to judge the nesting of if else.

-------------

# code analysis

## level 1

```c++
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


```


The code used is not clever enough, limited by my personal ability. My major is EE, and I am not good at coding. The code style is not standardized. I spent a long time looking at the specifications, but it is difficult to remember all. Moreover, due to the course reasons, I have to spend a lot of time on self-study when I have classes again, which is very difficult.

The logic of the code is to read the code line by line and compare the keywords one by one. I use the method of comparing strings. After converting keywords into strings, I will find that some keywords strings are descendants of other keywords.

## level 2

```c++
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


```

As analyzed earlier, there is only one switch keyword in each switch structure.Here, I only need to count the number of switch keywords.

## level 3 and level 4

```c++
int ElseReturn = elseIfReturn(address);
cout<<"if-else num: "<<if_Return(address)-ElseReturn<<endl;
cout<<"if-elseif-if num: "<<ElseReturn<<endl;

```

elseIfReturn() and if_Return() function is to distinguish if-else and if-elseif-else structure.Because there is an inclusive relationship between the two, you can use subtraction to calculate their respective quantities.

The above two functions mainly identify the two structures according to the code style of C + + specification, which is also realized by identifying strings. Therefore, once the code structure is not written in the code style of C + + specification, recognition errors will occur. Due to limited ability, this function can only identify one layer of nesting.

-------------

# Output results


![img](https://img-community.csdnimg.cn/images/c06e3fe5f38144518bebe2fe6a6f55b5.png "=800 #center")

-------------

##  Version update

I learned how to use git to manage versions on the evening of September 23. Before that, I had been using local project to store previous versions. I only updated four versions.


![img](https://img-community.csdnimg.cn/images/a4f0fa707bb740d38c20282c275c3d49.png "=800 #left")

-------------

# summary

This assignment is not difficult in code conception, but I have never heard of the two links of unit test and performance test because such a project has never been involved in professional courses in the past. Because I am still in class these days, I have not been able to successfully take enough time to learn the unit test link of code optimization, whether it is programming or version management, We also have not received any relevant education.
This assignment was completed without any relevant courses. Of course, it does not rule out that some students are particularly interested in in in-depth study in this aspect.
Although it's not difficult to complete the requirements, my ability is very limited. I thought of many bugs, but I didn't have time to update them. In the previous version of code update, I didn't learn how to use GitHub, so it's a pity that I only have four versions on GitHub. Because when I learned to use GitHub, the code function has been improved to a certain extent, and I also annotated the possible bugs next to the code. Due to time, I had no time to make large-scale changes and updates to the code.
Limited by our EE specialty's lack of software related knowledge, the methods I use to solve problems are very elementary, which may also be cumbersome and low-energy. I hope to learn relevant knowledge about coding in class, at least the guidance of algorithms or advanced skills.
Although we are already a junior, there are still many courses and there is not much spare time. Self-study needs clear guidance, otherwise homework oriented self-study can only be inefficient and laborious.
