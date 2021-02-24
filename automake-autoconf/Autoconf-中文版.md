Autoconf

# Autoconf

## Creating Automatic Configuration Scripts

## Edition 2.13, for Autoconf version 2.13

## December 1998

------

 

Permission is granted to make and distribute verbatim copies of this manual provided the copyright notice and this permission notice are  preserved on all copies.

Permission is granted to copy and distribute modified versions of  this manual under the conditions for verbatim copying, provided that the entire resulting derived work is distributed under the terms of a  permission notice identical to this one.

Permission is granted to copy and distribute translations of this  manual into another language, under the above conditions for modified  versions, except that this permission notice may be stated in a  translation approved by the Free Software Foundation.

------

本文档由王立翻译。 1999.12.16

译者在此声明：不对任何由译文错误或者对译文的误解承担任何责任。

------

# [介绍](https://blog.csdn.net/a751532301/article/details/101142061#TOC1)

```
A physicist, an engineer, and a computer scientist were
discussing the nature of God.  Surely a Physicist, said the
physicist, because early in the Creation, God made Light; and you
know, Maxwell's equations, the dual nature of electro-magnetic
waves, the relativist consequences... An Engineer!, said the
engineer, because before making Light, God split the Chaos into
Land and Water; it takes a hell of an engineer to handle that big
amount of mud, and orderly separation of solids from
liquids... The computer scientist shouted: And the Chaos,
where do you think it was coming from, hmm?

---Anonymous
```

Autoconf是一个用于生成可以自动地配置软件源代码包以适应多种Unix类系统的 shell脚本的工具。由Autoconf生成的配置脚本在运行的时候与Autoconf是无关的， 就是说配置脚本的用户并不需要拥有Autoconf。

由Autoconf生成的配置脚本在运行的时候不需要用户的手工干预；通常它们甚至不需要  通过给出参数以确定系统的类型。相反，它们对软件包可能需要的各种特征进行独立  的测试。（在每个测试之前，它们打印一个单行的消息以说明它们正在进行的检测，  以使得用户不会因为等待脚本执行完毕而焦躁。）因此，它们在混合系统或者从各种  常见Unix变种定制而成的系统中工作的很好。没有必要维护文件以储存由各个Unix变种 、各个发行版本所支持的特征的列表。

对于每个使用了Autoconf的软件包，Autoconf从一个列举了该软件包需要的，或者可以  使用的系统特征的列表的模板文件中生成配置脚本。在shell代码识别并响应了一个被  列出的系统特征之后，Autoconf允许多个可能使用（或者需要）该特征的软件包共享该特征。  如果后来因为某些原因需要调整shell代码，就只要在一个地方进行修改； 所有的配置脚本都将被自动地重新生成以使用更新了的代码。

Metaconfig包在目的上与Autoconf很相似，但它生成的脚本需要用户的手工干预，在配置一个  大的源代码树的时候这是十分不方便的。不象Metaconfig脚本，如果在编写脚本时小心谨慎，  Autoconf可以支持交叉编译（cross-compiling）。

Autoconf目前还不能完成几项使软件包可移植的工作。其中包括为所有标准的目标自动 创建``Makefile'`文件，包括在缺少标准库函数和头文件的系统上提供替代品。 目前正在为在将来添加这些特征而工作。

