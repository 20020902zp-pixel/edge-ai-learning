# Day 04｜C++ 指针、引用与 Tensor 内存基础

## 1. 今日学习目标

今天主要学习 C++ 中与内存相关的基础知识，为后续 ONNX Runtime、TensorRT、CUDA 和模型部署做准备。

今天重点掌握：

- 变量与内存地址
- 指针 `*`
- 取地址 `&`
- 解引用 `*p`
- 引用 `&`
- `const &`
- `nullptr`
- 栈 Stack 与堆 Heap
- `new / delete`
- 悬空指针
- `std::vector`
- `vector.data()`
- 指针偏移
- 一维数组与多维 Tensor
- NCHW 内存布局
- Tensor 的 Data + Shape
- `int64_t`
- `sizeof()`

---

# 2. 变量、值与地址

定义一个普通变量：

```cpp
int a = 10;
```

可以理解为：

```text
变量名：a
变量值：10
内存地址：例如 0x1000
```

访问变量的值：

```cpp
a
```

获取变量地址：

```cpp
&a
```

示例：

```cpp
#include <iostream>

int main()
{
    int a = 10;

    std::cout << "a  = " << a << std::endl;
    std::cout << "&a = " << &a << std::endl;

    return 0;
}
```

核心：

```text
a   → 变量的值
&a  → 变量的地址
```

---

# 3. 指针 Pointer

指针本质上是一个“保存地址的变量”。

```cpp
int a = 10;

int* p = &a;
```

这里：

```cpp
int* p;
```

表示：

> p 是一个指向 int 类型数据的指针。

而：

```cpp
p = &a;
```

表示：

> 把 a 的地址保存到 p 中。

因此：

```text
a = 10
&a = a 的地址
p = a 的地址
```

所以：

```cpp
p == &a
```

---

# 4. 解引用 `*p`

当：

```cpp
int* p = &a;
```

时：

```cpp
p
```

表示地址。

而：

```cpp
*p
```

表示：

> 找到 p 保存的地址，然后读取该地址中的数据。

例如：

```cpp
int a = 10;
int* p = &a;

std::cout << *p << std::endl;
```

输出：

```text
10
```

因此：

```text
&a == p
a  == *p
```

这两个关系非常重要。

---

# 5. 通过指针修改变量

```cpp
int a = 10;
int* p = &a;

*p = 20;
```

此时：

```cpp
a == 20
```

原因：

```text
p
↓
保存 a 的地址
↓
*p
↓
访问 a 所在的内存
↓
修改这块内存
```

所以：

```cpp
*p = 20;
```

实际上修改的是 `a`。

---

# 6. 引用 Reference

定义：

```cpp
int a = 10;
int& ref = a;
```

这里：

```cpp
ref
```

可以理解为：

> a 的另一个名字。

所以：

```cpp
ref = 30;
```

相当于：

```cpp
a = 30;
```

引用与普通变量不是复制关系，而是操作同一个对象。

---

# 7. 为什么需要引用

普通函数参数：

```cpp
void change(int x)
{
    x = 100;
}
```

调用：

```cpp
int a = 10;
change(a);
```

结果：

```cpp
a == 10
```

原因：

```text
a
↓
复制
↓
x
```

修改的是复制出来的 `x`。

如果改成引用：

```cpp
void change(int& x)
{
    x = 100;
}
```

调用：

```cpp
change(a);
```

此时 `x` 就是 `a` 的引用。

结果：

```cpp
a == 100
```

---

# 8. `const &`

非常常见的 C++ 写法：

```cpp
void process(const std::vector<float>& data)
```

可以拆成：

```text
&
→ 不复制原对象

const
→ 不允许修改原对象
```

所以：

```cpp
const std::vector<float>& data
```

表示：

> 直接读取原来的 vector，但是函数不允许修改它。

三种写法对比：

```cpp
void func(std::vector<float> data);
```

含义：

```text
复制一份数据
```

---

```cpp
void func(std::vector<float>& data);
```

含义：

```text
不复制
可以修改原数据
```

---

```cpp
void func(const std::vector<float>& data);
```

含义：

```text
不复制
不能修改原数据
```

以后处理图片、Tensor、大型数组时，`const &` 会非常常见。

---

# 9. 指针和引用的区别

指针：

```cpp
int* p = &a;
```

引用：

```cpp
int& ref = a;
```

主要区别：

```text
指针
→ 保存地址
→ 可以改变指向
→ 可以是 nullptr
→ 使用 *p 访问数据
```

```text
引用
→ 原变量的别名
→ 通常创建后绑定对象
→ 使用方式和普通变量类似
```

例如：

```cpp
int a = 10;
int b = 20;

int* p = &a;

p = &b;
```

此时 `p` 从指向 `a` 改成指向 `b`。

---

# 10. 空指针 nullptr

定义：

```cpp
int* p = nullptr;
```

表示：

> p 当前没有指向任何有效对象。

错误：

```cpp
int* p = nullptr;

std::cout << *p << std::endl;
```

因为 `p` 没有有效地址。

这种行为可能导致：

```text
Segmentation fault
```

