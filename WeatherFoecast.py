#!/usr/bin/env python3
#-*- coding:utf-8 -*-

import requests
from datetime import datetime,timedelta
from bs4 import BeautifulSoup

headers = {
    
   'User-Agent': 'Mozilla/5.0 (Windows NT 10.0; Win64; x64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/52.0.2743.116 Safari/537.36 Edge/15.15063'
}

def get_weather():
    res = requests.get('http://tianqi.moji.com/', headers=headers)

    soup = BeautifulSoup(res.text,"html.parser")
    temp = soup.find('div',attrs={'class':'wea_weather clearfix'}).em.getText()
    weather = soup.find('div',attrs={'class':'wea_weather clearfix'}).b.getText()
    humi = soup.find('div',attrs={'class':'wea_about clearfix'}).span.getText()
    wind = soup.find('div', attrs={'class': 'wea_about clearfix'}).em.getText()
    aqi = soup.find('div',attrs={'class':'wea_alert clearfix'}).em.getText()

    today = datetime.now().date().strftime('%Y年%m月%d日')

    text = '今天是%s,天气%s,室外温度%s°C,%s,%s,空气质量%s.'%(today,weather,temp,humi,wind,aqi)

    return text


text = get_weather()
print(text)