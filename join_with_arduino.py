__author__ = 'Lesko'
# Documentation is like sex.
# When it's good, it's very good.
# When it's bad, it's better than nothing.
# When it lies to you, it may be a while before you realize something's wrong.
import distutils.core

from_dir = "D:/workspace/arduino/Robot"
to_dir = "D:/workspace/robot/scratchpad/arduino"

distutils.dir_util.copy_tree(from_dir, to_dir)
