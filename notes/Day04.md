# Day 04｜Linux 进程管理基础

## 1. 今日学习目标

今天主要学习 Linux 中“程序运行以后发生了什么”。

核心知识包括：

- 程序与进程的区别
- PID 与 PPID
- `ps`
- `ps -ef`
- `grep`
- 管道 `|`
- `top`
- `kill`
- `kill -9`
- 后台运行 `&`
- `jobs`
- `fg`
- `/proc`
- `echo $$`

这些内容会直接用于后续：

```text
C++ 程序调试
模型推理程序监控
ONNX Runtime
TensorRT
AI 服务部署
性能分析
进程排错
```

---

# 2. 程序和进程

程序和进程不是同一个东西。

例如：

```bash
./demo
```

在没有运行之前：

```text
demo
→ 磁盘上的可执行文件
```

当执行：

```bash
./demo
```

以后：

```text
程序
↓
被 Linux 加载
↓
创建进程
↓
开始执行
```

所以可以理解为：

```text
Program
→ 静态文件

Process
→ 程序运行起来后的实例
```

一个程序可以启动多个进程。

---

# 3. PID

Linux 中每个进程都会有一个编号：

```text
PID
```

全称：

```text
Process ID
```

也就是：

```text
进程 ID
```

例如：

```text
PID = 532
```

表示：

```text
系统中编号为 532 的进程
```

PID 是 Linux 管理进程的重要标识。

很多命令都需要 PID，例如：

```bash
kill 532
```

---

# 4. ps

最基础的进程查看命令：

```bash
ps
```

可能输出：

```text
PID TTY          TIME CMD
532 pts/0    00:00:00 bash
846 pts/0    00:00:00 ps
```

重点看：

```text
PID
→ 进程编号

CMD
→ 当前进程执行的命令
```

为什么执行 `ps` 时能看到 `ps` 自己？

因为：

```text
输入 ps
↓
Linux 启动 ps 程序
↓
ps 本身也成为一个进程
```

---

# 5. ps -ef

```bash
ps -ef
```

可以查看更完整的系统进程。

常见输出：

```text
UID        PID  PPID  C STIME TTY      TIME CMD
root         1     0  ...
zp         532     1  ...
zp         846   532  ...
```

今天最重要的几列：

```text
UID
PID
PPID
CMD
```

---

# 6. UID

```text
UID
```

表示：

```text
这个进程属于哪个用户
```

例如：

```text
root
zp
```

Linux 是多用户系统。

不同用户启动的进程可能具有不同权限。

---

# 7. PPID

```text
PPID
```

全称：

```text
Parent Process ID
```

也就是：

```text
父进程 ID
```

例如：

```text
bash
PID = 532
```

然后在这个终端执行：

```bash
ps -ef
```

假设：

```text
ps
PID = 846
PPID = 532
```

说明：

```text
bash
PID 532
   ↓
创建
   ↓
ps
PID 846
```

所以 Linux 进程之间具有父子关系。

---

# 8. Shell 和子进程

平时在终端里执行：

```bash
./demo
```

通常可以理解为：

```text
bash
↓
启动
↓
demo
```

所以：

```text
bash
→ 父进程

demo
→ 子进程
```

这也是理解 Linux 进程树的重要基础。

---

# 9. grep 查找进程

如果：

```bash
ps -ef
```

输出太多，可以配合：

```bash
grep
```

例如：

```bash
ps -ef | grep bash
```

表示：

```text
先列出所有进程
↓
再筛选带 bash 的行
```

还可以：

```bash
ps -ef | grep python
```

查找 Python 进程。

以后运行推理程序，也可以：

```bash
ps -ef | grep inference
```

---

# 10. 管道 Pipe

这里：

```bash
|
```

叫：

```text
Pipe
管道
```

作用：

```text
把左边命令的输出
交给右边命令作为输入
```

例如：

```bash
ps -ef | grep bash
```

流程：

