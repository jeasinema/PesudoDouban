#!/usr/bin/env python3
# -*- coding:UTF-8 -*-

# File Name : get_movie.py
# Purpose :
# Creation Date : 04-06-2017
# Last Modified : Sun Jun  4 21:26:57 2017
# Created By : Jeasine Ma [jeasinema[at]gmail[dot]com]

from lxml import etree
import requests as r
import re

region = ["top100_chinese", "top100_japan", "top100_south_korea", "hot_top10", "top100"]
url = "http://www.mtime.com/top/movie/{}/"
suffix = "index-{}.html"
xpath = "//*[@id=\"asyncRatingRegion\"]/li[{}]/div[3]/h2/a"

def main(*args, **kwargs):
    for reg in region:
        response = []
        response.append(r.request("GET", url.format(reg)))
        for i in range(2,11):
            response.append(r.request("GET", url.format(reg)+suffix.format(i)))
        
        ret = []
        for i in response:
            for j in range(1,11):
                try:
                    title = etree.HTML(i.text).xpath(xpath.format(j))[0].text
                    ret.append(title.split()[0])
                except Exception as e:
                    pass
        ret.sort()

        with open("{}".format(reg), "w+") as f:
            for i in ret:
                f.write("{}\n".format(i))
                print(i)

        print(len(ret))


if __name__ == "__main__":
    main()
