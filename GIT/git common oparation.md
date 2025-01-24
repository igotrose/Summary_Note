# GIT 的基本使用
### GIT 工作示意
![alt text](<git workflow schematic.png>)
### GIT & GITHUB-DESKTOP基本下载安装
省略
## GIT 命令
### 初始化配置
``` bash
1. 初始化仓库
git init
2. 设置用户名
git config --global user.name "<username>"
3. 设置用户邮箱
git config --global user.email "<useremail>"
```
### 文件操作
* 添加文件进入缓存区（暂存更改）
    ``` bash 
    * 添加特定文件
    git add path/to/file
    * 添加多个文件
    git add file1.txt file2.txt
    * 添加当前目录所有更改
    git add .
    ```
* 提交暂存的文件更改到本地仓库
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
* 查看分支
    ``` bash 
    * 查看所有分支
    git branch 
    * 查看远程分支
    git branch -r
    * 查看本地和远程所有分支
    git branch -a 
    ```
* 创建新分支
    ``` bash 
    * 创建分支但不切换
    git branch [branch-name]
    * 创建并切换分支
    git checkout -b [branch-name]
    ```
* 切换分支
    ``` bash 
    git checkout [branch-name]
    ```
* 合并分支
    ```bash
    git merge [branch-name]
    ```
* 删除分支
    ```bash
    git branch -d [branch-name]
    ```
### 日志操作
``` bash
git log  
```
### 比较操作

### 远程操作
- 连接远程仓库
    * ssh方式   
    ``` bash 
    1. 生成SSH密钥（如果没有的话）
    ssh-keygen -t rsa -b 4096 -C "user_email@example.com"
    2. 将SSH公钥添加到远程仓库
    cat ~/.ssh/id_rsa.pub
    3. 在本地仓库进行初始化设置（如果需要的话）
    4. 添加远程仓库
    git remote add origin git@github.com:username/repository.git
    ```
    * https方式
    ```bash
    1. 在本地仓库进行初始化设置（如果需要的话）
    2. 添加远程仓库
    git remote add origin https://github.com/username/repository.git
    ```
- 克隆远程仓库
    * ssh方式
    ``` bash
    1. 克隆整个仓库
    git clone -b git@github.com:username/repository.git
    2. 克隆特定分支
    git clone -b branch-name git@github.com:username/repository.git 
    3. 克隆指定目录
    git clone git@github.com:username/repository.git folder-name
    4. 克隆特定分支的指定目录
    git clone -b branch-name git@github.com:username/repository.git folder-name
    ```
    * https方式
    ``` bash
    1. 克隆整个仓库
    git clone https://github.com/username/repository.git
    2. 克隆特定分支
    git clone -b branch-name https://github.com/username/repository.git
    3. 克隆指定目录
    git clone https://github.com/username/repository.git folder-name
    4. 克隆特定分支的指定目录
    git clone -b branch-name https://github.com/username/repository.git folder-name
    ```
- 拉取远程仓库
    ``` bash
    git pull origin branch-name
    ```
- 推送本地仓库
    ``` bash
    git push origin branch-name
    ```
### 其他操作