# C-person-example
个人C语言验证总结

编译器: gcc

测试环境：ubuntu debain

IDE：vscode + c/c++插件 + gdb

代码风格：1.C99特性 变量需要时，在创建与初始化，限定代码的作用访问，减少阅读代码心智负担。2.GNU风格。



# **有价值的实例**

## 1.进程 线程

#### 1.线程休眠/唤醒库，实现线程同步

 [thread_manage_test.c](29_thread_pthread/24_thread_manage_test/thread_manage_test.c)

 [sys_thread.c](29_thread_pthread/lib/sys_thread.c)

#### 2.读写锁

 [4_rwlock_自己实现读写锁.c](29_thread_pthread/rwlock读写锁/4_rwlock_自己实现读写锁.c)  [3_rwlock_写读测试.c](29_thread_pthread/rwlock读写锁/3_rwlock_写读测试.c)



## 2.事件

#### 1.netlink 监听内核事件实例

监听网卡拔插事件： [3.2_netlink_link_down_up.c](9_netlink/3.2_netlink_link_down_up.c)  [5.1_network_monitor_link_UpDwon.c](9_netlink/5.1_network_monitor_link_UpDwon.c)

监听USB拔插事件： [1_usb_hotplug.c](9_netlink/1_usb_hotplug.c)

监听网络事件: ip,route变更： [3.1_netlink_route.c](9_netlink/3.1_netlink_route.c)



#### 2.inotify 监听文件状态变化

监听单文件变化： [1_inotify_one_file.c](18_sys/1_inotify/1_inotify_one_file.c)

监听多文件变化实例：  [2_inotify_two_file.c](18_sys/1_inotify/2_inotify_two_file.c)   [3_inotify_实例.c](18_sys/1_inotify/3_inotify_实例.c)



#### 3.select epoll IO多路监听复用

epoll实例 [2_epoll_服务端.c](19_network/epoll/2_epoll_服务端.c)

select实例  [1_socket_server.c](19_network/socket/1_server_client/1_socket_server.c)  [3_AF_UNXI_socket_server.c](19_network/socket/1_server_client/3_AF_UNXI_socket_server.c)



## 3.网络

#### 1.网络设备操作

ifreq获取网络接口ethx 的ip，mac，status: [get_ifc_status.c](19_network/ifreq/1_get_ifc_status.c)  [1_get_sys_net_device_stats.c](19_network/interface/1_get_sys_net_device_stats.c)  [4.1_get_link_ipMaskGwHwFlagsMtu.c](19_network/4.1_get_link_ipMaskGwHwFlagsMtu.c)  [4.2_link_get_tx_rx_statistics.c](19_network/4.2_link_get_tx_rx_statistics.c)

#### 2.ipv6

获取网络接口的ipv6地址与地址类型: [31_get_ifname_ipv6_address.c](19_network/ipv6/31_get_ifname_ipv6_address.c)

测试ipv4/ipv6地址使用有效： [2_check_ipv4_ipv6.c](19_network/2_check_ipv4_ipv6.c) -- `IsValidIP()`



## 4.数据结构

#### 1.list

链表增，遍历，反向  [list_test.c](41_自己写的库/list/list_test.c)

#### 2.queue

to do

#### 3.自定义数据: 无序数组

 [1_unorder_array_无序数组.c](41_自己写的库/4_无序数组/1_unorder_array_无序数组.c)



## 5.字符操作

1.itoa() int转字符  [11_my_itoa_int转字符串.c](16_string/11_my_itoa_int转字符串.c)

2.sscanf 字符解析汇总
- snprintf float长度限定 [3_snprintf_限定float长度.c](1_C语言语法/12_string字符串处理/3_sprintf_字符串格式化/3_snprintf_限定float长度.c)


## 6.系统驱动相关
### 1.按键事件检查 --linux input事件
按键、键盘、触摸屏和鼠标等输入设备 属于input事件
---



# 7.通用库

## 1.日志库

syslog日志库封装 [libxlog.c](4_常用功能\2_Log_C日志库\1_syslog_日志库\libxlog.c)  [libxlog.h](4_常用功能\2_Log_C日志库\1_syslog_日志库\libxlog.h)

- http, mqtt 转发日志