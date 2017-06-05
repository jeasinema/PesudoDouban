#!/usr/bin/env python
# -*- coding:UTF-8 -*-

# File Name : slice.py
# Purpose :
# Creation Date : 04-06-2017
# Last Modified : Mon Jun  5 21:39:27 2017
# Created By : Jeasine Ma [jeasinema[at]gmail[dot]com]

import jieba
import numpy as np
import os
import pandas as pd
import pymongo
import json

def main(*args, **kwargs):
    seg_list = jieba.cut_for_search()
    ret = np.array(seg_list)
    

if __name__ == "__main__":
    main()
