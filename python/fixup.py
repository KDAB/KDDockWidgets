#!/usr/bin/python3
"""
Script to fix bugs in code generated by shiboken-generator vr2
"""

import sys
import re

# Remove namespace from default flag value
# this is a shiboken2 bug fixed on shiboken6
def removeExtraNamespaceForDefaultEnumValue(filename):
    regex = re.compile(r"\s=\s[^\s]+::{}")
    newContent = ""
    with open(filename) as f:
        for line in f:
            newContent += re.sub(regex, ' = {}', line)

    with open(filename, "w") as f:
        f.write(newContent)


# Usage: <script> <list-of-files>
# It will fix the file inplace
if __name__ == '__main__':
    for filename in sys.argv[1:]:
        print("Fixup: {}".format(filename))
        removeExtraNamespaceForDefaultEnumValue(filename)