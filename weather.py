#!/usr/bin/env python3
#-*- coding:utf-8 -*-

import requests
from datetime import datetime
from bs4 import BeautifulSoup

headers = {
    'Connection': 'Keep-Alive',
    'Accept': 'text/html,application/xhtml+xml,*/*',
    'Accept_Language': 'en-US,en;q=0.8,zh-Hans-CN;q=0.5,zh-Hans;q=0.3',
    'User_Agent': 'Mozilla/5.0 (Windows NT 6.3; WOW64; Trident/7.0; rv:11.0) like Gecko',
    'Accept-Encoding': 'gzip, deflate',
}

def get_weather():
    res = requests.get('http://tianqi.moji.com/', headers=headers)
    soup = BeautifulSoup(res.text,"html.parser")

    tem = soup.find('div',attrs={'class':'wea_weather clearfix'}).em.getText()
    wea = soup.find('div',attrs={'class':'wea_weather clearfix'}).b.getText()
    moi = soup.find('div',attrs={'class':'wea_about clearfix'}).span.getText()
    win = soup.find('div',attrs={'class':'wea_about clearfix'}).em.getText()
    aqi = soup.find('div',attrs={'class':'wea_alert clearfix'}).em.getText()

    today = datetime.now().strftime('%Y-%m-%d %H:%M')
    text = '现在是%s,天气%s,室外温度%s°C,%s,%s,空气质量%s.'%(today,wea,tem,moi,win,aqi)

    return text


text = get_weather()
print(text)
