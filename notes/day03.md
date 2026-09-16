# Day 03｜C++ 基础、Linux 编译与 CMake 入门

## 1. 今日学习目标

Day 03 的主要目标不是快速进入 ONNX、TensorRT，而是继续补齐 Edge AI / AI Systems 所需要的 C++ 工程基础。

今天主要学习：

- C++ 基础语法继续巩固
- `array` 和 `vector` 的基本概念
- Linux / WSL 下编译和运行 C++ 程序
- 理解源代码、编译器和可执行程序之间的关系
- 第一次学习 CMake
- 创建并成功构建第一个 CMake 项目
- 理解 `CMakeLists.txt`
- 理解 `cmake ..` 和 `cmake --build .`
- 理解 source directory 和 build directory
- 认识 VS Code + WSL 的 C++ 开发方式
- 完成 LeetCode 217 Contains Duplicate
- 更新 GitHub 学习记录

---

# 2. 我的长期学习路线

当前目标岗位：

- Edge AI Engineer
- AI Deployment Engineer
- 推理部署工程师
- AI Systems Engineer
- AI Infra Engineer
- GPU / NPU 推理优化相关岗位

目前整体学习路线：

```text
C++ 基础
    ↓
Linux 基础
    ↓
Git / GitHub
    ↓
CMake
    ↓
GDB / Debug
    ↓
C++ 工程化
    ↓
ONNX
    ↓
ONNX Runtime
    ↓
模型量化
    ↓
TensorRT
    ↓
CUDA
    ↓
GPU / NPU Optimization
    ↓
AI Systems / AI Infra
```

当前阶段：

```text
C++ + Linux + Git + CMake
```

目标不是一次性把所有工具学完，而是先建立工程基础，再逐渐进入模型部署和推理优化。

---

# 3. Day 03 推荐学习资源

后续不只依赖视频学习，而是使用：

