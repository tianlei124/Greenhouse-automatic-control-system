# 生态棚室自控系统

## 引言
"生态棚室自控系统"是基于农业大棚模型建立的自动调节系统。项目本身的代码实现比较简单，这里采用的是Python+C混合的方式，但是并不涉及两者之间的调用。事实上现在只有一个Python代码文件，即利用爬虫获取‘墨迹天气’的天气信息的 WeatherForecast.py。
### 效果图
![效果图](https://github.com/tianlei124/Greenhouse-automatic-control-system/raw/master/photos/效果图.JPG)

## 平台
项目是运行于树莓派这一平台的，这里使用的树莓派是Raspberry Pi3 B版。因为操作GPIO的代码是使用C语言写的，所采用的引脚定义方式自然就是wiringPi方式。如果想要移植到其他版本的树莓派或者使用别的语言操作GPIO，请根据实际情况修改引脚定义方式。

## (传感器&动作模块)的引脚对应表
|    传感器        | wiringPi| BCM         | BOARD |
| ---------------- | :-----: | :---------: | ----: |
|DHT11温、湿度传感器|    7    |  4          |  7    |
|    继电器2口     |    5    |  24         |  18   |
| 土壤湿度传感器    |    -    |  -          |   -   |
|    光强传感器    |    3    | 22          |   15  |
|    补光灯        |    1    | 18          |   12  |
|ULN2003(IN1~IN4)|(0,2,4,5)|(17,27,23,24)|(11,13,16,18)|

## （传感器&动作模块）驱动方法

### DHT11温度、湿度传感器（摘自DHT11 datasheet）
![DHT11温度、湿度传感器](https://github.com/tianlei124/Greenhouse-automatic-control-system/raw/master/photos/DHT11温、湿度传感器.JPG)

#### 引脚说明
* VDD 供电3.3～5.5V
* DATA 串行数据，单总线
* GND 接地/电源负极

#### 串行通信

DATA用于微处理器和DHT11之间的通讯和同步，采用单总线数据格式，一次传输40bit数据，高位先出。

#### 数据格式
8bit湿度证书数据+8bit湿度小数数据+8bit温度整数数据+8bit温度小数数据+8bit校验位
注：（其中温、湿度小数部分为0...其实我也不太懂为什么这么做）

校验位数据定义：
8bit湿度证书数据+8bit湿度小数数据+8bit温度整数数据+8bit温度小数数据 = 8bit校验位

#### 外设读取步骤
主机和从机之间的通信可通过如下几个步骤完成


**步骤一:**
DHT11 上电后（DHT11 上电后要等待 1S 以越过不稳定状态,在此期间不能发送任何指令），测试环境温湿度数据，并记录数据，同时 DHT11 的 DATA 数据线由上拉电阻拉高一直保持高电平；此时 DHT11 的DATA 引脚处于输入状态，时刻检测外部信号。

**步骤二:**
微处理器的 I/O 设置为输出同时输出低电平(实际上，应该在设置为输出之后先配置为高电平在配置为低电平，要体现出来由高变低的边沿)，且低电平保持时间不能小于 18ms，然后微处理器的 I/O设置为输入状态，由于上拉电阻，微处理器的 I/O 即 DHT11 的 DATA 数据线也随之变高，等待 DHT11 作出回答信号

**步骤三:**
DHT11 的 DATA 引脚检测到外部信号有低电平时，等待外部信号低电平结束，延迟后 DHT11 的 DATA引脚处于输出状态，输出 80 微秒的低电平作为应答信号，紧接着输出 80 微秒的高电平通知外设准备接收数据，微处理器的 I/O 此时处于输入状态，检测到 I/O 有低电平（DHT11 回应信号）后，等待 80 微秒的高电平后接收数据。接收每一位数据前都有80微妙的准备时间

**步骤四：**
由 DHT11 的 DATA 引脚输出 40 位数据，微处理器根据 I/O 电平的变化接收 40 位数据，位数据“ 0”的格式为： 50 微秒的低电平和 26-28 微秒的高电平，位数据“ 1”的格式为： 50 微秒的低电平加 70微秒的高电平。

结束信号:
DHT11 的 DATA 引脚输出 40 位数据后，继续输出低电平 50 微秒后转为输入状态，由于上拉电阻随
之变为高电平。但 DHT11 内部重测环境温湿度数据，并记录数据，等待外部信号的到来。


### 土壤湿度传感器
![土壤湿度传感器](https://github.com/tianlei124/Greenhouse-automatic-control-system/raw/master/photos/土壤湿度传感器.JPG)




### 二路继电器
![二路继电器](https://github.com/tianlei124/Greenhouse-automatic-control-system/raw/master/photos/二路继电器.JPG)




### 光强传感器
![光强传感器](https://github.com/tianlei124/Greenhouse-automatic-control-system/raw/master/photos/光强传感器.JPG)




### 补光灯

### ULN2003&步进电机
![ULN2003&步进电机](https://github.com/tianlei124/Greenhouse-automatic-control-system/raw/master/photos/ULN2003&步进电机.JPG)



