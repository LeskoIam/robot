from pprint import pprint

__author__ = 'Lesko'
# Documentation is like sex.
# When it's good, iaddress=4)
# When it's bad, it's better than nothing.
# When it lies to you, it may be a while before you realize something's wrong.
from Adafruit_I2C import Adafruit_I2C

class MyI2C(object):

    def __init__(self, i2c_address, debug=False):
        self.i2c_address = i2c_address
        self.debug = debug
        self.i2c = Adafruit_I2C(address=i2c_address, debug=debug)
        self._debug("__init__() done")

    @staticmethod
    def _debug(my_str):
        print "++dbg: {}".format(my_str)

    def _write(self, reg, data):
        self.i2c.writeList(reg, data)

    def write(self, my_str, reg=0):
        self._debug("write({}); length: {}".format(my_string, len(my_string)))
        if 1 < len(my_str) > 31:
            raise OverflowError("'my_str' must be between 1 and 31 characters long")
        out = [ord(s) for s in my_str]
        self._write(reg, out)

    def read(self, reg, length):
        return self.i2c.readList(reg, length)

    def read_8(self, reg):
        return self.i2c.readU8(reg)

if __name__ == '__main__':
    import sys
    import time

    my_string = " ".join(sys.argv[1:])
    if len(my_string) < 1:
        my_string = "default test string"

    i2c = MyI2C(i2c_address=8, debug=True)

    i2c.write(my_string)

    time.sleep(0.5)

    a = i2c.read_8(0)
    print "RECEIVED BACK:", a

    # time.sleep(0.5)
    #
    # a = i2c.read_8(7)
    # print "RECEIVED BACK:", a

    pprint(dir(Adafruit_I2C))