```text
学习计划
   ↓
优质教程 [?25l[?12l[?25h[26;1H[?1049l[23;0;0t[?1l>[?1049h[22;0;0t[1;26r[?12l[?25h[39;49m]104(B[m[4l[?7h[H[2J[?2004h[?1h=[?1h=(B[0;7m  GNU nano 8.7.1                                                             New Buffer *                                                                     [1;157H(B[m[2d```[4d建立了第一层工程基础。[6d当前阶段不追求学得快。[8d优先保证：[10d```text[11d基础理解正确[12d+[13d自己真正运行过[14d+[15d知道命令在干什么[16d+[17d能够处理基础报错[18d+[19d持续形成 GitHub 学习记录[20d```[25d(B[0;7m^C(B[m Cancel[?25l[A(B[0;7mSave modified buffer?                                                                                                                                         [25;1H Y(B[m Yes[K[26d(B[0;7m N(B[m No[26;17H(B[0;7m^C(B[m Cancel[24;23H[?12l[?25h[?25l[?12l[?25h[26;1H[?1049l[23;0;0t[?1l>[?1049h[22;0;0t[1;26r[?12l[?25h[39;49m]104(B[m[4l[?7h[H[2J(B[0;7m  GNU nano 8.7.1                                                             New Buffer *       [2d(B[m```[4d建立了第一层工程基础。[6d当前阶段不追求学得快。[8d优先保证：[10d```text[11d基础理解正确[12d+[13d自己真正运行过[14d+[15d知道命令在干什么[16d+[17d能够处理基础报错[18d+[19d持续形成 GitHub 学习记录[20d```[24d(B[0;7mSave modified buffer?                                                                           [25d Y(B[m Yes[26d(B[0;7m N(B[m No[26;17H(B[0;7m^C(B[m Cancel[H[?2004h[?1h=[?1h=[24d[J[1;73H(B[0;7mNew Buffer *     [97G                                                    [1;147H(B[m[25d(B[0;7m^C(B[m Cancel[?25l[A(B[0;7mSave modified buffer?                                                                                                                               [25;1H Y(B[m Yes[K[26d(B[0;7m N(B[m No[26;17H(B[0;7m^C(B[m Cancel[24;23H[?12l[?25h[?25l[?12l[?25h[26;1H[?1049l[23;0;0t[?1l>[?1049h[22;0;0t[1;27r[?12l[?25h[39;49m]104(B[m[4l[?7h[H[2J[?2004h[?1h=[?1h=(B[0;7m  GNU nano 8.7.1                                                        New Buffer *                                                                [1;147H(B[m[2d```[4d建立了第一层工程基础。[6d当前阶段不追求学得快。[8d优先保证：[10d```text[11d基础理解正确[12d+[13d自己真正运行过[14d+[15d知道命令在干什么[16d+[17d能够处理基础报错[18d+[19d持续形成 GitHub 学习记录[20d```[26d(B[0;7m^C(B[m Cancel[?25l[A(B[0;7mSave modified buffer?                                                                                                                               [26;1H Y(B[m Yes[K[27d(B[0;7m N(B[m No[27;17H(B[0;7m^C(B[m Cancel[25;23H[?12l[?25h[?25l[?12l[?25h[27;1H[?1049l[23;0;0t[?1l>[?2004l`text
启动程序
   ↓
找到 main()
   ↓
从 main 第一条语句开始执行
```

---

## 4.3 `cout`

```cpp
cout << "Hello" << endl;
```

作用：

向标准输出，也就是终端输出内容。

例如：

```cpp
cout << 10 << endl;
```

输出：

```text
10
```

---

## 4.4 `cin`

```cpp
int age;

cin >> age;
```

作用：

从键盘读取输入并保存到变量中。

---

# 5. C++ 数据类型

当前主要认识：

| 类型 | 用途 | 示例 |
|---|---|---|
| `int` | 整数 | `10` |
| `double` | 小数 | `3.14` |
| `char` | 单个字符 | `'A'` |
| `string` | 字符串 | `"hello"` |
| `bool` | 真 / 假 | `true` |

例如：

```cpp
int age = 24;
double score = 95.5;
char grade = 'A';
string name = "zp";
bool success = true;
```

和 Python 相比：

Python：

```python
a = 10
```

C++：

```cpp
int a = 10;
```

C++ 通常需要明确变量的数据类型。

这是后续理解：

```text
内存
指针
引用
Tensor 数据类型
CPU / GPU 数据存储
```

的基础。

---

# 6. 条件判断

基本结构：

```cpp
if (condition)
{
    // 条件成立
}
else
{
    // 条件不成立
}
```

例如：

```cpp
if (age >= 18)
{
    cout << "Adult" << endl;
}
else
{
    cout << "Not adult" << endl;
}
```

常用比较运算符：

```text
>      大于
<      小于
>=     大于等于
<=     小于等于
==     等于
!=     不等于
```

需要注意：

```cpp
a = 10;
```

表示：

```text
赋值
```

而：

```cpp
a == 10
```

表示：

```text
比较 a 是否等于 10
```

---

# 7. for 循环

基本形式：

```cpp
for (int i = 0; i < 5; i++)
{
    cout << i << endl;
}
```

执行逻辑：

```text
int i = 0
    ↓
判断 i < 5
    ↓
成立
    ↓
执行循环体
    ↓
i++
    ↓
再次判断
```

输出：

```text
0
1
2
3
4
```

需要开始形成：

```text
下标从 0 开始
```

的思维。

---

# 8. Array 与 Vector

## 8.1 Array

例如：

```cpp
int nums[5] = {1, 2, 3, 4, 5};
```

内存逻辑可以暂时理解为：

```text
index:    0   1   2   3   4
        +---+---+---+---+---+
value:  | 1 | 2 | 3 | 4 | 5 |
        +---+---+---+---+---+
```

访问第一个元素：

```cpp
nums[0]
```

结果：

```text
1
```

---

## 8.2 Vector

`vector` 是 C++ STL 中非常重要的容器。

目前可以暂时理解成：

```text
可以动态调整大小的数组
```

例如：

```cpp
vector<int> nums = {1, 2, 3};
```

添加：

```cpp
nums.push_back(4);
```

获取元素数量：

```cpp
nums.size();
```

访问：

```cpp
nums[0];
```

遍历：

```cpp
for (int i = 0; i < nums.size(); i++)
{
    cout << nums[i] << endl;
}
```

后续 LeetCode 和 Edge AI C++ 程序都会频繁使用 `vector`。

---

# 9. Linux / WSL 基础命令

今天使用的一些命令不仅要会敲，还要知道具体是什么意思。

---

## 9.1 `pwd`

```bash
pwd
```

含义：

```text
Print Working Directory
```

用于查看：

```text
我现在在哪个目录？
```

例如：

```text
/home/zp/edge-ai-learning
```

以后遇到：

```text
找不到文件
找不到 CMakeLists.txt
路径错误
```

第一件事可以先执行：

```bash
pwd
```

---

## 9.2 `ls`

```bash
ls
```

作用：

查看当前目录中的文件。

例如：

```text
CMakeLists.txt
main.cpp
build
```

更详细：

```bash
ls -la
```

其中：

```text
-l
```

表示详细列表。

```text
-a
```

表示包括隐藏文件。

---

## 9.3 `cd`

```bash
cd directory
```

作用：

Change Directory，即切换目录。

例如：

```bash
cd cpp/day03
```

进入：

```text
cpp/day03
```

---

## 9.4 `~`

Linux 中：

```text
~
```

通常表示：

```text
当前用户的 Home Directory
```

所以：

```bash
cd ~
```

会回到：

```text
/home/zp
```

而：

```bash
cd ~/edge-ai-learning
```

相当于进入：

```text
/home/zp/edge-ai-learning
```

---

## 9.5 `.`

```text
.
```

表示：

```text
当前目录
```

例如：

```bash
cmake --build .
```

这里的 `.` 表示：

```text
构建当前目录
```

---

## 9.6 `..`

```text
..
```

表示：

```text
上一级目录
```

例如当前位于：

```text
cmake_demo/build
```

那么：

```bash
cd ..
```

会回到：

```text
cmake_demo
```

同样：

```bash
cmake ..
```

表示：

```text
让 CMake 使用上一级目录作为 source directory
```

---

## 9.7 `mkdir`

```bash
mkdir build
```

含义：

```text
Make Directory
```

作用：

创建目录。

例如创建：

```text
build/
```

---

## 9.8 `mkdir -p`

例如：

```bash
mkdir -p cpp/day03/cmake_demo
```

`-p` 的作用是：

如果中间目录不存在，也一起创建。

例如：

```text
cpp/
└── day03/
    └── cmake_demo/
```

可以一次创建。

---

## 9.9 `cat`

```bash
cat CMakeLists.txt
```

当前阶段主要用于：

```text
直接在终端查看文本文件内容
```

当 CMake 报错时，可以快速执行：

```bash
cat CMakeLists.txt
```

检查内容。

---

## 9.10 `nano`

```bash
nano CMakeLists.txt
```

作用：

使用终端文本编辑器 Nano 打开文件。

常用：

```text
Ctrl + O    保存
Enter       确认文件名
Ctrl + X    退出
```

不过后续写较多代码时，更推荐使用 VS Code。

---

# 10. C++ 编译原理初步认识

今天非常重要的一点是：

C++ 源文件本身不能直接被 CPU 执行。

例如：

```text
main.cpp
```

需要经过编译。

基本流程：

```text
main.cpp
   ↓
Compiler
   ↓
Machine Code
   ↓
Executable
   ↓
CPU 执行
```

Linux 下使用：

```text
g++
```

作为 C++ 编译器。

---

# 11. `g++ main.cpp -o main` 命令解释

命令：

```bash
g++ main.cpp -o main
```

拆开理解：

### `g++`

```text
调用 GNU C++ Compiler
```

### `main.cpp`

```text
需要编译的源代码
```

### `-o`

```text
指定 Output 文件名
```

### `main`

表示最终输出程序叫：

```text
main
```

因此：

```bash
g++ main.cpp -o main
```

可以理解为：

```text
使用 g++
   ↓
编译 main.cpp
   ↓
输出 main
```

---

# 12. `./main` 为什么可以运行程序

编译完成之后：

```text
main
```

成为 Linux 可执行程序。

运行：

```bash
./main
```

这里：

```text
.
```

表示当前目录。

所以：

```text
./main
```

实际意思是：

```text
运行当前目录下的 main
```

---

# 13. CMake 是什么

Day 03 最重要的新工具是：

```text
CMake
```

CMake 本身不是 C++ 编译器。

这是今天必须记住的概念。

```text
CMake ≠ Compiler
```

真正编译 C++ 的仍然是：

```text
g++
```

CMake 更准确的作用是：

```text
描述和组织整个项目应该如何构建
```

---

# 14. 为什么需要 CMake

如果程序只有：

```text
main.cpp
```

可以：

```bash
g++ main.cpp -o main
```

但项目以后可能变成：

```text
project/
├── main.cpp
├── model.cpp
├── model.h
├── preprocess.cpp
├── preprocess.h
├── inference.cpp
├── inference.h
└── utils.cpp
```

再加入：

```text
OpenCV
ONNX Runtime
TensorRT
CUDA
```

如果全部手动写 `g++` 命令，会越来越复杂。

需要处理：

```text
有哪些 .cpp？
头文件在哪里？
库文件在哪里？
需要链接哪些库？
使用什么 C++ 标准？
Debug 还是 Release？
CUDA 在哪里？
TensorRT 在哪里？
```

CMake 就是用来管理这些关系。

---

# 15. CMake 的整体工作原理

目前可以理解为：

```text
开发者
   ↓
编写 CMakeLists.txt
   ↓
CMake 读取工程配置
   ↓
生成 Build System
   ↓
Make / Ninja
   ↓
调用 g++
   ↓
编译 + 链接
   ↓
生成程序
```

注意：

CMake：

```text
负责描述和生成构建规则
```

g++：

```text
负责真正编译 C++ 代码
```

---

# 16. 第一个 CMakeLists.txt

今天使用：

```cmake
cmake_minimum_required(VERSION 3.10)

project(cmake_demo)

add_executable(main main.cpp)
```

---

## 16.1 `cmake_minimum_required`

```cmake
cmake_minimum_required(VERSION 3.10)
```

表示：

```text
项目要求最低 CMake 版本
```

目前学习阶段主要知道它一般放在 CMakeLists.txt 开头即可。

---

## 16.2 `project`

```cmake
project(cmake_demo)
```

告诉 CMake：

```text
开始描述一个项目
```

项目名：

```text
cmake_demo
```

CMake 还会利用这个阶段检查：

```text
编译器
构建环境
平台
```

等信息。

---

## 16.3 `add_executable`

```cmake
add_executable(main main.cpp)
```

含义：

```text
创建一个 executable target
```

名字叫：

```text
main
```

它的源代码：

```text
main.cpp
```

可以简单理解为：

```text
main.cpp
   ↓
构建
   ↓
main
```

和：

```bash
g++ main.cpp -o main
```

目标类似。

---

# 17. 什么是 Target

这是 CMake 后续非常重要的概念。

今天第一次接触：

```cmake
add_executable(main main.cpp)
```

其中：

```text
main
```

不只是一个普通文件名。

在 CMake 中，它是一个：

```text
Target
```

当前可以简单理解：

```text
Target = CMake 要构建的一个目标
```

以后 Target 可能是：

```text
Executable
Library
```

例如未来可能出现：

```text
edge_ai_app
onnx_inference
tensorrt_demo
```

每一个都可以作为 Target。

之后很多现代 CMake 命令都是围绕 Target 使用的，例如：

```text
target_sources
target_include_directories
target_link_libraries
```

---

# 18. 为什么创建 build 目录

项目：

```text
cmake_demo/
├── CMakeLists.txt
├── main.cpp
└── build/
```

不建议把 CMake 生成的所有文件直接放进源码目录。

因此单独建立：

```text
build/
```

这种方式叫：

```text
Out-of-source Build
```

也就是：

```text
Source Code
和
Build Artifacts
分离
```

优势：

```text
源码目录更干净
更容易删除并重新构建
Git 不需要管理大量构建文件
不同构建配置更容易管理
```

---

# 19. `cmake ..` 原理

当位于：

```text
cmake_demo/build/
```

执行：

```bash
cmake ..
```

其中：

```text
..
```

表示上一级目录：

```text
cmake_demo/
```

那里存在：

```text
CMakeLists.txt
```

所以：

```bash
cmake ..
```

实际上是在告诉 CMake：

```text
source directory 在上一级
```

CMake 接下来：

```text
读取 CMakeLists.txt
        ↓
检查编译器
        ↓
处理项目配置
        ↓
生成 Build System
```

成功时通常会看到：

```text
Configuring done
Generating done
```

这里非常重要：

```text
cmake ..
```

主要是在：

```text
Configure + Generate
```

并不是简单地等同于：

```text
编译 C++
```

---

# 20. `cmake --build .` 原理

接下来：

```bash
cmake --build .
```

其中：

```text
.
```

表示：

```text
当前 build 目录
```

这一条命令告诉 CMake：

```text
构建当前已经配置好的工程
```

大致流程：

```text
cmake --build .
      ↓
调用底层 Build Tool
      ↓
例如 Make / Ninja
      ↓
调用 g++
      ↓
Compile
      ↓
Link
      ↓
生成 executable
```

所以可以这样记：

```text
cmake ..          → 准备怎么构建

cmake --build .   → 真正执行构建
```

---

# 21. Configure、Compile 和 Link

今天开始认识 C++ 工程的重要阶段。

简化流程：

```text
CMake Configure
      ↓
Compile
      ↓
Link
      ↓
Executable
```

### Configure

确定：

```text
有哪些源码
使用什么编译器
有哪些依赖
需要生成什么 Target
```

### Compile

把：

```text
.cpp
```

逐渐转化为机器可以进一步处理的目标代码。

### Link

把：

```text
多个目标文件
+
需要的 Library
```

连接起来。

最终生成：

```text
Executable
```

这个知识后续学习：

```text
ONNX Runtime
TensorRT
CUDA
```

时非常重要。

---

# 22. 今天使用的 CMake 完整流程

第一种方式：

```bash
mkdir build
cd build
cmake ..
cmake --build .
./main
```

完整含义：

```text
mkdir build
     ↓
创建构建目录

cd build
     ↓
进入构建目录

cmake ..
     ↓
读取上一级 CMakeLists.txt
配置 + 生成 Build System

cmake --build .
     ↓
构建当前工程

./main
     ↓
运行最终程序
```

---

# 23. CMake 的现代写法

后续还会逐渐使用一种更直接的写法：

```bash
cmake -S . -B build
cmake --build build
```

这里：

```text
-S
```

表示：

```text
Source Directory
```

而：

```text
-B
```

表示：

```text
Build Directory
```

所以：

```bash
cmake -S . -B build
```

可以理解为：

```text
Source = 当前目录
Build  = build 目录
```

然后：

```bash
cmake --build build
```

直接构建：

```text
build/
```

这和今天学习的：

```bash
mkdir build
cd build
cmake ..
cmake --build .
```

核心原理是一样的。

当前阶段两种写法都需要看得懂。

以后更推荐逐渐使用：

```bash
cmake -S . -B build
cmake --build build
```

因为 Source Directory 和 Build Directory 的含义更加明确。

---

# 24. 今天遇到的错误 1：找不到 CMakeLists.txt

错误：

```text
The source directory does not appear to contain CMakeLists.txt.
```

原因：

```bash
cmake ..
```

会让 CMake 去上一级目录寻找：

```text
CMakeLists.txt
```

但是对应位置没有找到。

解决思路：

第一步：

```bash
pwd
```

确认自己在哪里。

第二步：

```bash
ls
```

确认当前文件。

第三步：

```bash
ls ..
```

查看上一级。

然后确认：

```text
CMakeLists.txt
```

是否真的存在。

---

# 25. 今天遇到的错误 2：CMake Parse Error

出现：

```text
Parse error.
Expected a newline, got identifier with text "mkdir".
```

原因：

误把：

```bash
mkdir build
```

这种 Shell 命令写到了：

```text
CMakeLists.txt
```

里面。

这次错误让我进一步理解：

### Shell 命令

在终端运行：

```bash
mkdir build
cd build
cmake ..
```

### CMake Language

写在：

```text
CMakeLists.txt
```

里面：

```cmake
project(...)
add_executable(...)
```

它们属于不同的语言，不能混在一起。

---

# 26. VS Code、WSL、Linux 之间的关系

后续计划采用：

```text
Windows
   ↓
VS Code
   ↓
WSL
   ↓
Linux Environment
   ↓
C++ / CMake / Git
```

主要分工：

### VS Code

主要负责：

```text
编写代码
查看目录
修改 CMakeLists.txt
后续调试程序
```

### WSL

提供：

```text
Linux 开发环境
```

### Terminal

执行：

```text
g++
cmake
git
Linux commands
```

后续进入：

```text
ONNX Runtime
TensorRT
CUDA
```

仍然会大量使用这种开发模式。

---

# 27. CMake 为什么和 Edge AI 有关系

目前学习 CMake 不是单纯为了“会一个工具”。

真正原因是以后 Edge AI C++ 项目可能变成：

```text
MyEdgeAIProject/
├── CMakeLists.txt
├── src/
│   ├── main.cpp
│   ├── preprocess.cpp
│   ├── inference.cpp
│   └── postprocess.cpp
├── include/
│   ├── preprocess.h
│   └── inference.h
├── models/
│   └── model.onnx
└── build/
```

项目还可能需要：

```text
OpenCV
+
ONNX Runtime
+
TensorRT
+
CUDA
```

最终：

```text
自己的 C++ Code
        +
第三方 Library
        +
CUDA / TensorRT
        ↓
      CMake
        ↓
     Build
        ↓
Edge AI Inference Application
```

所以 CMake 是：

```text
C++ 基础
```

向：

```text
真正 C++ 工程
```

过渡的重要工具。

---

# 28. 当前暂时不用深入的 CMake 内容

目前不追求一次学完 CMake。

以下命令暂时只知道名字：

```cmake
add_library()

target_sources()

target_include_directories()

target_link_libraries()

find_package()
```

后续按照：

```text
实际遇到问题
      ↓
学习一个新命令
      ↓
马上在项目里使用
```

的方式学习。

不要脱离实际项目死记全部 CMake API。

---

# 29. LeetCode

Day 03 完成：

| No. | Problem | Topic | Difficulty | Status |
| ---: | ------- | ----- | ---------- | ------ |
| 217 | Contains Duplicate / 存在重复元素 | Array / Hash Table | Easy | Completed |

目前：

```text
Total Solved: 5
```

当前 LeetCode 学习目的不是大量刷题，而是逐渐熟悉：

```text
Array
Vector
Hash Table
Two Pointers
STL
Time Complexity
```

同时提高：

```text
阅读 C++ 代码
理解 STL
独立写基础算法
口述算法思路
```

按照当前规则：

```text
GitHub 只记录题目和完成状态
不上传 LeetCode 题解源代码
```

---

# 30. 当前 LeetCode Statistics

```text
Total Solved: 5
```

### Topic Statistics

```text
Array: 4
Hash Table: 3
Two Pointers: 2
```

---

# 31. Git / GitHub

今天学习结束后继续使用 Git 管理学习记录。

---

## `git status`

```bash
git status
```

作用：

查看：

```text
哪些文件被修改
哪些文件新增
哪些文件删除
哪些文件已经进入 staging area
```

提交前应养成先执行：

```bash
git status
```

的习惯。

---

## `git add .`

```bash
git add .
```

含义：

将当前目录及子目录相关修改加入：

```text
Staging Area
```

也就是：

```text
准备提交
```

---

## `git commit`

例如：

```bash
git commit -m "Day 03: learn C++ basics and CMake"
```

含义：

把当前 staged changes 保存为一次 Git commit。

---

## `git push`

```bash
git push
```

作用：

把本地 commit 上传到 GitHub Remote Repository。

因此基本流程：

```text
修改文件
   ↓
git status
   ↓
git add
   ↓
git commit
   ↓
git push
   ↓
GitHub
```

---

# 32. Day 03 今日完成内容

- [x] C++ 基础继续学习
- [x] `cout` / `cin`
- [x] 基本数据类型
- [x] `if / else`
- [x] `for`
- [x] Array 基础
- [x] Vector 基础
- [x] 理解 C++ 源码和可执行程序关系
- [x] 使用 `g++` 编译 C++ 程序
- [x] 第一次学习 CMake
- [x] 创建 `CMakeLists.txt`
- [x] 理解 `project()`
- [x] 理解 `add_executable()`
- [x] 理解 build directory
- [x] 成功执行 `cmake ..`
- [x] 成功执行 `cmake --build .`
- [x] 成功完成第一个 CMake 项目
- [x] 理解 CMake 与 g++ 的区别
- [x] 理解 `.`
- [x] 理解 `..`
- [x] 解决 CMake 找不到 `CMakeLists.txt` 的问题
- [x] 解决 CMake Parse Error
- [x] 完成 LeetCode 217
- [x] 更新 LeetCode 学习记录

---

# 33. Day 03 最重要的知识

今天最重要的不是记：

```bash
cmake ..
```

而是理解整个过程：

```text
写 C++ 源代码
      ↓
CMakeLists.txt 描述工程
      ↓
CMake Configure
      ↓
生成 Build System
      ↓
Build Tool
      ↓
Compiler
      ↓
Compile
      ↓
Link
      ↓
Executable
      ↓
运行程序
```

这是后续：

```text
ONNX Runtime
TensorRT
CUDA
AI Systems
```

必须具备的工程思维。

---

# 34. 当前仍然需要巩固

目前还不能认为 C++ 和 CMake 已经掌握。

后续继续加强：

### C++

```text
Function
Parameter
Return Value
Reference
Pointer
const
STL
Class
Memory
```

### C++ 工程

```text
.h
.cpp
Header File
Multiple Source Files
Library
```

### CMake

```text
Target
Multiple Source Files
Library
Include Directory
Link Library
Third-party Library
```

### Linux

```text
文件操作
权限
进程
环境变量
路径
Shell
```

### 调试

```text
GDB
Breakpoint
Call Stack
Variable Inspection
```

---

# 35. Day 04 学习路线

Day 04 不急着进入 ONNX。

下一阶段优先：

```text
C++ Function
     ↓
参数和返回值
     ↓
.h Header
     ↓
.cpp Source
     ↓
多文件 C++ Project
     ↓
CMake 构建多文件项目
```

同时继续：

```text
LeetCode
+
Linux
+
Git
+
真实 Edge AI 岗位技能分析
```

---

# 36. 后续学习方法

从 Day 03 开始固定采用：

```text
① 明确当天目标
       ↓
② LearnCpp / 官方教程学习
       ↓
③ 自己手敲代码
       ↓
④ Linux / WSL 实际运行
       ↓
⑤ 阅读错误信息
       ↓
⑥ 自己定位问题
       ↓
⑦ 解决问题
       ↓
⑧ 总结原理
       ↓
⑨ 更新 GitHub
```

学习时不追求：

```text
今天看了多少小时视频
```

而追求：

```text
我是否理解？
我是否自己敲过？
我是否运行成功？
报错是否知道原因？
我能否解释原理？
第二天还能否自己写出来？
```

---

# 37. Day 03 Summary

Day 03 是从：

```text
“学习 C++ 语法”
```

开始向：

```text
“理解 C++ 工程”
```

过渡的一天。

今天第一次真正建立：

```text
Source Code
    ↓
Build Configuration
    ↓
Build System
    ↓
Compiler
    ↓
Linker
    ↓
Executable
```

的基本概念。

这为后续：

```text
C++
→ Linux
→ CMake
→ ONNX
→ ONNX Runtime
→ TensorRT
→ CUDA
→ GPU / NPU Optimization
→ AI Systems
```

建立了第一层工程基础。

当前阶段不追求学得快。

优先保证：

```text
基础理解正确
+
自己真正运行过
+
知道命令在干什么
+
能够处理基础报错
+
持续形成 GitHub 学习记录



