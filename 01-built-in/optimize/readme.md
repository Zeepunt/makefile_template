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

### 2、生成 built-in.o 文件

参考 KBuild，将同一个目录下的所有源文件先编译为 .o，然后统一链接为 built-in.o ，最后再将各个目录的 built-in.o 一起链接为 elf 可执行文件。

```shell
gcc -c func_a.c -o func_a.o
gcc -c func_b.c -o func_b.o

# 对于 ld 命令来说:
#  -r: 产生可重定位的输出, 这个输出文件可以再次作为 ld 的输入
ld -r -o built-in.o func_a.o func_b.o

gcc -c main.c -o main.o
gcc main.o built-in.o -o main
```

## 二、optimize 模板说明

在当前的模板中，主要包括以下的内容：

1. `scripts/Makefile.build` 里面描述了如何将当前目录以及它包含的子目录中的 .c 文件编译并生成 built-in.o 文件的过程。
2. 顶层 Makefile 如何使用 `scripts/Makefile.build` 这个文件。

optimize 模板新增内容：

1. `scripts/Makefile.include` 里面添加了一些公用的变量，比如执行命令显示开关 `Q`。
2. 源代码和头文件分离，方便管理。
3. 源代码和编译过程分离，编译过程的中间文件和最终结果输出到 build 目录中。 

## 三、编译

编译命令为：

```shell
$ make
$ make clean
```

编译过程的打印如下：

```shell
$ make
make[1]: Entering directory '/d/Zeepunt/project/makefile_template/built-in/build'
make[2]: Entering directory '/d/Zeepunt/project/makefile_template/built-in/build/lib'
make[3]: Entering directory '/d/Zeepunt/project/makefile_template/built-in/build/lib/func_a'
cc -g -I/d/Zeepunt/project/makefile_template/built-in/build/include -Wp,-MD,/d/Zeepunt/project/makefile_template/built-in/build/build/lib/func_a/func_a.o.d -c -o /d/Zeepunt/project/makefile_template/built-in/build/build/lib/func_a/func_a.o func_a.c
make[3]: Leaving directory '/d/Zeepunt/project/makefile_template/built-in/build/lib/func_a'
make[3]: Entering directory '/d/Zeepunt/project/makefile_template/built-in/build/lib/func_b'
cc -g -I/d/Zeepunt/project/makefile_template/built-in/build/include -Wp,-MD,/d/Zeepunt/project/makefile_template/built-in/build/build/lib/func_b/func_b.o.d -c -o /d/Zeepunt/project/makefile_template/built-in/build/build/lib/func_b/func_b.o func_b.c
make[3]: Leaving directory '/d/Zeepunt/project/makefile_template/built-in/build/lib/func_b'
make[2]: Leaving directory '/d/Zeepunt/project/makefile_template/built-in/build/lib'
make[2]: Entering directory '/d/Zeepunt/project/makefile_template/built-in/build/src'
cc -g -I/d/Zeepunt/project/makefile_template/built-in/build/include -Wp,-MD,/d/Zeepunt/project/makefile_template/built-in/build/build/src/main.o.d -c -o /d/Zeepunt/project/makefile_template/built-in/build/build/src/main.o main.c
make[2]: Leaving directory '/d/Zeepunt/project/makefile_template/built-in/build/src'
make[1]: Leaving directory '/d/Zeepunt/project/makefile_template/built-in/build'
gcc  -I/d/Zeepunt/project/makefile_template/built-in/build/include -o /d/Zeepunt/project/makefile_template/built-in/build/build/example /d/Zeepunt/project/makefile_template/built-in/build/build/built-in.o
```

