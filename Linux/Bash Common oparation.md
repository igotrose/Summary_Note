# Linux的常用命令
### apt 
```bash
apt [options] [command] [package ...]
```
apt 指令一般需要root用户的权限
#### apt常用操作
| 操作 | 命令 | 说明 |
|------|------------------------|------------------------------------------------------------|
| 更新软件包列表 | `apt update` | 获取最新的软件信息，但不会实际安装或升级任何软件 |
| 升级已安装的软件包 | `apt upgrade` | 升级已安装的软件包 |
| 升级所有软件包 | `apt full-upgrade` | 升级所有软件包（包括可能需要移除旧软件的情况） |
| 安装新软件 | `apt install <package>` | 安装新软件 |
| 移除软件包 | `apt remove <package>` | 移除软件包，但保留配置文件 |
| 彻底删除软件包 | `apt purge <package>` | 彻底删除软件包（包括配置文件） |
| 清理无用依赖 | `apt autoremove` | 删除系统中已安装但不再被其他软件依赖的包 |
| 清理本地缓存 | `apt clean` | 删除 `/var/cache/apt/archives/` 目录中的已下载软件包 |
| 搜索软件包 | `apt search <package>` | 搜索软件包 |
| 查看软件包信息 | `apt show <package>` | 查看软件包详细信息 |
| 列出已安装软件 | `apt list --installed` | 列出已安装的软件包 |

### tar
```bash
tar [options] [file]   
```
#### tar常用操作
| 选项 | 作用 |
|------|--------------------------------------------------|
| `-c` | 创建新归档文件（create） |
| `-x` | 解压归档文件（extract） |
| `-v` | 显示详细信息（verbose） |
| `-f` | 指定归档文件名（file） |
| `-z` | 使用 gzip 压缩或解压缩（gzip） |
| `-j` | 使用 bzip2 压缩或解压缩（bzip2） |
| `-J` | 使用 xz 压缩或解压缩（xz） |
| `-C` | 指定解压目标目录（change directory） |
| `-t` | 查看归档文件内容（list） |