```text
ps -ef
↓
输出全部进程
↓
|
↓
grep bash
↓
筛选包含 bash 的内容
```

Linux 中管道非常重要。

以后会大量使用：

```bash
command1 | command2
```

---

# 11. top

```bash
top
```

用于：

```text
实时查看系统进程状态
```

进入后会持续刷新。

今天重点观察：

```text
PID
USER
%CPU
%MEM
COMMAND
```

含义：

```text
PID
→ 进程 ID

USER
→ 进程所属用户

%CPU
→ CPU 使用率

%MEM
→ 内存使用率

COMMAND
→ 程序名称
```

---

# 12. top 的作用

以后运行 AI 推理程序：

```bash
./inference
```

可以另开终端：

```bash
top
```

观察：

```text
CPU 是否很高
内存是否持续上涨
程序是否还在运行
程序是否异常占用资源
```

所以 `top` 是很重要的系统监控工具。

退出：

```text
q
```

---

# 13. kill

如果知道一个进程的 PID：

```text
PID = 1234
```

可以：

```bash
kill 1234
```

作用：

```text
向 PID 1234 的进程发送终止信号
```

注意：

```text
kill
```

不是删除文件。

它操作的是：

```text
正在运行的进程
```

---

# 14. kill 实验

可以先运行：

```bash
sleep 1000
```

这个程序会等待 1000 秒。

然后另开一个终端：

```bash
ps -ef | grep sleep
```

找到：

```text
sleep 1000
```

对应的 PID。

然后：

```bash
kill PID
```

原来的 `sleep` 就会结束。

---

# 15. kill -9

如果：

```bash
kill PID
```

没有效果，可以使用：

```bash
kill -9 PID
```

`-9` 对应强制终止信号。

可以简单理解：

```text
kill PID
→ 尝试正常结束

kill -9 PID
→ 强制结束
```

原则：

```text
优先普通 kill
不要一上来就 kill -9
```

因为强制结束时，程序没有机会进行正常清理。

---

# 16. 后台运行 &

普通：

```bash
sleep 1000
```

会占住当前终端。

如果：

```bash
sleep 1000 &
```

最后加：

```text
&
```

表示：

```text
让程序在后台运行
```

这样当前终端仍然可以继续输入其他命令。

---

# 17. Job ID 和 PID

执行：

```bash
sleep 1000 &
```

可能看到：

```text
[1] 2456
```

其中：

```text
[1]
→ Job ID

2456
→ PID
```

这两个概念不同。

```text
PID
→ Linux 系统级的进程编号

Job ID
→ 当前 Shell 中管理任务的编号
```

---

# 18. jobs

查看当前 Shell 中的后台任务：

```bash
jobs
```

可能输出：

```text
[1]+ Running sleep 1000 &
```

表示：

```text
Job 1
正在后台运行
```

---

# 19. fg

把后台任务切回前台：

```bash
fg %1
```

这里：

```text
%1
```

表示：

```text
Job ID = 1
```

所以：

```bash
fg %1
```

表示：

```text
把第 1 个后台任务切回前台
```

切回前台后，可以：

```text
Ctrl + C
```

结束程序。

---

# 20. /proc

Linux 有一个非常重要的目录：

```bash
/proc
```

它不是普通磁盘文件夹。

可以理解为：

```text
Linux 内核把系统和进程状态
以类似文件和目录的方式暴露出来
```

所以 `/proc` 中能看到很多系统信息。

---

# 21. /proc 中的 PID

执行：

```bash
ls /proc
```

会看到很多数字目录：

```text
1
15
532
846
...
```

很多数字就是：

```text
PID
```

例如：

```text
/proc/532
```

表示：

```text
PID 532 这个进程的信息目录
```

---

# 22. echo $$

查看当前 Shell 自己的 PID：

```bash
echo $$
```

例如输出：

```text
532
```

说明：

```text
当前 bash 的 PID = 532
```

于是可以：

```bash
ls /proc/532
```

