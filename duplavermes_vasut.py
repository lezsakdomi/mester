#!/usr/bin/env python3
# coding=utf8
# the above tag defines encoding for this document and is for Python 2.x compatibility

import re

regex = re.compile(r"^([123 ]*[234 ]*|[134 ]*[124 ]*[123 ]*)[34 ]*0?$")

for i in range(0, int(input())):
    if regex.match(input().strip()):
        print("IGEN")
    else:
        print("NEM")
