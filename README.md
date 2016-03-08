MP4やMKVといった、動画に埋め込むチャプターファイルの

時間を整えるプログラムです。

## 使い方

```
# 対象のチャプターファイルの時間を
# 100msを加え(correction_time)、hh:mm:ss.mssの下2桁(roundup_time)は切り上げます
ChapterAdjust --correction_time 100 --roundup_time 2 --chapter_file source_file
```

## 出力

上記コマンドですと、以下のように整えられます。

``` before.chap
# before
CHAPTER00=00:00:00.000
CHAPTER00NAME=Avant Title
CHAPTER01=00:01:49.943
CHAPTER01NAME=OP
CHAPTER02=00:03:20.075
CHAPTER02NAME=A-Part
CHAPTER03=00:12:07.018
CHAPTER03NAME=B-Part
CHAPTER04=00:22:30.015
CHAPTER04NAME=ED
CHAPTER05=00:23:59.939
CHAPTER05NAME=Next

# after
CHAPTER00=00:00:00.100
CHAPTER00NAME=Avant Title
CHAPTER01=00:01:50.100
CHAPTER01NAME=OP
CHAPTER02=00:03:20.200
CHAPTER02NAME=A-Part
CHAPTER03=00:12:07.200
CHAPTER03NAME=B-Part
CHAPTER04=00:22:30.200
CHAPTER04NAME=ED
CHAPTER05=00:24:00.100
CHAPTER05NAME=Next

```

[![Build Status](https://travis-ci.org/flowtumn/ChapterAdjust.svg?branch=master)] [![Build Status](https://travis-ci.org/flowtumn/ChapterAdjust.svg?branch=develop)]
