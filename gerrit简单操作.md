# gerrit简单操作

- 将自己主机的ssh公钥添加到gerrit服务器

  ```bash
  ssh-keygen -t rsa //一路回车
  cat ~/.ssh/id_rsa.pub //将出现的屏幕上的所有，复制到服务器上。(服务器上右上角设置按钮下ssh key)
  ```

  参见：[向服务器添加key](https://blog.csdn.net/zhoulw_25/article/details/83787262)

- 同步远程仓库，并设置用户

  ```bash
  git clone url
  git config --global user.name "lhx"
  git config --global user.email lhx@example.com
  ```

- 将修改文件保存到本地仓库。

  ```bash
  git status //查看工作区中的修改文件
  git add .  //将工作区中的修改的过的文件添加的暂存区中
  git commit -m "提交说明" //将暂存区中的文件，添加到本地仓库中
  ```

- 将本地文件推送到远程仓库中

  ```bash
  scp -p -P 29418 liuhuaxian@gerrit.chinaredflag.cn:hooks/commit-msg "test1/.git/hooks/"
  git push origin HEAD:refs/for/master
  ```

  