对于在C程序中的`#ifdef`中使用的宏的名字，Autoconf施加了一些限制 （参见[预处理器符号索引](https://blog.csdn.net/a751532301/article/details/101142061#SEC104)）。

Autoconf需要GNU `m4`以便于生成脚本。它使用了某些UNIX版本的`m4` 所不支持的特征。它还会超出包括GNU `m4` 1.0在内的某些`m4`版本的内部 限制。你必须使用GNU `m4`的1.1版或者更新的版本。使用1.3版或者更新的版本将比1.1 或1.2版快许多。

关于从版本1中升级的详情，参见[从版本1中升级](https://blog.csdn.net/a751532301/article/details/101142061#SEC88)。 关于Autoconf的开发历史，参见[Autoconf的历史](https://blog.csdn.net/a751532301/article/details/101142061#SEC95)。 对与Autoconf有关的常见问题的回答，参见[关于Autoconf的问题](https://blog.csdn.net/a751532301/article/details/101142061#SEC83)。

把关于Autoconf的建议和bug报告发送到`bug-gnu-utils@prep.ai.mit.edu`。 请把你通过运行`autoconf --version'而获得的Autoconf的版本号包括在内。

# [创建`configure`脚本](https://blog.csdn.net/a751532301/article/details/101142061#TOC2)

由Autoconf生成的配置脚本通常被称为`configure`。在运行的时候，`configure` 创建一些文件，在这些文件中以适当的值替换配置参数。由`configure`创建的文件有：

- 一个或者多个``Makefile'`文件，在包的每个子目录中都有一个（参见 [Makefile中的替换](https://blog.csdn.net/a751532301/article/details/101142061#SEC11)）；
- 有时创建一个C头文件，它的名字可以被配置，该头文件包含一些`#define`命令 （参见[配置头文件](https://blog.csdn.net/a751532301/article/details/101142061#SEC15)）；
- 一个名为``config.status'`的shell脚本，在运行时，它将重新创建上述文件。 （参见[重新创建一个配置](https://blog.csdn.net/a751532301/article/details/101142061#SEC82)）；
- 一个名为``config.cache'`的shell脚本，它储存了许多测试的运行结果 （参见[缓存文件](https://blog.csdn.net/a751532301/article/details/101142061#SEC57)）；
- 一个名为``config.log'`的文件，它包含了由编译器生成的许多消息，以便于 在`configure`出现错误时进行调试。

为了使用Autoconf创建一个`configure`脚本，你需要编写一个Autoconf的输入文件 ``configure.in'`并且对它运行`autoconf`。如果你自行编写了特征测试以补充 Autoconf所提供的测试，你可能还要编写一个名为``aclocal.m4'`的文件和一个名为 ``acsite.m4'`的文件。如果你使用了包含`#define`指令的C头文件，你可能 还要编写``acconfig.h'`，并且你需要与软件包一同发布由Autoconf生成的文件 ``config.h.in'`。

下面是一个说明了在配置中使用的文件是如何生成的图。运行的程序都标以后缀`*'。 可能出现的文件被方括号(`[]')括起来。`autoconf`和`autoheader` 还读取安装了的Autoconf宏文件（通过读取``autoconf.m4'`）。

在准备发布软件包的过程中使用的文件：

```
你的源文件 --> [autoscan*] --> [configure.scan] --> configure.in

configure.in --.   .------> autoconf* -----> configure
               +---+
[aclocal.m4] --+   `---.
[acsite.m4] ---'       |
                       +--> [autoheader*] -> [config.h.in]
[acconfig.h] ----.     |
                 +-----'
[config.h.top] --+
[config.h.bot] --'

Makefile.in -------------------------------> Makefile.in
```

在配置软件包的过程中使用的文件：

```
                       .-------------> config.cache
configure* ------------+-------------> config.log
                       |
[config.h.in] -.       v            .-> [config.h] -.
               +--> config.status* -+               +--> make*
Makefile.in ---'                    `-> Makefile ---'
```

## [编写``configure.in'`](https://blog.csdn.net/a751532301/article/details/101142061#TOC3)

为了为软件包创建`configure`脚本，需要编写一个名为``configure.in'` 的文件，该文件包含了对那些你的软件包需要或者可以使用的系统特征进行测试的Autoconf宏的调用。 现有的Autoconf宏可以检测许多特征； 对于它们的描述可以参见[现有的测试](https://blog.csdn.net/a751532301/article/details/101142061#SEC21)。 对于大部分其他特征，你可以使用Autconf模板宏以创建定制的测试；关于它们的详情，参见 [编写测试](https://blog.csdn.net/a751532301/article/details/101142061#SEC40)。对于特别古怪或者特殊的特征，``configure.in'` 可能需要包含一些手工编写的shell命令。程序`autoscan`可以为你编写``configure.in'` 开个好头（详情请参见[用`autoscan`创建``configure.in'`](https://blog.csdn.net/a751532301/article/details/101142061#SEC4)）。

除了少数特殊情况之外，在``configure.in'`中调用Autoconf宏的顺序并不重要。 在每个``configure.in'`中，必须在进行任何测试之间包含一个对`AC_INIT`的调用， 并且在结尾处包含一个对`AC_OUTPUT`的调用（参见[创建输出文件](https://blog.csdn.net/a751532301/article/details/101142061#SEC10)）。 此外，有些宏要求其他的宏在它们之前被调用，这是因为它们通过检查某些变量在前面设定的值以决定作些什么。 这些宏在独立的说明中给出（参见[现有的测试](https://blog.csdn.net/a751532301/article/details/101142061#SEC21)），而且如果没有 按照顺序调用宏，在生成`configure`时会向你发出警告。

为了提高一致性，下面是调用Autoconf宏的推荐顺序。通常，在本列表中靠后的项目依赖于表中靠前的项目。 例如，库函数可能受到typedefs和库的影响。

```
AC_INIT(file)
checks for programs
checks for libraries
checks for header files
checks for typedefs
checks for structures
checks for compiler characteristics
checks for library functions
checks for system services
AC_OUTPUT([file...])
```

最好让每个宏调用在``configure.in'`中占据单独的一行。大部分宏并不添加额外的新行； 它们依赖于在宏调用之后的新行以结束命令。这种方法使得生成的`configure`脚本 在不必添加大量的空行的情况下比较容易阅读。在宏调用的同一行中设置shell变量通常是安全的， 这是因为shell允许出现没有用新行间隔的赋值。

在调用带参数的宏的时候，在宏名和左括号之间不能出现任何空格。如果参数被`m4` 引用字符`['和`]'所包含，参数就可以多于一行。如果你有一个长行， 比如说一个文件名列表，你通常可以在行的结尾使用反斜线以便在逻辑上把它与下一行进行连接 （这是由shell实现的，Autoconf对此没有进行任何特殊的处理）。

有些宏处理两种情况：如果满足了某个给定的条件就做什么，如果没有满足某个给定的条件就做什么。 在有些地方，你可能希望在条件为真的情况下作些事，在为假时什么也不作。反之亦然。为了忽略 为真的情况，把空值作为参数action-if-found传递给宏。为了忽略为假的情况，可以 忽略包括前面的逗号在内的宏的参数action-if-not-found。

你可以在文件``configure.in'`中添加注释。注释以`m4`预定义宏`dnl` 开头，该宏丢弃在下一个新行之前的所有文本。这些注释并不在生成的`configure`脚本中 出现。例如，把下面给出的行作为文件``configure.in'`的开头是有好处的：

```
dnl Process this file with autoconf to produce a configure script.
```

## [用`autoscan`创建``configure.in'`](https://blog.csdn.net/a751532301/article/details/101142061#TOC4)

程序`autoscan`可以帮助你为软件包创建``configure.in'`文件。如果在命令行中给出了目录， `autoscan`就在给定目录及其子目录树中检查源文件，如果没有给出目录，就在当前目录及其子目录树中 进行检查。它搜索源文件以寻找一般的移植性问题并创建一个文件``configure.scan'`，该文件就是软件包 的``configure.in'`预备版本。

在把``configure.scan'`改名为``configure.in'`之前，你应该手工地检查它；它可能需要一些调整。 `autoscan`偶尔会按照相对于其他宏的错误的顺序输出宏，为此`autoconf`将给出警告；你需要 手工地移动这些宏。还有，如果你希望包使用一个配置头文件，你必须添加一个对`AC_CONFIG_HEADER`的调用。 （参见[配置头文件](https://blog.csdn.net/a751532301/article/details/101142061#SEC15)）。可能你还必须在你的程序中修改或者添加一些`#if` 指令以使得程序可以与Autoconf合作。（关于有助于该工作的程序的详情，参见 [用`ifnames`列举条件](https://blog.csdn.net/a751532301/article/details/101142061#SEC5)）。

`autoscan`使用一些数据文件，它们是随发布的Autoconf宏文件一起安装的，以便当它在包中的源文件中发现 某些特殊符号时决定输出那些宏。这些文件都具有相同的格式。每一个都是由符号、空白和在符号出现时应该输出的Autoconf 宏。以`#'开头的行是注释。

只有在你安装了Perl的情况下才安装`autoscan`。 `autoscan`接受如下选项：



## [用`ifnames`列举条件](https://blog.csdn.net/a751532301/article/details/101142061#TOC5)

在为一个软件包编写``configure.in'`时，`ifnames`可以提供一些帮助。它打印出包已经在C预处理条件 中使用的标识符。如果包已经被设置得具备了某些可移植性，该程序可以帮助你找到`configure`所需要进行 的检查。它可能有助于补足由`autoscan`生成的``configure.in'`中的某些缺陷。 （参见[用`autoscan`创建``configure.in'`](https://blog.csdn.net/a751532301/article/details/101142061#SEC4)）。

`ifnames`扫描所有在命令行中给出的C源代码文件（如果没有给出，就扫描标准输入）并且把排序后的、由 所有出现在这些文件中的`#if`、`#elif`、`#ifdef`或者`#ifndef` 命令中的标识符列表输出到标准输出中。它为每个标识符输出单独的一行，行中标识符之后是一个由空格分隔的、使用 了该标识符的文件名列表。

`ifnames`接受如下选项：



## [用`autoconf`创建`configure`](https://blog.csdn.net/a751532301/article/details/101142061#TOC6)

为了从``configure.in'`生成`configure`，不带参数地运行程序`autoconf`。 `autoconf`用使用Autoconf宏的`m4`宏处理器处理``configure.in'`。 如果你为`autoconf`提供了参数，它读入给出的文件而不是``configure.in'`并且 把配置脚本输出到标准输出而不是`configure`。如果你给`autoconf`以参数`-'， 它将从标准输入，而不是``configure.in'`中读取并且把配置脚本输出到标准输出。

Autoconf宏在几个文件中定义。在这些文件中，有些是与Autconf一同发布的；`autoconf`首先读入它们。 而后它在包含了发布的Autoconf宏文件的目录中寻找可能出现的文件``acsite.m4'`，并且在当前目录中寻找 可能出现的文件``aclocal.m4'`。这些文件可以包含你的站点的或者包自带的Autoconf宏定义（详情请参见 [编写宏](https://blog.csdn.net/a751532301/article/details/101142061#SEC59)）。如果宏在多于一个由`autoconf`读入了的文件中被 定义，那么后面的定义将覆盖前面的定义。

`autoconf`接受如下参数：



## [用`autoreconf`更新`configure`脚本](https://blog.csdn.net/a751532301/article/details/101142061#TOC7)

如果你有大量由Autoconf生成的`configure`脚本，程序`autoreconf`可以保留你的一些工作。 它重复地运行`autoconf`（在适当的情况下还运行`autoheader`）以重新创建以当前目录为根 的目录树的Autoconf `configure`脚本和配置头文件。在缺省情况下，它只重新创建那些比对应的 ``configure.in'`或者（如果出现）``aclocal.m4'`要旧的文件。由于在文件没有被改变的情况下， `autoheader`并不改变它的输出文件的时间标记（timestamp）。这是为了使工作量最小化，修改时间标记是不必要的。 如果你安装了新版本的Autoconf，你可以以选项`--force'调用`autoreconf`而重新创建 *所有*的文件。

如果你在调用`autoreconf`时给出选项`--macrodir=dir'或者`--localdir=dir'，它将把它们传递给`autoconf`和`autoheader` （相对路径将被正确地调整）。

在同一个目录树中，`autoreconf`不支持两个目录作为同一个大包的一部分（共享``aclocal.m4'`和 ``acconfig.h'`），也不支持每个目录都是独立包（每个目录都有它们自己的``aclocal.m4'`和 ``acconfig.h'`）。 如果你使用了`--localdir'，它假定所有的目录都是同一个包的一部分。如果你没有使用`--localdir'，它假定每个目录都是一个独立的包，这条限制在将来可能被取消。

关于在`configure`脚本的源文件发生变化的情况下自动地重新创建它们的``Makefile'`规则的细节， 参见[自动地重新创建](https://blog.csdn.net/a751532301/article/details/101142061#SEC14)。这种方法正确地处理了配置头文件模板的时间标记，但并不 传递`--macrodir=dir'或者`--localdir=dir'。

`autoreconf`接受如下选项：



# [初始化和输出文件](https://blog.csdn.net/a751532301/article/details/101142061#TOC8)

Autoconf生成的`configure`脚本需要一些关于如何进行初始化，诸如如何寻找包的源文件，的信息； 以及如何生成输出文件的信息。本节叙述如何进行初始化和创建输出文件。

## [寻找`configure`的输入文件](https://blog.csdn.net/a751532301/article/details/101142061#TOC9)

所有`configure`脚本在作任何其他事情之前都必须调用`AC_INIT`。此外唯一必须调用的宏是 `AC_OUTPUT`（参见[创建输出文件](https://blog.csdn.net/a751532301/article/details/101142061#SEC10)）。

 



 

对于需要手工配置或者使用`install`程序的包来说，虽然在缺省源代码位置在大部分情况 下看起来是正确的，包还是可能需要通过调用`AC_CONFIG_AUX_DIR`来告诉 `configure`到那里去寻找一些其他的shell脚本。

 



 

## [创建输出文件](https://blog.csdn.net/a751532301/article/details/101142061#TOC10)

每个Autoconf生成的`configure`脚本必须以对`AC_OUTPUT`的调用结尾。它是一个创建 作为配置结果的``Makefile'`以及其他一些可能的文件的宏。此外唯一必须调用的宏是`AC_INIT` （参见[寻找`configure`的输入文件](https://blog.csdn.net/a751532301/article/details/101142061#SEC9)）。

 



 

 



如果你在子目录中运行`make`，你应该通过使用`make`变量`MAKE`来运行它。 `make`的大部分版本把`MAKE`设置成`make`的程序名以及它所需要的任何选项。 （但许多版本并没有把在命令行中设定的变量的值包括进来，因此它们没有被自动地传递。）一些老版本的 `make`并不设定这个变量。以下的宏使你可以在这些版本上使用它。

 



 

为了使用这个宏，在每个其他的、运行`MAKE`的目录中的``Makefile.in'`添加一行：

```
@SET_MAKE@
```

## [Makefiles中的替换](https://blog.csdn.net/a751532301/article/details/101142061#TOC11)

发布版本中每个包含了需要被编译或者被安装的文件的目录都应该含有一个文件``Makefile.in'`， `configure`将利用它在那个目录中创建一个``Makefile'`。 为了创建``Makefile'`，`configure`进行一个简单的变量替换：用`configure` 为`@variable@'选取的值，在``Makefile.in'`中对它们进行替换。 按照这种方式被替换到输出文件中的变量被称为*输出变量*。在`configure`中，它们是普通 的shell变量。为了让`configure`把特殊的变量替换到输出文件中，必须把那个变量的名字作为调用 `AC_SUBST`的参数。其他变量的任何`@variable@'都保持不变。关于 使用`AC_SUBST`创建输出变量的详情，请参见[设定输出变量](https://blog.csdn.net/a751532301/article/details/101142061#SEC54)。

使用`configure`脚本的软件应该发布文件``Makefile.in'`，而不是``Makefile'`； 这样，用户就可以在编译它之前正确地为本地系统进行配置了。

关于应该把哪些东西放入``Makefile'`的详情，请参见GNU编码标准中的`Makefile惯例'。

### [预定义输出变量](https://blog.csdn.net/a751532301/article/details/101142061#TOC12)

有些输出变量是由Autoconf宏预定义的。一部分Autoconf宏设置一些附加的输出变量，这些变量在对这些宏的描述 中被说明。关于输出变量的完整列表，参见[输出变量索引](https://blog.csdn.net/a751532301/article/details/101142061#SEC103)。下面是每个预 定义变量所包含的内容。关于变量名以`dir'结尾的变量，参见GNU编码标准中的 `为安装目录而提供的变量'。

 



 

 



 

 



 

 



 

 



 

 



 

 



 

 



 

 



 

 



 

 



 

 



 

 



 

 



 

 



 

 



 

 



 

 



 

 



 

 



 

 



 

 



 

 



 

 



 

### [创建目录](https://blog.csdn.net/a751532301/article/details/101142061#TOC13)

你可以支持从一个软件包的一份源代码拷贝中为多种结构同时进行编译的功能。为每种结构生成的目标文件都在 它们自己的目录中储存。

为了支持这个功能，`make`用变量`VPATH`来寻找储存在源代码目录中的文件。 GNU `make`和其他大部分近来的`make`程序都可以这样做。老版本的`make` 程序不支持`VPATH`；在使用它们的时候，源代码必须与目标代码处于同一个目录。

为了支持`VPATH`，每个``Makefile.in'`文件都应该包含下列两行：

```
srcdir = @srcdir@
VPATH = @srcdir@
```

不要把`VPATH`设置成其他变量的值，比如说`VPATH = $(srcdir)'，这是因为 某些版本的`make`并不对`VPATH`的值进行变量替换。

在`configure`生成``Makefile'`的时候，它用正确的值对`srcdir`进行替换。

除非在隐含规则中，不要使用`make`变量`$<`，它将被展开成到源代码目录的文件 的路径（通过`VPATH`找到的）。（诸如`.c.o'的隐含规则用于说明如何从``.c'` 文件创建``.o'`文件）有些版本的`make`在隐含规则中不设置`$<`； 它们被展开成空值。

``Makefile'`命令行总是应该通过使用前缀`$(srcdir)/'来引用源代码文件。例如：

```
time.info: time.texinfo
        $(MAKEINFO) $(srcdir)/time.texinfo
```

### [自动地重新创建](https://blog.csdn.net/a751532301/article/details/101142061#TOC14)

你可以在包的顶层目录中的``Makefile.in'`文件中添加如下的规则，以使得在你更新了配置文件之后 可以自动地更新配置信息。这个例子包括了所有可选的文件，例如``aclocal.m4'`和那些与配置头文件 有关的文件。从``Makefile.in'`规则中忽略所有你的所不需要的文件。

因为`VPATH`机制的限制，应该包含`${srcdir}/'前缀。

在重新创建不改变``config.h.in'`和``config.h'`的内容的情况下，就不会改变这两个文件的时间标记 ，因此需要``stamp-'`文件。这个特征避免了不必要的重新编译工作。你应该把文件``stamp-h.in'` 包含在你的包的发布中，以便`make`能够把``config.h.in'`看作是更新了的文件。在一些 老的BSD系统中，`touch`或者任何可能导致空文件的命令不会更改时间标记，所以使用诸如`echo` 之类的命令。

```
${srcdir}/configure: configure.in aclocal.m4
        cd ${srcdir} && autoconf

# autoheader might not change config.h.in, so touch a stamp file.
${srcdir}/config.h.in: stamp-h.in
${srcdir}/stamp-h.in: configure.in aclocal.m4 acconfig.h \
    config.h.top config.h.bot
        cd ${srcdir} && autoheader
        echo timestamp > ${srcdir}/stamp-h.in

config.h: stamp-h
stamp-h: config.h.in config.status
        ./config.status

Makefile: Makefile.in config.status
        ./config.status

config.status: configure
        ./config.status --recheck
```

此外，你应该把`echo timestamp > stamp-h'作为extra-cmds参数传递给`AC_OUTPUT`， 以便``config.status'`能够确认``config.h'`是更新了的。关于`AC_OUTPUT`的详情，请参见 [创建输出文件](https://blog.csdn.net/a751532301/article/details/101142061#SEC10)。

关于处理与配置相关的依赖性问题的更多例子，请参见[重新创建一个配置](https://blog.csdn.net/a751532301/article/details/101142061#SEC82)。

## [配置头文件](https://blog.csdn.net/a751532301/article/details/101142061#TOC15)

在包测试的C预处理器符号比较多的时候，用于把`-D'传递给编译器的命令行就会变得很长。 这导致了两个问题。一个是通过观察寻找`make`输出中的错误变得困难了。更严重的是，命令行 可能超过某些操作系统的长度限制。作为把`-D'选项传递给编译器的替代办法，`configure` 脚本可以创建一个包含了`#define'指令的C头文件。宏`AC_CONFIG_HEADER` 选择了这种输出。它应该在`AC_INIT`之后立即调用。

包应该在引入其他任何头文件之前`#include'配置头文件，以防止出现声明中的不一致性 （例如，配置头文件可能重定义了`const`）。使用`#include <config.h>'并且把选项`-I.'（或者是`-I..'；或者是任何包含``config.h'` 的目录）传递给C编译器，而不是使用`#include "config.h"'。按照这种方式，即使源代码 自行进行配置（可能是创建发布版本），其他创建目录也可以在没有找到``config.h'`的情况下， 从源代码目录进行配置。

 



 

### [配置头文件模板](https://blog.csdn.net/a751532301/article/details/101142061#TOC16)

你的发布版本应该包含一个如你所望的最终的头文件那样的模板文件，它包括注释、以及`#define` 语句的缺省值。例如，假如你的``configure.in'`进行了下列调用：

```
AC_CONFIG_HEADER(conf.h)
AC_CHECK_HEADERS(unistd.h)
```

那么你就应该在``conf.h.in'`中包含下列代码。 在含有``unistd.h'`的系统中，`configure`应该把0改成1。在其他系统中，这一行将保持不变。

```
/* Define as 1 if you have unistd.h.  */
#define HAVE_UNISTD_H 0
```

如果你的代码使用`#ifdef`而不是`#if`来测试配置选项，缺省值就可能是取消对一个变量 的定义而不是把它定义成一个值。在含有``unistd.h'`的系统中，`configure`将修改读入的第二行`#define HAVE_UNISTD_H 1'。在其他的系统中，（在系统预定义了那个符号的情况下） `configure`将以注释的方式排除这一行。

```
/* Define if you have unistd.h.  */
#undef HAVE_UNISTD_H
```

### [用`autoheader`创建``config.h.in'`](https://blog.csdn.net/a751532301/article/details/101142061#TOC17)

程序`autoheader`可以创建含有C的`#define'语句的模板文件以供`configure`使用。 如果``configure.in'`调用了`AC_CONFIG_HEADER(file)`，`autoheader`就创建 ``file.in'`；如果给出了多文件参数，就使用第一个文件。否则，`autoheader`就创建 ``config.h.in'`。

如果你为`autoheader`提供一个参数，它就使用给出的文件而不是``configure.in'`，并且把头文件输出 到标准输出中去，而不是输出到``config.h.in'`。如果你把`-'作为参数提供给`autoheader` ，它就从标准输入中，而不是从``configure.in'`中读出，并且把头文件输出到标准输出中去。

`autoheader`扫描``configure.in'`并且找出它可能要定义的C预处理器符号。它从一个名为 ``acconfig.h'`的文件中复制注释、`#define`和`#undef`语句，该文件与Autoconf一同发布 并且一同安装。如果当前目录中含有``acconfig.h'`文件，它也会使用这个文件。如果你用`AC_DEFINE` 定义了任何附加的符号，你必须在创建的那个``acconfig.h'`文件中包含附加的符号。对于由 `AC_CHECK_HEADERS`、`AC_CHECK_FUNCS`、`AC_CHECK_SIZEOF`或者 `AC_CHECK_LIB`定义的符号，`autoheader`生成注释和`#undef`语句，而不是从一个 文件中复制它们，这是因为可能的符号是无限的。

`autoheader`创建的文件包含了大部分`#define`和`#undef`语句，以及相关的注释。 如果``./acconfig.h'`包含了字符串`@TOP@'，`autoheader`就把在包含`@TOP@'的行之前的所有行复制到它生成的文件的开头。相似地，如果``./acconfig.h'`包含了字符串`@BOTTOM@'， `autoheader`就把那一行之后的所有行复制到它生成的文件的末尾。这两个字符串的任何一个都可以被忽略， 也可以被同时忽略。

产生相同效果的另一种办法是在当前目录中创建文件``file.top'`（通常是``config.h.top'`）和/或 文件``file.bot'`。如果它们存在，`autoheader`就把它们分别复制到它的输出的开头和末尾。 不鼓励使用它们是因为它们的文件名含有两个点，并因此不能在MS-DOS中储存；它们在目录中多创建了两个文件。但如果你给出 选项`--localdir=dir'以使用在其他目录中的``acconfig.h'`，它们就为你提供了一种把 定制的模板（boilerplate）放入各个独立的``config.h.in'`中的方式。

`autoheader`接受如下选项：



## [在子目录中配置其它包](https://blog.csdn.net/a751532301/article/details/101142061#TOC18)

在大多数情况下，调用`AC_OUTPUT`足以在子目录中生成``Makefile'`。然而，控制了多于一个 独立包的`configure`脚本可以使用`AC_CONFIG_SUBDIRS`来为每个子目录中的其他包运行 `configure`脚本。

 



 

## [缺省的前缀](https://blog.csdn.net/a751532301/article/details/101142061#TOC19)

在缺省状态下，`configure`把它所安装的文件的前缀设置成``/usr/local'`。 `configure`的用户可以通过选项`--prefix'和`--exec-prefix'选择一个不同的前缀。 有两种方式修改缺省的行为：在创建`configure`时，和运行`configure`时。

有些软件包在缺省情况下可能需要安装到``/usr/local'`以外的目录中。为此，使用宏`AC_PREFIX_DEFAULT`。

 



 

对于用户来说，让`configure`根据它们已经安装的相关程序的位置来猜测安装前缀，可能会带来方便。如果你 希望这样做，你可以调用`AC_PREFIX_PROGRAM`。

 



 

## [`configure`中的版本号](https://blog.csdn.net/a751532301/article/details/101142061#TOC20)

以下的宏为`configure`脚本管理版本号。使用它们是可选的。

 



 

 



# [现有的测试](https://blog.csdn.net/a751532301/article/details/101142061#TOC21)

这些宏测试了包可能需要或者需要使用的特定的系统特征。如果你要测试这些宏所不能测试的特征，可能你可以用 适当的参数调用主测试宏来达到目的（参见[编写测试](https://blog.csdn.net/a751532301/article/details/101142061#SEC40)）。

这些宏打印消息以告诉用户它们正在测试的特征，以及它们的测试结果。它们为未来运行的`configure` 储存测试结果（参见[缓存结果](https://blog.csdn.net/a751532301/article/details/101142061#SEC55)）。

在这些宏中，有的宏设置输出变量。关于如何获取它们的值，请参见[Makefile中的替换](https://blog.csdn.net/a751532301/article/details/101142061#SEC11)。 在下面出现的术语“定义name”是“把C预处理符号name定义成1”的简称。 关于如何把这些符号的定义放入你的程序中，参见[定义C预处理器符号](https://blog.csdn.net/a751532301/article/details/101142061#SEC53)。

## [对程序的选择](https://blog.csdn.net/a751532301/article/details/101142061#TOC22)

这些宏检查了特定程序的存在或者特定程序的特征。它们被用于在几个可以相互替代的程序间进行选择，并且在决定选用 某一个的时候作些什么。如果没有为你要使用的程序定义特定的宏，并且你不需要检查它的任何特殊的特征，那么你就 可以选用一个通用程序检查宏。

### [对特定程序的检查](https://blog.csdn.net/a751532301/article/details/101142061#TOC23)

这些宏检查特定的程序--它们是否存在，并且在某些情况下它们是否支持一些特征。

 



 

 



 

 



 

 



 

 



 

 



 

 



 

 



 

 



 

 



 

 



 

 



 

 



 



 

 



 

### [对普通程序和文件的检查](https://blog.csdn.net/a751532301/article/details/101142061#TOC24)

这些宏用于寻找没有包含在特定程序测试宏中的程序。如果你除了需要确定程序是否存在，还需要检测程序的行为，你就 不得不为它编写你自己的测试了（参见[编写测试](https://blog.csdn.net/a751532301/article/details/101142061#SEC40)）。在缺省情况下，这些宏使用 环境变量`PATH`。如果你需要检查可能不会出现在`PATH`中的程序，你可能要按照下面的方式 给出修改了的路径：

```
AC_PATH_PROG(INETD, inetd, /usr/libexec/inetd,
  $PATH:/usr/libexec:/usr/sbin:/usr/etc:etc)
```

 



 

 



 

 



 

 



 

 



 

 



 

 



 

## [库文件](https://blog.csdn.net/a751532301/article/details/101142061#TOC25)

下列的宏检查某些C、C++或者Fortran 77库文件是否存在。

 



 

 



 

 



 

 



 

## [库函数](https://blog.csdn.net/a751532301/article/details/101142061#TOC26)

以下的宏用于检测特定的C库函数。如果没有为你需要的函数定义特定的宏，而且你不需要检查它的任何特殊性质， 那么你可以使用一个通用函数检测宏。

### [对特定函数的检查](https://blog.csdn.net/a751532301/article/details/101142061#TOC27)

这些宏用于检测特定的C函数--它们是否存在，以及在某些情况下，当给出了特定的参数时，它们是如何响应的。

 



 



 

 



 

 



 



 

 



 

 



 

 



 

 



 

 



 

 



 

 



 

 



 

 



 

 



 

 



 

 



 

### [对普通函数的检查](https://blog.csdn.net/a751532301/article/details/101142061#TOC28)

这些宏被用于寻找没有包括在特定函数测试宏中的函数。如果函数可能出现在除了缺省C库以外的库中，就 要首先为这些库调用`AC_CHECK_LIB`。如果你除了需要检查函数是否存在之外，还要检查函数 的行为，你就不得不为此而编写你自己的测试（参见[编写测试](https://blog.csdn.net/a751532301/article/details/101142061#SEC40)）。

 



 

 



 

 



 

## [头文件](https://blog.csdn.net/a751532301/article/details/101142061#TOC29)

下列宏检查某些C头文件是否存在。如果没有为你需要检查的头文件定义特定的宏，而且你不需要检查它的任何特殊 属性，那么你就可以使用一个通用的头文件检查宏。

### [对特定头文件的检查](https://blog.csdn.net/a751532301/article/details/101142061#TOC30)

这些宏检查特定的系统头文件--它们是否存在，以及在某些情况下它们是否定义了特定的符号。

 



 

 



 

 



 

 



 

 



 

 



 



 

 



 

 



 

### [对普通头文件的检查](https://blog.csdn.net/a751532301/article/details/101142061#TOC31)

这些宏被用于寻找没有包括在特定测试宏中的系统头文件。如果你除了检查头文件是否存在之外还要检查它的内容， 你就不得不为此而编写你自己的测试（参见[编写测试](https://blog.csdn.net/a751532301/article/details/101142061#SEC40)）。

 



 

 



 

## [结构](https://blog.csdn.net/a751532301/article/details/101142061#TOC32)

以下的宏检查某些结构或者某些结构成员。为了检查没有在此给出的结构，使用`AC_EGREP_CPP` （参见[检验声明](https://blog.csdn.net/a751532301/article/details/101142061#SEC41)）或者使用`AC_TRY_COMPILE` （参见[检验语法](https://blog.csdn.net/a751532301/article/details/101142061#SEC42)）。

 



 

 



 



 

 



 

 



 

 



 

 



 

## [类型定义](https://blog.csdn.net/a751532301/article/details/101142061#TOC33)

以下的宏检查C typedefs。如果没有为你需要检查的typedef定义特定的宏，并且你不需要检查该类型 的任何特殊的特征，那么你可以使用一个普通的typedef检查宏。

### [对特定类型定义的检查](https://blog.csdn.net/a751532301/article/details/101142061#TOC34)

这些宏检查在``sys/types.h'`和``stdlib.h'`（如果它存在）中定义的特定的C typedef。

 



 

 



 

 



 

 



 

 



 



 

 



 

### [对普通类型定义的检查](https://blog.csdn.net/a751532301/article/details/101142061#TOC35)

本宏用于检查没有包括在特定类型测试宏中的typedef。

 



 

## [C编译器的特征](https://blog.csdn.net/a751532301/article/details/101142061#TOC36)

下列宏检查C编译器或者机器结构的特征。为了检查没有在此列出的特征，使用`AC_TRY_COMPILE` （参见[检验语法](https://blog.csdn.net/a751532301/article/details/101142061#SEC42)）或者`AC_TRY_RUN` （参见[检查运行时的特征](https://blog.csdn.net/a751532301/article/details/101142061#SEC44))

 



 

 



 

 



 

 



 

 



 

 



 



 

 



 

 



 

## [Fortran 77编译器的特征](https://blog.csdn.net/a751532301/article/details/101142061#TOC37)

下列的宏检查Fortran 77编译器的特征。为了检查没有在此列出的特征，使用`AC_TRY_COMPILE` （参见[检验语法](https://blog.csdn.net/a751532301/article/details/101142061#SEC42)）或者`AC_TRY_RUN` （参见[检验运行时的特征](https://blog.csdn.net/a751532301/article/details/101142061#SEC44)），但首先必须确认当前语言被设置成 Fortran 77 `AC_LANG_FORTRAN77`（参见[对语言的选择](https://blog.csdn.net/a751532301/article/details/101142061#SEC51)）。

 



 

## [系统服务](https://blog.csdn.net/a751532301/article/details/101142061#TOC38)

下列宏检查操作系统服务或者操作系统能力。

 



 

 



 

 



 

 



 

 



 

 



 



 

 



 

 



 

## [UNIX变种](https://blog.csdn.net/a751532301/article/details/101142061#TOC39)

下列宏检查对于有些程序来说需要特殊处理的一些操作系统，这是因为它们的头文件或库文件中含有特别 怪异的东西。这些宏不讨人喜欢；它们将根据它们所支持的函数或者它们提供的环境，被更加系统化的方法所代替。

 



 

 



 

 



 

 



 

 



 

 



 

 



 

# [编写测试](https://blog.csdn.net/a751532301/article/details/101142061#TOC40)

如果现有的特征测试不能完成你所需要的工作，你就必须编写一个新的。这些宏是创建模块。它们为其它宏提供了检查各种 特征是否存在并且报告结果的方式。

本章包括一些建议和一些关于现有的测试的为什么要那样编写的原因。通过阅读现有的测试，你还可以学到许多关于编写  Autoconf测试的方法。如果在一个或多个Autoconf测试中出现了错误，这些信息可以帮助你理解它们意味着什么，这有助  于你找到最佳的解决问题的办法。

这些宏检查C编译器系统的输出。它们并不为未来的使用而缓存测试的结果（参见[缓存结果](https://blog.csdn.net/a751532301/article/details/101142061#SEC55)）， 这是因为它们没有足够的信息以生成缓存变量名。基于同样的原因，它们还不会输出任何消息。对特殊的C的特征进行的测试 调用这些宏并且缓存它们的结果、打印关于它们所进行的测试的消息。

当你编写了一个可以适用于多于一个软件包的特征测试时，最好的方式就是用一个新宏封装它。关于如何封装，参见 [编写宏](https://blog.csdn.net/a751532301/article/details/101142061#SEC59)。

## [检验声明](https://blog.csdn.net/a751532301/article/details/101142061#TOC41)

宏`AC_TRY_CPP`用于检测某个特定的头文件是否存在。你可以一次检查一个头文件，或者如果你为了某些目的 而希望多个头文件都存在，也可以一次检查多个头文件。

 



 

下面是如何确认在某个头文件中是否包含一个特定的声明，比如说typedef、结构、结构成员或者一个函数。使用 `AC_EGREP_HEADER`而不是对头文件直接运行`grep`；在某些系统中，符号可能是在另一个你所检查的`#include'文件。

 



 

为了检查由头文件或者C预处理器预定义的C预处理器符号，使用`AC_EGREP_CPP`。下面是后者的一个例子：

```
AC_EGREP_CPP(yes,
[#ifdef _AIX
  yes
#endif
], is_aix=yes, is_aix=no)
```

 



 

## [检验语法](https://blog.csdn.net/a751532301/article/details/101142061#TOC42)

为了检查C、C++或者Fortran 77编译器的语法特征，比如说它是否能够识别某个关键字，就使用`AC_TRY_COMPILE` 来尝试编译一个小的使用该特征的程序。你还可以用它检查不是所有系统都支持的结构和结构成员。

 



 

## [检验库](https://blog.csdn.net/a751532301/article/details/101142061#TOC43)

为了检查一个库、函数或者全局变量，Autoconf `configure`脚本试图编译并连接一个使用它的小程序。 不像Metaconfig，它在缺省情况下对C库使用`nm`或者`ar`以试图确认可以使用那个函数。 由于与函数相连接避免了处理`nm`和`ar`的各个变种的选项及输出格式，而且不必处理标准库的位置， 所以与函数连接通常是更加可靠的办法。如果需要，它还允许进行交叉配置或者检查函数的运行是特征。另一方面， 它比一次性扫描库要慢一些。

少数系统的连接器在出现找不到的函数错误（unresolved functions）时不返回失败的退出状态。这个错误使得由Autoconf 生成的配置脚本不能在这样的系统中使用。然而，有些这样的连接器允许给出选项以便正确地返回错误状态。  Autoconf目前还不能自动地处理这个问题。如果用户遇到了这样的问题，他们可能可以通过在环境中设置`LDFLAGS` 以把连接器所需要的选项（例如，`-Wl,-dn'on MIPS RISC/OS）传递给连接器，从而解决这个问题。

`AC_TRY_LINK`用于编译测试程序，以测试函数和全局变量。`AC_CHECK_LIB`还用本宏把被测试的库 暂时地加入`LIBS`并试图连接一个小程序，从而对库进行检查（参见[库文件](https://blog.csdn.net/a751532301/article/details/101142061#SEC25)）。

 



 

 



 

 



 

 



 

## [检验运行时的特征](https://blog.csdn.net/a751532301/article/details/101142061#TOC44)

有时候，你需要知道系统在运行时作了些什么，比如说某个给定的函数是否具备某种能力或者是否含有错误。如果你能， 你可以在你的程序初始化时自行检查这类事件（比如说machine's endianness）。

如果你实在需要在配置时刻检查运行时的特征，你可以编写一个测试程序以确定结果，并且通过`AC_TRY_RUN` 来编译和运行它。如果可能就避免运行测试程序，这是因为使用它们使得人们不能对你的包进行交叉编译。

### [运行测试程序](https://blog.csdn.net/a751532301/article/details/101142061#TOC45)

如果你希望在配置的时候测试系统运行时的特征，就使用如下的宏。

 



 

当交叉编译使运行时测试变得不可能的时候，就尝试提供一个应急（pessimistic）的缺省值以供使用。你通过把可选的最后一个参数 传递给`AC_TRY_RUN`来完成这个工作。在每次生成`configure`的过程中，每次遇到没有提供 action-if-cross-compiling参数的`AC_TRY_RUN`调用时，`autoconf`都打印一条警告消息。 虽然用户将不能为交叉编译你的包而进行配置，你仍可以忽略该警告。与Autoconf一同发行的少数宏产生该警告消息。

为了为交叉编译进行配置，你还可以根据规范系统名（canonical system name）为这些参数选择值 （参见[手工配置](https://blog.csdn.net/a751532301/article/details/101142061#SEC67)）。另一种方式是把测试缓存文件设置成目标系统的正确值 （参见[缓存结果](https://blog.csdn.net/a751532301/article/details/101142061#SEC55)）。

为了给嵌入到其它宏（包括少数与Autoconf一同发行的宏）中的，对`AC_TRY_RUN`的调用提供缺省值， 你可以在它们运行之前调用`AC_PROG_CC`。那么，如果shell变量`cross_compiling`被设置成`yes'，就使用另一种方法来获取结果，而不是调用宏。

 



 

### [测试程序指南](https://blog.csdn.net/a751532301/article/details/101142061#TOC46)

测试程序不应该向标准输出输出任何信息。如果测试成功，它们应该返回0，否则返回非0，以便于把成功的执行 从core dump或者其它失败中区分出来；段冲突（segmentation violations）和其它失败产生一个非0的退出状态。 测试程序应该从`main`中`exit`，而不是`return`，这是因为在某些系统中 （至少在老式的Sun上），`main`的`return`的参数将被忽略。

测试程序可以使用`#if`或者`#ifdef`来检查由已经执行了的测试定义的预处理器宏的值。 例如，如果你调用`AC_HEADER_STDC`，那么在``configure.in'`的随后部分，你可以使用一个有 条件地引入标准C头文件的测试程序：

```
#if STDC_HEADERS
# include <stdlib.h>
#endif
```

如果测试程序需要使用或者创建数据文件，其文件名应该以``conftest'`开头，例如``conftestdata'`。 在运行测试程序之后或者脚本被中断时，`configure`将通过运行`rm -rf conftest*'来清除数据文件。

### [测试函数](https://blog.csdn.net/a751532301/article/details/101142061#TOC47)

在测试程序中的函数声明应该条件地含有为C++提供的原型。虽然实际上测试程序很少需要带参数的函数。

```
#ifdef __cplusplus
foo(int i)
#else
foo(i) int i;
#endif
```

测试程序声明的函数也应该有条件地含有为C++提供的，需要`extern "C"'的原型。要确保不要引入 任何包含冲突原型的头文件。

```
#ifdef __cplusplus
extern "C" void *malloc(size_t);
#else
char *malloc();
#endif
```

如果测试程序以非法的参数调用函数（仅仅看它是否存在），就组织程序以确保它从不调用这个函数。你可以 在另一个从不调用的函数中调用它。你不能把它放在对`exit`的调用之后，这是因为GCC第2版知道 `exit`永远不会返回，并且把同一块中该调用之后的所有代码都优化掉。

如果你引入了任何头文件，确保使用正确数量的参数调用与它们相关的函数，即使它们不带参数也是如此， 以避免原型造成的编译错误。GCC第2版为有些它自动嵌入（inline）的函数设置了内置原型；例如， `memcpy`。为了在检查它们时避免错误，既可以给它们正确数量的参数，也可以以不同的返回 类型（例如`char`）重新声明它们。

## [可移植的Shell编程](https://blog.csdn.net/a751532301/article/details/101142061#TOC48)

在编写你自己的测试时，为了使你的代码可以移植，你应该避免使用某些shell脚本编程技术。 Bourne  shell和诸如Bash和Korn shell之类的向上兼容的shell已经发展了多年，但为了避免麻烦，不要利用 在UNIX版本7，circa  1977之后添加的新特征。你不应该使用shell函数、别名、负字符集（negated character classes）  或者其它不是在所有与Bourne兼容的shell中都能找到的特征；把你自己限制到最低的风险中去。 （the lowest common  denominator）。即使是`unset`都不能够被所有的shell所支持！ 还有，像下面那样在指定解释器的惊叹号之后给出空格：

```
#! /usr/bin/perl
```

如果你忽略了路径之前的空格，那么基于4.2BSD的系统（比如说Sequent DYNIX）将忽略这一行，这是因为它们把`#! /'看作一个四字节的魔数（magic number）。

你在`configure`脚本中运行的外部程序，应该是一个相当小的集合。关于可用的外部程序列表，参见 GNU编码标准中的‘Makefile中的工具’一节。这个限制允许用户在只拥有相当少的程序时进行配置 和编译，这避免了软件包之间过多的依赖性。

此外，这些外部工具中的某些工具只有一部分特征是可移植的。例如，不要依赖`ln`支持`-f'选项， 也不要依赖`cat`含有任何选项。`sed`脚本不应该含有注释，也不应该使用长于8个字符的分支标记。 不要使用`grep -s'来禁止（suppress）输出。而要把`grep`的标准输出和标准错误输出 （在文件不存在的情况下会输出信息到标准错误输出）重新定向到``/dev/null'`中。检查`grep`的退出 状态以确定它是否找到了一个匹配。

## [测试值和文件](https://blog.csdn.net/a751532301/article/details/101142061#TOC49)

`configure`脚本需要测试许多文件和字符串的属性。下面是在进行这些测试的时候需要提防的一些移植性问题。

程序`test`是进行许多文件和字符串测试的方式。人们使用替代（alternate）名`['来调用它， 但因为`['是一个`m4`的引用字符，在Autoconf代码中使用`['将带来麻烦。

如果你需要通过`test`创建多个检查，就用shell操作符`&&'和`||'把它们组合起来，而不是使用`test`操作符`-a'和`-o'。在System V中，`-a'和`-o'相对于unary操作符的优先级是错误的；为此，POSIX并未给出它们，所以使用它们是 不可移植的。如果你在同一个语句中组合使用了`&&'和`||'，要记住它们的 优先级是相同的。

为了使得`configure`脚本可以支持交叉编译，它们不能作任何测试主系统而不是测试目标系统的事。但你偶尔 可以发现有必要检查某些特定（arbitrary）文件的存在。为此，使用`test -f'或者`test -r'。 不要使用`test -x'，因为4.3BSD不支持它。

另一个不可移植的shell编程结构是

```
var=${var:-value}
```

它的目的是仅仅在没有设定var的值的情况下，把var设置成value， 但如果var已经含有值，即使是空字符串，也不修改var。老式BSD shell，包括 Ultrix `sh`，不接受这个冒号，并且给出错误并停止。一个可以移植的等价方式是

```
: ${var=value}
```

## [多种情况](https://blog.csdn.net/a751532301/article/details/101142061#TOC50)

有些操作是以几种可能的方式完成的，它依赖于UNIX的变种。检查它们通常需要一个"case 语句"。Autoconf不能直接提供该语句； 然而，通过用一个shell变量来记录是否采用了操作的某种已知的方式，可以容易地模拟该语句。

下面是用shell变量`fstype`记录是否还有需要检查的情况的例子。

```
AC_MSG_CHECKING(how to get filesystem type)
fstype=no
# The order of these tests is important.
AC_TRY_CPP([#include <sys/statvfs.h>
#include <sys/fstyp.h>], AC_DEFINE(FSTYPE_STATVFS) fstype=SVR4)
if test $fstype = no; then
AC_TRY_CPP([#include <sys/statfs.h>
#include <sys/fstyp.h>], AC_DEFINE(FSTYPE_USG_STATFS) fstype=SVR3)
fi
if test $fstype = no; then
AC_TRY_CPP([#include <sys/statfs.h>
#include <sys/vmount.h>], AC_DEFINE(FSTYPE_AIX_STATFS) fstype=AIX)
fi
# (more cases omitted here)
AC_MSG_RESULT($fstype)
```

## [对语言的选择](https://blog.csdn.net/a751532301/article/details/101142061#TOC51)

既使用C又使用C++的包需要同时测试两个编译器。Autoconf生成的`configure`脚本 在缺省情况下检查C的特征。以下的宏决定在``configure.in'`的随后部分使用那个语言的编译器。

 



 

 



 

 



 

 



 

 



 

 



 

# [测试的结果](https://blog.csdn.net/a751532301/article/details/101142061#TOC52)

一旦`configure`确定了某个特征是否存在，它将如何记录这一信息？这里有四种记录方式： 定义一个C预处理器符号、在输出文件中设置一个变量、为将来运行`configure`而把结果储存到一个缓存文件中， 以及打印一条消息以便让用户知道测试的结果。

## [定义C预处理器符号](https://blog.csdn.net/a751532301/article/details/101142061#TOC53)

对一个特征的检测的常见回应是定义一个表示测试结果的C预处理器符号。这是通过调用`AC_DEFINE` 或者`AC_DEFINE_UNQUOTED`来完成的。

在缺省状态下，`AC_OUTPUT`把由这些宏定义的符号放置到输出变量`DEFS`中，该变量为每个 定义了的符号添加一个选项`-Dsymbol=value'。与Autoconf第1版不同，在运行时 不定义`DEFS`变量。为了检查Autoconf宏是否已经定义了某个C预处理器符号，就检查适当的缓存变量的值， 例子如下：

```
AC_CHECK_FUNC(vprintf, AC_DEFINE(HAVE_VPRINTF))
if test "$ac_cv_func_vprintf" != yes; then
AC_CHECK_FUNC(_doprnt, AC_DEFINE(HAVE_DOPRNT))
fi
```

如果已经调用了`AC_CONFIG_HEADER`，那么就不是创建`DEFS`，而是由`AC_OUTPUT` 创建一个头文件，这是通过在一个暂时文件中把正确的值替换到`#define`语句中来实现的。 关于这种输出的详情，请参见[配置头文件](https://blog.csdn.net/a751532301/article/details/101142061#SEC15)。

 



 



由于Bourne shell在语法上的特异性，不要用分号来分隔对`AC_DEFINE`或者`AC_DEFINE_UNQUOTED`的调用和 其它的宏调用或者shell代码；这将在最终的`configure`脚本中导致语法错误。你既可以使用空格，也可以使用 换行。就是这样：

```
AC_CHECK_HEADER(elf.h, AC_DEFINE(SVR4) LIBS="$LIBS -lelf")
```

或者：

```
AC_CHECK_HEADER(elf.h,
  AC_DEFINE(SVR4)
  LIBS="$LIBS -lelf")
```

而不是：

```
AC_CHECK_HEADER(elf.h, AC_DEFINE(SVR4); LIBS="$LIBS -lelf")
```

## [设置输出变量](https://blog.csdn.net/a751532301/article/details/101142061#TOC54)

记录测试结果的一种方式是设置*输出变量*，该变量是shell变量，它的值将被替换到`configure`输出的文件中。 下面的两个宏创建新的输出变量。关于总是可用的输出变量的列表，参见[预定义输出变量](https://blog.csdn.net/a751532301/article/details/101142061#SEC12)。

 



 

 



## [缓存结果](https://blog.csdn.net/a751532301/article/details/101142061#TOC55)

为了避免在各种`configure`脚本中重复地对相同的特征进行检查（或者重复地运行同一个脚本）， `configure`把它的检查的许多结果储存在*缓存文件*。如果在`configure`脚本运行时，它找到了 缓存文件，它就从中读取从前运行的结果并且不再重新运行这些检查。因此，`configure`将比每次都运行所有的检查 要快得多。

 



 

 



 

 



 

 



 

### [缓存变量名](https://blog.csdn.net/a751532301/article/details/101142061#TOC56)

缓存变量的名字应该符合如下格式：

```
package-prefix_cv_value-type_specific-value[_additional-options]
```

例如，`ac_cv_header_stat_broken'或者`ac_cv_prog_gcc_traditional'。 变量名的各个部分为：



赋予缓存变量的值不能含有新行。通常，它们的是将是布尔（`yes'或`no'）或者文件名或者函数名； 所以，这并不是一个重要的限制。

### [缓存文件](https://blog.csdn.net/a751532301/article/details/101142061#TOC57)

缓存文件是一个缓存了在一个系统上进行配置测试的结果，以便在配置脚本和配置的运行之间共享的shell脚本。 它对于其他系统来说是没有用的。如果它的内容因为某些原因而变得无效了，用户可以删除或者编辑它。

在缺省情况下，configure把``./config.cache'`作为缓存文件，如果它还不存在，就创建它。 `configure`接受选项`--cache-file=file'以使用不同的缓存文件； 这就是`configure`在调用子目录中的`configure`脚本时所作的工作。 关于使用宏`AC_CONFIG_SUBDIRS`在子目录中进行配置的信息，参见 [在子目录中配置其它包](https://blog.csdn.net/a751532301/article/details/101142061#SEC18)。

给出`--cache-file=/dev/null'会关闭缓存，这是为调试`configure`提供的。 只有在调用``config.status'`时给出选项`--recheck'，这将导致它重新运行`configure`， 它才会注意到缓存文件。如果你预计需要一个长的调试时期，你还可以通过在``configure.in'`的开头重新定义 缓存宏而关闭对`configure`脚本的装入和储存：

```
define([AC_CACHE_LOAD], )dnl
define([AC_CACHE_SAVE], )dnl
AC_INIT(whatever)
 ... rest of configure.in ...
```

试图为特定的系统类型发布缓存文件是错误的。这里存在太多的导致错误的空间，并带来太多的用于维护它们的管理开销。 对于任何不能被自动猜测出来的特征，应使用规范系统类型和连接文件的方法（参见[手工配置](https://blog.csdn.net/a751532301/article/details/101142061#SEC67)）。

在特定系统中，每当有人运行`configure`脚本时，缓存文件将逐渐积累起来；缓存文件在一开始并不存在。 运行`configure`会把新的缓存结果与现存的缓存文件结合起来。为了让它透明地工作，只要每次都使用相同的C编译器， 站点初始化（site initialization）脚本可以指定一个站点范围（site-wide）的缓存文件以代替缺省的缓存文件。 （参见[设定本地缺省值](https://blog.csdn.net/a751532301/article/details/101142061#SEC80)）。

如果你的配置脚本，或者configure.in中的宏调用，偶尔导致配置过程的失败，在几个关键点进行缓存可能是有用的。 在有希望修正导致上次运行的错误的时候，这样做将减少重新运行configure脚本的时间。

```
 ... AC_INIT, etc. ...
dnl checks for programs
AC_PROG_CC
AC_PROG_GCC_TRADITIONAL
 ... more program checks ...
AC_CACHE_SAVE

dnl checks for libraries
AC_CHECK_LIB(nsl, gethostbyname)
AC_CHECK_LIB(socket, connect)
 ... more lib checks ...
AC_CACHE_SAVE

dnl Might abort...
AM_PATH_GTK(1.0.2, , exit 1)
AM_PATH_GTKMM(0.9.5, , exit 1)
```

## [打印消息](https://blog.csdn.net/a751532301/article/details/101142061#TOC58)

`configure`脚本需要为运行它们的用户提供几种信息。下列的宏为每种信息以适当的方式打印消息。 所有宏的参数都应该由shell双引号括起来，以便shell可以对它们进行变量替换和反引号替换。你可以把消息用 `m4`引用字符括起来以打印包含括号的消息：

```
AC_MSG_RESULT([never mind, I found the BASIC compiler])
```

这些宏都是对shell命令`echo`的封装。`configure`应该很少需要直接运行`echo`来为 用户打印消息。使用这些宏使得修改每种消息如何打印及何时打印变得容易了；这些修改只需要对宏的定义进行就行了， 而所有的调用都将自动地改变。

 



 

 



 

 



 

 



 

下列两个宏是`AC_MSG_CHECKING`和`AC_MSG_RESULT`的过时的替代版本。

 



 



 

# [编写宏](https://blog.csdn.net/a751532301/article/details/101142061#TOC59)

当你编写了一个可以用于多个软件包的特征测试时，最好用一个新宏把它封装起来。下面是一些关于编写 Autoconf宏的要求（instructions）和指导（guidelines）。

## [宏定义](https://blog.csdn.net/a751532301/article/details/101142061#TOC60)

 Autoconf宏是用宏`AC_DEFUN`定义的，该宏与`m4`的内置`define`宏相似。 除了定义一个宏，`AC_DEFUN`把某些用于限制宏调用顺序的代码添加到其中。 （参见[首要的宏](https://blog.csdn.net/a751532301/article/details/101142061#SEC64)）。

一个Autoconf宏像下面那样定义：

```
AC_DEFUN(macro-name, [macro-body])
```

这里的方括号并不表示可选的文本：它们应当原样出现在宏定义中，以避免宏扩展问题 （参见[引用](https://blog.csdn.net/a751532301/article/details/101142061#SEC62)）。你可以使用`$1'、`$2'等等来访问 传递给宏的任何参数。

为使用`m4`注释，使用`m4`内置的`dnl`； 它使`m4`放弃本行中其后的所有文本。因为在调用`AC_INIT`之前，所有的输出都被取消， 所以在``acsite.m4'`和``aclocal.m4'`中的宏定义之间不需要它。

关于编写`m4`宏的更完整的信息，参见GNU m4中的`如何定义新宏'。

## [宏名](https://blog.csdn.net/a751532301/article/details/101142061#TOC61)

所有Autoconf宏都以`AC_'起头以防止偶然地与其它文本发生冲突。所有它们用于内部目的的shell变量 几乎全部是由小写字母组成的，并且以`ac_'开头的名字。为了确保你的宏不会与现在的或者将来的Autoconf宏冲突， 你应该给你自己的宏名和任何它们因为某些原因而需要使用的shell变量添加前缀。它可能是你名字的开头字符，或者 你的组织或软件包名称的缩写。

大部分Autoconf宏的名字服从一个表明特征检查的种类命名惯例。宏名由几个单词组成，由下划线分隔，可以是最常见的， 也可以是最特殊的。它们的缓存变量名服从相同的惯例。（关于它们的详细信息， 参见[缓存变量名](https://blog.csdn.net/a751532301/article/details/101142061#SEC56)）。

`AC_'之后的第一个单词通常给出被测试特征的类别。下面是Autoconf为特殊测试宏使用的类别， 它们是你很可能要编写的宏。它们的全小写形式还用于缓存变量。在可能的地方使用它们；如果不能，就发明一个你自己的类别。



在类别之后就是特定的被测试特征的名称。宏名中所有的其它单词指明了特征的特殊方面。 例如，`AC_FUNC_UTIME_NULL`检查用`NULL`指针调用`utime`函数时该函数的行为。

一个作为另一个宏的内部子程序的宏的名字应该以使用它的宏的名字开头，而后是说明内部宏作了什么的一个或多个单词。 例如，`AC_PATH_X`有内部宏`AC_PATH_X_XMKMF`和`AC_PATH_X_DIRECT`。

## [引用](https://blog.csdn.net/a751532301/article/details/101142061#TOC62)

由其他的宏调用的宏将被`m4`进行几次求值；每次求值都可能需要一层引号以防止对宏或者`m4` 内置宏的不必要扩展，例如说`define'和`$1'。引号还需要出现在含有逗号的宏参数中， 这是因为逗号把参数与参数分隔开来。还有，把所有含有新行和调用其它宏的宏参数引起来是一个好主意。

Autoconf把`m4`的引用字符从缺省的``'和`''改为`['和`]'， 这是因为许多宏使用``'和`''，这不方便。然而，在少数情况下，宏需要使用方括号（通常在C程序文本 或者常规表达式中）。在这些情况下，它们使用`m4`内置命令`changequote`暂时地把引用字符改为`<<'和`>>'。 （有时，如果它们不需要引用任何东西，它们就通过把引用字符设置成空字符串以完全关闭引用。）下面是一个例子：

```
AC_TRY_LINK(
changequote(<<, >>)dnl
<<#include <time.h>
#ifndef tzname /* For SGI.  */
extern char *tzname[]; /* RS6000 and others reject char **tzname.  */
#endif>>,
changequote([, ])dnl
[atoi(*tzname);], ac_cv_var_tzname=yes, ac_cv_var_tzname=no)
```

当你用新编写的宏创建`configure`脚本时，仔细地验证它以检查你是否需要在你的宏之中添加更多的引号。 如果一个或多个单词在`m4`的输出中消失了，你就需要更多的引号。当你不能确定的时候，就使用引号。

但是，还有放置了过多层的引号的可能。如果这发生了，`configure`脚本的结果将包含未扩展的宏。 程序`autoconf`通过执行`grep AC_ configure'来检查这个问题。

## [宏之间的依赖性](https://blog.csdn.net/a751532301/article/details/101142061#TOC63)

为了正确地工作，有些Autoconf宏要求在调用它们之前调用其它的宏。Autoconf提供了一种方式以确保在需要时， 某个宏已经被调用过了，以及一种在宏可能导致不正确的操作时给出警告的方式。

### [首要的宏](https://blog.csdn.net/a751532301/article/details/101142061#TOC64)

你编写的宏可能需要使用从前有其它宏计算出来的结果。例如，`AC_DECL_YYTEXT`要检验`flex`或 `lex`的输出，所以它要求首先调用`AC_PROG_LEX`以设置shell变量`LEX`。

比强制宏的用户跟踪宏以前的依赖性更好的是，你可以使用宏`AC_REQUIRE`以自动地完成这一任务。 `AC_REQUIRE`可以确保只在需要的时候调用宏，并且只被调用一次。

 



 

一个替代`AC_DEFUN`的方法是使用`define`并且调用`AC_PROVIDE`。 因为这个技术并不防止出现嵌套的消息，它已经是过时的了。

 



### [建议的顺序](https://blog.csdn.net/a751532301/article/details/101142061#TOC65)

有些宏在都被调用的时候，一个宏就需要在另一个宏之前运行，但是它们并不要求调用另一个宏。例如，应该在任何运行C编译器的宏 之前调用修改了C编译器行为的宏。在文档中给出了许多这样的依赖性。

当``configure.in'`文件中的宏违背了这类依赖性，Autoconf就提供宏`AC_BEFORE`以警告用户。 警告出现在从``configure.in'`创建`configure`的时候，而不是在运行`configure`的时候。 例如，`AC_PROG_CPP`检查C编译器是否可以在给出`-E'的情况下运行C预处理器。因而应该在任何 改变将要使用的C编译器的宏之后调用它 。所以`AC_PROG_CC`包含：

```
AC_BEFORE([$0], [AC_PROG_CPP])dnl
```

如果在调用`AC_PROG_CC`时，已经调用了`AC_PROG_CPP`，它就警告用户。

 



 

### [过时的宏](https://blog.csdn.net/a751532301/article/details/101142061#TOC66)

配置和移植技术已经演化了好些年了。对于特定的问题，通常已经提出了更好的解决办法，或者同类的方法（ad-hoc approaches） 已经被系统化了。结果就是有些宏现在已经被认为是*过时*了；它们仍然能工作，但不再被认为是最佳选择。 Autoconf提供了宏`AC_OBSOLETE`，当用户使用过时的宏时，就在生成`configure`脚本的时候 对用户提出警告，以鼓励他们跟上潮流。一个调用实例是：

```
AC_OBSOLETE([$0], [; use AC_CHECK_HEADERS(unistd.h) instead])dnl
```

 



 

# [手工配置](https://blog.csdn.net/a751532301/article/details/101142061#TOC67)

有几种特征不能通过运行测试程序而自动猜测出来。例如，目标文件格式的细节，或者需要传递给编译器或连接器的特殊选项。 你可以使用同类手段（ad-hoc means）来检查这类特征，比如说让`configure`检查`uname`程序的 输出，或者寻找仅仅在特定系统中出现的库。然而，Autoconf为处理不可猜测的特征提供了统一的手段。

## [指定系统的类型](https://blog.csdn.net/a751532301/article/details/101142061#TOC68)

类似与其它GNU `configure`脚本，Autoconf生成的`configure`脚本可以根据系统类型的规范名 (canonical name)做出决定，该规范系统名的形式为：

```
cpu-company-system
```

`configure`通常可以猜测出它正在运行的系统类型的规范名。为此，它运行一个称为`config.guess` 的脚本，该脚本使用`uname`或者预定义的C预处理器符号来推断系统类型的规范名。

另外，用户可以通过给`configure`传递命令行参数而指定系统类型。在交叉编译时必须这样作。 在大多数交叉编译的复杂情况下，要涉及到三种系统类型。用于指定它们的选项是：



如果用户给`configure`一个非选项参数，如果用户没有显式地用选项指明，它就作为缺省情况表示主机类型、 目标类型和创建系统类型。如果给出了主机类型而没有给出目标类型和创建类型，目标类型和创建类型就被设置为主机类型。 如果你正在交叉编译，你仍然必须在`configure`的命令行中给出你使用的交叉工具（cross-tools）的名称， 特别是C编译器。例如，

```
CC=m68k-coff-gcc configure --target=m68k-coff
```

`configure`能够识别许多系统类型的短别名；例如，可以在命令行中给出`decstation'而不是`mips-dec-ultrix4.2'。`configure`运行一个被称为`config.sub`的脚本以使 系统类型别名规范化。

## [获取规范的系统类型](https://blog.csdn.net/a751532301/article/details/101142061#TOC69)

下列的宏使得`configure`脚本可以获得系统类型。它们运行shell脚本`config.guess`以确定 用户在命令行中没有给出的、它们需要的关于主机、目标和创建类型的所有值。它们运行`config.sub`对 用户给出的任何别名进行规范化。如果你使用这些宏，你必须把这两个shell脚本与你的源代码一同发布。关于 `AC_CONFIG_AUX_DIR`的信息，你可以通过该宏设置`configure`查找这些脚本的目录，请参见 [创建输出文件](https://blog.csdn.net/a751532301/article/details/101142061#SEC10)。如果你没有使用这些宏中的任意一个，`configure` 就忽略任何传递给它的`--host'、`--target'和`--build'选项。

 



 

 



 

 



 

## [系统类型变量](https://blog.csdn.net/a751532301/article/details/101142061#TOC70)

在调用了`AC_CANONICAL_SYSTEM`之后，下列输出变量包含了系统类型信息。在调用了`AC_CANONICAL_HOST` 之后，只设置了下列`host`变量。



## [使用系统类型](https://blog.csdn.net/a751532301/article/details/101142061#TOC71)

你将如何使用规范的系统类型？通常，你在``configure.in'`中的一个或多个`case`语句中使用它来 选择系统特定的C文件。而后把那些使用基于系统名的文件名的文件连接到诸如``host.h'`或``target.c'`的 普通的文件上。`case`语句模型允许使用shell通配符对多种情况进行编组，就像下面的片断：

```
case "$target" in
i386-*-mach* | i386-*-gnu*) obj_format=aout emulation=mach bfd_gas=yes ;;
i960-*-bout) obj_format=bout ;;
esac
```

 



 

你还可以使用主机系统类型以寻找交叉编译工具。关于完成该任务的宏`AC_CHECK_TOOL`的信息， 参见[对普通程序和文件的检查](https://blog.csdn.net/a751532301/article/details/101142061#SEC24)。

# [站点配置](https://blog.csdn.net/a751532301/article/details/101142061#TOC72)

`configure`脚本支持几种本地配置决策方式。它们是用户指明外部软件的位置，包括或除去可选的特征， 以修改过的名称安装的程序，以及为`configure`选项设置缺省值的手段。

## [与外部软件一起工作](https://blog.csdn.net/a751532301/article/details/101142061#TOC73)

有些软件包需要，或者可选地使用其它已经安装的软件包。用户可以把命令行选项传递给`configure` 以指明使用那个外部软件。选项采用下列形式之一：

```
--with-package[=arg]
--without-package
```

例如，`--with-gnu-ld'的意思是使用GNU连接器而不是任何其它连接器。`--with-x'的意思是 使用X Window系统。

用户可以给出包名加`='加参数的命令行参数。`no'是关于包的缺省参数；它表示*不*使用 包。既不是`yes'又不是`no'的参数将包含其它包的名字或者版本号，以便更精确地指定本程序可以 与之协同工作的包。如果没有给出参数，`--without-package'的缺省参数为`yes'。`--without-package'等价于`--with-package=no'。

`configure`脚本并不对它们不支持的`--with-package'选项发出警告。 本特征允许顶层目录中的`configure`脚本配置一个包含多个包的源代码树。 在包支持不同的选项的时候，不会因为给出了只有一部分包支持的选项而导致不必要的错误消息。 一个不幸的副作用是选项的拼写错误就不能被检查出来了。迄今为止还没有处理该问题的更好办法。

对于每个可能使用的外部软件包，``configure.in'`都应该调用`AC_ARG_WITH`以检测 `configure`的用户是否要求使用它。确定在缺省状态下，是使用还是不使用每个包，以及那个参数是合法的， 是你的任务。

 



 

 



 

## [选择包选项](https://blog.csdn.net/a751532301/article/details/101142061#TOC74)

如果软件包含有可选的编译时（compile-time）特征，用户就可以在调用`configure`时使用命令行选项来指明 是否编译它们。选项采用如下形式之一：

```
--enable-feature[=arg]
--disable-feature
```

这些选项允许用户选择可选的选项进行创建和安装。`--enable-feature'选项永远不要使特征的行为 变得不同或者导致一个特征代替另一个特征。它们只应该导致程序的一部分被创建而另一部分不创建。

用户可以通过在特征名之后添加`='和参数来给出参数。给出参数`no'表示 *不能*使用该特征。一个带有参数的特征看起来就像`--enable-debug=stabs'。如果没有给出参数， 它的缺省值就是`yes'。`--disable-feature'等价于`--enable-feature=no'。

`configure`脚本并不对它们所不支持的`--enable-feature'选项发出警告。 本特征允许顶层目录中的`configure`脚本配置一个包含多个包的源代码树。 在包支持不同的选项的时候，不会因为给出了只有一部分包支持的选项而导致不必要的错误消息。 一个不幸的副作用是选项的拼写错误就不能被检查出来了。迄今为止还没有处理该问题的更好办法。

对于每个可选的特征，``configure.in'`都应该调用`AC_ARG_ENABLE`以检测`configure` 的用户是否要求把该特征包含进来。确定在缺省情况下，每个特征是否被包含进来，以及那些选项是合法的，是你的任务。

 



 

 



 

## [配置站点细节](https://blog.csdn.net/a751532301/article/details/101142061#TOC75)

有些软件包需要复杂的与站点相关（site-specific）的信息。例如用于某种服务、公司名称和email联系地址的主名（host  names）。 因为有些配置脚本是通过Metaconfig方式交互地询问这些信息生成的，人们有时对于按非交互方式，  由Autoconf生成配置脚本如何获取这些信息感到困惑。

这些站点配置信息应该被储存在一个*仅仅由用户*，而不是程序，编辑的文件中。文件的位置既可以基于 `prefix`变量，也可以是一个标准的位置，比如说用户的home目录。它甚至可能通过一个环境变量给出。 程序应该在运行时，而不是在编译时，检查那个文件。运行时配置对于用户来说更为方便，并且使得配置过程比 在配置时获取这些信息要简单。关于存放数据文件的地点的详细信息，参见GNU编码标准中的 `为安装目录而提供的变量'。

## [在安装的时候改变程序的名称](https://blog.csdn.net/a751532301/article/details/101142061#TOC76)

Autoconf支持在安装程序的时候修改程序的名称。为了使用这些变换，``configure.in'`必须调用宏 `AC_ARG_PROGRAM`。

 



 

### [转换选项](https://blog.csdn.net/a751532301/article/details/101142061#TOC77)

你可以把下列命令行选项传递给`configure`以指定名称的转换：



### [转换的例子](https://blog.csdn.net/a751532301/article/details/101142061#TOC78)

这些变换对于作为交叉编译开发环境的一部分的程序是有用的。例如，用`--target=i960-vxworks'选项配置的 运行在Sun 4上的交叉汇编器通常以``i960-vxworks-as'`为名称进行安装，而不是以``as'`为名安装，该名称 将于原来的Sun 4汇编器混淆。

如果你不希望安装在你的系统上的GNU程序遮蔽具有相同名称的其它程序，你可以强行要求程序名以``g'`开头。 例如，如果你使用`--program-prefix=g'来配置GNU `diff`，那么在你运行`make install'的时候，它就安装到``/usr/local/bin/gdiff'`。

作为更复杂的例子，你可以使用

```
--program-transform-name='s/^/g/; s/^gg/g/; s/^gless/less/'
```

在源代码树中的大部分程序的名字之前附加`g'，已经含有一个`g'的程序，诸如`gdb`， 和不是GNU程序的程序，比如说`less`和`lesskey`，除外。（它假定你有一个包含了设置成使用 这些特征的程序的源代码树。）

同时安装某些程序的多个版本的一种方法是为其中一个程序的名称或为所有程序的名称附加版本号。例如，如果你还希望把 Autoconf版本1保留一段时间，你可以使用`--program-suffix=2'来配置Autoconf第2版，并且以名称 ``/usr/local/bin/autoconf2'`、``/usr/local/bin/autoheader2'`等等来安装程序。

### [转换的规则](https://blog.csdn.net/a751532301/article/details/101142061#TOC79)

下面是如何在``Makefile.in'`中使用变量`program_transform_name`：

```
transform=@program_transform_name@
install: all
        $(INSTALL_PROGRAM) myprog $(bindir)/`echo myprog|sed '$(transform)'`

uninstall:
        rm -f $(bindir)/`echo myprog|sed '$(transform)'`
```

如果你要安装多个程序，你可以通过一个循环来完成：

```
PROGRAMS=cp ls rm
install:
        for p in $(PROGRAMS); do \
          $(INSTALL_PROGRAM) $$p $(bindir)/`echo $$p|sed '$(transform)'`; \
        done

uninstall:
        for p in $(PROGRAMS); do \
          rm -f $(bindir)/`echo $$p|sed '$(transform)'`; \
        done
```

是否在文档文件中进行变换（Texinfo或者`man`）是个麻烦的问题；由于名称变换的几个原因，好像不存在完美的答案。 文档对于特定的结构来说并不特殊，并且Texinfo文件与系统文档并不冲突。但它们可能与同一文件的早期版本冲突，而且 `man`手册有时与系统文档冲突。作为一个折衷，可能最好是对`man`手册进行名称替换而不对Texinfo手册 进行替换。

## [设定站点缺省值](https://blog.csdn.net/a751532301/article/details/101142061#TOC80)

Autoconf生成的`configure`脚本允许你的站点（site）为某些配置值提供缺省值。你可以通过创建 站点范围（site-wide）或者系统范围（system-wide）的初始化文件来达到这个目的。

 如果设置了环境变量`CONFIG_SITE`，`configure`就把它的值作为读入的shell脚本的名称。 否则如果``prefix/share/config.site'`存在，它就读入该脚本， 否则如果``prefix/etc/config.site'`存在，它就读入该脚本。因此，如果出现冲突， 在机器特定文件中的设置将覆盖那些与机器独立的文件中的设置。

站点文件（site files）可以是任意shell脚本，但只能包含某种适于包含在其中的代码。因为`configure`在它读入所有 站点文件之后读取任何缓存文件，站点文件可以定义一个缺省的缓存文件以便在本系统中运行的所有Autoconf生成的 `configure`之间共享。如果你在站点文件中设置了缺省缓存文件，那么再在那个站点文件中设置输出变量 `CC`就是个好主意，这是因为缓存文件仅仅对特定的编译器来说是合法的，但许多系统还有好几个可用的编译器。

你可以在站点文件中检验或者覆盖由命令行选项设置的值；与选项对应的shell变量的名称与选项的名字的唯一区别是选项名中所有 的破折号应变换成的下划线。选项`--without-'和`--disable-'是个例外，出现它们就如同出现对应的`--with-'或者`--enable-'并且把值设置为`no'。因此，`--cache-file=localcache'把变量`cache_file`的值设置为`localcache'；`--enable-warnings=no'或者`--disable-warnings'把变量`enable_warnings` 的值设置为`no'；`--prefix=/usr'把变量`prefix`设置为`/usr'；等等。

如果你需要为其它输出变量设置与缺省值不同的值（你通常不得不在命令行中重复地进行设置），比如说`CFLAGS`， 站点文件就是进行这种设置的好地方。如果你为prefix或者exec_prefix设置了非缺省值 （你放置站点文件的地方），如果你用环境变量`CONFIG_SITE`给出了站点文件，你就可以在站点文件中设置 这些非缺省值。

你可以在站点文件中设置一些缓存值。如果你正在进行交叉编译，这样做就是有用的，以避免对需要运行测试程序的特征 进行检查。你可以为``prefix/etc/config.site'`中的系统正确地设置这些值来“预备缓存（prime cache）”。 为了找到你要设置的缓存变量名，可以在受到影响的`configure`脚本中寻找带有`_cv_'的shell变量， 也可以在Autoconf `m4`源代码中寻找这些宏。

缓存文件将十分谨慎而不至于覆盖任何在站点文件中设置的变量。类似地，你不应该在站点文件中覆盖命令行选项。 你的代码应该在修改诸如`prefix`和`cache_file`的变量之前，检查它们的缺省值（就是在 靠近`configure`开头的地方设置的值）。

下面是一个例子文件``/usr/share/local/gnu/share/config.site'`。 （如果没有把`CONFIG_SITE`设置成其它文件，）命令`configure --prefix=/usr/share/local/gnu'将读入该文件。

```
# config.site for configure
#
# Change some defaults.
test "$prefix" = NONE && prefix=/usr/share/local/gnu
test "$exec_prefix" = NONE && exec_prefix=/usr/local/gnu
test "$sharedstatedir" = '${prefix}/com' && sharedstatedir=/var
test "$localstatedir" = '${prefix}/var' && localstatedir=/var
#
# Give Autoconf 2.x generated configure scripts a shared default
# cache file for feature test results, architecture-specific.
if test "$cache_file" = ./config.cache; then
  cache_file="$prefix/var/config.cache"
  # A cache file is only valid for one C compiler.
  CC=gcc
fi
```

# [运行`configure`脚本](https://blog.csdn.net/a751532301/article/details/101142061#TOC81)

下面是关于如何配置使用`configure`脚本的软件包的说明，适用于包中的``INSTALL'`文件。 你可能要使用的普通文本的``INSTALL'`与Autoconf一同发行。

# [重新创建一个配置](https://blog.csdn.net/a751532301/article/details/101142061#TOC82)

`configure`脚本创建一个名为``config.status'`的文件，用它描述在包最后一次进行配置时 给出的配置选项。该文件是一个shell脚本文件，如果运行它，将重新创建相同的配置。

你可以用`--recheck'选项调用``config.status'`以更新它自身。如果你修改了`configure`， 该选项是有用的，这是因为某些测试的结果可能会与上一次运行的结果不同。选项`--recheck'以与从前使用的参数 相同的参数，再加上`--no-create'选项以防止`configure`运行``config.status'`并创建 ``Makefile'`和其它文件，再加上`--no-recursion'选项以防止`configure`在子目录中运行 其它的`configure`，来重新运行`configure`。（这样做是让其它的``Makefile'`规则可以在 ``config.status'`改变时运行它；关于一个例子，参见[自动地重新创建](https://blog.csdn.net/a751532301/article/details/101142061#SEC14)）。

``config.status'`还接受选项`--help'，它打印``config.status'`接受的选项的概述。 还接受选项`--version'，它打印用于创建生成``config.status'`的`configure`脚本的 Autoconf的版本号。

``config.status'`检查几个能够改变它的行为的可选的环境变量：

 



 

 



 

以下的变量为分开发布的包提供了一种共享由`configure`计算的结果的方式。如果某些包需要它们中某个包， 可能是一个通用库，所需要的特征的超集那么这样做就是有用的。这些变量允许一个``config.status'`文件创建 由它的``configure.in'`所指明的文件之外的文件，因此它就可以被用于不同的包。

 



 

 



 

这些变量还允许你编写只重新生成一部分文件的``Makefile'`规则。例如，在上面给出的依赖性之中 （参见[自动地重新创建](https://blog.csdn.net/a751532301/article/details/101142061#SEC14)），在``configure.in'`发生改变时， ``config.status'`将运行两次。如果你对此感到厌烦，你可以使得每次运行都仅仅重新生成关于 那条规则的文件。

```
config.h: stamp-h
stamp-h: config.h.in config.status
        CONFIG_FILES= CONFIG_HEADERS=config.h ./config.status
        echo > stamp-h

Makefile: Makefile.in config.status
        CONFIG_FILES=Makefile CONFIG_HEADERS= ./config.status
```

（如果``configure.in'`并不调用`AC_CONFIG_HEADER`，就不必在`make`规则中设置 `CONFIG_HEADERS`。）

# [关于Autoconf的问题](https://blog.csdn.net/a751532301/article/details/101142061#TOC83)

有时我们会遇到几个关于Autoconf的问题。下面是被提及的一些问题。

## [发布`configure`脚本](https://blog.csdn.net/a751532301/article/details/101142061#TOC84)

```
对发行由Autoconf生成的configure有什么限制？它们是如何影响我那些使用它们的程序的？
```

关于由Autoconf生成的配置脚本是如何发行和如何被使用的，并没有限制。在Autoconf第1版中，它们是服从GNU通用公共许可证的。 我们仍然鼓励软件的作者按照诸如GPL的条款发行他们的作品，但Autoconf并不要求这样做。

关于可能由`configure`使用的其它文件，``config.h.in'`服从你为你的``configure.in'`而使用的 任何版权规定，这是因为它是从那个文件和公有文件``acconfig.h'`中派生出来的。当``config.sub'`和 ``config.guess'`被用于由Autoconf生成的、允许你按照与你的软件包其它部分相同的条款发布的`configure` 脚本中时，它们就是GPL的一个例外。``install-sh'`是来自于X Consortium并且是没有版权的。

## [为什么需要使用GNU `m4`?](https://blog.csdn.net/a751532301/article/details/101142061#TOC85)

```
为什么Autoconf需要使用GNU m4？
```

许多`m4`的实现含有编码性（hard-coded）的，对宏的大小和数量的限制，Autoconf超过了这些限制。 它们还缺少一些内置宏，没有它们，诸如Autoconf之类的复杂应用程序将难以应付，它们包括：

```
builtin
indir
patsubst
__file__
__line__
```

因为只有软件维护者需要使用Autoconf，并且因为GNU `m4`易于配置和安装，需要安装GNU `m4` 好像是合理的。许多GNU和其它自由软件的维护者，因为他们更喜爱GNU工具，都已经安装了大部分GNU工具。

## [我如何解开死结?](https://blog.csdn.net/a751532301/article/details/101142061#TOC86)

```
如果Autoconf需要GNU m4并且GNU m4还有一个Autoconf configure脚本，
我如何解开这个死结？它好像是一个类似于鸡和蛋的问题！
```

这实际上是一种误解。虽然GNU `m4`带有一个由Autoconf生成的`configure`脚本，但在运行脚本 及安装GNU `m4`的时候并不需要安装Autoconf。只有在你需要修改`m4`的`configure` 脚本的时候，这只是少数几个人（主要是它的维护者）必须去作的事，才需要Autoconf。

## [为什么不使用Imake?](https://blog.csdn.net/a751532301/article/details/101142061#TOC87)

```
为什么不用Imake来代替configure脚本？
```

有些人已经提出了这个问题，所以在改编之后，我把给他们的解释写在这里。

下面是对Richard Pixley的问题的回答：

由Autoconf生成的脚本经常地在它以前从未设置过的机器上工作。这就是说，它善于推断新系统的配置。而Imake不能做到。

Imake使用含有主机特定数据的通用数据库。对X11来说，这种方法具有意义是因为发布版本是由一个控制整个 数据库的总管机关管理的一组工具组成的。

GNU工具并不按这种方式发行。每个GNU工具都有一个维护者；这些维护者散布在世界各地。使用统一的数据库将使维护变成噩梦。 Autoconf可能成为这类数据库，但实际上它没有。不是列举主机的依赖性，它列举的是程序的需求。

如果你把GNU套件看作一组本地工具，那么问题就很相似了。但GNU开发工具可以作为交叉工具（cross tools）而在几乎  所有主机+目标机的组合中进行配置。所有的这些配置都可以同时（concurrency）安装。它们甚至可以被配置成可以在不同主机上共享  与主机独立的信息的形式。Imake不能处理这些问题。

Imake模板是标准的一种形式。GNU编码标准在没有强加相同的限制的情况下，解决了相同的问题。

下面是一些由Per Bothner撰写的进一步的解释：

Imake的一个长处是它易于通过使用`cpp`的`#include'和宏机制生成大的Makefile。 然而，`cpp`是不可编程的：它含有有限的条件工具，而不含有循环。而且`cpp`不能检查它的环境。

所有这些问题可以通过使用`sh`而不是`cpp`来解决。shell是完全可编程的、含有宏替换、可以执行 （或者编制）其它的shell脚本，并且可以检查它的环境。

Paul Eggert更详细地阐述：

使用Autoconf，安装者不必假定Imake自身已经被安装并且正常地工作了。这对于习惯使用Imake的人们来说，看起来不是  突出的长处。但在许多主机上，并没有安装Imake或者缺省的安装不能很好地工作，为此，要求安装Imake就阻碍了在这些主机  上使用由Imake配置的软件包。例如，Imake模板和配置文件可能不能适当地安装在一个主机上，或者Imake创建过程可能  会错误地假定所有的源代码文件都在一个大目录树中，或者Imake配置可能使用某个编译器而包或者安装器需要使用另一个编译器，  或者包需要的Imake的版本号与系统支持的版本号不匹配。这些问题在Autoconf中很少出现，这是因为包附带属于它自己的 独立配置处理器。

还有，Imake通常会在`make`和安装者的C预处理器之间遇到难以预期的影响。这里的基本问题是，C预处理器 是为处理C程序而不是``Makefile'`而设计的。这对Autoconf来说问题小得多，它使用通用目的预处理器`m4`， 并且包的作者（而不是安装者）以标准的方式进行预处理。

最后，Mark Eichin解释道：

Imake还不是完全可扩展的。为了把新特征添加到Imake中，你需要提供你自己的项目模板，并且复制已经存在的特征的主要部分。  这意味着对于复杂的项目来说，使用由买主提供的（vendor-provided）Imake模板不能提供任何平衡作用--这是因为它们不包括  你自己的项目的任何东西（除非它是一个X11程序）。

但是，另一方面：

一个Imake胜过`configure`的长处是： ``Imakefile'`总是趋向于比``Makefile.in'`简短（同样地，冗余较少）。 但是，这儿有一个修正的方法--至少对于Kerberos V5树来说，我们已经在整个树中进行了修改以调用通用的 ``post.in'`和``pre.in'` ``Makefile'`片断。 这意味着大部分通用的东西，即使它们通常是在`configure`中设置的，也不必复制。

# [从版本1中升级](https://blog.csdn.net/a751532301/article/details/101142061#TOC88)

Autoconf第2版基本上与第1版是向后兼容的。但是，它给出了作某些事的更好方法，并且不再支持版本1中一些丑陋的东西。 因此，根据你的``configure.in'`文件的复杂性，你可能必须作一些手工的工作以升级到版本2。本章指出了一些在 升级的时候需要注意的问题。还有，可能你的`configure`脚本可以从版本2中的新特征中获得一些好处； 在Autoconf发布包中的``NEWS'`文件概括了改变的部分。

首先，确认你安装了1.1版或者更高版本的GNU `m4`，最好是1.3版或者更高版本。在1.1版之前的版本含有bug 以至于它不能与Autoconf版本2一同工作。版本1.3及其后的版本比早期的版本更快一些，这是因为1.3版的GNU `m4` 对转换（diversions）进行了更有效的实现并且能够在可以快速读回的文件中冻结（freeze）它的内部状态。

## [改变了的文件名](https://blog.csdn.net/a751532301/article/details/101142061#TOC89)

如果你随Autoconf一起安装了``aclocal.m4'`（相对于特定软件包的源代码目录中的``aclocal.m4'`）， 你必须把它重命名为``acsite.m4'`。 参见[用`autoconf`创建`configure`](https://blog.csdn.net/a751532301/article/details/101142061#SEC6)。

如果你与你的软件包一同发布``install.sh'`，就把它重命名为``install-sh'`以便`make`的内置 规则不会无意地从该文件创建一个称为``install'`的文件。`AC_PROG_INSTALL`将寻找这两个名字的脚本， 但最好使用新名字。

如果你使用``config.h.top'`或者``config.h.bot'`，你仍然可以使用它们，但如果你把它们混合到 ``acconfig.h'`之中，将减少你的麻烦。 参见[用`autoheader`创建``config.h.in'`](https://blog.csdn.net/a751532301/article/details/101142061#SEC17)。

## [改变了的Makefile](https://blog.csdn.net/a751532301/article/details/101142061#TOC90)

在你的``Makefile.in'`文件中添加`@CFLAGS@'、`@CPPFLAGS@'和`@LDFLAGS@'， 以便它们可以在`configure`运行的时候利用环境中的这些变量的值。这样做不是必须的，但对用户来说比较方便。

对于`AC_OUTPUT`的每个非``Makefile'`的输入文件，你还应该添加一条含有`@configure_input@'的注释， 以便输出文件将会包含一条注释以说明它们是由`configure`生成的。 自动地为每种人们在`AC_OUTPUT`中输出的文件选择正确的注释语法需要做太多的工作。

把``config.log'`和``config.cache'`添加到你要在`distclean`目标中删除的文件的列表中。

如果你的``Makefile.in'`如下：

```
prefix = /usr/local
exec_prefix = ${prefix}
```

你必须把它修改成：

```
prefix = @prefix@
exec_prefix = @exec_prefix@
```

不使用`@'字符的老式的对这些变量的替换行为已经被删除了。

## [改变了的宏](https://blog.csdn.net/a751532301/article/details/101142061#TOC91)

在Autoconf第2版中，重新命名了许多宏。你仍然可以使用旧名字，但新名字更清晰，并且易于找到相关文档。 关于为旧宏名提供新宏名的列表，参见[陈旧的宏名](https://blog.csdn.net/a751532301/article/details/101142061#SEC101)。 用`autoupdate`程序转换你的``configure.in'`以使用新的宏名。 参见[用`autoupdate`更新`configure`](https://blog.csdn.net/a751532301/article/details/101142061#SEC92)。

有些宏已经被能够更好地完成工作的类似宏所代替，但在调用上并不兼容。 如果你在运行`autoconf`时受到了关于调用过时宏的警告，你可以安全地忽略它们，但如果你按照打印的建议 替换过时的宏，你的`configure`脚本通常可以工作的更好。特别地，报告测试结果的机制已经改变了。 如果你使用了`echo`或者`AC_VERBOSE`（可能是通过`AC_COMPILE_CHECK`）， 如果你改用`AC_MSG_CHECKING`和`AC_MSG_RESULT`，你的`configure`脚本的输出将 更加美观。参见[打印消息](https://blog.csdn.net/a751532301/article/details/101142061#SEC58)。这些宏能够更好地与缓存变量协同工作。 参见[缓存结果](https://blog.csdn.net/a751532301/article/details/101142061#SEC55)。

## [用`autoupdate`更新`configure`](https://blog.csdn.net/a751532301/article/details/101142061#TOC92)

程序`autoupdate`把使用Autoconf旧宏名的``configure.in'`文件更新为使用当前宏名的文件。 在Autoconf第2版中，大部分宏被重命名以使用一个更统一、更具有描述性的命名机制。关于对新的命名机制的描述， 参见[宏名](https://blog.csdn.net/a751532301/article/details/101142061#SEC61)。虽然旧宏名仍然可以工作（关于旧宏名和对应的新宏名的列表， 参见[陈旧的宏名](https://blog.csdn.net/a751532301/article/details/101142061#SEC101)），如果你更新它们以使用新的宏名，你可以使你的 ``configure.in'`文件更加可读并且易于使用当前的Autoconf文档。

 如果没有给出参数，`autoupdate`就更新``configure.in'`，并且通过添加后缀``~'` （或者在设置了环境变量`SIMPLE_BACKUP_SUFFIX`的时候，使用该环境变量的值）以备份原始版本。 如果你带参数调用`autoupdate`，它就读入那个文件而不是读入``configure.in'`，并且把 更新的文件输出到标准输出。

`autoupdate`接受下列选项：



## [改变了的结果](https://blog.csdn.net/a751532301/article/details/101142061#TOC93)

如果你通过检验shell变量`DEFS`来检验以前测试的结果，你需要把这些检验替换为对那些测试的缓存变量的检查。 在`configure`运行的时候，`DEFS`不再存在；它仅仅在生成输出文件的时候才被创建。这种与第1版 的不同是因为正确地对变量实行引用（quoting）实在太麻烦而且在每次调用`AC_DEFINE`都要实行引用是低效的。 参见[缓存变量名](https://blog.csdn.net/a751532301/article/details/101142061#SEC56)。

例如，下面是为Autoconf第1版编写的``configure.in'`的片断：

```
AC_HAVE_FUNCS(syslog)
case "$DEFS" in
*-DHAVE_SYSLOG*) ;;
*) # syslog is not in the default libraries.  See if it's in some other.
  saved_LIBS="$LIBS"
  for lib in bsd socket inet; do
    AC_CHECKING(for syslog in -l$lib)
    LIBS="$saved_LIBS -l$lib"
    AC_HAVE_FUNCS(syslog)
    case "$DEFS" in
    *-DHAVE_SYSLOG*) break ;;
    *) ;;
    esac
    LIBS="$saved_LIBS"
  done ;;
esac
```

这里是为版本2编写的方式：

```
AC_CHECK_FUNCS(syslog)
if test $ac_cv_func_syslog = no; then
  # syslog is not in the default libraries.  See if it's in some other.
  for lib in bsd socket inet; do
    AC_CHECK_LIB($lib, syslog, [AC_DEFINE(HAVE_SYSLOG)
      LIBS="$LIBS $lib"; break])
  done
fi
```

如果你通过在引号的后边添加反斜线以处理`AC_DEFINE_UNQUOTED`中的bug，你需要删除它们。 它现在以可以预期的方式工作，并且不需要特别地处理引号（处理反斜线）。 参见[设定输出变量](https://blog.csdn.net/a751532301/article/details/101142061#SEC54)。

所有由Autoconf宏设置的布尔shell变量现在用`yes'来表示真值。虽然为了向后兼容，有些宏使用空字符串 表示假，大部分宏使用`no'来表示假。如果你依赖于shell变量用诸如1或者`t'来表示真， 你就需要改变你的测试。

## [改变了的宏的编写](https://blog.csdn.net/a751532301/article/details/101142061#TOC94)

在定义你自己的宏时，你现在应该使用`AC_DEFUN`而不是`define`。 `AC_DEFUN`自动调用`AC_PROVIDE`并且确保通过`AC_REQUIRE`调用该宏 不会被其他宏所打断，从而防止在屏幕上出现嵌套的`checking...'消息。继续按照老办法行事没有实际上的伤害， 但它缺乏便利和吸引力。参见[宏定义](https://blog.csdn.net/a751532301/article/details/101142061#SEC60)。

你可能把与Autoconf一同发行的宏作为如何解决问题的指南。看看它们的新版本将是一个好主意，因为风格已经有些改进并且 它们利用了一些新的特征。

如果你利用未公开的（undocumented）Autoconf内部元素（宏、变量、变换（diversions））作了微妙的工作，就要检查 你是否需要修改些什么以适应已经发生的变化。可能你甚至能够用版本2中公开（officially）支持的技术来代替你的拼装（kludging）。  但也可能不能。

为了加快你自行编写的特征测试，为它们添加缓存。看看你所有的测试是否足够一般化，从而具有足够的用途以把它们 封装到你可以共享的宏中去。

# [Autoconf的历史](https://blog.csdn.net/a751532301/article/details/101142061#TOC95)

你可能会困惑，最初为什么要编写Autoconf？它是如何演变到今天的形式的？（为什么它看起来就像大猩猩的吐沫？） 如果你不困惑，那么本章就不包含对你有用的信息，你也可能会跳过它。如果你*困惑*，那就让它明白些...

## [起源（Genesis）](https://blog.csdn.net/a751532301/article/details/101142061#TOC96)

在1991年六月，我为自由软件基金会维护了许多GNU工具。由于它们被移植到更多的平台并且增加了更多的程序， 用户必须在``Makefile'`中选择的`-D'选项的数目（大约20个）变得难以承受。尤其是我-- 我不得不在许多不同的系统上对每个新的发布版本进行测试。所以我编写了一个简单的shell脚本为fileutils包猜测一些 正确的设置，并且把它作为fileutils 2.0的一部分进行发布。这个`configure`能够胜任工作，因此， 我在下个月中，手工对其进行了修改以用于其他几个GNU工具包，从而创建了相似的`configure`脚本。 Brian Berliner也修改了我的脚本以用与它的CVS修订控制系统。

那个夏天以后，我得知Richard Stallman和Richard Pixley正在开发用于GNU编译器工具的类似脚本；所以我对我的 `configure`进行了修改以支持它们的进化的界面：把名为``Makefile.in'`的文件当作模板； 添加`+srcdir'，作为许多选项的第一个选项；并创建``config.status'`文件。

## [出发（Exodus）](https://blog.csdn.net/a751532301/article/details/101142061#TOC97)

由于我从用户那里获得了反馈，我组合了许多改进，使用Emacs进行搜索和替换、剪切（cut）和粘贴（paste），在 每个脚本中进行类似的修改。随着我修改更多的GNU工具包以使用`configure`脚本，完全用手工更新它们 就不可能了。Rich Murphey，GNU图形工具的维护者，在给我发送的邮件中说`configure`脚本很好，并 问我是否有一个可以生成它们的工具可以发给他。没有，我想，但我将会有！所以我开始考虑如何生成它们。这样， 从手工编写`configure`脚本的苦力向功能强大而易于使用的Autoconf前进的旅程开始了。

Cygnus `configure`，它大约也在那个时候被开发，是表驱动的；这意味着用少量的大体上不可猜测  的特征来处理离散数量的系统类型（例如目标文件格式的细节）。Brian Fox为Bash开发的自动配置系统采用了类似  的方法。为了统一用法，我好像必须绝望地试图为每个操作系统的变种的特征维护一个及时更新的数据库。  更容易和更可靠的办法是不检查大多数特征--特别是在那些人们已经在本地深入地研究或者安装了买主提供的补丁 的杂合的系统。

我考虑到使用与Cygnus `configure`相似的结构，就是提供一个单独的`configure`脚本， 在运行时读入``configure.in'`的片断。但是我不想让每个包都发布所有的特征测试，所以我选择了使用 预处理器从每个``configure.in'`中创建不同的`configure`。这个方法还提供了更多的控制和便利。

我简要地察看了被Larry Wall、Harlan Stenn和Raphael Manfredi采用的Metaconfig包，但我为了几个原因而不采用它。 这种方式生成的`Configure`脚本是交互式的，我认为太不方便了；我不喜欢它测试某些特征的方式 （例如库函数）；我不知道它是否还有人维护，并且我所见到的`Configure`脚本在许多现代系统 （例如System V R4和NeXT）中都不能工作；设置在支持某个特征或者不支持该特征时所进行的动作也不是很方便； 我发现它难于学习；并且对于我的需要，它太大、太复杂了（我没有意识到Autoconf最终将变得多么大）。

我考虑过使用Perl来生成我的风格的`configure`脚本，但显然`m4`更加适合于简单的 文本替换工作：由于输出是隐含的，它的工作比较少。还有，每个人都已经拥有它了。（一开始，我并不依赖于 GNU对`m4`的扩展。）我在Maryland大学的一些朋友最近用一些程序，包括`tvtwm`， 制作了`m4`的前端，并且我也有兴趣试试一种新语言。

## [上路（Leviticus）](https://blog.csdn.net/a751532301/article/details/101142061#TOC98)

因为我的`configure`在没有与用户进行交互的条件下自动地确定了系统的能力，我决定把生成它们 的程序称作Autoconfig。但附加了版本号之后，这个名字对于老式的UNIX文件系统来说就太长了，所以我把它缩短 成Autoconf。

在1991年秋天，我召集了一群期望获得移植性的家伙（alpha测试者）以给我提供反馈从而使我可以压缩（encapsulate） 我用`m4`宏写的脚本并且继续添加特征、改进检查中采用的技术。测试者中的杰出人物有Pinard，他提出了 创建一个``autoconf'`来运行`m4`并且检查找不到的宏调用的想法；还有Richard Pixley，他建议通过 运行编译器而不是在文件系统中寻找引入文件和符号，以获得更精确的结果；还有Kerl  Berry，他使得Autoconf可以配置 Tex并且把宏索引添加到文档中；还有Ian Taylor，他增加了对创建C头文件的支持以代替在``Makefile'`中添加`-D'选项的方法，以便他可以把Autoconf用于他的UUCP包。alpha测试者愉快地、一次又一次地随着 Autoconf不同发布版本中的Autoconf名称和宏调用惯例的改变而调整他们的文件。他们都贡献了许多特定的检查、绝妙的 想法，以及对bug的修正。

## [发展（Numbers）](https://blog.csdn.net/a751532301/article/details/101142061#TOC99)

在1992年七月，在alpha测试之后一个月，我发布了Autoconf 1.0，并且修改了许多GNU包以使用它。我对它带来的正面  作用感到很吃惊。很多人，包括那些编写并不属于GNU工程的软件（例如TCL、FSP和Kerberos V5）的人们，开始使用它，  以至于我无法跟踪他们了。随着很多使用`configure`脚本的人报告他们所遇到的问题，Autoconf继续快速地得到改进，

Autoconf成为考验`m4`实现的酷刑般的测试。由于Autoconf定义的宏的长度，UNIX `m4`开始 失败（dump core），同时也发现了GNU `m4`中的一些bug。最终，我们意识到我们需要使用一些只有 GNU `m4`才提供的特征。特别的，4.3BSD `m4`含有一组增强了的内置宏；System V版本更好 一些，但仍然不能提供我们所需要的所有东西。

随着Autoconf得到人们越来越多的重视，对Autoconf进行了更多的开发（并且有了我不能预见的用途）。Karl Berry添加了  对X11的检查。david zuhn贡献了对C++的支持。Pinard使Autoconf能够诊断非法的参数。Jim Blandy勇敢地用它配置  了GNU Emacs，并且为某些未来的改进打下了基础。Roland McGrath用它配置了GNU C库，编写了`autoheader` 脚本以自动创建C头文件模板，并且为`configure`添加了一个`--verbose'选项。 Noah Friedman添加了`--macrodir'选项和环境变量`AC_MACRODIR`。（他还提出了术语 *autoconfiscate*，用来表示“调整软件包以使用Autoconf”。）Roland和Noah改进了`AC_DEFINE` 中的引用保护并且修正了许多bug，特别是在1993年二月到六月间我们对处理移植性问题感到厌倦的时候。

## [现状（Deuteronomy）](https://blog.csdn.net/a751532301/article/details/101142061#TOC100)

在积累了一个关于希望添加的主要特征的长长的列表，并且在几年之中各式各样的人们提供的补丁残留了古怪的效果之后。 在1994年四月，处理对Cygnus的支持时，我开始对Autoconf进行一次主要的修订。我添加了大部分Cygnus `configure` 有，而Autoconf缺少的特征，主要是在david zuhn和Ken Raeburn的帮助下改编Cygnus `configure`的 相关部分。这些特征包括对使用``config.sub'`、``config.guess'`、`--host'和`--target'的支持；创建对文件的连接；以及在子目录中运行`configure`脚本。 添加这些特征使得Ken可以放弃GNU `as`，Rob Savoye可以放弃DejaGNU，而改用Autoconf。

作为对其他人的要求的回应，我添加了更多的特征。许多人要求`configure`脚本能够  在不同的运行中共享检查的结果，这是因为它们实在太慢了（尤其是像Cygnus那样在配置一个大的源代码树的时候）。 Mike  Haertel建议增加与位置有关的初始化脚本。发布必须在MS-DOS中解包（unpack）的软件的人们要求 提供一种覆盖那些诸如``config.h.in'`那样的、含有两个点的文件名中的``.in'`扩展名的方法。 Jim Avera通过`AC_DEFINE`和`AC_SUBST`中的引用扩展了对程序的检测；他的洞察力带来 了重要的改进。Richard Stallman要求把编译器的输出送到``config.log'`中，而不是送到``/dev/null'`中， 以帮助人们调试Emacs `configure`脚本。

由于我对程序质量的不满，我进行了一些其他的修改。我减少了用于显示检查结果的消息的二义性，总是打印结果。  我识别宏的名字并且消除编码风格的不一致性。我添加了一些我所开发的附加工具以助于修改源代码包以使用Autoconf。  在Pinard的帮助下，我创建了不会在彼此的消息中导致冲突的宏。（这个特征暴露了他草率地修正的、GNU `m4` 中的一些性能瓶颈！）我重新组织了人们需要解决的问题的文档。并且我开始了一组测试（testsuite），这是因为 经验已经表明：在我们修改Autoconf的时候，它有明显的回归倾向。

一些alpha测试者再次给出了难以估量的反馈，特别是 Pinard、Jim Meyering、Karl Berry、Rob Savoye、Ken Raeburn和Mark Eichin。

最后，2.0版本准备好了。而且我们也很高兴。（我们又有闲暇时间了。我想。哇，很好。）

# [陈旧的宏名](https://blog.csdn.net/a751532301/article/details/101142061#TOC101)

在Autoconf的第2版，大部分宏被重新命名以使用更加统一和具有描述性的命名方案。下面是被重新命名了的宏的原来名字， 随后给出了这些宏现在的名字。虽然为了保持向后兼容，旧名字仍然能够被`autoconf`程序所接受，旧名字都 被看作过时的。关于新的命名方案，参见[宏名](https://blog.csdn.net/a751532301/article/details/101142061#SEC61)。



# [环境变量索引](https://blog.csdn.net/a751532301/article/details/101142061#TOC102)

这是一个按照字母顺序排序的，由Autoconf检查的环境变量的列表。

Jump to: [a](https://blog.csdn.net/a751532301/article/details/101142061#evindex_a) - [c](https://blog.csdn.net/a751532301/article/details/101142061#evindex_c) - [s](https://blog.csdn.net/a751532301/article/details/101142061#evindex_s)

 

## a

  [AC_MACRODIR](https://blog.csdn.net/a751532301/article/details/101142061#IDX1), [AC_MACRODIR](https://blog.csdn.net/a751532301/article/details/101142061#IDX2), [AC_MACRODIR](https://blog.csdn.net/a751532301/article/details/101142061#IDX3), [AC_MACRODIR](https://blog.csdn.net/a751532301/article/details/101142061#IDX4), [AC_MACRODIR](https://blog.csdn.net/a751532301/article/details/101142061#IDX66), [AC_MACRODIR](https://blog.csdn.net/a751532301/article/details/101142061#IDX505)  

## c

  [CONFIG_FILES](https://blog.csdn.net/a751532301/article/details/101142061#IDX501)   [CONFIG_HEADERS](https://blog.csdn.net/a751532301/article/details/101142061#IDX503)   [CONFIG_SHELL](https://blog.csdn.net/a751532301/article/details/101142061#IDX497)   [CONFIG_SITE](https://blog.csdn.net/a751532301/article/details/101142061#IDX495)   [CONFIG_STATUS](https://blog.csdn.net/a751532301/article/details/101142061#IDX499)  

## s

  [SIMPLE_BACKUP_SUFFIX](https://blog.csdn.net/a751532301/article/details/101142061#IDX504)  

 

# [输出变量索引](https://blog.csdn.net/a751532301/article/details/101142061#TOC103)

这是一个按照字母顺序排序的，Autoconf将在它所创建的文件（通常是一个或更多``Makefile'`） 中进行替换的变量的列表。关于这些是如何实现的，请参见[设定输出变量](https://blog.csdn.net/a751532301/article/details/101142061#SEC54)。

Jump to: [a](https://blog.csdn.net/a751532301/article/details/101142061#ovindex_a) - [b](https://blog.csdn.net/a751532301/article/details/101142061#ovindex_b) - [c](https://blog.csdn.net/a751532301/article/details/101142061#ovindex_c) - [d](https://blog.csdn.net/a751532301/article/details/101142061#ovindex_d) - [e](https://blog.csdn.net/a751532301/article/details/101142061#ovindex_e) - [f](https://blog.csdn.net/a751532301/article/details/101142061#ovindex_f) - [h](https://blog.csdn.net/a751532301/article/details/101142061#ovindex_h) - [i](https://blog.csdn.net/a751532301/article/details/101142061#ovindex_i) - [k](https://blog.csdn.net/a751532301/article/details/101142061#ovindex_k) - [l](https://blog.csdn.net/a751532301/article/details/101142061#ovindex_l) - [m](https://blog.csdn.net/a751532301/article/details/101142061#ovindex_m) - [n](https://blog.csdn.net/a751532301/article/details/101142061#ovindex_n) - [o](https://blog.csdn.net/a751532301/article/details/101142061#ovindex_o) - [p](https://blog.csdn.net/a751532301/article/details/101142061#ovindex_p) - [r](https://blog.csdn.net/a751532301/article/details/101142061#ovindex_r) - [s](https://blog.csdn.net/a751532301/article/details/101142061#ovindex_s) - [t](https://blog.csdn.net/a751532301/article/details/101142061#ovindex_t) - [x](https://blog.csdn.net/a751532301/article/details/101142061#ovindex_x) - [y](https://blog.csdn.net/a751532301/article/details/101142061#ovindex_y)

 

## a

  [ALLOCA](https://blog.csdn.net/a751532301/article/details/101142061#IDX156)   [AWK](https://blog.csdn.net/a751532301/article/details/101142061#IDX83)  

## b

  [bindir](https://blog.csdn.net/a751532301/article/details/101142061#IDX16)   [build](https://blog.csdn.net/a751532301/article/details/101142061#IDX467)   [build_alias](https://blog.csdn.net/a751532301/article/details/101142061#IDX470)   [build_cpu](https://blog.csdn.net/a751532301/article/details/101142061#IDX473)   [build_os](https://blog.csdn.net/a751532301/article/details/101142061#IDX479)   [build_vendor](https://blog.csdn.net/a751532301/article/details/101142061#IDX476)  

## c

  [CC](https://blog.csdn.net/a751532301/article/details/101142061#IDX86), [CC](https://blog.csdn.net/a751532301/article/details/101142061#IDX110), [CC](https://blog.csdn.net/a751532301/article/details/101142061#IDX380)   [CFLAGS](https://blog.csdn.net/a751532301/article/details/101142061#IDX50), [CFLAGS](https://blog.csdn.net/a751532301/article/details/101142061#IDX87)   [configure_input](https://blog.csdn.net/a751532301/article/details/101142061#IDX18)   [CPP](https://blog.csdn.net/a751532301/article/details/101142061#IDX93)   [CPPFLAGS](https://blog.csdn.net/a751532301/article/details/101142061#IDX52)   [CXX](https://blog.csdn.net/a751532301/article/details/101142061#IDX96)   [CXXCPP](https://blog.csdn.net/a751532301/article/details/101142061#IDX100)   [CXXFLAGS](https://blog.csdn.net/a751532301/article/details/101142061#IDX54), [CXXFLAGS](https://blog.csdn.net/a751532301/article/details/101142061#IDX97)  

## d

  [datadir](https://blog.csdn.net/a751532301/article/details/101142061#IDX20)   [DEFS](https://blog.csdn.net/a751532301/article/details/101142061#IDX58)  

## e

  [exec_prefix](https://blog.csdn.net/a751532301/article/details/101142061#IDX22)   [EXEEXT](https://blog.csdn.net/a751532301/article/details/101142061#IDX348)  

## f

  [F77](https://blog.csdn.net/a751532301/article/details/101142061#IDX103)   [FFLAGS](https://blog.csdn.net/a751532301/article/details/101142061#IDX56), [FFLAGS](https://blog.csdn.net/a751532301/article/details/101142061#IDX104)   [FLIBS](https://blog.csdn.net/a751532301/article/details/101142061#IDX343)  

## h

  [host](https://blog.csdn.net/a751532301/article/details/101142061#IDX468)   [host_alias](https://blog.csdn.net/a751532301/article/details/101142061#IDX471)   [host_cpu](https://blog.csdn.net/a751532301/article/details/101142061#IDX474)   [host_os](https://blog.csdn.net/a751532301/article/details/101142061#IDX480)   [host_vendor](https://blog.csdn.net/a751532301/article/details/101142061#IDX477)  

## i

  [includedir](https://blog.csdn.net/a751532301/article/details/101142061#IDX24)   [infodir](https://blog.csdn.net/a751532301/article/details/101142061#IDX26)   [INSTALL](https://blog.csdn.net/a751532301/article/details/101142061#IDX113)   [INSTALL_DATA](https://blog.csdn.net/a751532301/article/details/101142061#IDX115)   [INSTALL_PROGRAM](https://blog.csdn.net/a751532301/article/details/101142061#IDX114)   [INSTALL_SCRIPT](https://blog.csdn.net/a751532301/article/details/101142061#IDX116)  

## k

  [KMEM_GROUP](https://blog.csdn.net/a751532301/article/details/101142061#IDX175)  

## l

  [LDFLAGS](https://blog.csdn.net/a751532301/article/details/101142061#IDX60)   [LEX](https://blog.csdn.net/a751532301/article/details/101142061#IDX119)   [LEX_OUTPUT_ROOT](https://blog.csdn.net/a751532301/article/details/101142061#IDX80)   [LEXLIB](https://blog.csdn.net/a751532301/article/details/101142061#IDX120)   [libdir](https://blog.csdn.net/a751532301/article/details/101142061#IDX28)   [libexecdir](https://blog.csdn.net/a751532301/article/details/101142061#IDX30)   [LIBOBJS](https://blog.csdn.net/a751532301/article/details/101142061#IDX162), [LIBOBJS](https://blog.csdn.net/a751532301/article/details/101142061#IDX173), [LIBOBJS](https://blog.csdn.net/a751532301/article/details/101142061#IDX184), [LIBOBJS](https://blog.csdn.net/a751532301/article/details/101142061#IDX226), [LIBOBJS](https://blog.csdn.net/a751532301/article/details/101142061#IDX280)   [LIBS](https://blog.csdn.net/a751532301/article/details/101142061#IDX62), [LIBS](https://blog.csdn.net/a751532301/article/details/101142061#IDX388), [LIBS](https://blog.csdn.net/a751532301/article/details/101142061#IDX391)   [LN_S](https://blog.csdn.net/a751532301/article/details/101142061#IDX123)   [localstatedir](https://blog.csdn.net/a751532301/article/details/101142061#IDX32)  

## m

  [mandir](https://blog.csdn.net/a751532301/article/details/101142061#IDX34)  

## n

  [NEED_SETGID](https://blog.csdn.net/a751532301/article/details/101142061#IDX174)  

## o

  [OBJEXT](https://blog.csdn.net/a751532301/article/details/101142061#IDX351)   [oldincludedir](https://blog.csdn.net/a751532301/article/details/101142061#IDX36)  

## p

  [prefix](https://blog.csdn.net/a751532301/article/details/101142061#IDX38)   [program_transform_name](https://blog.csdn.net/a751532301/article/details/101142061#IDX494)  

## r

  [RANLIB](https://blog.csdn.net/a751532301/article/details/101142061#IDX126)  

## s

  [sbindir](https://blog.csdn.net/a751532301/article/details/101142061#IDX40)   [SET_MAKE](https://blog.csdn.net/a751532301/article/details/101142061#IDX14)   [sharedstatedir](https://blog.csdn.net/a751532301/article/details/101142061#IDX42)   [srcdir](https://blog.csdn.net/a751532301/article/details/101142061#IDX44)   [subdirs](https://blog.csdn.net/a751532301/article/details/101142061#IDX69)   [sysconfdir](https://blog.csdn.net/a751532301/article/details/101142061#IDX46)  

## t

  [target](https://blog.csdn.net/a751532301/article/details/101142061#IDX469)   [target_alias](https://blog.csdn.net/a751532301/article/details/101142061#IDX472)   [target_cpu](https://blog.csdn.net/a751532301/article/details/101142061#IDX475)   [target_os](https://blog.csdn.net/a751532301/article/details/101142061#IDX481)   [target_vendor](https://blog.csdn.net/a751532301/article/details/101142061#IDX478)   [top_srcdir](https://blog.csdn.net/a751532301/article/details/101142061#IDX48)  

## x

  [X_CFLAGS](https://blog.csdn.net/a751532301/article/details/101142061#IDX358)   [X_EXTRA_LIBS](https://blog.csdn.net/a751532301/article/details/101142061#IDX360)   [X_LIBS](https://blog.csdn.net/a751532301/article/details/101142061#IDX359)   [X_PRE_LIBS](https://blog.csdn.net/a751532301/article/details/101142061#IDX361)  

## y

  [YACC](https://blog.csdn.net/a751532301/article/details/101142061#IDX129)  

 

# [预处理器符号索引](https://blog.csdn.net/a751532301/article/details/101142061#TOC104)

这是一个按照字母顺序排序的，由Autoconf宏定义的C预处理符号的列表。为了与Autoconf协同工作，C源代码应该 在`#if`指令中使用这些名字。

Jump to: [_](https://blog.csdn.net/a751532301/article/details/101142061#cvindex__) - [c](https://blog.csdn.net/a751532301/article/details/101142061#cvindex_c) - [d](https://blog.csdn.net/a751532301/article/details/101142061#cvindex_d) - [f](https://blog.csdn.net/a751532301/article/details/101142061#cvindex_f) - [g](https://blog.csdn.net/a751532301/article/details/101142061#cvindex_g) - [h](https://blog.csdn.net/a751532301/article/details/101142061#cvindex_h) - [i](https://blog.csdn.net/a751532301/article/details/101142061#cvindex_i) - [l](https://blog.csdn.net/a751532301/article/details/101142061#cvindex_l) - [m](https://blog.csdn.net/a751532301/article/details/101142061#cvindex_m) - [n](https://blog.csdn.net/a751532301/article/details/101142061#cvindex_n) - [o](https://blog.csdn.net/a751532301/article/details/101142061#cvindex_o) - [p](https://blog.csdn.net/a751532301/article/details/101142061#cvindex_p) - [r](https://blog.csdn.net/a751532301/article/details/101142061#cvindex_r) - [s](https://blog.csdn.net/a751532301/article/details/101142061#cvindex_s) - [t](https://blog.csdn.net/a751532301/article/details/101142061#cvindex_t) - [u](https://blog.csdn.net/a751532301/article/details/101142061#cvindex_u) - [v](https://blog.csdn.net/a751532301/article/details/101142061#cvindex_v) - [w](https://blog.csdn.net/a751532301/article/details/101142061#cvindex_w) - [y](https://blog.csdn.net/a751532301/article/details/101142061#cvindex_y)

 

## _

  [__CHAR_UNSIGNED__](https://blog.csdn.net/a751532301/article/details/101142061#IDX326)   [_ALL_SOURCE](https://blog.csdn.net/a751532301/article/details/101142061#IDX372)   [_MINIX](https://blog.csdn.net/a751532301/article/details/101142061#IDX383)   [_POSIX_1_SOURCE](https://blog.csdn.net/a751532301/article/details/101142061#IDX385)   [_POSIX_SOURCE](https://blog.csdn.net/a751532301/article/details/101142061#IDX379), [_POSIX_SOURCE](https://blog.csdn.net/a751532301/article/details/101142061#IDX384)   [_POSIX_VERSION](https://blog.csdn.net/a751532301/article/details/101142061#IDX259)  

## c

  [C_ALLOCA](https://blog.csdn.net/a751532301/article/details/101142061#IDX154)   [CLOSEDIR_VOID](https://blog.csdn.net/a751532301/article/details/101142061#IDX159)   [const](https://blog.csdn.net/a751532301/article/details/101142061#IDX320)  

## d

  [DGUX](https://blog.csdn.net/a751532301/article/details/101142061#IDX166)   [DIRENT](https://blog.csdn.net/a751532301/article/details/101142061#IDX232)  

## f

  [F77_NO_MINUS_C_MINUS_O](https://blog.csdn.net/a751532301/article/details/101142061#IDX107)  

## g

  [GETGROUPS_T](https://blog.csdn.net/a751532301/article/details/101142061#IDX293)   [GETLODAVG_PRIVILEGED](https://blog.csdn.net/a751532301/article/details/101142061#IDX171)   [GETPGRP_VOID](https://blog.csdn.net/a751532301/article/details/101142061#IDX181)   [gid_t](https://blog.csdn.net/a751532301/article/details/101142061#IDX312)  

## h

  [HAVE_ALLOCA_H](https://blog.csdn.net/a751532301/article/details/101142061#IDX155)   [HAVE_CONFIG_H](https://blog.csdn.net/a751532301/article/details/101142061#IDX65)   [HAVE_DIRENT_H](https://blog.csdn.net/a751532301/article/details/101142061#IDX239)   [HAVE_DOPRNT](https://blog.csdn.net/a751532301/article/details/101142061#IDX215)   [HAVE_function](https://blog.csdn.net/a751532301/article/details/101142061#IDX223)   [HAVE_GETMNTENT](https://blog.csdn.net/a751532301/article/details/101142061#IDX178)   [HAVE_header](https://blog.csdn.net/a751532301/article/details/101142061#IDX267)   [HAVE_LONG_DOUBLE](https://blog.csdn.net/a751532301/article/details/101142061#IDX329)   [HAVE_LONG_FILE_NAMES](https://blog.csdn.net/a751532301/article/details/101142061#IDX366)   [HAVE_MMAP](https://blog.csdn.net/a751532301/article/details/101142061#IDX187)   [HAVE_NDIR_H](https://blog.csdn.net/a751532301/article/details/101142061#IDX240)   [HAVE_RESTARTABLE_SYSCALLS](https://blog.csdn.net/a751532301/article/details/101142061#IDX369)   [HAVE_ST_BLKSIZE](https://blog.csdn.net/a751532301/article/details/101142061#IDX276)   [HAVE_ST_BLOCKS](https://blog.csdn.net/a751532301/article/details/101142061#IDX279)   [HAVE_ST_RDEV](https://blog.csdn.net/a751532301/article/details/101142061#IDX283)   [HAVE_STRCOLL](https://blog.csdn.net/a751532301/article/details/101142061#IDX201)   [HAVE_STRFTIME](https://blog.csdn.net/a751532301/article/details/101142061#IDX204)   [HAVE_STRINGIZE](https://blog.csdn.net/a751532301/article/details/101142061#IDX332)   [HAVE_SYS_DIR_H](https://blog.csdn.net/a751532301/article/details/101142061#IDX241)   [HAVE_SYS_NDIR_H](https://blog.csdn.net/a751532301/article/details/101142061#IDX242)   [HAVE_SYS_WAIT_H](https://blog.csdn.net/a751532301/article/details/101142061#IDX252)   [HAVE_TM_ZONE](https://blog.csdn.net/a751532301/article/details/101142061#IDX289)   [HAVE_TZNAME](https://blog.csdn.net/a751532301/article/details/101142061#IDX290)   [HAVE_UNISTD_H](https://blog.csdn.net/a751532301/article/details/101142061#IDX258)   [HAVE_UTIME_NULL](https://blog.csdn.net/a751532301/article/details/101142061#IDX207)   [HAVE_VFORK_H](https://blog.csdn.net/a751532301/article/details/101142061#IDX210)   [HAVE_VPRINTF](https://blog.csdn.net/a751532301/article/details/101142061#IDX214)   [HAVE_WAIT3](https://blog.csdn.net/a751532301/article/details/101142061#IDX218)  

## i

  [inline](https://blog.csdn.net/a751532301/article/details/101142061#IDX323)   [INT_16_BITS](https://blog.csdn.net/a751532301/article/details/101142061#IDX337)  

## l

  [LONG_64_BITS](https://blog.csdn.net/a751532301/article/details/101142061#IDX340)  

## m

  [MAJOR_IN_MKDEV](https://blog.csdn.net/a751532301/article/details/101142061#IDX245)   [MAJOR_IN_SYSMACROS](https://blog.csdn.net/a751532301/article/details/101142061#IDX246)   [mode_t](https://blog.csdn.net/a751532301/article/details/101142061#IDX296)  

## n

  [NDIR](https://blog.csdn.net/a751532301/article/details/101142061#IDX235)   [NEED_MEMORY_H](https://blog.csdn.net/a751532301/article/details/101142061#IDX255)   [NEED_SETGID](https://blog.csdn.net/a751532301/article/details/101142061#IDX172)   [NLIST_NAME_UNION](https://blog.csdn.net/a751532301/article/details/101142061#IDX170)   [NLIST_STRUCT](https://blog.csdn.net/a751532301/article/details/101142061#IDX169)   [NO_MINUS_C_MINUS_O](https://blog.csdn.net/a751532301/article/details/101142061#IDX90)  

## o

  [off_t](https://blog.csdn.net/a751532301/article/details/101142061#IDX299)  

## p

  [pid_t](https://blog.csdn.net/a751532301/article/details/101142061#IDX302)  

## r

  [RETSIGTYPE](https://blog.csdn.net/a751532301/article/details/101142061#IDX305)  

## s

  [SELECT_TYPE_ARG1](https://blog.csdn.net/a751532301/article/details/101142061#IDX190)   [SELECT_TYPE_ARG234](https://blog.csdn.net/a751532301/article/details/101142061#IDX191)   [SELECT_TYPE_ARG5](https://blog.csdn.net/a751532301/article/details/101142061#IDX192)   [SETPGRP_VOID](https://blog.csdn.net/a751532301/article/details/101142061#IDX195)   [SETVBUF_REVERSED](https://blog.csdn.net/a751532301/article/details/101142061#IDX198)   [size_t](https://blog.csdn.net/a751532301/article/details/101142061#IDX308)   [STDC_HEADERS](https://blog.csdn.net/a751532301/article/details/101142061#IDX249)   [SVR4](https://blog.csdn.net/a751532301/article/details/101142061#IDX165)   [SYS_SIGLIST_DECLARED](https://blog.csdn.net/a751532301/article/details/101142061#IDX229)   [SYSDIR](https://blog.csdn.net/a751532301/article/details/101142061#IDX233)   [SYSNDIR](https://blog.csdn.net/a751532301/article/details/101142061#IDX234)  

## t

  [TIME_WITH_SYS_TIME](https://blog.csdn.net/a751532301/article/details/101142061#IDX273)   [TM_IN_SYS_TIME](https://blog.csdn.net/a751532301/article/details/101142061#IDX286)  

## u

  [uid_t](https://blog.csdn.net/a751532301/article/details/101142061#IDX311)   [UMAX](https://blog.csdn.net/a751532301/article/details/101142061#IDX167)   [UMAX4_3](https://blog.csdn.net/a751532301/article/details/101142061#IDX168)   [USG](https://blog.csdn.net/a751532301/article/details/101142061#IDX262)  

## v

  [vfork](https://blog.csdn.net/a751532301/article/details/101142061#IDX211)   [VOID_CLOSEDIR](https://blog.csdn.net/a751532301/article/details/101142061#IDX236)  

## w

  [WORDS_BIGENDIAN](https://blog.csdn.net/a751532301/article/details/101142061#IDX317)  

## y

  [YYTEXT_POINTER](https://blog.csdn.net/a751532301/article/details/101142061#IDX79)  

 

# [宏索引](https://blog.csdn.net/a751532301/article/details/101142061#TOC105)

这是按字母排序的Autoconf宏列表。为了使列表易于使用，宏以没有前缀`AC_'的形式列出。

Jump to: [a](https://blog.csdn.net/a751532301/article/details/101142061#maindex_a) - [b](https://blog.csdn.net/a751532301/article/details/101142061#maindex_b) - [c](https://blog.csdn.net/a751532301/article/details/101142061#maindex_c) - [d](https://blog.csdn.net/a751532301/article/details/101142061#maindex_d) - [e](https://blog.csdn.net/a751532301/article/details/101142061#maindex_e) - [f](https://blog.csdn.net/a751532301/article/details/101142061#maindex_f) - [g](https://blog.csdn.net/a751532301/article/details/101142061#maindex_g) - [h](https://blog.csdn.net/a751532301/article/details/101142061#maindex_h) - [i](https://blog.csdn.net/a751532301/article/details/101142061#maindex_i) - [l](https://blog.csdn.net/a751532301/article/details/101142061#maindex_l) - [m](https://blog.csdn.net/a751532301/article/details/101142061#maindex_m) - [o](https://blog.csdn.net/a751532301/article/details/101142061#maindex_o) - [p](https://blog.csdn.net/a751532301/article/details/101142061#maindex_p) - [r](https://blog.csdn.net/a751532301/article/details/101142061#maindex_r) - [s](https://blog.csdn.net/a751532301/article/details/101142061#maindex_s) - [t](https://blog.csdn.net/a751532301/article/details/101142061#maindex_t) - [u](https://blog.csdn.net/a751532301/article/details/101142061#maindex_u) - [v](https://blog.csdn.net/a751532301/article/details/101142061#maindex_v) - [w](https://blog.csdn.net/a751532301/article/details/101142061#maindex_w) - [x](https://blog.csdn.net/a751532301/article/details/101142061#maindex_x) - [y](https://blog.csdn.net/a751532301/article/details/101142061#maindex_y)

 

## a

  [AIX](https://blog.csdn.net/a751532301/article/details/101142061#IDX371)   [ALLOCA](https://blog.csdn.net/a751532301/article/details/101142061#IDX506)   [ARG_ARRAY](https://blog.csdn.net/a751532301/article/details/101142061#IDX507)   [ARG_ENABLE](https://blog.csdn.net/a751532301/article/details/101142061#IDX489)   [ARG_PROGRAM](https://blog.csdn.net/a751532301/article/details/101142061#IDX493)   [ARG_WITH](https://blog.csdn.net/a751532301/article/details/101142061#IDX485)  

## b

  [BEFORE](https://blog.csdn.net/a751532301/article/details/101142061#IDX458)  

## c

  [C_BIGENDIAN](https://blog.csdn.net/a751532301/article/details/101142061#IDX316)   [C_CHAR_UNSIGNED](https://blog.csdn.net/a751532301/article/details/101142061#IDX325)   [C_CONST](https://blog.csdn.net/a751532301/article/details/101142061#IDX319)   [C_CROSS](https://blog.csdn.net/a751532301/article/details/101142061#IDX411)   [C_INLINE](https://blog.csdn.net/a751532301/article/details/101142061#IDX322)   [C_LONG_DOUBLE](https://blog.csdn.net/a751532301/article/details/101142061#IDX328)   [C_STRINGIZE](https://blog.csdn.net/a751532301/article/details/101142061#IDX331)   [CACHE_CHECK](https://blog.csdn.net/a751532301/article/details/101142061#IDX435)   [CACHE_LOAD](https://blog.csdn.net/a751532301/article/details/101142061#IDX437)   [CACHE_SAVE](https://blog.csdn.net/a751532301/article/details/101142061#IDX439)   [CACHE_VAL](https://blog.csdn.net/a751532301/article/details/101142061#IDX433)   [CANONICAL_HOST](https://blog.csdn.net/a751532301/article/details/101142061#IDX464)   [CANONICAL_SYSTEM](https://blog.csdn.net/a751532301/article/details/101142061#IDX462)   [CHAR_UNSIGNED](https://blog.csdn.net/a751532301/article/details/101142061#IDX508)   [CHECK_FILE](https://blog.csdn.net/a751532301/article/details/101142061#IDX131)   [CHECK_FILES](https://blog.csdn.net/a751532301/article/details/101142061#IDX133)   [CHECK_FUNC](https://blog.csdn.net/a751532301/article/details/101142061#IDX220)   [CHECK_FUNCS](https://blog.csdn.net/a751532301/article/details/101142061#IDX222)   [CHECK_HEADER](https://blog.csdn.net/a751532301/article/details/101142061#IDX264)   [CHECK_HEADERS](https://blog.csdn.net/a751532301/article/details/101142061#IDX266)   [CHECK_LIB](https://blog.csdn.net/a751532301/article/details/101142061#IDX145)   [CHECK_PROG](https://blog.csdn.net/a751532301/article/details/101142061#IDX135)   [CHECK_PROGS](https://blog.csdn.net/a751532301/article/details/101142061#IDX137)   [CHECK_SIZEOF](https://blog.csdn.net/a751532301/article/details/101142061#IDX334)   [CHECK_TOOL](https://blog.csdn.net/a751532301/article/details/101142061#IDX139)   [CHECK_TYPE](https://blog.csdn.net/a751532301/article/details/101142061#IDX314)   [CHECKING](https://blog.csdn.net/a751532301/article/details/101142061#IDX449)   [COMPILE_CHECK](https://blog.csdn.net/a751532301/article/details/101142061#IDX407)   [CONFIG_AUX_DIR](https://blog.csdn.net/a751532301/article/details/101142061#IDX8)   [CONFIG_HEADER](https://blog.csdn.net/a751532301/article/details/101142061#IDX64)   [CONFIG_SUBDIRS](https://blog.csdn.net/a751532301/article/details/101142061#IDX68)   [CONST](https://blog.csdn.net/a751532301/article/details/101142061#IDX509)   [CROSS_CHECK](https://blog.csdn.net/a751532301/article/details/101142061#IDX510)   [CYGWIN](https://blog.csdn.net/a751532301/article/details/101142061#IDX345)  

## d

  [DECL_SYS_SIGLIST](https://blog.csdn.net/a751532301/article/details/101142061#IDX228)   [DECL_YYTEXT](https://blog.csdn.net/a751532301/article/details/101142061#IDX78)   [DEFINE](https://blog.csdn.net/a751532301/article/details/101142061#IDX425)   [DEFINE_UNQUOTED](https://blog.csdn.net/a751532301/article/details/101142061#IDX427)   [DEFUN](https://blog.csdn.net/a751532301/article/details/101142061#IDX452)   [DIR_HEADER](https://blog.csdn.net/a751532301/article/details/101142061#IDX231)   [DYNIX_SEQ](https://blog.csdn.net/a751532301/article/details/101142061#IDX374)  

## e

  [EGREP_CPP](https://blog.csdn.net/a751532301/article/details/101142061#IDX397)   [EGREP_HEADER](https://blog.csdn.net/a751532301/article/details/101142061#IDX395)   [ENABLE](https://blog.csdn.net/a751532301/article/details/101142061#IDX491)   [ERROR](https://blog.csdn.net/a751532301/article/details/101142061#IDX511)   [EXEEXT](https://blog.csdn.net/a751532301/article/details/101142061#IDX347)  

## f

  [F77_LIBRARY_LDFLAGS](https://blog.csdn.net/a751532301/article/details/101142061#IDX342)   [FIND_X](https://blog.csdn.net/a751532301/article/details/101142061#IDX512)   [FIND_XTRA](https://blog.csdn.net/a751532301/article/details/101142061#IDX513)   [FUNC_ALLOCA](https://blog.csdn.net/a751532301/article/details/101142061#IDX153)   [FUNC_CHECK](https://blog.csdn.net/a751532301/article/details/101142061#IDX514)   [FUNC_CLOSEDIR_VOID](https://blog.csdn.net/a751532301/article/details/101142061#IDX158)   [FUNC_FNMATCH](https://blog.csdn.net/a751532301/article/details/101142061#IDX161)   [FUNC_GETLOADAVG](https://blog.csdn.net/a751532301/article/details/101142061#IDX164)   [FUNC_GETMNTENT](https://blog.csdn.net/a751532301/article/details/101142061#IDX177)   [FUNC_GETPGRP](https://blog.csdn.net/a751532301/article/details/101142061#IDX180)   [FUNC_MEMCMP](https://blog.csdn.net/a751532301/article/details/101142061#IDX183)   [FUNC_MMAP](https://blog.csdn.net/a751532301/article/details/101142061#IDX186)   [FUNC_SELECT_ARGTYPES](https://blog.csdn.net/a751532301/article/details/101142061#IDX189)   [FUNC_SETPGRP](https://blog.csdn.net/a751532301/article/details/101142061#IDX194)   [FUNC_SETVBUF_REVERSED](https://blog.csdn.net/a751532301/article/details/101142061#IDX197)   [FUNC_STRCOLL](https://blog.csdn.net/a751532301/article/details/101142061#IDX200)   [FUNC_STRFTIME](https://blog.csdn.net/a751532301/article/details/101142061#IDX203)   [FUNC_UTIME_NULL](https://blog.csdn.net/a751532301/article/details/101142061#IDX206)   [FUNC_VFORK](https://blog.csdn.net/a751532301/article/details/101142061#IDX209)   [FUNC_VPRINTF](https://blog.csdn.net/a751532301/article/details/101142061#IDX213)   [FUNC_WAIT3](https://blog.csdn.net/a751532301/article/details/101142061#IDX217)  

## g

  [GCC_TRADITIONAL](https://blog.csdn.net/a751532301/article/details/101142061#IDX515)   [GETGROUPS_T](https://blog.csdn.net/a751532301/article/details/101142061#IDX516)   [GETLOADAVG](https://blog.csdn.net/a751532301/article/details/101142061#IDX517)  

## h

  [HAVE_FUNCS](https://blog.csdn.net/a751532301/article/details/101142061#IDX518)   [HAVE_HEADERS](https://blog.csdn.net/a751532301/article/details/101142061#IDX519)   [HAVE_LIBRARY](https://blog.csdn.net/a751532301/article/details/101142061#IDX147)   [HAVE_POUNDBANG](https://blog.csdn.net/a751532301/article/details/101142061#IDX520)   [HEADER_CHECK](https://blog.csdn.net/a751532301/article/details/101142061#IDX521)   [HEADER_DIRENT](https://blog.csdn.net/a751532301/article/details/101142061#IDX238)   [HEADER_EGREP](https://blog.csdn.net/a751532301/article/details/101142061#IDX522)   [HEADER_MAJOR](https://blog.csdn.net/a751532301/article/details/101142061#IDX244)   [HEADER_STAT](https://blog.csdn.net/a751532301/article/details/101142061#IDX269)   [HEADER_STDC](https://blog.csdn.net/a751532301/article/details/101142061#IDX248)   [HEADER_SYS_WAIT](https://blog.csdn.net/a751532301/article/details/101142061#IDX251)   [HEADER_TIME](https://blog.csdn.net/a751532301/article/details/101142061#IDX272)  

## i

  [INIT](https://blog.csdn.net/a751532301/article/details/101142061#IDX6)   [INLINE](https://blog.csdn.net/a751532301/article/details/101142061#IDX523)   [INT_16_BITS](https://blog.csdn.net/a751532301/article/details/101142061#IDX336)   [IRIX_SUN](https://blog.csdn.net/a751532301/article/details/101142061#IDX376)   [ISC_POSIX](https://blog.csdn.net/a751532301/article/details/101142061#IDX378)  

## l

  [LANG_C](https://blog.csdn.net/a751532301/article/details/101142061#IDX413)   [LANG_CPLUSPLUS](https://blog.csdn.net/a751532301/article/details/101142061#IDX415)   [LANG_FORTRAN77](https://blog.csdn.net/a751532301/article/details/101142061#IDX417)   [LANG_RESTORE](https://blog.csdn.net/a751532301/article/details/101142061#IDX421)   [LANG_SAVE](https://blog.csdn.net/a751532301/article/details/101142061#IDX419)   [LINK_FILES](https://blog.csdn.net/a751532301/article/details/101142061#IDX483)   [LN_S](https://blog.csdn.net/a751532301/article/details/101142061#IDX524)   [LONG_64_BITS](https://blog.csdn.net/a751532301/article/details/101142061#IDX339)   [LONG_DOUBLE](https://blog.csdn.net/a751532301/article/details/101142061#IDX525)   [LONG_FILE_NAMES](https://blog.csdn.net/a751532301/article/details/101142061#IDX526)  

## m

  [MAJOR_HEADER](https://blog.csdn.net/a751532301/article/details/101142061#IDX527)   [MEMORY_H](https://blog.csdn.net/a751532301/article/details/101142061#IDX254)   [MINGW32](https://blog.csdn.net/a751532301/article/details/101142061#IDX353)   [MINIX](https://blog.csdn.net/a751532301/article/details/101142061#IDX382)   [MINUS_C_MINUS_O](https://blog.csdn.net/a751532301/article/details/101142061#IDX528)   [MMAP](https://blog.csdn.net/a751532301/article/details/101142061#IDX529)   [MODE_T](https://blog.csdn.net/a751532301/article/details/101142061#IDX530)   [MSG_CHECKING](https://blog.csdn.net/a751532301/article/details/101142061#IDX441)   [MSG_ERROR](https://blog.csdn.net/a751532301/article/details/101142061#IDX445)   [MSG_RESULT](https://blog.csdn.net/a751532301/article/details/101142061#IDX443)   [MSG_WARN](https://blog.csdn.net/a751532301/article/details/101142061#IDX447)  

## o

  [OBJEXT](https://blog.csdn.net/a751532301/article/details/101142061#IDX350)   [OBSOLETE](https://blog.csdn.net/a751532301/article/details/101142061#IDX460)   [OFF_T](https://blog.csdn.net/a751532301/article/details/101142061#IDX531)   [OUTPUT](https://blog.csdn.net/a751532301/article/details/101142061#IDX10)  

## p

  [PATH_PROG](https://blog.csdn.net/a751532301/article/details/101142061#IDX141)   [PATH_PROGS](https://blog.csdn.net/a751532301/article/details/101142061#IDX143)   [PATH_X](https://blog.csdn.net/a751532301/article/details/101142061#IDX355)   [PATH_XTRA](https://blog.csdn.net/a751532301/article/details/101142061#IDX357)   [PID_T](https://blog.csdn.net/a751532301/article/details/101142061#IDX532)   [PREFIX](https://blog.csdn.net/a751532301/article/details/101142061#IDX533)   [PREFIX_PROGRAM](https://blog.csdn.net/a751532301/article/details/101142061#IDX72)   [PREREQ](https://blog.csdn.net/a751532301/article/details/101142061#IDX74)   [PROG_AWK](https://blog.csdn.net/a751532301/article/details/101142061#IDX82)   [PROG_CC](https://blog.csdn.net/a751532301/article/details/101142061#IDX85)   [PROG_CC_C_O](https://blog.csdn.net/a751532301/article/details/101142061#IDX89)   [PROG_CPP](https://blog.csdn.net/a751532301/article/details/101142061#IDX92)   [PROG_CXX](https://blog.csdn.net/a751532301/article/details/101142061#IDX95)   [PROG_CXXCPP](https://blog.csdn.net/a751532301/article/details/101142061#IDX99)   [PROG_F77_C_O](https://blog.csdn.net/a751532301/article/details/101142061#IDX106)   [PROG_FORTRAN](https://blog.csdn.net/a751532301/article/details/101142061#IDX102)   [PROG_GCC_TRADITIONAL](https://blog.csdn.net/a751532301/article/details/101142061#IDX109)   [PROG_INSTALL](https://blog.csdn.net/a751532301/article/details/101142061#IDX112)   [PROG_LEX](https://blog.csdn.net/a751532301/article/details/101142061#IDX118)   [PROG_LN_S](https://blog.csdn.net/a751532301/article/details/101142061#IDX122)   [PROG_MAKE_SET](https://blog.csdn.net/a751532301/article/details/101142061#IDX13)   [PROG_RANLIB](https://blog.csdn.net/a751532301/article/details/101142061#IDX125)   [PROG_YACC](https://blog.csdn.net/a751532301/article/details/101142061#IDX128)   [PROGRAM_CHECK](https://blog.csdn.net/a751532301/article/details/101142061#IDX536)   [PROGRAM_EGREP](https://blog.csdn.net/a751532301/article/details/101142061#IDX537)   [PROGRAM_PATH](https://blog.csdn.net/a751532301/article/details/101142061#IDX538)   [PROGRAMS_CHECK](https://blog.csdn.net/a751532301/article/details/101142061#IDX534)   [PROGRAMS_PATH](https://blog.csdn.net/a751532301/article/details/101142061#IDX535)   [PROVIDE](https://blog.csdn.net/a751532301/article/details/101142061#IDX456)  

## r

  [REMOTE_TAPE](https://blog.csdn.net/a751532301/article/details/101142061#IDX539)   [REPLACE_FUNCS](https://blog.csdn.net/a751532301/article/details/101142061#IDX225)   [REQUIRE](https://blog.csdn.net/a751532301/article/details/101142061#IDX454)   [REQUIRE_CPP](https://blog.csdn.net/a751532301/article/details/101142061#IDX423)   [RESTARTABLE_SYSCALLS](https://blog.csdn.net/a751532301/article/details/101142061#IDX540)   [RETSIGTYPE](https://blog.csdn.net/a751532301/article/details/101142061#IDX541)   [REVISION](https://blog.csdn.net/a751532301/article/details/101142061#IDX76)   [RSH](https://blog.csdn.net/a751532301/article/details/101142061#IDX542)  

## s

  [SCO_INTL](https://blog.csdn.net/a751532301/article/details/101142061#IDX387)   [SEARCH_LIBS](https://blog.csdn.net/a751532301/article/details/101142061#IDX149), [SEARCH_LIBS](https://blog.csdn.net/a751532301/article/details/101142061#IDX151)   [SET_MAKE](https://blog.csdn.net/a751532301/article/details/101142061#IDX544)   [SETVBUF_REVERSED](https://blog.csdn.net/a751532301/article/details/101142061#IDX543)   [SIZE_T](https://blog.csdn.net/a751532301/article/details/101142061#IDX546)   [SIZEOF_TYPE](https://blog.csdn.net/a751532301/article/details/101142061#IDX545)   [ST_BLKSIZE](https://blog.csdn.net/a751532301/article/details/101142061#IDX550)   [ST_BLOCKS](https://blog.csdn.net/a751532301/article/details/101142061#IDX551)   [ST_RDEV](https://blog.csdn.net/a751532301/article/details/101142061#IDX552)   [STAT_MACROS_BROKEN](https://blog.csdn.net/a751532301/article/details/101142061#IDX270), [STAT_MACROS_BROKEN](https://blog.csdn.net/a751532301/article/details/101142061#IDX547)   [STDC_HEADERS](https://blog.csdn.net/a751532301/article/details/101142061#IDX548)   [STRCOLL](https://blog.csdn.net/a751532301/article/details/101142061#IDX549)   [STRUCT_ST_BLKSIZE](https://blog.csdn.net/a751532301/article/details/101142061#IDX275)   [STRUCT_ST_BLOCKS](https://blog.csdn.net/a751532301/article/details/101142061#IDX278)   [STRUCT_ST_RDEV](https://blog.csdn.net/a751532301/article/details/101142061#IDX282)   [STRUCT_TIMEZONE](https://blog.csdn.net/a751532301/article/details/101142061#IDX288)   [STRUCT_TM](https://blog.csdn.net/a751532301/article/details/101142061#IDX285)   [SUBST](https://blog.csdn.net/a751532301/article/details/101142061#IDX429)   [SUBST_FILE](https://blog.csdn.net/a751532301/article/details/101142061#IDX431)   [SYS_INTERPRETER](https://blog.csdn.net/a751532301/article/details/101142061#IDX363)   [SYS_LONG_FILE_NAMES](https://blog.csdn.net/a751532301/article/details/101142061#IDX365)   [SYS_RESTARTABLE_SYSCALLS](https://blog.csdn.net/a751532301/article/details/101142061#IDX368)   [SYS_SIGLIST_DECLARED](https://blog.csdn.net/a751532301/article/details/101142061#IDX553)  

## t

  [TEST_CPP](https://blog.csdn.net/a751532301/article/details/101142061#IDX554)   [TEST_PROGRAM](https://blog.csdn.net/a751532301/article/details/101142061#IDX555)   [TIME_WITH_SYS_TIME](https://blog.csdn.net/a751532301/article/details/101142061#IDX557)   [TIMEZONE](https://blog.csdn.net/a751532301/article/details/101142061#IDX556)   [TRY_COMPILE](https://blog.csdn.net/a751532301/article/details/101142061#IDX399)   [TRY_CPP](https://blog.csdn.net/a751532301/article/details/101142061#IDX393)   [TRY_LINK](https://blog.csdn.net/a751532301/article/details/101142061#IDX401)   [TRY_LINK_FUNC](https://blog.csdn.net/a751532301/article/details/101142061#IDX403), [TRY_LINK_FUNC](https://blog.csdn.net/a751532301/article/details/101142061#IDX405)   [TRY_RUN](https://blog.csdn.net/a751532301/article/details/101142061#IDX409)   [TYPE_GETGROUPS](https://blog.csdn.net/a751532301/article/details/101142061#IDX292)   [TYPE_MODE_T](https://blog.csdn.net/a751532301/article/details/101142061#IDX295)   [TYPE_OFF_T](https://blog.csdn.net/a751532301/article/details/101142061#IDX298)   [TYPE_PID_T](https://blog.csdn.net/a751532301/article/details/101142061#IDX301)   [TYPE_SIGNAL](https://blog.csdn.net/a751532301/article/details/101142061#IDX304)   [TYPE_SIZE_T](https://blog.csdn.net/a751532301/article/details/101142061#IDX307)   [TYPE_UID_T](https://blog.csdn.net/a751532301/article/details/101142061#IDX310)  

## u

  [UID_T](https://blog.csdn.net/a751532301/article/details/101142061#IDX558)   [UNISTD_H](https://blog.csdn.net/a751532301/article/details/101142061#IDX257)   [USG](https://blog.csdn.net/a751532301/article/details/101142061#IDX261)   [UTIME_NULL](https://blog.csdn.net/a751532301/article/details/101142061#IDX559)  

## v

  [VALIDATE_CACHED_SYSTEM_TUPLE](https://blog.csdn.net/a751532301/article/details/101142061#IDX466)   [VERBOSE](https://blog.csdn.net/a751532301/article/details/101142061#IDX451)   [VFORK](https://blog.csdn.net/a751532301/article/details/101142061#IDX560)   [VPRINTF](https://blog.csdn.net/a751532301/article/details/101142061#IDX561)  

## w

  [WAIT3](https://blog.csdn.net/a751532301/article/details/101142061#IDX562)   [WARN](https://blog.csdn.net/a751532301/article/details/101142061#IDX563)   [WITH](https://blog.csdn.net/a751532301/article/details/101142061#IDX487)   [WORDS_BIGENDIAN](https://blog.csdn.net/a751532301/article/details/101142061#IDX564)  

## x

  [XENIX_DIR](https://blog.csdn.net/a751532301/article/details/101142061#IDX390)  

## y

  [YYTEXT_POINTER](https://blog.csdn.net/a751532301/article/details/101142061#IDX565)  

 

 