查看当前 Shell 的进程信息。

---

# 23. /proc/PID/status

例如：

```bash
cat /proc/532/status
```

可以看到：

```text
进程状态
进程名字
PID
PPID
内存使用
线程数量
```

等信息。

如果只想看前几行：

```bash
cat /proc/532/status | head
```

---

# 24. /proc/PID/exe

查看某个进程实际运行的是哪个可执行文件：

```bash
readlink /proc/532/exe
```

例如可能输出：

```text
/usr/bin/bash
```

说明：

```text
PID 532
```

对应：

```text
/usr/bin/bash
```

---

# 25. Linux 进程知识链

今天整个 Linux 部分可以串成：

```text
磁盘上的程序
↓
运行
↓
进程
↓
PID
↓
PPID
↓
ps 查看
↓
grep 筛选
↓
top 实时监控
↓
kill 结束
↓
& 后台运行
↓
jobs 管理任务
↓
fg 切回前台
↓
/proc 查看底层进程信息
```

---

# 26. 今天最应该记住的命令

查看当前进程：

```bash
ps
```

查看所有进程：

```bash
ps -ef
```

搜索：

```bash
ps -ef | grep xxx
```

实时监控：

```bash
top
```

结束：

```bash
kill PID
```

强制结束：

```bash
kill -9 PID
```

后台运行：

```bash
command &
```

查看后台任务：

```bash
jobs
```

切回前台：

```bash
fg %1
```

查看当前 Shell PID：

```bash
echo $$
```

查看进程状态：

```bash
cat /proc/PID/status
```

查看进程可执行文件：

```bash
readlink /proc/PID/exe
```

---

# 27. 今日复习问题

以后复习 Day 04 Linux 时，应尝试自己回答：

1. 程序和进程有什么区别？
2. PID 是什么？
3. PPID 是什么？
4. 为什么 `ps` 能看到 `ps` 自己？
5. `ps` 和 `ps -ef` 有什么区别？
6. `grep` 在进程查询中有什么作用？
7. `|` 管道是什么意思？
8. `top` 主要观察哪些指标？
9. `kill PID` 是什么意思？
10. `kill -9` 为什么不建议优先使用？
11. `&` 的作用是什么？
12. Job ID 和 PID 有什么区别？
13. `jobs` 有什么作用？
14. `fg %1` 是什么意思？
15. `/proc` 是什么？
16. `/proc/PID` 代表什么？
17. `echo $$` 为什么能查看当前 Shell PID？
18. `/proc/PID/status` 能看到什么？
19. `/proc/PID/exe` 有什么作用？
20. 如果一个推理程序 CPU 占用异常，应先用哪些命令观察？

---

# 28. 与 Edge AI / AI Systems 的关系

以后做模型部署时，经常会遇到：

```text
推理程序启动后有没有正常运行？
CPU 占用多少？
内存有没有持续增长？
程序 PID 是多少？
程序卡住后如何结束？
程序运行的是哪个二进制？
```

今天的命令就是这些问题的基础工具。

例如：

```bash
ps -ef | grep inference
```

找到推理进程。

```bash
top
```

观察 CPU 和内存。

```bash
kill PID
```

结束异常程序。

```bash
cat /proc/PID/status
```

查看进程内部状态。

因此：

```text
Linux 进程管理
```

是后续：

```text
模型部署
推理服务
性能分析
系统调试
AI Systems
```

必须掌握的基础能力。

---

# 29. Day 04 Linux 完成状态

```text
✅ Program / Process
✅ PID
✅ PPID
✅ ps
✅ ps -ef
✅ grep
✅ Pipe
✅ top
✅ kill
✅ kill -9
✅ &
✅ jobs
✅ fg
✅ /proc
✅ echo $$
✅ /proc/PID/status
✅ /proc/PID/exe
```

下一步 Linux 学习方向：

```text
文件系统
环境变量
PATH
权限进一步理解
ldd
动态库加载
进程与线程
```
