# W5500-codes-base-STM32
## 自己写的一些使用官方库开发W5500的一些例子
## 官方库地址 https://github.com/Wiznet/ioLibrary_Driver.git
------
## W5500_TCP_Client_F1_V1
### 1. 实现了DHCP获取IP
### 2. 实现了阻塞式监听服务器，在接受到服务器的数据后，向服务器返回相同的数据

----------------------
## W5500_TCP_Client_F1_MQTT_V1
###  关于MQTT在W5500下的移植
### 1.在 https://github.com/eclipse/paho.mqtt.embedded-c.git 获取MQTT的代码
### 其中，MQTTPacket/src/目录下为我们需要的库文件，MQTTPacket/samples/下为实例代码
### 2.将MQTTPacket/src/中的文件加入项目，并复制MQTTPacket/samples/中的transport.c和transport.h到相同目录
### 3.建transport中的函数，根据实际的硬件平台进行重写
### 4.测试

