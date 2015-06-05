__author__ = 'Lesko'
# Documentation is like sex.
# When it's good, it's very good.
# When it's bad, it's better than nothing.
# When it lies to you, it may be a while before you realize something's wrong.
from ri2c_lib import MyI2C

"""
This... a funny place...

ri2c - Robot i2c protocol.


Robot will have a lot of sensors. Only I2C is implemented here.

Single arduino will support:
  - 2 motors
  - 2 encoders (attached to interrupts)
  - as many as possible IO pins should be accessible

"""


class Ri2c(object):

    ANS_GET_OK = 22
    ANS_SET_OK = 23

    def __init__(self, i2c_address, debug=False):
        self.i2c_address = i2c_address
        self.debug = debug
        self.i2c = MyI2C(i2c_address=i2c_address, debug=debug)
        self._running = False

    def _debug(self, message):
        if self.debug:
            print "++dbg: {}".format(message)

    def start(self):
        if not self._running:
            self.i2c.open()
            self._running = True
        else:
            self._debug("Communication already running!")

    def stop(self):
        if self._running:
            self.i2c.close()
            self._running = False
        else:
            self._debug("Communication already stopped!")

    def com_get(self, command):
        """Command get eg. commands that "get" something

        :param command:
        """

        pass