安全写法：

```cpp
if (p != nullptr)
{
    std::cout << *p << std::endl;
}
```

或者：

```cpp
if (p)
{
    std::cout << *p << std::endl;
}
```

---

# 11. Stack 与 Heap

## Stack 栈

例如：

```cpp
int a = 10;
```

局部变量一般存储在栈中。

特点：

```text
自动申请
自动释放
速度快
生命周期通常与作用域有关
```

---

## Heap 堆

例如：

```cpp
int* p = new int;
```

表示：

> 在堆上申请一块能够存放 int 的内存。

赋值：

```cpp
*p = 100;
```

释放：

```cpp
delete p;
```

特点：

```text
程序主动申请
程序负责释放
```

---

# 12. new 与 delete

申请：

```cpp
int* p = new int;
```

使用：

```cpp
*p = 100;
```

释放：

```cpp
delete p;
p = nullptr;
```

如果只 `new` 不 `delete`：

```text
可能产生 Memory Leak
内存泄漏
```

---

# 13. 悬空指针 Dangling Pointer

例如：

```cpp
int* p = new int;

delete p;
```

这里内存已经释放，但 `p` 可能仍然保存原来的地址。

此时：

```text
p
```

就是悬空指针。

如果再次：

```cpp
*p
```

属于未定义行为。

因此通常：

```cpp
delete p;
p = nullptr;
```

---

# 14. 动态数组

传统方式：

```cpp
int* data = new int[5];
```

释放时需要：

```cpp
delete[] data;
```

注意：

```text
new       ↔ delete
new[]     ↔ delete[]
```

但是现代 C++ 中，一般更推荐使用：

```cpp
std::vector
```

---

# 15. std::vector

例如：

```cpp
std::vector<int> data = {
    10,
    20,
    30
};
```

可以先理解为：

> 自动管理动态数组内存的容器。

优点：

```text
自动管理内存
不需要手动 new/delete
可以自动扩展
数据连续存储
```

---

# 16. vector.data()

```cpp
std::vector<float> tensor = {
    1.0f,
    2.0f,
    3.0f
};

float* p = tensor.data();
```

`tensor.data()` 返回：

> vector 底层第一个元素的地址。

因此：

```cpp
*p
```

就是：

```cpp
tensor[0]
```

即：

```text
*p == tensor[0]
```

这对于模型推理非常重要，因为推理框架经常需要直接获取 Tensor 的底层内存地址。

---

# 17. 指针偏移

如果：

```cpp
float* p = tensor.data();
```

那么：

```cpp
p + 1
```

表示：

> 向后移动一个 float。

不是简单加一个字节。

例如：

```text
p      → tensor[0]
p + 1  → tensor[1]
p + 2  → tensor[2]
```

因此：

```cpp
*p
```

等价于：

```cpp
tensor[0]
```

```cpp
*(p + 1)
```

等价于：

```cpp
tensor[1]
```

```cpp
*(p + 2)
```

等价于：

```cpp
tensor[2]
```

核心公式：

```cpp
p[n] == *(p + n)
```

---

# 18. 普通数组与指针数组

普通数组：

```cpp
int arr[3] = {
    10,
    20,
    30
};
```

里面存的是：

```text
int
int
int
```

---

指针数组：

```cpp
int* arr[3];
```

里面存的是：

```text
int*
int*
int*
```

例如：

```cpp
int a = 10;
int b = 20;
int c = 30;

int* arr[3] = {
    &a,
    &b,
    &c
};
```

此时：

```cpp
*arr[0]
```

得到：

```text
10
```

---

# 19. 多维数组本质仍然是连续内存

例如：

```cpp
int a[2][3] = {
    {1, 2, 3},
    {4, 5, 6}
};
```

逻辑上：

```text
1 2 3
4 5 6
```

内存中：

```text
1 2 3 4 5 6
```

因此二维坐标：

```text
[row][col]
```

可以转换为：

```cpp
index = row * W + col;
```

---

# 20. Tensor 的 NCHW

深度学习中常见：

```text
[N, C, H, W]
```

含义：

```text
N = Batch / 图片数量
C = Channel / 通道数
H = Height / 高度
W = Width / 宽度
```

例如：

```text
[1, 3, 224, 224]
```

表示：

```text
1 张图片
3 个通道
高 224
宽 224
```

对于 RGB 图片：

```text
C = 3
```

通常对应：

```text
R
G
B
```

---

# 21. CHW 转一维 index

对于：

```text
[C,H,W]
```

一维位置：

```cpp
index = (c * H + h) * W + w;
```

例如：

```text
C = 3
H = 2
W = 2
```

数据：

```text
Channel 0
1 2
3 4

Channel 1
5 6
7 8

Channel 2
9 10
11 12
```

访问：

```text
c = 1
h = 0
w = 1
```

得到：

```text
6
```

计算：

```cpp
index = (1 * 2 + 0) * 2 + 1;
```

结果：

```text
index = 5
```

因此：

```cpp
tensor[5] == 6
```

---

# 22. NCHW 转一维 index

完整四维：

```text
[N,C,H,W]
```

转换公式：

