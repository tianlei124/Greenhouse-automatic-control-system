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

### DHT11温度、湿度传感器
![DHT11温度、湿度传感器](https://github.com/tianlei124/Greenhouse-automatic-control-system/raw/master\photos\DHT11温、湿度传感器.JPG)

### 土壤湿度传感器
![土壤湿度传感器](https://github.com/tianlei124/Greenhouse-automatic-control-system/raw/master\photos\土壤湿度传感器.JPG)

### 二路继电器
![二路继电器](https://github.com/tianlei124/Greenhouse-automatic-control-system/raw/master\photos\二路继电器.JPG)

### 光强传感器
![光强传感器](https://github.com/tianlei124/Greenhouse-automatic-control-system/raw/master\photos\光强传感器.JPG)

### 补光灯

### ULN2003&步进电机
![ULN2003&步进电机](https://github.com/tianlei124/Greenhouse-automatic-control-system/raw/master\photos\ULN2003&步进电机.JPG)
