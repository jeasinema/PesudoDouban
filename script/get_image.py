#!/usr/bin/env python3
# -*- coding:UTF-8 -*-

# File Name : get_image.py
# Purpose :
# Creation Date : 04-06-2017
# Last Modified : Sun Jun  4 21:26:20 2017
# Created By : Jeasine Ma [jeasinema[at]gmail[dot]com]

import requests as r
import shutil
import re
import cv2
from lxml import etree
import argparse
import sys

parser = argparse.ArgumentParser(description='run get_image')
parser.add_argument('--url', type=str, default="test.jpg")
parser.add_argument('--width', type=int, default=640)
parser.add_argument('--height', type=int, default=480)
args = parser.parse_args()

def main():
    url = args.url
    img_name = url.split('/')[-1]
    print("Now get {}".format(url))
    response = r.get(url, stream=True)
    with open(img_name, 'wb') as out_file:
        shutil.copyfileobj(response.raw, out_file)

    img = cv.imread(img_name)
    img = cv2.resize(img, (args.width, args.height))
    cv2.imwrite(img_name, img)
    print("{} done".format(img_name))

if __name__ == "__main__":
    main()
