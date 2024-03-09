import re
# 爬取数据与使用正则表达式
import requests
# 导入requests包来作为爬虫的基础
import time
# 使用sleep函数

if __name__ == "__main__":
# 函数入口，防止程序从模块较大的程序运行

    url1 = 'https://cn.bing.com/search?q='
    while 1:

        file = open("C:\\Users\\33746\\Desktop\\low.txt","r",encoding='gb2312')
        log = file.read()
        file.close()

        file = open("C:\\Users\\33746\\Desktop\\high.txt", "r", encoding='gb2312')
        log2 = file.read()
        file.close()

        if log != ' ' or log2 != ' ':
            print("已搜索完成，等待下一步")
            time.sleep(0.5)
            continue
        file = open("C:\\Users\\33746\\Desktop\\data.txt","r",encoding='gb2312')
        find = file.read()
        file.close()
        print("搜寻内容："+find)
        url2 = '生长温度范围&sc=1-8&sk=&cvid=CFE7CD7774434B4B9EC92AA0777F013C&ghsh=0&ghacc=0&ghpl='
        url = url1+find+url2
        # 设置爬取数据网站的路由url
        print(url)
        header = {
            'User-Agent': 'Mozilla/5.0 (Windows NT 10.0; Win64; x64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/115.0.0.0 Safari/537.36 Edg/115.0.1901.200'
        }
        # User Agent，使得爬虫伪装成为正常的浏览器请求从而可以访问爬取内容
        requests.encoding = 'utf-8'
        response = requests.get(url=url,headers=header)
        # 修改文件形式为utf-8的形式
        text = response.text
        # requests包get响应格式（响应路由，响应变量名字，UA伪装机制“即是将爬虫伪装成为一个正常的浏览器，需要在网页上获取相应浏览器信息”）
        ex1 = r'\d+°'
        info_list0 = re.findall(ex1, text)
        ex2 = r'\d+℃'
        info_list = re.findall(ex2, text) + info_list0
        ex3 = r'\d+度'
        info_list1 = re.findall(ex3, text) + info_list
        # 正则表达式读取所有关于温度的数据

        time.sleep(2)
        info_list = info_list + info_list1
        print(info_list)

        key1 = -10
        key2 = 50
        key3 = 0
        num = len(info_list)

        if num != 0:
            # 使用正则表达式提取内容
            info_list = [item[:-1] for item in info_list]
            info_list = [int(item) for item in info_list]
            # 将获取到的数据全部变为整数类型，并且删除最后一个摄氏度字符
            for num in info_list:
                if info_list[key3] > 50 or info_list[key3] < -10:
                    print("num erron")
                    info_list[key3] = 22
                key3 = key3 + 1
            # 判读错误温度参数
            info_list.sort()
            # 将列表排序
            print(info_list)

            key3 = 0
            keynum = 0
            while key3 < len(info_list) // 4:
                key3 = key3 + 1
                keynum = keynum + info_list[key3]

            lownum = keynum // key3 + 2
            print(lownum)

            key3 = len(info_list) - 1
            keynum = 0
            while key3 > 3 * len(info_list) // 4:
                key3 = key3 - 1
                keynum = keynum + info_list[key3]

            highnum = keynum // (len(info_list) // 4) - 2
            print(highnum)
            # 获取最高温度和最低温度的算法
            file = open("C:\\Users\\33746\\Desktop\\low.txt", "w")
            file.write(str(lownum))
            file.close()

            file = open("C:\\Users\\33746\\Desktop\\high.txt", "w")
            file.write(str(highnum))
            file.close()

        while info_list == []:
            print("重新爬取")
            time.sleep(1)
            requests.encoding = 'utf-8'
            response = requests.get(url=url, headers=header)

            # 修改文件形式为utf-8的形式
            time.sleep(1)
            # requests包get响应格式（响应路由，响应变量名字，UA伪装机制“即是将爬虫伪装成为一个正常的浏览器，需要在网页上获取相应浏览器信息”）
            ex1 = r'\d+\w'
            info_list = re.findall(ex1, text, re.IGNORECASE)

            print(info_list)

            key1 = -10
            key2 = 50
            key3 = 0
            num = len(info_list)
            # 使用正则表达式提取内容
            info_list = [item[:-1] for item in info_list]
            info_list = [int(item) for item in info_list]
            # 将获取到的数据全部变为整数类型，并且删除最后一个摄氏度字符
            for num in info_list:
                if info_list[key3] > 50 or info_list[key3] < -10:
                    print("num erron")
                    info_list[key3] = 22
                key3 = key3 + 1
            # 判读错误温度参数
            info_list.sort()
            # 将列表排序
            print(info_list)

            key3 = len(info_list) // 4
            keynum = 0
            while key3 < len(info_list) // 2:
                key3 = key3 + 1
                keynum = keynum + info_list[key3]

            lownum = keynum // key3 + 2
            print(lownum)

            key3 = 3 * len(info_list) // 4
            keynum = 0
            while key3 > len(info_list) // 2:
                key3 = key3 - 1
                keynum = keynum + info_list[key3]

            highnum = keynum // (len(info_list) // 4) - 2
            print(highnum)
            # 获取最高温度和最低温度的算法
            file = open("C:\\Users\\33746\\Desktop\\low.txt", "w")
            file.write(str(lownum))
            file.close()

            file = open("C:\\Users\\33746\\Desktop\\high.txt", "w")
            file.write(str(highnum))
            file.close()
            # 将读取到的内容存放在列表内

        print("爬取完成")
        time.sleep(3)
