# Centos系统中用mock构建rpm的方法

**前言**

在centos下执行`rpmbuild -ba package.spec`的时候，通常会要求系统也安装对应的依赖包，这样就会导致系统装上许多没用的软件包，占用空间。于是搜索了一下，发现可以通过`mock`命令来解决这个问题。

**构建方法**

首先是安装`mock`，由于`mock`是在`epel`仓库里的，所以还需要先装`epel`仓库

```
`yum -y ``install` `epel-release``yum -y ``install` `mock`
```

通常情况下使用`rpmbuild`会新开一个用户，比如`builder`，这样就不会污染系统环境。我们需要把`builder`用户加入`mock`用户组

```
`usermod` `-a -G mock builder`
```

`mock`下使用`rebuild`需要src.rpm文件，所以如果只有.spec文件的话，需要先生成src.rpm文件

```
`rpmbuild -bs package.spec`
```

这样在SRPM目录下就会生成一个src.rpm文件了，然后就可以通过`mock`命令来`rebuild rpm`文件

首先需要初始化`mock`环境，在/etc/mock文件夹下有各个环境的配置文件，比如centos 6就是epel-6-x86_64，初始化命令就是：

```
`mock -r epel-6-x86_64 --init`
```

初始化完毕之后就可以开始构建了

```
`mock -r epel-6-x86_64 rebuild package-1.1-1.src.rpm`
```

构建完毕，`rpm`文件会存放在/var/lib/mock/epel-6-x86_64/result目录下。当然我们可以通过`–resultdir`参数来指定`rpm`文件的生成目录

```
`mock -r epel-6-x86_64 rebuild package-1.1-1.src.rpm --resultdir=``/home/builder/rpms`
```

最后执行`clean`命令清理环境

```
`mock -r epel-6-x86_64 --clean`
```

**总结**

以上就是关于Centos下使用mock构建rpm的全部内容了，希望本文的内容对大家的学习或者工作能带来一定的帮助，如果有疑问大家可以留言交流。