```cpp
index = ((n * C + c) * H + h) * W + w;
```

理解方式：

```text
先跳过前面的图片
↓
再跳过前面的通道
↓
再跳过前面的行
↓
找到当前列
```

不要单纯死记公式，要理解数据在内存中是连续展开的。

---

# 23. Tensor 本质：Data + Shape

例如：

```cpp
std::vector<float> data(24);
```

这个 vector 本身只知道：

```text
有 24 个 float
```

它不知道这些数据是：

```text
[24]
```

还是：

```text
[2,3,2,2]
```

因此 Tensor 还需要 Shape。

例如：

```cpp
std::vector<float> data(24);

std::vector<int64_t> shape = {
    2,
    3,
    2,
    2
};
```

可以理解为：

```text
Tensor
=
Data
+
Shape
```

其中：

```text
Data
→ 真正的数据
```

```text
Shape
→ 告诉程序如何解释这些数据
```

---

# 24. int64_t

Tensor Shape 经常使用：

```cpp
std::vector<int64_t> shape;
```

`int64_t` 表示：

> 固定 64 位有符号整数。

通常：

```text
64 bit
=
8 byte
```

需要：

```cpp
#include <cstdint>
```

使用 `int64_t` 的优势是：

```text
类型大小明确
跨平台更加稳定
适合框架 API
```

---

# 25. sizeof()

`sizeof()` 用于查看变量或数据类型占多少字节。

例如：

```cpp
int a;
float b;
double c;
int64_t d;
```

查看：

```cpp
sizeof(a);
sizeof(b);
sizeof(c);
sizeof(d);
```

在常见 64 位 Linux 环境中通常：

```text
int      = 4 byte
float    = 4 byte
double   = 8 byte
int64_t  = 8 byte
```

指针：

```cpp
int* p;
```

在 64 位系统中通常：

```text
sizeof(p) = 8 byte
```

因为指针保存的是地址。

---

# 26. Tensor 内存大小计算

例如 Tensor：

```text
[1,3,224,224]
```

元素数量：

```text
1 × 3 × 224 × 224
=
150528
```

如果使用：

```text
FP32
```

每个元素：

```text
4 byte
```

总内存：

```text
150528 × 4
=
602112 byte
≈ 588 KB
```

不同数据类型：

```text
FP32 → 4 byte
FP16 → 2 byte
INT8 → 1 byte
```

因此量化能够减少模型和 Tensor 的内存占用。

---

# 27. 今天最重要的关系

必须记住：

```cpp
&a == p
```

地址关系。

```cpp
a == *p
```

值关系。

```cpp
p[n] == *(p + n)
```

数组访问和指针访问关系。

```text
Tensor
=
Data + Shape
```

Tensor 基本思想。

```text
Tensor 内存占用
≈
元素数量 × 每个元素字节数
```

---

# 28. 今日知识与 Edge AI 的关系

今天学习的知识不是单纯的 C++ 语法。

后续进入：

```text
ONNX Runtime
TensorRT
CUDA
GPU 推理
量化
内存优化
```

都会不断遇到：

```cpp
float*
void*
.data()
const &
size
shape
buffer
```

例如模型输入最终通常都会转化为：

```text
一块连续内存
+
Tensor Shape
+
Data Type
```

因此今天学习的：

```text
指针
引用
vector
连续内存
NCHW
sizeof
```

都是后续模型部署和推理优化的直接基础。

---

# 29. 今日复习检查

以后复习 Day 04 时，应尝试不看答案回答：

1. `&a` 是什么意思？
2. `int* p = &a` 是什么意思？
3. `p` 和 `*p` 有什么区别？
4. 为什么 `*p = 20` 会修改 `a`？
5. 引用和指针有什么区别？
6. 为什么函数参数经常使用 `const T&`？
7. `nullptr` 是什么意思？
8. 为什么不能解引用空指针？
9. Stack 和 Heap 有什么区别？
10. `new` 和 `delete` 分别干什么？
11. 什么是悬空指针？
12. 为什么推荐 `std::vector` 而不是大量使用 `new[]`？
13. `vector.data()` 返回什么？
14. 为什么 `p[1] == *(p + 1)`？
15. `[N,C,H,W]` 各代表什么？
16. 多维 Tensor 为什么能够存在一维内存中？
17. Tensor 的 Data 和 Shape 分别有什么作用？
18. FP32 为什么比 FP16 占更多内存？
19. `sizeof()` 返回 bit 还是 byte？
20. `[1,3,224,224]` 的 FP32 Tensor 大约占多少内存？

如果能够自己解释这些问题，说明 Day 04 C++ 部分基本掌握。

---

# 30. Day 04 C++ 阶段结论

今天完成了从：

```text
普通 C++ 变量
```

到：

```text
内存
↓
地址
↓
指针
↓
引用
↓
连续数组
↓
std::vector
↓
Tensor
↓
NCHW
```

这一整条知识链。

后续继续学习：

```text
Linux 进程
CMake Target
GDB
ONNX
ONNX Runtime
TensorRT
CUDA
```

今天的内存基础会在后面的部署代码中反复出现。

