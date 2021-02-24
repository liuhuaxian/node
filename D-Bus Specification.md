# D-Bus Specification

## Type System 

### *wire format*   *marshaling*    *unmarshaling* 

D-Bus有一个类型系统，在这个系统中，各种类型的值可以序列化为一个字节序列，以标准的方式称为wire format

 将值从其他表示形式转换为连接格式称为封送处理***marshaling***，而将其从连接格式转换回来称为反封送处理***unmarshaling*** 。 

###  *type  signature* 

 D-Bus协议不包括封送数据中的类型标记;一组封送值必须具有已知的 **type  signature** 。**类型签名**由零个或多个**完整类型**组成，每个**完整类型**由一个或多个**类型代码**组成 

 **类型代码**是表示值类型的ASCII字符。 因为使用了ASCII字符，所以类型签名将始终形成有效的ASCII字符串。 一个简单的字符串比较确定两个类型签名是否等效。 

 一个**完整的类型**是一个类型代码序列，它完全描述了一种类型:要么是一个基本类型，要么是一个完整描述的容器类型。一个完整的类型是一个基本类型代码、一个变体类型代码、一个带有它的元素类型的数组，或者一个带有它的字段的结构(所有这些都在下面定义)。因此，以下签名不是单一的完整类型 

```c
        "aa"
        "(ii" 
        "ii)" 
```

 并且以下签名包含多个完整类型： 

```c
        "ii" 
        "aiai"
        "(ii)(ii)"
```

 但是请注意，单个完整类型可以通过包含struct或dict条目来包含多个其他单个完整类型。 

### Basic types

#### **fixed types **

 最简单的类型代码是**基本类型**，这些类型的结构完全由其1个字符的类型代码定义。**基本类型由固定类型和类字符串的类型组成**。 

 **固定类型**是其值具有**固定长度的基本类型**，即BYTE，BOOLEAN，DOUBLE，UNIX_FD以及长度为16、32或64位的有符号或无符号整数。 

作为一个简单的例子，32位整数(INT32)的类型代码是ASCII字符“i”。因此，包含单个INT32的值块的签名是           "i"

 一个包含两个INT32的值的块会有这个签名 "ii"

 表中列出了固定类型的特征。 

