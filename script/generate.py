#!/usr/bin/env python
# -*- coding:UTF-8 -*-

# File Name : generate.py
# Purpose :
# Creation Date : 31-05-2017
# Last Modified : Wed May 31 22:55:33 2017
# Created By : Jeasine Ma [jeasinema[at]gmail[dot]com]

import os
import pandas as pd
import pymongo
import json

res = []
res1 = [{'region': 'us', 'movie' : [] }, {'region': 'japan', 'movie' : [] }, {'region': 'china', 'movie' : [] }]

def process(item):
    new_item = {}
    new_item['movie_name'] = item['movie_title']
    new_item['movie_date'] = item['title_year']
    new_item['movie_time'] = item['duration']
    new_item['movie_rate'] = item['imdb_score']
    new_item['movie_level'] = item['content_rating']
    new_item['movie_poster_id'] = "1"
    new_item['movie_name_id'] = "1"
    try:
        new_item['movie_class'] = item['plot_keywords'].split("|")
    except AttributeError as err:
        new_item['movie_class'] = ["Fiction"]
    new_item['movie_abstract'] = "..."
    new_item['movie_detail'] = "..."
    new_item['movie_critic'] = "..."
    new_item['movie_star'] = [{'name' : item['actor_1_name'], 'image_id' : "1"}, {'name' : item['actor_2_name'], 'image_id' : "1"}]
    new_item['movie_director'] = [{'name' : item['director_name'], 'image_id' : "1"}]
    new_item['movie_writer'] = [{'name' : "haha", 'image_id' : "1"}]
    new_item['movie_relate'] = ["A", "B"]
    res.append(new_item)

def import_content(filepath):
    mng_client = pymongo.MongoClient('localhost', 27017)
    mng_db = mng_client['movie_db'] # Replace mongo db name
    collection_name = 'movie' # Replace mongo db collection name
    collection_name1 = 'today_movie'
    db_cm = mng_db[collection_name]
    db_cm1 = mng_db[collection_name1]
    # cdir = os.path.dirname(__file__)
    # file_res = os.path.join(cdir, filepath)
    file_res = filepath

    data = pd.read_csv(file_res)
    data_json = json.loads(data.to_json(orient='records'))

    i = 0
    for item in data_json:
        process(item)
        if item['country'] == 'USA':
            res1[0]['movie'].append(item['movie_title'])
            print("USA")
        elif item['country'] == 'Japan':
            res1[1]['movie'].append(item['movie_title'])
            print("Japan")
        elif item['country'] == 'China':
            res1[2]['movie'].append(item['movie_title'])
            print("China")

    db_cm.remove()
    db_cm.insert(res)

    db_cm1.remove()
    db_cm1.insert(res1)


if __name__ == "__main__":
  filepath = './movie_metadata.csv'  # pass csv file path
  import_content(filepath)

if __name__ == "__main__":
    pass	
