# C-person-example
个人C语言验证总结

编译器: gcc

测试环境：ubuntu debain

IDE：vscode  c/c++插件,  gdb 

构建工具: scons 比Makefile, cmake更简洁的构建脚本

代码风格：

1. C99特性 变量需要时，在创建与初始化，限定代码的作用访问，减少阅读代码心智负担。
2. GNU风格。



# **有价值的实例**

## 1.进程 线程

#### 1.线程休眠/唤醒库，实现线程同步

 [thread_manage_test.c](2_linux编程\8_pthread线程\24_thread_manage_test\thread_manage_test.c) 

 [sys_thread.c](2_linux编程\8_pthread线程\thread_manage\sys_thread.c) 

#### 2.读写锁

 [1_rwlock_读写锁实例.c](2_linux编程\8_pthread线程\rwlock读写锁\1_rwlock_读写锁实例.c) 

 [2_rwlock_读写读测试.c](2_linux编程\8_pthread线程\rwlock读写锁\2_rwlock_读写读测试.c) 

 [3_rwlock_写读测试.c](2_linux编程\8_pthread线程\rwlock读写锁\3_rwlock_写读测试.c) 
 [5_rwlock_读写锁_带输入命令测试.c](2_linux编程\8_pthread线程\rwlock读写锁\5_rwlock_读写锁_带输入命令测试.c) 

## 2.事件

#### 1.netlink 监听内核事件实例

监听网卡拔插事件：

 [3.2_netlink_link_down_up.c](5_第3方库\9_netlink\3.2_netlink_link_down_up.c) 

 [5.1_network_monitor_link_UpDwon.c](5_第3方库\9_netlink\5.1_network_monitor_link_UpDwon.c) 

监听USB拔插事件：

 [1_usb_hotplug.c](5_第3方库\9_netlink\1_usb_hotplug.c) 

监听网络事件: ip,route变更：

 [2_netlink_uevent.c](5_第3方库\9_netlink\2_netlink_uevent.c) 

 [3.1_netlink_route.c](5_第3方库\9_netlink\3.1_netlink_route.c) 



#### 2.inotify 监听文件状态变化

监听单文件变化：

 [1_inotify_one_file.c](2_linux编程\2_env环境变量\18_sys\1_inotify\1_inotify_one_file.c) 

监听多文件变化实例：

 [3_inotify_实例.c](2_linux编程\2_env环境变量\18_sys\1_inotify\3_inotify_实例.c) 

 [2_inotify_two_file.c](2_linux编程\2_env环境变量\18_sys\1_inotify\2_inotify_two_file.c) 



#### 3.select epoll IO多路监听复用

epoll实例 

 [2_epoll_服务端.c](2_linux编程\25_网络编程\19_network\epoll\2_epoll_服务端.c) 

 [1_server_epoll.c](2_linux编程\25_网络编程\19_network\epoll\1_server_epoll.c) 

select实例 

 [1_socket_server.c](2_linux编程\25_网络编程\19_network\socket\1_server_client\1_socket_server.c) 

 [2_socket_client.c](2_linux编程\25_网络编程\19_network\socket\1_server_client\2_socket_client.c) 

 [3_AF_UNXI_socket_server.c](2_linux编程\25_网络编程\19_network\socket\1_server_client\3_AF_UNXI_socket_server.c) 

 [4_AF_UNIX_socket_client.c](2_linux编程\25_网络编程\19_network\socket\1_server_client\4_AF_UNIX_socket_client.c) 

 [5_monitor_event.c](2_linux编程\25_网络编程\19_network\socket\1_server_client\5_monitor_event.c) 

 [6_event_client_A.c](2_linux编程\25_网络编程\19_network\socket\1_server_client\6_event_client_A.c) 

 [6_event_client_B.c](2_linux编程\25_网络编程\19_network\socket\1_server_client\6_event_client_B.c) 

## 3.网络

#### 1.网络设备操作

ifreq获取网络接口ethx 的ip，mac，status:

 [1_get_ifc_status.c](2_linux编程\25_网络编程\19_network\ifreq\1_get_ifc_status.c) 

 [2_get_interface_mac.c](2_linux编程\25_网络编程\19_network\interface\2_get_interface_mac.c) 

 [1.1_ifconfig_get_stats.c](2_linux编程\25_网络编程\19_network\interface\1.1_ifconfig_get_stats.c) 

 [1_get_sys_net_device_stats.c](2_linux编程\25_网络编程\19_network\interface\1_get_sys_net_device_stats.c) 

 [4.2_link_get_tx_rx_statistics.c](2_linux编程\25_网络编程\19_network\4.2_link_get_tx_rx_statistics.c) 

 [4.1_get_link_ipMaskGwHwFlagsMtu.c](2_linux编程\25_网络编程\19_network\4.1_get_link_ipMaskGwHwFlagsMtu.c) 

#### 2.ipv6

获取网络接口的ipv6地址与地址类型:

 [32_get_ipv6_address_type.c](2_linux编程\25_网络编程\19_network\ipv6\32_get_ipv6_address_type.c) 

 [31_get_ifname_ipv6_address.c](2_linux编程\25_网络编程\19_network\ipv6\31_get_ifname_ipv6_address.c) 

测试ipv4/ipv6地址使用有效:

 [2_check_ipv4_ipv6.c](2_linux编程\25_网络编程\19_network\2_check_ipv4_ipv6.c) 



## 4.数据结构

#### 1.list

链表增，遍历，反向  

 [test_list.c](3_算法_数据结构\1_list链表\test_list.c) 

 [list.c](3_算法_数据结构\1_list链表\list.c) 

#### 2.queue

Todo

#### 3.自定义数据: 无序数组

Todo

## 5.字符操作

1.itoa() int转字符  

 [11_my_itoa_int转字符串.c](1_C语言语法\12_string字符串处理\11_my_itoa_int转字符串.c) 

2.sscanf 字符解析汇总 

 [15.3_sscanf.c](1_C语言语法\12_string字符串处理\15.3_sscanf.c) 

 [15.4_sscanf.c](1_C语言语法\12_string字符串处理\15.4_sscanf.c) 

 [15.5_sscanf.c](1_C语言语法\12_string字符串处理\15.5_sscanf.c) 

 [15.5_sscanf_get_oneline.c](1_C语言语法\12_string字符串处理\15.5_sscanf_get_oneline.c) 

 [15.6_sscanf.c](1_C语言语法\12_string字符串处理\15.6_sscanf.c) 

 [15_sscanf_pro.c](1_C语言语法\12_string字符串处理\15_sscanf_pro.c) 

 [16.1_get_oneline.c](1_C语言语法\12_string字符串处理\16.1_get_oneline.c) 

 [16_get_oneline.c](1_C语言语法\12_string字符串处理\16_get_oneline.c) 

 [16_sscanf.c](1_C语言语法\12_string字符串处理\16_sscanf.c) 


## 6.系统驱动相关
### 1.按键事件检查 --linux input事件
按键、键盘、触摸屏和鼠标等输入设备 属于input事件
---