| Conventional name | ASCII type-code | Encoding                                                     |
| ----------------- | --------------- | ------------------------------------------------------------ |
| `BYTE`            | `y` (121)       | Unsigned 8-bit integer                                       |
| `BOOLEAN`         | `b` (98)        | Boolean value: 0 is false, 1 is true, any other value allowed by the marshalling format is invalid |
| `INT16`           | `n` (110)       | Signed (two's complement) 16-bit integer                     |
| `UINT16`          | `q` (113)       | Unsigned 16-bit integer                                      |
| `INT32`           | `i` (105)       | Signed (two's complement) 32-bit integer                     |
| `UINT32`          | `u` (117)       | Unsigned 32-bit integer                                      |
| `INT64`           | `x` (120)       | Signed (two's complement) 64-bit integer    (mnemonic: x and t are the first characters in "sixty" not  already used for something more common) |
| `UINT64`          | `t` (116)       | Unsigned 64-bit integer                                      |
| `DOUBLE`          | `d` (100)       | IEEE 754 double-precision floating point                     |
| `UNIX_FD`         | `h` (104)       | Unsigned 32-bit integer representing an index into an   out-of-band array of file descriptors, transferred via some  platform-specific mechanism (mnemonic: h for handle) |

####  *string-like types*  

 **类字符串类型**是具有可变长度的基本类型。任何类似字符串类型的值在概念上都是0或更多的用UTF-8编码的Unicode代码点，其中没有一个可能是U+0000。必须严格验证UTF-8文本:特别是，它不能包含超过U+10FFFF的超长序列或代码点。 

由于D-Bus规范版本0.21，按照Unicode勘误表#9，“非字符”U+FDD0..在UTF-8字符串中允许U+FDEF、U+nFFFE和U+nFFFF(但是请注意，D-Bus的旧版本拒绝了这些非字符)。 

类字符串类型的封送格式都以一个零字节(NUL)结束，但该字节不被认为是文本的一部分。 

表中列出了类字符串类型的特征。 

| Conventional name | ASCII type-code | Validity constraints                                         |
| ----------------- | --------------- | ------------------------------------------------------------ |
| `STRING`          | `s` (115)       | No extra constraints                                         |
| `OBJECT_PATH`     | `o` (111)       | Must be  [asyntactically valid object path](https://dbus.freedesktop.org/doc/dbus-specification.html#message-protocol-marshaling-object-path) |
| `SIGNATURE`       | `g` (103)       | Zero or more *[single complete types](https://dbus.freedesktop.org/doc/dbus-specification.html#term-single-complete-type)* |

##### Valid Object Paths

`OBJECT_PATH`是用于引用对象实例的名称。从概念上讲，D-Bus消息交换中的每个参与者可以拥有任意数量的对象实例(考虑c++或Java对象)，并且每个这样的实例都有一个路径。与文件系统一样，应用程序中的对象实例形成层次树。 

 对象路径通常以颠倒的域名开头并包含接口版本号来命名，这与 [interface names](https://dbus.freedesktop.org/doc/dbus-specification.html#message-protocol-names-interface) 和 [well-known bus](https://dbus.freedesktop.org/doc/dbus-specification.html#message-protocol-names-bus) 相同。这使得在同一进程中实现多个服务或一个服务的多个版本成为可能，即使这些服务共享一个连接但不能以其他方式协作(例如，如果它们是由不同的插件实现的)。   

 允许使用/的对象路径，但建议不要使用/，因为它会使接口的版本控制变得困难。  D-Bus对象发出的任何信号都具有与之关联的服务的唯一总线名称，而不是其众所周知的名称。 这意味着信号的接收者必须完全依靠信号名称和对象路径来确定信号源自哪个接口。 

例如，如果example.com的所有者正在为音乐播放器开发D-Bus API，那么他们可能会为其对象使用以/com/example/MusicPlayer1开头的对象路径层次结构。 

下面的规则定义了一个有效的对象路径 

-  路径的长度可以是任意的。 
-  该路径必须以ASCII '/'(整数47)字符开头，并且必须由由斜杠字符分隔的元素组成。           
- 每个元素只能包含ASCII字符“ [A-Z] [a-z] [0-9] _”     
-  任何元素都不能是空字符串。         
-  多个'/'字符不能顺序出现。            
-  除非路径是根路径（单个“ /”字符），否则不允许尾随“ /”字符。          

##### Valid Signatures

 有效签名将符合以下规则 :

-  签名是单个完整类型的列表。数组必须有元素类型，结构体必须有开括号和闭括号。            
-  签名中仅允许输入类型代码，打开和关闭括号以及打开和关闭大括号。 签名中不允许使用STRUCT类型代码，因为使用括号代替。 同样，签名中不允许使用DICT_ENTRY类型代码，因为使用大括号代替。           
-  容器类型嵌套的最大深度为32个数组类型代码和32个开放括号。 这意味着对于“存在...的struct的结构...的struct的数组...的结构的数组的数组”，最大递归总深度为64，其中存在32个array和32个struct。 
-  签名的最大长度是255。              

当签名出现在消息中时，封送格式必须保证后面会跟一个nul字节(可以解释为c风格的字符串终止或无效的类型代码)，但这在概念上不是签名的一部分。 

### Container types

 除了基本类型外，还有四种容器类型：STRUCT，ARRAY，VARIANT和DICT_ENTRY。 

#### `STRUCT`

STRUCT具有类型代码，ASCII字符“ r”，但是此类型代码不会出现在签名中。 而是使用ASCII字符'（'和'）'来标记结构的开始和结束。 因此，例如，包含两个整数的结构将具有以下签名： "(ii)"

可以嵌套结构，例如，一个包含整数和另一个结构的结构："(i(ii))"

 存储该结构的值块将包含三个整数。 类型签名可将“（i（ii））”与“（（ii）i）”或“（iii）”或“ iii”区分开。 

 STRUCT类型代码“ r”当前未在D-Bus协议中使用，但在实现该协议的代码中很有用。 指定此类型代码是为了允许此类代码在非协议上下文中进行互操作。 

 不允许使用空结构； 括号之间必须至少有一个类型代码。 

####  `ARRAY` 

 数组的ASCII字符“a”作为类型代码。数组类型代码后面必须跟着一个完整的类型。数组后面的单个完整类型是每个数组元素的类型。简单的例子是 "ai"

 这是一个32位整数的数组。 但是一个数组可以是任何类型，例如 array-of-struct-with-two-int32-fields ：**"a(ii)"** 

 或此整数数组的数组： "aai"

####  `VARIANT`  

 VARIANT具有ASCII字符“ v”作为其类型代码。 类型为VARIANT的封送值将具有单个完整类型的签名作为值的一部分。 该签名后将带有该类型的封送处理的值。 

 与消息签名不同，变量签名只能包含一个完整的类型。所以“i”，“ai”或者“(ii)”是可以的，但是“ii”就不行。变量的使用可能不会导致总消息深度大于64，包括其他容器类型(如结构)。 

####  `DICT_ENTRY`  

 DICT_ENTRY的工作原理与结构体完全相同，但是它使用花括号而不是括号，并且具有更多的限制。 限制是：它仅作为数组元素类型出现；  花括号内有两个完全完整的类型； 第一个单个完整类型（“键”）必须是基本类型，而不是容器类型。  实现不得接受数组外部的dict条目，不得接受具有零个，一个或两个以上字段的dict条目，并且不得接受具有非基本类型键的dict条目。  字典条目始终是键值对。 

 DICT_ENTRY中的第一个字段始终是关键。 如果同一密钥在同一DICT_ENTRY数组中出现两次，则认为该消息已损坏。 但是，出于性能原因，不需要实现拒绝具有重复键的命令。 

 在大多数语言中，字典条目数组将表示为映射，哈希表或字典对象。 

### Summary of types

| Category           | Conventional Name | Code                                                         | Description                                                  |
| ------------------ | ----------------- | ------------------------------------------------------------ | ------------------------------------------------------------ |
| reserved           | `INVALID`         | 0 (ASCII NUL)                                                | Not a valid type code, used to terminate signatures          |
| fixed, basic       | `BYTE`            | 121 (ASCII 'y')                                              | 8-bit unsigned integer                                       |
| fixed, basic       | `BOOLEAN`         | 98 (ASCII 'b')                                               | Boolean value, 0 is `FALSE` and 1 is `TRUE`. Everything else is invalid. |
| fixed, basic       | `INT16`           | 110 (ASCII 'n')                                              | 16-bit signed integer                                        |
| fixed, basic       | `UINT16`          | 113 (ASCII 'q')                                              | 16-bit unsigned integer                                      |
| fixed, basic       | `INT32`           | 105 (ASCII 'i')                                              | 32-bit signed integer                                        |
| fixed, basic       | `UINT32`          | 117 (ASCII 'u')                                              | 32-bit unsigned integer                                      |
| fixed, basic       | `INT64`           | 120 (ASCII 'x')                                              | 64-bit signed integer                                        |
| fixed, basic       | `UINT64`          | 116 (ASCII 't')                                              | 64-bit unsigned integer                                      |
| fixed, basic       | `DOUBLE`          | 100 (ASCII 'd')                                              | IEEE 754 double                                              |
| string-like, basic | `STRING`          | 115 (ASCII 's')                                              | UTF-8 string (*must* be valid UTF-8). Must be nul terminated and contain no other nul bytes. |
| string-like, basic | `OBJECT_PATH`     | 111 (ASCII 'o')                                              | Name of an object instance                                   |
| string-like, basic | `SIGNATURE`       | 103 (ASCII 'g')                                              | A type signature                                             |
| container          | `ARRAY`           | 97 (ASCII 'a')                                               | Array                                                        |
| container          | `STRUCT`          | 114 (ASCII 'r'), 40 (ASCII '('), 41 (ASCII ')')              | Struct; type code 114 'r' is reserved for use in                  bindings and implementations to represent the general                  concept of a struct, and must not appear in signatures                  used on D-Bus. |
| container          | `VARIANT`         | 118 (ASCII 'v')                                              | Variant type (the type of the value is part of the value itself) |
| container          | `DICT_ENTRY`      | 101 (ASCII 'e'), 123 (ASCII '{'), 125 (ASCII '}')            | Entry in a dict or map (array of key-value pairs).                  Type code 101 'e' is reserved for use in bindings and                  implementations to represent the general concept of a                  dict or dict-entry, and must not appear in signatures                  used on D-Bus. |
| fixed, basic       | `UNIX_FD`         | 104 (ASCII 'h')                                              | Unix file descriptor                                         |
| reserved           | (reserved)        | 109 (ASCII 'm')                                              | Reserved for [a 'maybe' type compatible with the one in GVariant](https://bugs.freedesktop.org/show_bug.cgi?id=27857), and must not appear in signatures used on D-Bus until specified here |
| reserved           | (reserved)        | 42 (ASCII '*')                                               | Reserved for use in bindings/implementations to                  represent any *single complete type*,and must not appear in signatures used on D-Bus. |
| reserved           | (reserved)        | 63 (ASCII '?')                                               | Reserved for use in bindings/implementations to                  represent any *basic type*, and must not appear in signatures used on D-Bus. |
| reserved           | (reserved)        | 64 (ASCII '@'), 38 (ASCII '&'),                  94 (ASCII '^') | Reserved for internal use by bindings/implementations,                  and must not appear in signatures used on D-Bus.                  GVariant uses these type-codes to encode calling                  conventions. |

## Marshaling (Wire Format)

 D-Bus为其类型系统定义了编组格式，该格式在D-Bus消息中使用。 这不是类型系统的唯一可能的编组格式：例如，GVariant（GLib的一部分）重新使用了D-Bus类型系统，但实现了另一种编组格式。 

### Byte order and alignment

 在给定类型签名，一个字节块可以转换为类型化的值。 本节描述字节块的格式。 对于所有D-Bus类型，均会统一处理字节顺序和对齐问题。 

 字节块具有关联的字节顺序。 必须以某种方式发现字节顺序。 对于D-Bus消息，字节顺序是消息头的一部分，如“消息格式”部分所述。 现在，假设已知字节顺序为小端或大端。 

 字节块中的每个值都“自然地”对齐，例如4字节值与4字节边界对齐，而8字节值与8字节边界对齐。 相对于消息中的第一个字节，边界是全局计算的。  要正确对齐一个值，可能需要在该值之前添加对齐填充。 对齐填充必须始终是最小填充以正确对齐以下值； 并且必须始终由nul个字节组成。  对齐填充必须保持未初始化状态（不能包含垃圾），并且不得使用超出要求的填充。 

 作为自然对齐方式的一个例外，STRUCT和DICT_ENTRY值始终与8字节边界对齐，而不考虑其内容的对齐方式。 

### Marshalling basic types

 要封送和取消封送固定类型，您只需从数据块中读取与签名中每种类型代码相对应的一个值。 所有带符号的整数值都以二进制补码编码，DOUBLE值是IEEE 754双精度浮点数，而BOOLEAN值则以32位编码（其中仅使用最低有效位）。 

 类似字符串的类型（STRING，OBJECT_PATH和SIGNATURE）都被整理为固定长度的无符号整数n，给出变量部分的长度，其后是n个非零字节的UTF-8文本，后跟一个零（nul） 不视为文本一部分的字节。 字符串类型的对齐方式与n的对齐方式相同：n所需的任何填充都在n本身之前出现。  在n和字符串文本之间，或在字符串文本和尾随nul之间，永远不会有任何对齐填充。 消息中的下一个值（如果有）的对齐填充在尾随nul之后开始。 

 对于STRING和OBJECT_PATH类型，n编码为4个字节（一个UINT32），导致4字节对齐。 对于SIGNATURE类型，n被编码为一个字节（UINT8）。 结果，在签名之前永远不需要对齐填充。 

 例如，如果当前位置是从little-endian消息开始的8字节的倍数，则字符串'foo'，'+'和'bar'将按以下顺序进行序列化： 

以下表示字串"foo+bar"

```bash
                                          no padding required, we are already at a multiple of 4
0x03 0x00 0x00 0x00                       length of ‘foo’ = 3
                    0x66 0x6f 0x6f        ‘foo’
                                   0x00   trailing nul

                                          no padding required, we are already at a multiple of 4
0x01 0x00 0x00 0x00                       length of ‘+’ = 1
                    0x2b                  ‘+’
                         0x00             trailing nul

                               0x00 0x00  2 bytes of padding to reach next multiple of 4
0x03 0x00 0x00 0x00                       length of ‘bar’ = 3
                    0x62 0x61 0x72        ‘bar’
                                    0x00  trailing nul
```

### Marshalling containers

 数组以UINT32 n的形式编组，以字节为单位给出数组数据的长度，然后将对齐填充填充到数组元素类型的对齐边界，然后依次排列n个字节的数组元素。  n不包括长度后的填充或最后一个元素后的任何填充。 即n应该可以被数组中元素的数量整除。 

 例如，如果消息中的当前位置是8字节的倍数，而字节顺序是大端字节数，那么只包含64位整数5的数组将被编组为: 

```
00 00 00 08               n = 8 bytes of data
00 00 00 00               padding to 8-byte boundary
00 00 00 00  00 00 00 05  first element = 5
```

 数组的最大长度定义为2的26次方或67108864 (64 MiB)。实现不能发送或接受超过这个长度的数组。 

 struct和dict条目的编组方式与它们的内容相同，但它们的对齐方式始终是8字节边界，即使它们的内容通常不是严格对齐的。 

 变量被编组为内容的签名（必须是单个完整类型），后跟具有该签名给定类型的编组值。 变量与签名具有相同的1字节对齐方式，这意味着永远不需要在变量之前进行对齐填充。 使用变量不得导致总消息深度大于64，包括其他容器类型（例如结构）。  （请参阅有效签名。） 

### Summary of D-Bus marshalling

| Conventional Name | Encoding                                                     | Alignment                      |
| ----------------- | ------------------------------------------------------------ | ------------------------------ |
| `INVALID`         | Not applicable; cannot be marshaled.                         | N/A                            |
| `BYTE`            | A single 8-bit byte.                                         | 1                              |
| `BOOLEAN`         | As for `UINT32`, but only 0 and 1 are valid values.          | 4                              |
| `INT16`           | 16-bit signed integer in the message's byte order.           | 2                              |
| `UINT16`          | 16-bit unsigned integer in the message's byte order.         | 2                              |
| `INT32`           | 32-bit signed integer in the message's byte order.           | 4                              |
| `UINT32`          | 32-bit unsigned integer in the message's byte order.         | 4                              |
| `INT64`           | 64-bit signed integer in the message's byte order.           | 8                              |
| `UINT64`          | 64-bit unsigned integer in the message's byte order.         | 8                              |
| `DOUBLE`          | 64-bit IEEE 754 double in the message's byte order.          | 8                              |
| `STRING`          | A `UINT32` indicating the string's                  length in bytes excluding its terminating nul, followed by                  non-nul string data of the given length, followed by a terminating nul                  byte. | 4 (for the length)             |
| `OBJECT_PATH`     | Exactly the same as `STRING` except the                  content must be a valid object path (see above). | 4 (for the length)             |
| `SIGNATURE`       | The same as `STRING` except the length is a single                  byte (thus signatures have a maximum length of 255)                  and the content must be a valid signature (see above). | 1                              |
| `ARRAY`           | A `UINT32` giving the length of the array data in bytes, followed by                  alignment padding to the alignment boundary of the array element type,                  followed by each array element. | 4 (for the length)             |
| `STRUCT`          | A struct must start on an 8-byte boundary regardless of the                  type of the struct fields. The struct value consists of each                  field marshaled in sequence starting from that 8-byte                  alignment boundary. | 8                              |
| `VARIANT`         | The marshaled `SIGNATURE` of a single                  complete type, followed by a marshaled value with the type                  given in the signature. | 1 (alignment of the signature) |
| `DICT_ENTRY`      | Identical to STRUCT.                                         | 8                              |
| `UNIX_FD`         | 32-bit unsigned integer in the message's byte                order. The actual file descriptors need to be                transferred out-of-band via some platform specific                mechanism. On the wire, values of this type store the index to the                file descriptor in the array of file descriptors that                accompany the message. |                                |

## Message Protocol

 消息由标题和正文组成。 如果您将消息视为包，则标题是地址，正文包含包的内容。 消息传递系统使用标头信息来确定将消息发送到何处以及如何解释消息； 收件人解释 消息体。 

 消息的主体由零个或多个参数组成，这些参数是类型化的值，例如整数或字节数组。 

 头和正文都使用D-Bus类型系统和数据序列化格式。 

### Message Format

 消息由标题和正文组成。 标头是具有固定签名和含义的值的块。 主体是一个单独的值块，在标题中指定了签名。 

 标头的长度必须是8的倍数，以便在将整个消息存储在单个缓冲区中时允许主体从8字节边界开始。 如果标题不是自然地在8字节边界上结束，则必须添加最多7个字节的nul初始化对齐填充。 

 消息体不需要在8字节边界上结束 。

 消息的最大长度（包括标题，标题对齐填充和正文）为2到27的幂或134217728（128 MiB）。 

 标头的签名为： "yyyyuua(yv)"

 写出来更容易读，这是: 

```
BYTE, BYTE, BYTE, BYTE, UINT32, UINT32, ARRAY of STRUCT of (BYTE,VARIANT)
```

 这些值有以下含义 ：

| Value                                     | Description                                                  |
| ----------------------------------------- | ------------------------------------------------------------ |
| 1st `BYTE`                                | 字节序标志；  little-endian的ASCII'l'或big-endian的ASCII'B'。 标头和正文都按照此字节序排序。 |
| 2nd `BYTE`                                | 消息类型。未知类型必须被忽略。下面描述当前定义的类型         |
| 3rd `BYTE`                                | 按位或的标志。 未知标志必须被忽略。 当前定义的标志描述如下   |
| 4th `BYTE`                                | 发送应用程序的主要协议版本。 如果接收应用程序的主协议版本不匹配，则应用程序将无法通信，并且必须断开D-Bus连接。 该规范版本的主要协议版本为1。 |
| 1st `UINT32`                              | 消息体的长度(以字节为单位)，从消息头的末尾开始。标题在对齐填充到8边界后结束。 |
| 2nd `UINT32`                              | 此消息的序列号，由发送方用作cookie，以标识与此请求相对应的答复。 不能为零。 |
| `ARRAY` of `STRUCT` of (`BYTE`,`VARIANT`) | 零个或多个标头字段的数组，其中字节是域代码，而变量是字段值。 消息类型确定哪些字段是必需的。 |

 可以在标头的第二个字节中出现的消息类型是： 

| Conventional name | Decimal value | Description                                             |
| ----------------- | ------------- | ------------------------------------------------------- |
| `INVALID`         | 0             | This is an invalid type.                                |
| `METHOD_CALL`     | 1             | 方法调用。 此消息类型可能会提示您答复。                 |
| `METHOD_RETURN`   | 2             | 方法应答与返回的数据。                                  |
| `ERROR`           | 3             | 错误回复。 如果第一个参数存在且为字符串，则为错误消息。 |
| `SIGNAL`          | 4             | Signal emission.                                        |

 可以出现在头的第三个字节中的标志 

| Conventional name                 | Hex value | Description                                                  |
| --------------------------------- | --------- | ------------------------------------------------------------ |
| `NO_REPLY_EXPECTED`               | 0x1       | 此消息不希望方法返回答复或错误答复，即使它是可以答复的类型也是如此。 答复应省略。   <br />请注意，METHOD_CALL是此规范中当前定义的唯一可以期待答复的消息类型，因此，在当前记录的其他三种消息类型中是否存在此标志是没有意义的：不应发送对这些消息类型的答复， 此标志是否存在。 |
| `NO_AUTO_START`                   | 0x2       | 总线不能启动目标名称的所有者来响应此消息                     |
| `ALLOW_INTERACTIVE_AUTHORIZATION` | 0x4       | 可以在方法调用消息上设置此标志，以通知接收方调用者已准备好等待交互式授权，这可能需要花费大量时间才能完成。 例如，如果设置了此标志，则可以通过Polkit或类似框架向用户查询密码或确认密码。<br />仅当非特权代码调用特权更大的方法调用并且部署了允许进行交互式授权的授权框架时，此标志才有用。 如果没有部署这样的框架，它将没有效果。  客户端实现默认不应设置此标志。 如果已设置，则调用方还应在方法调用上设置适当的长时间超时，以确保用户交互可以完成。  该标志仅对方法调用消息有效，否则将被忽略。<br />作为调用方法效果的一部分而发生的交互作用超出了此标志的范围，即使该交互作用也可以称为身份验证或授权。  例如，在引导网络管理服务尝试连接到虚拟专用网络的方法调用中，此标志应控制网络管理服务如何做出“是否允许该用户更改系统网络配置？”的决定。  不应影响网络管理服务如何与用户交互或是否与用户交互以获取访问VPN所需的凭据。<br />如果未在方法调用上设置此标志，并且服务确定在没有交互式授权的情况下不允许请求的操作，但是在成功进行交互式授权后可以允许该操作，则它可能返回org.freedesktop.DBus.Error.InteractiveAuthorizationRequired错误 。<br />缺少此标志并不能保证不会应用交互式授权，因为在此标志之前的现有服务可能已经使用了交互式授权。 但是，将使用交互式授权的现有D-Bus API应该记录该调用可能比平时花费更长的时间，并且新的D-Bus API应该在没有此标志的情况下避免交互式授权。 |

#### Header Fields

 标头末尾的数组包含标头字段，其中每个字段是一个1字节的字段代码，后跟一个字段值。  标头必须包含其消息类型所需的标头字段，以及零个或多个任何可选的标头字段。 该协议规范的未来版本可能会添加新字段。 应用中不得发明自己的标头字段；  仅对此规范的更改可能会引入新的标头字段。 

 如果应用看到了它不期望的标头字段代码，则它必须接受并忽略该字段，因为它将成为此规范的新（但兼容）版本的一部分。 这也适用于出现在意外消息中的已知标头字段，例如：如果信号具有应答序列，则即使此规范版本没有任何意义，也必须将其忽略。 

 但是，应用不得以字段值中存储的错误类型发送或接受已知的头字段。 因此，例如具有UINT32类型的INTERFACE字段的消息将被视为损坏。 

 服务器实现可能会将消息从一个相互不信任的客户机传递到另一个客户机(如消息总线)，因此应该删除服务器无法识别的报头字段。但是，客户端必须假定服务器没有这样做，除非它有相反的证据，例如检查了HeaderFiltering消息总线特性。 

由消息总线控制的新标题字段（类似于SENDER）将来可能会添加到此规范中。  此类消息字段通常仅应添加到要传递给专门请求它们的客户端的消息中（例如，通过调用某种方法），并且消息总线应从其中继的所有其他消息中删除这些标头字段。 该设计原理有两个主要目的。 一种是在将消息传递给对新头字段不感兴趣的客户端时避免不必要的内存和吞吐量开销。  另一个是让客户有理由调用请求那些消息的方法（否则，客户将无法工作）。  这是合乎需要的，因为查看对该方法调用的答复是检查消息总线保证过滤掉可能由恶意对等方发送的伪造报头字段的自然方法。

这是当前定义的标题字段：

| Conventional Name | Decimal Code | Type          | Required In              | Description                                                  |
| ----------------- | ------------ | ------------- | ------------------------ | ------------------------------------------------------------ |
| `INVALID`         | 0            | N/A           | not allowed              | 无效的字段名称（如果出现在消息中则为错误）                   |
| `PATH`            | 1            | `OBJECT_PATH` | `METHOD_CALL`, `SIGNAL`  | 发送调用的对象，或发送信号的对象。保留专用路径/ / freedesktop/dbus/local;实现不应该使用此路径发送消息，总线守护进程的参考实现将断开试图这样做的任何应用程序的连接。这个头字段由消息发送方控制。 |
| `INTERFACE`       | 2            | `STRING`      | `SIGNAL`                 | 调用方法调用或发出信号的接口。 对于方法调用是可选的，对于信号是必需的。  保留了特殊接口org.freedesktop.DBus.Local；  实现不应使用此接口发送消息，并且总线守护程序的参考实现将断开任何尝试这样做的应用程序的连接。 此头字段由消息发送者控制。 |
| `MEMBER`          | 3            | `STRING`      | `METHOD_CALL`, `SIGNAL`  | 成员，方法名称或信号名称。 此头字段由消息发送者控制。        |
| `ERROR_NAME`      | 4            | `STRING`      | `ERROR`                  | 发生的错误的名称                                             |
| `REPLY_SERIAL`    | 5            | `UINT32`      | `ERROR`, `METHOD_RETURN` | 该消息是答复的消息的序列号。  （序列号是标头中的第二个UINT32。）此标头字段由消息发送者控制。 |
| `DESTINATION`     | 6            | `STRING`      | optional                 | 此消息打算用于的连接的名称。 该字段通常仅与消息总线结合使用才有意义（请参阅“消息总线规范”一节），但其他服务器可能会为其定义自己的含义。 此头字段由消息发送者控制。 |
| `SENDER`          | 7            | `STRING`      | optional                 | 发送连接的唯一名称。 通常，该字段仅与消息总线结合使用才有意义，但是其他服务器可能会定义它们自己的含义。 在消息总线上，此标头字段由消息总线控制，因此它与消息总线本身一样可靠且值得信赖。 否则，除非有其他指示的带外信息，否则此头字段由消息发送方控制。 |
| `SIGNATURE`       | 8            | `SIGNATURE`   | optional                 | 消息正文的签名。 如果省略，则假定为空签名“”（即主体必须为0长度）。 此头字段由消息发送者控制。 |
| `UNIX_FDS`        | 9            | `UINT32`      | optional                 | 消息附带的Unix文件描述符的数量。  如果省略，则假定该消息中没有Unix文件描述符。 实际文件描述符需要通过特定于平台的机制进行带外传输。 它们必须作为消息本身的一部分同时发送。  在消息本身的第一个字节被传输之前或消息本身的最后一个字节之后，可能不会发送它们。 此头字段由消息发送者控制。 |

### Valid Names

D-Bus消息中的各种名称都有一些限制。

总线名称，接口和成员的最大名称长度为255。

#### Interface names

接口的名称具有STRING类型，这意味着它们必须是有效的UTF-8。 但是，还有一些其他限制特别适用于接口名称：

- 接口名称由2个或多个以句点（.）字符分隔的元素组成。 所有元素必须至少包含一个字符。              
- 每个元素只能包含ASCII字符“ [A-Z] [a-z] [0-9] _”，并且不能以数字开头。
-  接口名称不得超过最大名称长度 

接口名称应以接口作者的反向DNS域名（小写）开头，例如Java中的接口名称。 界面名称的其余部分通常由一起运行的单词组成，所有单词上均带有大写字母（“ CamelCase”）。 可以使用几个层次结构。  最好在名称中包含接口的主要版本，并在进行不兼容的更改时将其递增； 这样，如果需要，单个对象可以并行实现接口的多个版本。

例如，如果example.com的所有者正在为音乐播放器开发D-Bus  API，则他们可能会定义名为com.example.MusicPlayer1，com.example.MusicPlayer1.Track和com.example.MusicPlayer1.Seekable的接口。

如果作者的DNS域名包含连字符/减字符('-')，这在D-Bus接口名中是不允许的，它们应该被下划线替换。如果DNS域名包含紧跟在句号('.')后面的数字(接口名中也不允许使用该数字)，则接口名应在该数字前添加下划线。例如，如果7-zip.org的所有者为进程外插件定义了一个接口，那么它可能被命名为org._7_zip.Plugin。

D-Bus不能区分Java中称为类和接口的概念：可以在D-Bus上通过接口名称来标识两者。

#### Bus names

连接具有一个或多个与之关联的总线名称。 一个连接只有一个总线名称，这是唯一的连接名称。 在连接的整个生命周期中，唯一的连接名称将保留在连接中。 总线名称的类型为STRING，这意味着它必须是有效的UTF-8。 但是，还有一些其他限制特别适用于总线名称：

- 以冒号（'：'）开头的总线名称是唯一的连接名称。 其他总线名称称为 *well-known bus names* 。
- 总线名称由1个或多个由句点（。）字符分隔的元素组成。 所有元素必须至少包含一个字符。
- 每个元素只能包含ASCII字符“ [[A-Z] [a-z] [0-9] _-”，在新的总线名称中不建议使用“-”。 仅属于唯一连接名称的元素可以以数字开头，其他总线名称中的元素不能以数字开头。
- 总线名称必须至少包含一个“。”（句点）字符（因此至少两个元素）。
- 总线名称不能以“。”开头。  （句点）字符。
-  总线名称不得超过最大名称长度 

请注意，总线名称中允许使用连字符（'-'），但接口名称中不允许使用连字符（'-'）。 在各种引用D-Bus的规范和API中，例如Flatpak应用程序ID，Desktop Entry  Specification中的DBusActivatable接口以及应用程序的“主”接口和对象路径类似于其总线的约定，这也是有问题的或不允许的  名称。 为避免需要特殊情况的情况，建议新的D-Bus名称始终用下划线替换连字符。

与接口名称一样，众所周知的总线名称应以接口作者的反向DNS域名开头（小写），其余的众所周知的总线名称通常由一起运行的单词组成 ，以大写字母开头。 与接口名称一样，在知名的总线名称中包含版本号是一个好主意。 如果需要向后兼容，则可以同时具有多个版本的知名总线名称。

如果一个众所周知的总线名意味着存在一个“main”接口，那么这个“main”接口通常与这个众所周知的总线名具有相同的名称，并且位于相应的对象路径上。例如，如果example.com的所有者正在为音乐播放器开发D-Bus  API，他们可能会定义任何采用众所周知的com.example名称的应用程序。MusicPlayer1应该在对象路径/com/example/MusicPlayer1上有一个对象，该对象实现了com.example.MusicPlayer1接口。

#### Member names

成员(即方法或信号)名称:

- 必须仅包含ASCII字符“ [A-Z] [a-z] [0-9] _”，并且不能以数字开头。
- 不得包含“。”  （句点）字符。
- 不能超过名称的最大长度。
- 长度必须至少为1个字节。

D-Bus上的成员名称通常由不带标点的大写单词组成（“驼峰式”）。 方法名称通常应该是动词，例如GetItems，信号名称通常应该是事件的描述，例如ItemsChanged。

#### Error names

 错误名称具有与接口名称相同的限制 

错误名称与接口名称具有相同的命名约定，并且通常包含.Error。  例如，example.com的所有者可能会定义错误com.example.MusicPlayer1.Error.FileNotFound和com.example.MusicPlayer1.Error.OutOfMemory。 由D-Bus本身定义的错误（例如org.freedesktop.DBus.Error.Failed）遵循类似的模式。

### Message Types

每种消息类型（METHOD_CALL，METHOD_RETURN，ERROR和SIGNAL）都有其自己的预期使用约定和标头字段。 本节介绍这些约定。

#### Method Calls

一些消息调用对远程对象的操作。 这些称为方法调用消息，并且具有类型标记METHOD_CALL。 这样的消息自然地映射到典型程序中对象上的方法。

方法调用消息需要具有指示方法名称的成员标头字段。可选地，消息有一个接口字段，该字段提供方法所属的接口。强烈建议在所有方法调用消息中包含接口。

在没有INTERFACE字段的情况下，如果同一对象上的两个或多个接口具有名称相同的方法，则将不确定将调用其中哪些方法。 应用可以选择返回错误或传递消息，就好像它具有这些接口中的任意一个一样。

在某些情况下（例如众所周知的系统总线），消息是通过远程对象实现外部的访问控制列表进行过滤的。 如果该筛选器通过匹配它们的接口来拒绝某些消息，或者仅接受到特定接口的消息，则它还必须拒绝没有接口的消息：否则，恶意应用程序可能会使用它绕过筛选器。

方法调用消息还包括一个PATH字段，该字段指示要在其上调用方法的对象。如果调用通过消息总线传递，则消息还具有一个DESTINATION字段，该字段给出接收消息的连接的名称。

当应用程序处理方法调用消息时，需要返回答复。 答复由REPLY_SERIAL标头字段标识，该字段指示要回复的METHOD_CALL的序列号。 回复可以是以下两种类型之一：  METHOD_RETURN或ERROR。

如果答复的类型为METHOD_RETURN，则答复消息的参数为方法调用的返回值或“输出参数”。 如果答复的类型为ERROR，则抛出“ exception”，并且调用失败；否则，调用将失败。 没有提供返回值。 向同一方法调用发送多个答复是没有意义的。

即使方法调用没有返回值，也需要METHOD_RETURN答复，因此调用方将知道该方法已成功处理。

METHOD_RETURN或ERROR答复消息必须具有REPLY_SERIAL标头字段。

如果METHOD_CALL消息具有标志NO_REPLY_EXPECTED，则接收该方法的应用程序不应发送答复消息（无论答复是Method_RETURN还是ERROR）。

除非消息具有标志NO_AUTO_START，否则如果目标名称不存在，则在传递消息之前将启动（激活）拥有目标名称的程序。 请参阅“消息总线启动服务（激活）”一节。 该消息将一直保留到新程序成功启动或启动失败为止； 如果失败，将返回错误。  该标志仅在消息总线的上下文中相关，在没有中间总线的一对一通信期间将被忽略。

##### Mapping method calls to native APIs

用于D-Bus的api可以将方法调用映射到特定编程语言(如c++)中的方法调用，也可以将用IDL编写的方法调用映射到D-Bus消息。

 在这种性质的api中，方法的参数通常被称为“In”(这意味着在METHOD_CALL中发送)或“out”(这意味着在METHOD_RETURN中返回)。一些api，如CORBA，也有“inout”参数，发送和接收，即调用者传入一个修改后的值。映射到D-Bus，一个“inout”参数相当于一个“in”参数，后面跟着一个“out”参数。您不能通过连线传递“引用”，因此“inout”纯粹是进程内API的一种错觉。 

给定一个返回值为0或1的方法，后跟0或多个参数，其中每个参数可以是“in”、“out”或“inout”，调用者通过附加每个“in”或“inout”参数来构造消息。“out”参数在调用方的消息中没有赋值。

接收者通过首先附加返回值(如果有)来构造应答，然后依次添加每个“out”或“inout”参数。“in”参数在应答消息中没有表示。

在有异常的语言中，错误应答通常被映射到异常。

在从本机api转换为D-Bus的过程中，将D-Bus命名约定(“FooBar”)自动映射到本机约定(如“FooBar”或“foo_bar”)可能会更好。只要您能说本机API是专门为D-Bus编写的，这就没有问题。在编写将通过总线导出的对象实现时，这是最有意义的。用于调用远程D-Bus对象的对象代理可能需要能够调用任何D-Bus方法，因此像这样的神奇名称映射可能会成为一个问题。

该规范不需要任何本机API绑定;前面的只是一个建议的绑定一致性约定。

#### Signal Emission

与方法调用不同，信号发射没有响应。 信号发射只是SIGNAL类型的单个消息。 它必须具有三个标头字段：PATH给出从中发出信号的对象，加上INTERFACE和MEMBER给出信号的标准名称。 信号需要INTERFACE标头，尽管方法调用是可选的。 

#### Errors

ERROR类型的消息最常见的是对METHOD_CALL的答复，但可以用于答复任何类型的消息。 例如，如果消息总线没有足够的内存来发送信号，则消息总线将返回ERROR来响应信号的发出。 

ERROR可以有任何参数，但是如果第一个参数是STRING，则它必须是错误消息。 错误消息可能以某种方式被记录或显示给用户。 

#### Notation in this document

 本文档使用简单的 pseudo-IDL 来描述特定的方法调用和信号。 这是方法调用的示例 ：

```bask
 org.freedesktop.DBus.StartServiceByName (in STRING name, in UINT32 flags,
                                                     out UINT32 resultcode)
```

 这意味着INTERFACE = org.freedesktop.DBus，MEMBER =  StartServiceByName，METHOD_CALL参数为STRING和UINT32，METHOD_RETURN参数为UINT32。  请记住，“成员”字段不能包含任何“.”。  （句点）字符，因此已知“ IDL”中名称的最后一部分是成员名称。 

 在C ++中，最终可能看起来像这样： 

```bash
 unsigned int org::freedesktop::DBus::StartServiceByName (const char  *name,
                                                                     unsigned int flags);
```

 或者，返回值可以作为一个参数 

```bash
 void org::freedesktop::DBus::StartServiceByName (const char   *name,
                                                             unsigned int  flags,
                                                             unsigned int *resultcode);
```

实际上，这取决于API设计人员如何使其具有这种外观。 您可以设计一个API，在该API中不使用C ++，使用STL或Qt，使用varargs或任何您想要的名称空间。 

信号编写如下：

```bash
org.freedesktop.DBus.NameLost (STRING name)
```

信号没有指定“入”与“出”，因为只能有一个方向。

### Invalid Protocol and Spec Extensions

 出于安全原因，除已定义的扩展点外，应严格分析和验证D-Bus协议。 任何无效的协议或违反规范的行为都应导致立即断开连接，而无需通知另一端。  应该仔细考虑例外情况，例如 对于广泛部署的实现方式，如果有一个很好理解的特质，则可能需要例外。  如果连接的另一端是100％信任的并且已知是友好的，则出于性能原因而跳过验证在某些情况下也很有意义。 

 通常，应该将违反本规范中“must”要求的行为视为利用安全性的可能尝试，并且应当将违反“should”建议的行为视为合法（尽管在某些情况下可能会产生错误）。 

 以下扩展点是故意内置到D-Bus中的，不得将其视为无效协议。 扩展点旨在供本规范的将来版本使用，而不适用于第三方。  目前，第三方在不破坏互操作性的情况下扩展D-Bus的唯一方法是引入一种使用 EXTENSION_-prefixed 命令协商新功能支持的方法，作为auth协议的一部分。 尚无标准的功能协商方式。 

-  在身份验证协议（请参阅“身份验证协议”一节）中，未知命令会导致错误而不是断开连接。 这样可以将来扩展该协议。 以EXTENSION_开头的命令保留给第三方。 
-  身份验证协议支持可插入身份验证机制 
- 地址格式（请参阅“服务器地址”一节）支持新的传输方式。
- 类型未知的消息（METHOD_CALL，METHOD_RETURN，ERROR，SIGNAL以外的消息）将被忽略。 但是，未知类型的消息仍必须采用与已知消息相同的格式。 它们仍然具有正常的标题和正文。
- 具有未知或意外字段代码的标头字段必须被忽略，尽管它们仍然必须格式正确。
- 当然可以添加新的标准接口（具有新的方法和信号）。

## Authentication Protocol

在开始消息流之前，必须先验证两个应用程序。 使用简单的纯文本协议进行身份验证； 该协议是SASL规范，并且直接从SASL规范中进行映射。 此处不使用消息编码，仅使用纯文本消息。

在D-Bus中使用SASL要求我们定义非空授权标识字符串的含义。  在Unix平台上使用D-Bus时，非空的SASL授权身份代表Unix用户。  完全由ASCII十进制数字组成的授权身份代表POSIX定义的数字用户ID，例如，在许多系统上创建的root用户为0，第一个用户为1000。  不需要接受或支持非数字授权身份，但是如果使用非数字授权身份，则必须将它们解释为登录名，如POSIX struct  passwd的pw_name字段中所显示的（例如root），并标准化为相应的数字用户ID。  为了获得最佳的互操作性，客户端和服务器应使用数字用户ID。

在Windows平台上使用D-Bus时，非空的SASL授权身份以字符串形式表示Windows安全标识符（SID），例如，域的S-1-5-21-3623811015-3361044348-30300820-1013 或本地计算机用户，或LOCAL_SYSTEM用户的S-1-5-18。   D-Bus协议中未使用面向用户的用户名，例如Administrator或LOCAL_SYSTEM。

在Windows平台上使用D-Bus时，非空的SASL授权身份以字符串形式表示Windows安全标识符（SID），例如，域的S-1-5-21-3623811015-3361044348-30300820-1013 或本地计算机用户，或LOCAL_SYSTEM用户的S-1-5-18。   D-Bus协议中未使用面向用户的用户名，例如Administrator或LOCAL_SYSTEM。

在示例中，“ C：”和“ S：”分别指示客户端和服务器发送的行。 客户端发送第一行，并且服务器必须用单行答复来响应来自客户机的每一行，但有一个例外：没有对BEGIN命令的答复。

### Protocol Overview

该协议是基于行的协议，其中每行以\ r \ n结尾。  每行以全大写ASCII命令名称开头，该命令名称仅包含字符范围[A-Z_]，一个空格，该命令的所有参数，然后\ r \ n结束该行。  该协议区分大小写。 所有字节都必须在ASCII字符集中。 从客户端到服务器的命令如下：

- AUTH [mechanism] [initial-response]
- CANCEL
- BEGIN
- DATA <data in hex encoding>
- ERROR [human-readable error explanation]
- NEGOTIATE_UNIX_FD

从服务器到客户端如下:

- REJECTED <space-separated list of mechanism names>
- OK <GUID in hex>
- DATA <data in hex encoding>
- ERROR [human-readable error explanation]
- AGREE_UNIX_FD

命令集的非官方扩展名必须以字母“ EXTENSION_”开头，以避免与以后的正式命令冲突。 例如，“ EXTENSION_COM_MYDOMAIN_DO_STUFF”。

### Special credentials-passing nul byte

连接到服务器后，客户端必须立即发送单个nul字节。  在某些使用sendmsg（）和SCM_CREDS或SCM_CREDENTIALS来通过UNIX域套接字传递凭据的操作系统上，此字节可能伴随有凭据信息。 但是，即使在其他类型的套接字上，甚至在不需要发送字节即可传输凭据的操作系统上，也必须发送nul字节。  本文档中描述的文本协议在单个nul字节之后开始。 如果从客户端收到的第一个字节不是空字节，则服务器可能会断开该客户端的连接。

除初始字节外的任何上下文中的nul字节都是错误； 该协议仅是ASCII。

随nul字节一起发送的凭据可以与外部SASL机制一起使用。

### AUTH command

客户端将AUTH命令发送到服务器。 服务器以DATA，OK或REJECTED答复。

如果AUTH命令没有参数，则它是列出可用机制的请求。 服务器必须以列出其理解的机制的REJECTED命令或错误来响应。

如果AUTH命令指定了一种机制，并且服务器支持该机制，则服务器应开始使用DATA命令与客户端交换SASL质询响应数据。

如果服务器不支持AUTH命令中给出的机制，它必须发送一个拒绝命令，列出它支持的机制，或者一个错误 

如果提供了[initial-response]参数，它将用于没有初始质询(或空初始质询)的机制，就好像它是初始数据命令的参数一样。如果所选的机制有一个初始质疑并且提供了[initial-response]，服务器应该通过发送REJECTED来拒绝身份验证。 

如果在交换DATA命令后身份验证成功，则必须将OK命令发送给客户端。如果在交换DATA命令后身份验证成功，则必须将OK命令发送给客户端。

### CANCEL Command

客户端将CANCEL命令发送到服务器。 服务器回复“ REJECTED ”。

 在发送BEGIN命令之前的任何时间，客户端都可以发送CANCEL命令。 服务器收到CANCEL命令后，必须发送REJECTED命令并中止当前的身份验证交换。 

### DATA Command

DATA命令可以来自客户端或服务器，并且仅包含一个十六进制编码的数据块，该数据块将根据使用中的SASL机制进行解释。 如果由客户端发送，则服务器以DATA，OK或REJECTED答复。

一些SASL机制支持发送“空字符串”。  FIXME我们需要一些方法来做到这一点。

### BEGIN Command

客户端将BEGIN命令发送到服务器。 服务器不回复。

BEGIN命令确认客户端已从服务器收到OK命令并完成了其希望进行的所有功能协商，并声明消息流即将开始。

在客户机发出BEGIN命令的\r\n之后，服务器接收到的第一个八位字节必须是经过身份验证/加密的D-Bus消息流的第一个八位字节。

与所有其他命令不同，服务器不会使用自己的身份验证命令来回复BEGIN命令。 在BEGIN之前对命令的回复\ r \ n之后，客户端收到的下一个八位位组必须是经过身份验证/加密的D-Bus消息流的第一个八位位组。

### REJECTED Command

服务器将REJECTED命令发送到客户端。

REJECTED命令指示当前的身份验证交换已失败，并且进一步的DATA交换是不合适的。 客户通常会尝试另一种机制，或尝试对挑战提供不同的响应。

可选地，REJECTED命令将可用的身份验证机制以空格分隔的列表作为参数。 如果服务器曾经提供过受支持机制的列表，则它每次发送REJECTED消息时都必须提供相同的列表。 客户可以随意忽略第一个列表之后收到的所有列表。

### OK Command

OK命令由服务器发送到客户端。

OK命令指示客户端已通过身份验证。 客户端现在可以继续协商Unix文件描述符传递。 为此，它将NEGOTIATE_UNIX_FD发送到服务器。

OK命令指示客户端已通过身份验证。 客户端现在可以继续协商Unix文件描述符传递。 为此，它将NEGOTIATE_UNIX_FD发送到服务器。

否则，客户端必须通过发送BEGIN命令，其消息流或断开连接来响应OK命令。 收到BEGIN命令后，服务器不得使用此协议接受其他命令。 进一步的通信将是D-Bus消息流（经过协商可选加密），而不是该协议。

如果没有协商，客户端在OK命令的\r\n之后接收到的第一个八位字节必须是经过身份验证/加密的D-Bus消息流的第一个八位字节。如果客户端协商传递Unix文件描述符，那么在AGREE_UNIX_FD或错误应答的\r\n之后，客户端接收到的第一个八位符必须是经过身份验证/加密的流的第一个八位符。

OK命令具有一个参数，即服务器的GUID。 有关服务器GUID的更多信息，请参见“服务器地址”一节。

### ERROR Command

ERROR命令可以向任一方向发送。 如果由客户端发送，则服务器以REJECTED答复。

ERROR命令指示服务器或客户机不知道某个命令，在当前上下文中不接受给定的命令，或者不理解命令的参数。这使得协议得以扩展;客户机或服务器可以发送在新协议版本中存在或只允许的命令，如果接收到错误而不是适当的响应，可以使用其他一些技术。

 如果发送了错误，则发送错误的服务器或客户端必须继续运行，就像从未收到导致错误的命令一样。 但是，接收错误的服务器或客户端应尝试执行其他操作，而不是导致错误的原因。 如果仅取消/拒绝身份验证。 

如果D-Bus协议在将来的某个时间发生不兼容的更改，则实现新协议的应用程序可能会通过发送新命令并从不了解该应用程序的错误中接收错误来检查对新协议的支持。 因此，auth协议的ERROR功能是一个逃生舱口，使我们将来可以协商对D-Bus协议的扩展或更改。

### NEGOTIATE_UNIX_FD Command

客户端将NEGOTIATE_UNIX_FD命令发送到服务器。 服务器回复AGREE_UNIX_FD或ERROR。

NEGOTIATE_UNIX_FD命令指示客户端支持Unix文件描述符传递。 仅在验证连接后，即客户端收到OK后，才能发送此命令。 此命令只能在支持Unix文件描述符传递的传输上发送。

收到NEGOTIATE_UNIX_FD时，服务器必须以AGREE_UNIX_FD或ERROR响应。 如果选择的传输支持Unix文件描述符传递，并且服务器支持此功能，它将响应前者。  如果传输不支持Unix文件描述符传递，服务器不支持此功能，或者由于安全性或其他原因服务器决定不启用文件描述符传递，则它将响应后者。

### AGREE_UNIX_FD Command

服务器将AGREE_UNIX_FD命令发送到客户端。

AGREE_UNIX_FD命令指示服务器支持Unix文件描述符传递。 仅在对连接进行身份验证后才能发送此命令，并且客户端发送NEGOTIATE_UNIX_FD以启用Unix文件描述符传递。 此命令只能在支持Unix文件描述符传递的传输上发送。

收到AGREE_UNIX_FD时，客户端必须以BEGIN响应，其后是消息流或断开连接。 收到BEGIN命令后，服务器不得使用此协议接受其他命令。 进一步的通信将是D-Bus消息流（经过协商可选加密），而不是该协议。

### Future Extensions

将来可能会扩展身份验证和协商协议。 为此，可以引入新命令。 如果客户端或服务器收到未知命令，它将以ERROR响应并且不认为这是致命的。 可以在认证之前和之后引入新命令，即在OK命令之前和之后引入。

### Authentication examples

**Figure 1. Example of successful EXTERNAL authentication**

```
            31303030 is ASCII decimal "1000" represented in hex, so
            the client is authenticating as Unix uid 1000 in this example.

            C: AUTH EXTERNAL 31303030
            S: OK 1234deadbeef
            C: BEGIN
          
```

**Figure 2. Example of finding out mechanisms then picking one**

```
            C: AUTH
            S: REJECTED KERBEROS_V4 SKEY
            C: AUTH SKEY 7ab83f32ee
            S: DATA 8799cabb2ea93e
            C: DATA 8ac876e8f68ee9809bfa876e6f9876g8fa8e76e98f
            S: OK 1234deadbeef
            C: BEGIN
          
```



**Figure 3. Example of client sends unknown command then falls back to regular auth**

```
            532d312d352d3138 is the Windows SID "S-1-5-18" in hex,
            so the client is authenticating as Windows SID S-1-5-18
            in this example.

            C: FOOBAR
            S: ERROR
            C: AUTH EXTERNAL 532d312d352d3138
            S: OK 1234deadbeef
            C: BEGIN
          
```



**Figure 4. Example of server doesn't support initial auth mechanism**

```
            C: AUTH EXTERNAL
            S: REJECTED KERBEROS_V4 SKEY
            C: AUTH SKEY 7ab83f32ee
            S: DATA 8799cabb2ea93e
            C: DATA 8ac876e8f68ee9809bfa876e6f9876g8fa8e76e98f
            S: OK 1234deadbeef
            C: BEGIN
          
```



**Figure 5. Example of wrong password or the like followed by successful retry**

```
            C: AUTH EXTERNAL 736d6376
            S: REJECTED KERBEROS_V4 SKEY
            C: AUTH SKEY 7ab83f32ee
            S: DATA 8799cabb2ea93e
            C: DATA 8ac876e8f68ee9809bfa876e6f9876g8fa8e76e98f
            S: REJECTED
            C: AUTH SKEY 7ab83f32ee
            S: DATA 8799cabb2ea93e
            C: DATA 8ac876e8f68ee9809bfa876e6f9876g8fa8e76e98f
            S: OK 1234deadbeef
            C: BEGIN
          
```



**Figure 6. Example of skey cancelled and restarted**

```
            C: AUTH EXTERNAL 32303438
            S: REJECTED KERBEROS_V4 SKEY
            C: AUTH SKEY 7ab83f32ee
            S: DATA 8799cabb2ea93e
            C: CANCEL
            S: REJECTED
            C: AUTH SKEY 7ab83f32ee
            S: DATA 8799cabb2ea93e
            C: DATA 8ac876e8f68ee9809bfa876e6f9876g8fa8e76e98f
            S: OK 1234deadbeef
            C: BEGIN
          
```



**Figure 7. Example of successful EXTERNAL authentication with successful negotiation of Unix FD passing**

```
            C: AUTH EXTERNAL 31303030
            S: OK 1234deadbeef
            C: NEGOTIATE_UNIX_FD
            S: AGREE_UNIX_FD
            C: BEGIN
          
```


**Figure 8. Example of successful EXTERNAL authentication with unsuccessful negotiation of Unix FD passing**

```
            C: AUTH EXTERNAL 31303030
            S: OK 1234deadbeef
            C: NEGOTIATE_UNIX_FD
            S: ERROR Not supported on this OS
            C: BEGIN
          
```

### Authentication state diagrams

本节以客户端和服务器的状态机记录了auth协议。 这可能是实现协议的最可靠的方法。

#### Client states

为了更精确地描述协议状态机和身份验证机制之间的交互，使用了以下符号:MECH(CHALL)表示服务器向机制MECH发送CHALL, MECH返回其中一个

- CONTINUE（RESP）表示继续进行身份验证对话，并将RESP作为响应发送到服务器；             
-  OK（RESP）表示将RESP发送到服务器后，身份验证会话的客户端已完成，服务器应返回“ OK”；              
-  ERROR表示CHALL无效，无法处理。    

RESP和CHALL都可能为空。

客户端首先从默认机制获取初始响应，然后发送AUTH MECH  RESP，如果该机制未提供初始响应，则发送AUTH MECH。  如果该机制返回CONTINUE，则客户端以状态WaitingForData启动；如果该机制返回OK，则客户端以WaitingForOK状态启动。

客户端应跟踪可用的机制以及已经尝试过的机制。 该列表用于决定发送哪个AUTH命令。 列表用完后，客户端应放弃并关闭连接。

***WaitingForData***

- Receive DATA CHALL

  | MECH(CHALL) returns CONTINUE(RESP) → send DATA RESP, goto WaitingForData* |
  | ------------------------------------------------------------ |
  | MECH(CHALL) returns OK(RESP) → send DATA RESP, goto *WaitingForOK* |
  | MECH(CHALL) returns ERROR → send ERROR  [msg], goto *WaitingForData* |

- Receive REJECTED [mechs] →send AUTH [next mech], goto WaitingForData or *WaitingForOK* 

-  Receive ERROR → send CANCEL, goto *WaitingForReject* 

-  Receive OK → *authenticated*, choose one: 

- | send NEGOTIATE_UNIX_FD, goto *WaitingForAgreeUnixFD*   |
  | ------------------------------------------------------ |
  | send BEGIN, terminate auth conversation (successfully) |

-  Receive anything else → send ERROR, goto *WaitingForData* 

 ***WaitingForOK*.**

-  Receive OK → *authenticated*, choose one: 

  | send NEGOTIATE_UNIX_FD, goto *WaitingForAgreeUnixFD*   |
  | ------------------------------------------------------ |
  | send BEGIN, terminate auth conversation (successfully) |

-  Receive REJECTED [mechs] → send AUTH [next mech],goto *WaitingForData* or *WaitingForOK* 

-  Receive DATA → send CANCEL, goto *WaitingForReject*

-  Receive ERROR → send CANCEL, goto *WaitingForReject*

-  Receive anything else → send ERROR, goto *WaitingForOK*

***WaitingForReject*.**             

- Receive REJECTED [mechs] → send AUTH [next mech],goto *WaitingForData* or *WaitingForOK*                
- Receive anything else → terminate auth conversation, disconnect

***WaitingForAgreeUnixFD*.** By the time this state is reached, the client has already  been authenticated.            

- Receive AGREE_UNIX_FD → enable Unix fd passing, send BEGIN, terminate auth conversation (successfully)                
- Receive ERROR → disable Unix fd passing, send BEGIN, terminate auth conversation (successfully)                
- Receive anything else → terminate auth conversation, disconnect                

#### Server states

 对于服务器MECH（RESP）表示将客户端响应RESP反馈送到机制MECH，该机制返回以下内容之一： 

- CONTINUE（CHALL）表示继续进行身份验证对话，并将CHALL作为质询发送给客户端；           
-  OK表示客户已经成功验证 
- REJECTED表示客户端认证失败或RESP中存在错误。

 服务器以WaitingForAuth状态启动。 如果客户端被拒绝太多次，则服务器必须断开客户端的连接。 

***WaitingForAuth*.**             

- Receive AUTH → send REJECTED [mechs], goto *WaitingForAuth*                

- Receive AUTH MECH RESP                   

  | MECH not valid mechanism → send REJECTED [mechs], goto  WaitingForAuth* |
  | ------------------------------------------------------------ |
  | MECH(RESP) returns CONTINUE(CHALL) → send DATA CHALL, goto *WaitingForData* |
  | MECH(RESP) returns OK → send OK, goto *WaitingForBegin*      |
  | MECH(RESP) returns REJECTED → send REJECTED [mechs], goto *WaitingForAuth* |

- Receive BEGIN → terminate auth conversation, disconnect                

- Receive ERROR → send REJECTED [mechs], goto *WaitingForAuth*

- Receive anything else → send ERROR, goto *WaitingForAuth*

***WaitingForData*.**             

- Receive DATA RESP                  

  | MECH(RESP) returns CONTINUE(CHALL) → send DATA CHALL, goto *WaitingForData* |
  | ------------------------------------------------------------ |
  | MECH(RESP) returns OK → send OK, goto *WaitingForBegin*      |
  | MECH(RESP) returns REJECTED → send REJECTED [mechs], goto *WaitingForAuth* |

- Receive BEGIN → terminate auth conversation, disconnect                

- Receive CANCEL → send REJECTED [mechs], goto WaitingForAuth                

- Receive ERROR → send REJECTED [mechs], goto WaitingForAuth               

- Receive anything else → send ERROR, goto WaitingForData              

***WaitingForBegin*.**             

- Receive BEGIN → terminate auth conversation, client authenticated                
- Receive NEGOTIATE_UNIX_FD → send AGREE_UNIX_FD or ERROR, goto *WaitingForBegin*                
- Receive CANCEL → send REJECTED [mechs], goto *WaitingForAuth*             
- Receive ERROR → send REJECTED [mechs], goto  *WaitingForAuth*                
- Receive anything else → send ERROR, goto  *WaitingForBegin*                

### Authentication mechanisms

本节介绍了一些实际的D-Bus实现通常支持的身份验证机制。  D-Bus协议还允许任何其他标准的SASL机制，尽管D-Bus的实现通常不允许。

#### EXTERNAL

RFC 4422“简单身份验证和安全层（SASL）”的附录A“ SASL EXTERNAL机制”中定义了EXTERNAL机制。 这是在凭据可以带外传输的平台上（特别是可以在unix：传输上执行凭据传递的Unix平台上）推荐的身份验证机制。

在Unix平台上，可互操作的客户端应首选发送整数Unix用户ID的ASCII十进制字符串形式作为授权身份，例如1000。通过身份验证协议以十六进制编码时，通常会导致出现类似AUTH EXTERNAL 31303030的行 然后是\ r \ n。

在Windows平台上，使用EXTERNAL机制的客户端应使用其字符串形式的Windows安全标识符作为授权身份，例如对于域或本地计算机用户，为S-1-5-21-3623811015-3361044348-30300820-1013  S-1-5-18（用于LOCAL_SYSTEM用户）。 当通过身份验证协议以十六进制编码时，这通常会导致类似于AUTH EXTERNAL  532d312d352d3138的行，后跟\ r \ n。

#### DBUS_COOKIE_SHA1

#### ANONYMOUS

省略 见官网。

## Server Addresses

 服务器地址包括一个传输名称，后跟一个冒号，然后是一个可选的，逗号分隔的键和值列表，格式为key = value。 每个值都被转义。 

For example:      

```c
unix:path=/tmp/dbus-test
```

 它是一个unix套接字的地址，路径为/tmp/dbus-test。 

 值转义类似于URI转义，但更简单。 

- 可选择转义的字节集是[-0-9A-Za-z_/.\]。要转义，不在可选择转义字节集中的每个字节(注意，不是字符)必须用ASCII百分比(%)和十六进制字节值替换。十六进制的值必须总是两个数字，即使第一个数字是零。如果需要，可选择转义的字节可以进行转义。

- 若要取消转义，请将每个字节追加到值中;如果字节是ASCII百分比(%)字符，则将后面的十六进制值追加。如果一个%字节后面没有两个十六进制数字，这是一个错误。如果看到非可选转义的字节未转义，则将出错。 

 一组可选的转义字节旨在保留地址的可读性和便利性。

服务器可以使用键guid和值（十六进制编码的16字节序列）指定键值对。  “ UUID”一节描述了guid字段的格式。 如果存在，此UUID可用于区分一个服务器地址和另一个服务器地址。  服务器应针对其侦听的每个地址使用不同的UUID。  例如，如果消息总线守护程序同时提供UNIX域套接字和TCP连接，但是无论客户端如何连接都将其视为相同，则这两个连接是等效的后连接，但应具有不同的UUID来区分连接的类型。

地址UUID功能的目的是通过允许客户端检查地址是否对应于已经存在的连接，来允许客户端避免打开与同一服务器的多个相同连接。  比较两个地址是不够的，因为地址可以由不同的服务器回收，并且如果简单地将其与字符串进行比较，则等效地址可能看起来有所不同（例如，TCP地址中的主机可以指定为IP地址或主机名）。

请注意，地址键是guid，尽管由于历史原因，API的其余部分和文档都说“UUID”。

当连接到服务器时，多个服务器地址可以用分号分隔。然后库将尝试连接到第一个地址，如果失败，它将尝试连接到指定的下一个地址，以此类推。例如

```
unix:path=/tmp/dbus-test;unix:path=/tmp/dbus-test2
```

一些地址是可连接的。 可连接地址是一种包含足以让客户端连接到它的信息的地址。 例如，tcp：host = 127.0.0.1，port = 4242是可连接的地址。 不一定可以侦听每个可连接的地址：例如，不可能侦听unixexec：地址。

有些地址是可收听的。 可监听地址是包含足以让服务器在其上监听的信息的地址，从而产生可连接地址（可能与原始地址不同）。 许多可监听地址不可连接：例如，tcp：host = 127.0.0.1是可监听的，但不可连接（因为它未指定端口号）。

在不可连接的地址上进行侦听将导致可连接的地址与可侦听的地址不同。  例如，侦听tcp：host = 127.0.0.1可能会导致可连接的地址tcp：host = 127.0.0.1，port =  30958，侦听unix：tmpdir = / tmp可能会导致可连接的地址unix：abstract = / tmp  /  dbus-U8OSdmf7或在unix：runtime = yes上侦听可能会导致可连接地址unix：path = / run / user / 1234 / bus。

## Transports

当前传输包括:unix域套接字(包括linux上的抽象名称空间)，launchd, systemd, TCP/IP，一个执行的子进程和使用进程内管道的调试/测试传输。未来可能的传输包括通过X11协议传输的传输。

### Unix Domain Sockets

Unix域套接字可以是文件系统中的路径，也可以是Linux内核上的路径，它们可以是抽象的，类似于路径，但不会显示在文件系统中。

当D-Bus库打开套接字时，它将在第一个尾随Nul字节之前截断路径名。 普通路径和抽象路径均是如此。 请注意，这与以前的D-Bus版本有所不同，后者会创建具有固定长度路径名的套接字。 比固定长度短的名称将用Nul字节填充。

Unix域套接字在Windows上不可用。 在所有其他平台上，建议将它们单独或与系统地址或启动地址一起使用的D-Bus传输。

指定路径或抽象的Unix地址是可监听和可连接的。 指定tmpdir或dir的Unix地址只能监听：相应的可连接地址将指定路径或抽象。 同样，指定运行时的Unix地址只能监听，而相应的可连接地址将指定路径。

#### Server Address Format

Unix域套接字地址由“ unix：”前缀标识，并支持以下键/值对：

| Name     | Values   | Description                                                  |
| -------- | -------- | ------------------------------------------------------------ |
| path     | (path)   | Path of the unix domain socket.                              |
| dir      | (path)   | Directory in which a socket file with a random file name starting with 'dbus-' will be created by the server. This key  can only be used in server addresses, not in client addresses;  the resulting client address will have the "path" key instead.              be set. |
| tmpdir   | (path)   | The same as "dir", except that on platforms with abstract sockets, the server may attempt to create an  abstract socket whose name starts with this directory instead of a path-based socket. This key can only be used in server addresses, not in client addresses; the resulting client address will have the "abstract" or "path" key instead. |
| abstract | (string) | Unique string in the abstract namespace, often syntactically resembling a path but unconnected to the filesystem namespace.  This key is only supported on platforms with abstract Unix  sockets, of which Linux is the only known example. |
| runtime  | `yes`    | If given, This key can only be used in server addresses, not in client addresses. If set, its value must be `yes`. This is typically used in an address string like `unix:runtime=yes;unix:tmpdir=/tmp` so that there can be a fallback if `XDG_RUNTIME_DIR` is not set. |

必须提供键路径，abstract，runtime，dir或tmpdir之一。

### launchd

launchd是一个开源服务器管理系统，它取代了苹果Mac OS X 10.4及以上版本上的init、inetd和cron。它为每个用户提供一个通用的会话总线地址，并反对OSX上启用x11的D-Bus启动程序。

launchd会分配一个套接字，并在启动环境中通过DBUS_LAUNCHD_SESSION_BUS_SOCKET变量为它提供unix路径。 由launchd（或dbus-daemon，如果是通过launchd启动）产生的每个进程都可以通过其环境访问它。  其他进程可以通过执行以下命令来查询已启动的套接字：$ launchctl getenv DBUS_LAUNCHD_SESSION_BUS_SOCKET通常由D-Bus客户端库完成，因此不必手动进行。

launchd在Microsoft Windows上不可用。

启动的地址是可监听且可连接的。

#### Server Address Format

启动的地址由“ launchd：”前缀标识，并支持以下键/值对：

| Name | Values                 | Description                                                  |
| ---- | ---------------------- | ------------------------------------------------------------ |
| env  | (environment variable) | path of the unix domain socket for the launchd created dbus-daemon. |

env键是必需的。

### systemd

systemd是一个开源服务器管理系统，它替代了较新的Linux系统上的init和inetd。 它支持套接字激活。  D-Bus systemd传输用于从systemd获取套接字激活文件描述符，并在当前进程通过套接字激活产生时用作D-Bus传输。

系统传输仅接受通过套接字激活传递的一个或多个Unix域或TCP流套接字。 强烈建议使用Unix域套接字。

系统传输在非Linux操作系统上不可用。

systemd地址是可侦听的，但不可连接。 对应的可连接地址是套接字的Unix或tcp地址。

### TCP Sockets

tcp传输在位于相同或不同主机上的客户机之间提供基于tcp /IP的连接。

与远程X11相似，TCP传输没有完整性或机密性保护，因此通常只能在本地回送接口上使用它，例如，使用类似tcp：host = 127.0.0.1或tcp：host = localhost的地址。  特别地，配置众所周知的系统总线或众所周知的会话总线以侦听非环回TCP地址是不安全的。

在Windows和大多数Unix平台上，TCP堆栈无法通过TCP连接传输凭据，因此EXTERNAL身份验证机制通常不适用于此传输（尽管D-Bus的参考实现能够识别Windows上的环回TCPv4连接 通过其端口号，部分启用EXTERNAL机制）。 通常使用DBUS_COOKIE_SHA1机制。

开发人员有时会尝试使用远程TCP作为调试工具。但是，如果在成品中启用此功能，结果将是危险的不安全的。开发人员应该通过Secure Shell或类似的协议来中继连接，而不是使用远程TCP。

在过去，远程TCP连接有时用于在受信任的局域网内的不同机器上相同用户的登录会话之间共享单个会话总线，并与未加密的远程X11、nfs共享的主目录和NIS  (YP)身份验证一起使用。这对同一局域网上的攻击者是不安全的，应该被认为是强烈反对的;更具体地说，它与未加密的远程X11和NFSv2/NFSv3具有相同的不安全方式和原因。D-Bus维护者建议对每个(用户、机器)使用单独的会话总线，只能从该机器内部访问。

所有tcp地址都是可监听的。 也可以连接其中指定了主机和端口且端口非零的tcp地址。

#### Server Address Format

TCP / IP套接字地址由“ tcp：”前缀标识，并支持以下键/值对：

| Name   | Values   | Description                                                  |
| ------ | -------- | ------------------------------------------------------------ |
| host   | (string) | DNS name or IP address                                       |
| bind   | (string) | Used in a listenable address to configure the interface on which the server will listen: either the IP address of one of  the local machine's interfaces (most commonly `127.0.0.1            `), or a DNS name that resolves to one of those IP addresses, or '*' to listen on all interfaces simultaneously.   If not specified, the default is the same value as "host". |
| port   | (number) | The tcp port the server will open. A zero value let the server choose a free port provided from the underlaying operating system. libdbus is able to retrieve the real used port from the server. |
| family | (string) | If set, provide the type of socket family either "ipv4" or "ipv6". If unset, the family is unspecified. |

### Nonce-authenticated TCP Sockets

nonce-tcp传输使用简单的身份验证机制提供了一种经过修改的TCP传输，以确保只有对文件系统中某个位置具有读取访问权限的客户端才能连接到服务器。 服务器将机密（随机数）写入文件，并且仅当客户端在连接后立即发送随机数时，才接受传入的客户端连接。  随机数机制不需要任何设置，并且与“身份验证”部分中描述的高级身份验证机制正交。

nonce-tcp传输在概念上类似于DBUS_COOKIE_SHA1身份验证机制和tcp传输的组合，并且似乎是由于对SASL身份验证机制的误解而最初实现的。

像普通的tcp传输一样，nonce-tcp传输也没有完整性或机密性保护，因此通常只能在本地环回接口上使用它，例如，使用类似tcp：host = 127.0.0.1或tcp：host = localhost的地址 。 其他用途是不安全的。  有关使用这些传输的情况以及这些传输的替代方法的更多信息，请参见“ TCP套接字”一节。

Windows操作系统上的D-Bus实现通常通过本地回送接口使用nonce-tcp传输。 这是因为在这些操作系统上无法使用unix传输，否则将建议使用unix传输。

启动时，服务器会生成一个随机的16字节随机数，并将其写入用户临时目录中的文件中。 使用“ noncefile”键值对将现时文件位置发布为服务器D-Bus地址的一部分。 接受后，服务器从套接字读取16个字节。  如果读取的字节与存储在随机数文件中的随机数不匹配，则服务器必须立即断开连接。  如果随机数与接收到的字节序列匹配，则客户端将被接受，并且传输的行为类似于普通的tcp传输。

成功连接到服务器套接字后，客户端必须通过noncefile =键值对从服务器发布的文件中读取现时值，并将其通过套接字发送。 此后，传输的行为就像普通的tcp传输。

所有nonce-tcp地址都是可监听的。 也可以连接其中主机，端口和noncefile都指定且port非零的nonce-tcp地址。

#### Server Address Format

Nonce TCP / IP套接字地址使用“ nonce-tcp：”前缀，并支持以下键/值对：

| Name      | Values   | Description                                                  |
| --------- | -------- | ------------------------------------------------------------ |
| host      | (string) | DNS name or IP address                                       |
| bind      | (string) | The same as for tcp: addresses                               |
| port      | (number) | The tcp port the server will open. A zero value let the server choose a free port provided from the underlaying operating system. libdbus is able to retrieve the real used port from the server. |
| family    | (string) | If set, provide the type of socket family either "ipv4" or "ipv6". If unset, the family is unspecified. |
| noncefile | (path)   | File location containing the secret.  This is only meaningful in connectable addresses: a listening D-Bus server that offers this transport will always create a new nonce file. |

### Executed Subprocesses on Unix

此传输派生一个进程，并将其标准输入和标准输出与匿名Unix域套接字连接。 然后，此套接字用于传输工具的通信。 此传输可用于将进程外转发器程序用作D-Bus协议的基础。

分叉的流程将继承父流程的标准错误输出和流程组。

执行的子进程在Windows上不可用。

unixexec地址是可连接的，但不可监听。

#### Server Address Format

执行的子进程地址由“ unixexec：”前缀标识，并支持以下键/值对：

| Name              | Values   | Description                                                  |
| ----------------- | -------- | ------------------------------------------------------------ |
| path              | (path)   | Path of the binary to execute, either an absolute path or a binary name that is searched for in the default search path of the OS. This corresponds to the first            argument of execlp(). This key is mandatory. |
| argv0             | (string) | The program name to use when executing the binary. If omitted the same value as specified for path=will be used. This corresponds to the second argument of            execlp(). |
| argv1, argv2, ... | (string) | Arguments to pass to the binary. This corresponds to the third and later arguments of execlp(). If a specific argvX is not specified no further argvY for Y > X            are taken into account. |

## Meta Transports

元传输是一种具有特殊增强或行为的传输。 当前可用的元传输包括：自动启动

### Autolaunch

自动启动传输为dbus客户端提供了一种方法，可以自动检测正在运行的dbus会话总线，并自动启动会话总线（如果不存在）。

在Unix上，自动启动地址是可连接的，但不可监听。

在Windows上，自动启动地址既可连接又可监听。

#### Server Address Format

Autolaunch地址使用“Autolaunch:”前缀，支持以下键/值对:

| Name  | Values   | Description                                                  |
| ----- | -------- | ------------------------------------------------------------ |
| scope | (string) | scope of autolaunch (Windows only)  <br />"*install-path" - limit session bus to dbus installation path. The dbus installation path is determined from the location of   the shared dbus library. If the library is located in a 'bin'   subdirectory the installation root is the directory above, otherwise the directory where the library lives is taken as installation root.  <br />                         <install-root>/bin/[lib]dbus-1.dll           <br />                          <install-root>/[lib]dbus-1.dll              `           <br />                  "*user" - limit session bus to the recent user.                   <br />          other values - specify dedicated session bus like "release",   "debug" or other |

#### Windows implementation

在启动时，服务器打开特定于平台的传输，创建一个互斥体和一个包含相关会话总线地址的共享内存部分。  dbus客户端库将检查此互斥量，以检测正在运行的dbus会话总线。 互斥锁和共享内存部分的访问受全局锁保护。

在最近的实现中，自动启动传输在本地主机上使用tcp传输，并从操作系统中选择了端口。 此细节将来可能会更改。

## UUIDs

一个有效的D-Bus实现在两个地方使用通用唯一ID。  首先，每个服务器地址都有一个标识该地址的UUID，如“服务器地址”一节所述。  其次，每个运行D-Bus客户端或服务器的操作系统内核实例都有一个UUID，用于标识该内核，可以通过调用方法org.freedesktop.DBus.Peer.GetMachineId（）进行检索（请参阅“ org.freedesktop.DBus”部分。 对等”）。

本文档中的术语“ UUID”是字面上的意思，即普遍唯一的标识符。 它无意参考RFC4122，实际上D-Bus UUID与该RFC不兼容。

UUID必须包含128位数据并进行十六进制编码。 十六进制编码的字符串不能包含连字符或其他非十六进制字符，并且长度必须恰好是32个字符。 为了生成UUID，当前参考实现将自UNIX时代以来（大字节序）的32位时间（以秒为单位）串联96位随机数据。

只要随机数生成器的质量很高，简单地生成128位随机数据也是可以接受的，并且可能更好。 如果随机位不是非常随机，则时间戳可能会有所帮助。 使用高质量的随机数生成器，即使只有96位，也极不可能发生冲突，因此这有点学术性。

但是，对于UUID的前96位，实现应坚持随机数据。

