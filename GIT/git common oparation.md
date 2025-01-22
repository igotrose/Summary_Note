# GIT 的基本使用
### GIT 工作示意
![alt text](<git workflow schematic.png>)
### GIT & GITHUB-DESKTOP基本下载安装
省略
## GIT 命令
### 初始化配置
* 初始化仓库
``` bash
git init
```
* 设置用户名
``` bash 
git config --global user.name "<username>"
```
* 设置用户邮箱
``` bash 
git config --global user.email "<useremail>"
```
### 文件操作
* 添加文件进入缓存区
``` bash 
git add [file]
```
* 添加文件提交到本地仓库
``` bash 
git commit -m "<commit info>"
```
* 将文件从缓存区和工作区中删除
``` bash 
git rm [file]
```
* 移动或者重命名工作区的文件
``` bash 
git mv [file]
```
### 分支操作
* 查看或者创建分支
``` bash 
git branch 
```
* 恢复文件或者切换创建分支
``` bash
git checkout
```
### 日志操作
``` bash
git log  
```
### 比较操作

### 远程操作
``` bash 
```
### 其他操作