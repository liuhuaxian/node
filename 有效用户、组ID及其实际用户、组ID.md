# 有效用户、组ID及其实际用户、组ID

## 代码

```c
#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>

int main(int argc, char* argv[])
{
        if(argc < 2)
                printf("error argc!\n");
        if(access(argv[1],R_OK)<0) 
                perror("access");
        else
                printf("access Ok!\n");
        if(open(argv[1], O_RDONLY))
                perror("open");
        else
                printf("open OK\n");
        return 0;
}
```

## 运行演示1

```bash
[builder@localhost UC]$ ./a.out /etc/shadow
access: Permission denied
open: Permission denied
```

### 分析

- `access`函数验证的`a.out`进程的**实际用户id**和**实际组id**对`/etc/shadow`是否有访问权限，此时是以builder用户运行`a.out`，及进程`a.out`的实际用户id和实际组id均是builder用户，必然没有访问权限。
- open函数验证的`a.out`进程的**有效用户id**和**有效组id**对`/etc/shadow`是否有访问权限，此时是以builder用户运行`a.out`，及进程`a.out`的实际用户id和实际组id均是builder用户，必然没有访问权限。

## 运行演示2

```bash
[builder@localhost UC]$ sudo chown root a.out 
[builder@localhost UC]$ ls -al
total 16
drwxrwxr-x. 2 builder builder    31 Sep 22 23:24 .
drwxrwxr-x. 9 builder builder   110 Sep 22 23:01 ..
-rwxrwxr-x. 1 root    builder 11272 Sep 22 23:24 a.out
-rw-rw-r--. 1 builder builder   351 Sep 22 23:22 ID.c
[builder@localhost UC]$ ./a.out /etc/shadow
access: Permission denied
open: Permission denied
```

- `access`函数验证的`a.out`进程的**实际用户id**和**实际组id**对`/etc/shadow`是否有访问权限，此时是以builder用户运行`a.out`，及进程`a.out`的实际用户id和实际组id均是builder用户，必然没有访问权限。
- open函数验证的`a.out`进程的**有效用户id**和**有效组id**对`/etc/shadow`是否有访问权限，此时是以builder用户运行`a.out`，及进程`a.out`的实际用户id和实际组id均是builder用户和其所在的组，必然没有访问权限。

## 运行演示3

```bash
[builder@localhost UC]$ sudo chown root a.out 
[builder@localhost UC]$ sudo chmod u+s a.out 
[builder@localhost UC]$ ls -al a.out 
-rwsrwxr-x. 1 root builder 11272 Sep 22 23:22 a.out
[builder@localhost UC]$ ./a.out /etc/shadow
access: Permission denied
open OK
```

### 分析

- `access`函数验证的`a.out`进程的**实际用户id**和**实际组id**对`/etc/shadow`是否有访问权限，此时是以builder用户运行`a.out`，及进程`a.out`的实际用户id和实际组id均是builder用户，必然没有访问权限。
- open函数验证的`a.out`进程的**有效用户id**和**有效组id**对`/etc/shadow`是否有访问权限，此时是以builder用户运行`a.out`，但由于设置了文件模式子（st_mode）中设置一个特殊标志，其含义是“当执行此文件时，将进程的有效用户id设置成文件所有者的用户od(st_uid)”。同理组id也有同样的设置方法。在文件模式字中的这两位称为`设置用户ID位（set-user-id）`和`设置组ID位(set-group-ID)。`此时`sudo chmod u+s a.out`操作底层相当于设置了用户ID位。及此时的a.out进程的有效用户id时root用户，当然可以访问/etc/shadow文件.

### 注：

- 文件模式字可通过stat(2)获取。

## 总结

- 实际用户ID和实际组ID标识了我们究竟是谁。
- 有效用户ID和有效组ID以及附属组ID决定了我们对文件的访问权限。

