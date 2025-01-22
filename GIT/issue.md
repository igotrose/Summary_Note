# GIT 遇到的问题
### ping 无法访问GitHub
1. 如果是企业内部网络可能会被阻挡，可以尝试切换热点或者其他网络
### ssh 无法访问GitHub
``` bash
ssh: connect to host github.com port 443: Connection timed out
```
#### 在 ~\.ssh\config中
|label|origin|update|
|-----|------|------|
|Host|github.com|github.com|
|HostName|github.com|ssh.github.com|
|User|git|git|
|Port|443|443|
-   **ssh.github.com**是为SSH连接专门优化的端点，它被配置为监听443端口以便于那些无法使用22端口的用户。
- 而直接使用**github.com**并尝试通过443端口连接可能不会成功，因为GitHub的主服务器github.com标准上不监听443端口用于SSH。
### ping 和 ssh 都无法访问github
