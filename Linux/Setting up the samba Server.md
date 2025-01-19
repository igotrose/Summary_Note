# 搭建samba 服务器
实现从 **window** 访问并写入 **Linux** 的 samba共享文件夹
## 更新系统并安装Samba
``` bash
apt update
apt install samba
```
## 检查Samba是否安装成功
``` bash
samba --version
```
## 创建共享文件夹
    ``` bash
    mkdir -p workplace
    chomod -R 777 workplace
    ```
## 创建Samba用户并设置密码    
``` bash
smbpasswd -a igotu
```
## 编辑Samba的配置文件
``` bash
vim /etc/samba/smb.conf
```
### 在文件末尾添加
``` ini
[workplace]
comment = samba share folder
path = /home/igotu/workplace
public = yes
writable = yes
available = yes
browseable = yes
valid users = igotu
guest ok = yes
```
## 设置防火墙允许Samba
``` bash
ufw allow samba
ufw reload
```
## 确保windows和linux在同一网络
``` bash
ping xxx.xxx.xxx.xxx
```
## 刷新一下windows samba的缓存，在window的cmd中运行
``` bash
net use * /delete
```