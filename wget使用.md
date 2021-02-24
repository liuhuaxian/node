# wget使用

## wget下载带递归时出现错误，顶层不让你递归！

```bash
wget url //下载该网页将其保存为index.html文件
wget -i index.html -F -B url //解析index.html文件将其的链接加上url进行下载
```

## wget下载src_link网站中所有的rpm格式的文件

```bash
wget -r -c -np -nd $src_link --accept=rpm  --directory-prefix=$dirname
```

