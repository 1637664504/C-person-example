# C-person-example
个人C语言验证总结



# **有价值的实例**

## 1.进程 线程

#### 1.线程休眠/唤醒库，实现线程同步

 [thread_manage_test.c](29_thread_pthread\24_thread_manage_test\thread_manage_test.c) 

 [sys_thread.c](29_thread_pthread\lib\sys_thread.c) 



## 2.事件

#### 1.netlink 监听内核事件实例

监听网卡拔插事件： [3.2_netlink_link_down_up.c](9_netlink\3.2_netlink_link_down_up.c)  [5.1_network_monitor_link_UpDwon.c](9_netlink\5.1_network_monitor_link_UpDwon.c) 

监听USB拔插事件： [1_usb_hotplug.c](9_netlink\1_usb_hotplug.c) 

监听网络事件: ip,route变更： [3.1_netlink_route.c](9_netlink\3.1_netlink_route.c) 



#### 2.inotify 监听文件状态变化

监听单文件变化： [1_inotify_one_file.c](18_sys\1_inotify\1_inotify_one_file.c) 

监听多文件变化实例：  [2_inotify_two_file.c](18_sys\1_inotify\2_inotify_two_file.c)   [3_inotify_实例.c](18_sys\1_inotify\3_inotify_实例.c) 

select/poll/epoll 监听文件变化：to do



## 3.网络

#### 1.网络设备操作

ifreq获取网络接口ethx 的ip，mac，status: [get_ifc_status.c](19_network\ifreq\1_get_ifc_status.c)  [1_get_sys_net_device_stats.c](19_network\interface\1_get_sys_net_device_stats.c)  [4.1_get_link_ipMaskGwHwFlagsMtu.c](19_network\4.1_get_link_ipMaskGwHwFlagsMtu.c)  [4.2_link_get_tx_rx_statistics.c](19_network\4.2_link_get_tx_rx_statistics.c) 

#### 2.ipv6

获取网络接口的ipv6地址与地址类型: [31_get_ifname_ipv6_address.c](19_network\ipv6\31_get_ifname_ipv6_address.c) 

测试ipv4/ipv6地址使用有效： [2_check_ipv4_ipv6.c](19_network\2_check_ipv4_ipv6.c) -- `IsValidIP()`



## 4.数据结构

#### 1.list

链表增，遍历，反向  [list_test.c](41_自己写的库\list\list_test.c) 

#### 2.queue

to do



## 5.字符操作

1.itoa() int转字符  [11_my_itoa_int转字符串.c](16_string\11_my_itoa_int转字符串.c) 

2.sscanf 字符解析汇总 

---