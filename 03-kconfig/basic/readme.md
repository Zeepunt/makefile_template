## 一、GCC 的使用

### 1、编译过程

对于一个 main.c ，它的编译过程：

```shell
# 1. 预编译
gcc -E main.c -o main.i

# 2. 编译
gcc -S main.i -o main.s

# 3. 汇编
gcc -c main.s -o main.o

# 4. 链接
gcc main.o -o main
```

### 2、生成静态库 .a 文件

由于我们之前将同一个目录下的所有源文件先编译为 .o，然后统一链接为 built-in.o ，那么只需要将 built-in.o 重新打包成 .a 文件即可。

```shell
gcc -c func_a.c -o func_a.o
gcc -c func_b.c -o func_b.o

# 对于 ld 命令来说:
#  -r: 产生可重定位的输出, 这个输出文件可以再次作为 ld 的输入
ld -r -o built-in.o func_a.o func_b.o

gcc -c main.c -o main.o
gcc main.o built-in.o -o main

# 对于 ar 命令来说:
#   c: 创建一个新的静态库文件
#   r: 如果静态库已经存在, 则替换其中的目标文件
ar cr built-in.o built-in.a
```

## 二、basic 模板说明

在当前的模板中，主要包括以下的内容：

1. `scripts/Makefile.build` 里面描述了如何将当前目录以及它包含的子目录中的 .c 文件编译并生成 built-in.o 文件的过程。
2. 顶层 Makefile 如何使用 `scripts/Makefile.build` 这个文件。
3. `scripts/Makefile.include` 里面添加了一些公用的变量，比如执行命令显示开关 `Q`。
4. 源代码和头文件分离，方便管理。
5. 源代码和编译过程分离，编译过程的中间文件和最终结果输出到 build 目录中。 
6. `scripts/Makefile.include` 里面添加了一些公用的变量，比如打印美化开关 `quiet`。
7. 支持通过 `lib-y += <name>.a` 的方式生成 name.a 静态库，目前只支持一个目录生成一个静态库。

basic 模板新增内容：

## 三、Kconfig 工具

### 1、安装方式

- 选择一：自己编译一个 Kconfig。

  安装 Kconfig 的依赖：

  ```shell
  # ncurses 库: menuconfig 依赖该库来实现终端中的图形用户界面
  sudo apt install -y ncurses-devel
  ```
  
  将 Linux 内核中的 scripts/kconfig 拷贝到当前的环境下：
  
  ```shell
  # 这里将 5.15.146 中的 scripts/kconfig 拷贝到了 scripts 目录中
  cd scripts/kconfig
  make mconf
  ```
  
- 选择二：使用 `kconfig-frontends` 已经提供好的工具。

  ```shell
  sudo apt -y install kconfig-frontends
  ```
  
- 选择三：使用 `kconfiglib` 提供好的工具。（Python3 环境，当前选择）

  ```shell
  pip install kconfiglib
  
  # 如果是在 windows 环境下安装的话, 还需要以下工具
  pip install windows-curses
  ```

### 2、使用

[Kconfig 的语法](https://www.kernel.org/doc/html/latest/kbuild/kconfig-language.html#)。

[kconfiglib 的使用](https://pypi.org/project/kconfiglib/)。

```shell
# 进行配置
$ menuconfig

# 配置完成后一般都会自动生成 .h 头文件, 如果没有的话, 可以手动生成
$ genconfig
```

## 四、编译

编译命令为：

```shell
$ menuconfig && genconfig
$ make
$ make clean
```

编译过程的打印如下：

```shell
$ make
make[1]: Entering directory '/d/Zeepunt/project/makefile_template/library/basic'
make[2]: Entering directory '/d/Zeepunt/project/makefile_template/library/basic/lib'
make[3]: Entering directory '/d/Zeepunt/project/makefile_template/library/basic/lib/func_a'
  CC    /d/Zeepunt/project/makefile_template/library/basic/build/lib/func_a/func_a.o
  LD    /d/Zeepunt/project/makefile_template/library/basic/build/lib/func_a/built-in.o
  AR    /d/Zeepunt/project/makefile_template/library/basic/build/lib/func_a/func_a.a
make[3]: Leaving directory '/d/Zeepunt/project/makefile_template/library/basic/lib/func_a'
make[3]: Entering directory '/d/Zeepunt/project/makefile_template/library/basic/lib/func_b'
  CC    /d/Zeepunt/project/makefile_template/library/basic/build/lib/func_b/func_b.o
  LD    /d/Zeepunt/project/makefile_template/library/basic/build/lib/func_b/built-in.o
  AR    /d/Zeepunt/project/makefile_template/library/basic/build/lib/func_b/func_b.a
make[3]: Leaving directory '/d/Zeepunt/project/makefile_template/library/basic/lib/func_b'
  LD    /d/Zeepunt/project/makefile_template/library/basic/build/lib/built-in.o
  AR    /d/Zeepunt/project/makefile_template/library/basic/build/lib/lib.a
make[2]: Leaving directory '/d/Zeepunt/project/makefile_template/library/basic/lib'
make[2]: Entering directory '/d/Zeepunt/project/makefile_template/library/basic/src'
  CC    /d/Zeepunt/project/makefile_template/library/basic/build/src/main.o
  LD    /d/Zeepunt/project/makefile_template/library/basic/build/src/built-in.o
make[2]: Leaving directory '/d/Zeepunt/project/makefile_template/library/basic/src'
  LD    /d/Zeepunt/project/makefile_template/library/basic/build/built-in.o
  AR    /d/Zeepunt/project/makefile_template/library/basic/build/example.a
make[1]: Leaving directory '/d/Zeepunt/project/makefile_template/library/basic'
gcc  -I/d/Zeepunt/project/makefile_template/library/basic/include -o /d/Zeepunt/project/makefile_template/library/basic/build/example /d/Zeepunt/project/makefile_template/library/basic/build/built-in.o
```
