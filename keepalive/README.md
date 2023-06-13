## TCP Keep-Alive
最少需要经过 2 小时 11 分 15 秒才可以发现一个“死亡”连接,系统配置如下：
net.ipv4.tcp_keepalive_time(7200)
net.ipv4.tcp_keepalive_intvl(75)
net.ipv4.tcp_keepalve_probes(9)

