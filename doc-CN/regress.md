# 回归测试

回归测试是PolarDB PostgreSQL（以下简称PolarDB）中一组对SQL实现的综合测试，主要用来测试标准SQL操作以及PolarDB的扩展功能。

## 运行测试
回归测试可以在一个已经安装并且正在运行的服务器上运行，也可以在编译树中的一个临时安装上运行。此外，回归测试支持两种运行模式：并行模式和顺序模式。顺序模式单独运行每一个测试脚本，并行模式则开启多个服务器进程来并行运行多组测试。
并行测试更利于检查进程间的通信和锁定是否正常工作。通过使用编译树中的临时安装，PolarDB支持单节点回归测试和基于X-Paxos的三节点集群回归测试。

## 基于Paxos进行三节点回归
### 在临时安装上运行测试

在根目录下执行以下命令：

```shell
make checkdma
```

执行完成后，您会看到如下信息：

```shell
============================================
All 187 tests passed. 1 tests in dma ignore
============================================
```

该测试方法在临时数据库服务器中运行。如果编译由根用户（root）完成，测试将无法运行，因为服务器无法以root身份启动。

并行回归测试会在用户ID下启动多个进程。当前，最大并发量是20个并行测试脚本，这意味着40个进程，即每一个测试脚本有一个服务器进程和一个psql进程。如果您的系统对每个用户的进程数有强制限制，请确保这个限制至少是50，否则并行测试可能会失败。如果无法提高该限制，您可以通过设置MAX_CONNECTIONS参数来降低并发度。例如：

```shell
make MAX_CONNECTIONS=10 checkdma
```

## 附加测试套件
make check命令只可以运行核心的回归测试，即只测试PostgreSQL服务器的内置功能。源代码发布还包含附加的测试套件，其中大多数用于测试附加功能，例如可选过程语言。

要运行编译所选模块所需的所有测试套件（包括核心测试），请在编译树的顶部输入以下命令之一：

```shell
make check-world-dma
```

与前面介绍的make checkdma命令类似，这些命令也是用来在临时服务器上运行测试。其他的注意事项与前文介绍的测试方式相同。请注意，make check-world-dma为每个测试模块构建了一个单独的临时安装树，因此它需要更多的时间和磁盘空间。

您也可以通过在编译树适当的子目录下输入make checkdma来分别运行测试套件。

可以通过这种方法调用的附加测试包括：

* 可选过程语言的回归测试（除PL/pgSQL之外。PL/pgSQL的测试由核心测试来完成）。这些测试位于src/pl。

* contrib模块的回归测试，位于contrib。不是所有的contrib模块都有测试。

* ECPG接口库的回归测试，位于src/interfaces/ecpg/test。

* 并发会话行为的压力测试，位于src/test/isolation。

* 客户端程序的测试，位于src/bin。

仅当PostgreSQL配置了选项--enable-tap-tests时，才会运行基于TAP的测试。在开发时推荐运行基于TAP的测试。如果没有合适的Perl安装，可忽略此建议。

## 其他测试
详情请查阅PostgreSQL回归测试的相关描述。

## 单节点回归
详情请查阅PostgreSQL回归测试的相关描述。

___

© 阿里巴巴集团控股有限公司 版权所有