## 搭建SSH服务
SSH（Secure Shell）是一种加密的网络协议，为Linux系统提供了安全、加密的远程访问方式。通过正确配置和使用SSH，管理员可以远程管理服务器，传输文件，并确保通信的机密性。
### 安装OpenSSH服务
```bash
sudo apt update
sudo apt install openssh-server
```
### 启动SSH服务
安装完成后，启动 SSH 服务并将其设置为开机自动启动
```bash
sudo systemctl start ssh
sudo systemctl enable ssh
```
### 检查SSH服务状态
```bash
sudo systemctl status ssh
或者
sudo service ssh status
```
### 配置防火墙
```bash
sudo ufw allow ssh
```
### 测试SSH链接
```bash
ssh username@your-server-ip
```