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

## 二、basic 模板说明

在当前的模板中，主要包括以下的内容：

1. `scripts/Makefile.build` 里面描述了如何将当前目录以及它包含的子目录中的 .c 文件编译并生成 built-in.o 文件的过程。
2. 顶层 Makefile 如何使用 `scripts/Makefile.build` 这个文件。

## 三、编译

编译命令为：

```shell
$ make
```

编译过程的打印如下：

```shell
$ make
make -C lib -f /d/Zeepunt/project/makefile_template/built-in/basic/scripts/Makefile.build build
make[1]: Entering directory '/d/Zeepunt/project/makefile_template/built-in/basic/lib'
make -C func_a -f /d/Zeepunt/project/makefile_template/built-in/basic/scripts/Makefile.build build
make[2]: Entering directory '/d/Zeepunt/project/makefile_template/built-in/basic/lib/func_a'
make[2]: Nothing to be done for 'build'.
make[2]: Leaving directory '/d/Zeepunt/project/makefile_template/built-in/basic/lib/func_a'
make -C func_b -f /d/Zeepunt/project/makefile_template/built-in/basic/scripts/Makefile.build build
make[2]: Entering directory '/d/Zeepunt/project/makefile_template/built-in/basic/lib/func_b'
make[2]: Nothing to be done for 'build'.
make[2]: Leaving directory '/d/Zeepunt/project/makefile_template/built-in/basic/lib/func_b'
make[1]: Leaving directory '/d/Zeepunt/project/makefile_template/built-in/basic/lib'
make -C src -f /d/Zeepunt/project/makefile_template/built-in/basic/scripts/Makefile.build build
make[1]: Entering directory '/d/Zeepunt/project/makefile_template/built-in/basic/src'
cc -g -I/d/Zeepunt/project/makefile_template/built-in/basic/lib/func_a/ -I/d/Zeepunt/project/makefile_template/built-in/basic/lib/func_b/ -Wp,-MD,.main.o.d -c -o main.o main.c
ld -r -o built-in.o main.o
make[1]: Leaving directory '/d/Zeepunt/project/makefile_template/built-in/basic/src'
gcc  -I/d/Zeepunt/project/makefile_template/built-in/basic/lib/func_a/ -I/d/Zeepunt/project/makefile_template/built-in/basic/lib/func_b/ -o example lib/built-in.o src/built-in.o
```

