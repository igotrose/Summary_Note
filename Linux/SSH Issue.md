# SSH 遇到的问题
### SSH密钥变更
```cmd
C:\Users\20657>ssh igotu@192.168.75.130
@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
@    WARNING: REMOTE HOST IDENTIFICATION HAS CHANGED!     @
@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
IT IS POSSIBLE THAT SOMEONE IS DOING SOMETHING NASTY!
Someone could be eavesdropping on you right now (man-in-the-middle attack)!
It is also possible that a host key has just been changed.
The fingerprint for the ED25519 key sent by the remote host is
SHA256:S3aXu0S1TnhEnVWLDm7dcTCDcczhFvaou47jGKeC96c.
Please contact your system administrator.
Add correct host key in C:\\Users\\20657/.ssh/known_hosts to get rid of this message.
Offending ECDSA key in C:\\Users\\20657/.ssh/known_hosts:6
Host key for 192.168.75.130 has changed and you have requested strict checking.
Host key verification failed.
```
这个问题是因为之前连接过**192.168.75.130**，这个主机的密钥已经记录在k**nown_hosts**文件中，但因为重装系统或者更新配置的问题导致机密钥更改，和**nown_hosts**文件记录的不一样，出于安全考虑拒接链接
#### 解决方法
1. 查看主机的密钥信息，看是否警告信息一样
    ```bash
    ssh-keygen -lf /etc/ssh/ssh_host_ed25519_key.pub
    ```
1. 删除旧的主机密钥，使用SSH自带的命令删除，在window的Power Shell下运行
    ```cmd
    ssh-keygen -R 192.168.75.130
    ```
