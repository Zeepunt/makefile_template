## makefile_template

`Makefile` 工程模板。

其主要目录结构为：

```shell
|- built-in       # 如何生成 built-in.o 文件
|     |- basic    # 基础版本
|     |- optimize # 优化版本
|- library        # 如何生成库文件
      |- basic    # 基础版本
```

模板阅读顺序：（后续的模板是依赖前面的模板）

1. `built-in：basic -> optimize`。
1. `libaray: basic`。

