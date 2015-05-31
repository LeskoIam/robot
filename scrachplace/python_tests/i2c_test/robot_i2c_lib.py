__author__ = 'Lesko'
# Documentation is like sex.
# When it's good, iaddress=4)
# When it's bad, it's better than nothing.
# When it lies to you, it may be a while before you realize something's wrong.


"""
To be used with slaveRecive_pyBBIO.ino
"""
import bbio


class MyI2C(object):

    def __init__(self, i2c_address, debug=False):
        self.i2c_address = i2c_address
        self.debug = debug
        self.bbio = bbio
        self.i2c = bbio.I2C2
        self._debug("__init__() done")

    def _debug(self, message):
        if self.debug:
            print "++dbg: {}".format(message)

    def _write(self, i2c_address, data):
        if i2c_address is None:
            i2c_address = self.i2c_address
        self.i2c.write(i2c_address, data)

    def open(self):
        return self.i2c.open()
    
    def close(self):
        return self.i2c.close()

    def write_list(self, tx_list, i2c_address=None):
        if len(tx_list) > 32:
            raise OverflowError("String must be shorter or equal to 32")
        self._debug("write('{}'); length: {}".format(str(tx_list), len(tx_list)))
        self._write(i2c_address, tx_list)

    def write_string(self, tx_string, i2c_address=None):
        """Write <tx_string> to i2c device. String must be shorter then 32 characters (32 bytes)

        :param tx_string: String to send to i2c device
        :param i2c_address: Address of the i2c device
        :raise OverflowError: If string is longer then 32 characters (bytes)
        """
        if len(tx_string) > 32:
            raise OverflowError("String must be shorter or equal to 32")
        self._debug("write('{}'); length: {}".format(tx_string, len(tx_string)))
        out = [ord(s) for s in tx_string]
        self._debug("raw my_string: {}".format(str(out)))
        self._write(i2c_address, out)

    def read(self, rx_len, i2c_address=None):
        """Read <rx_len> bytes from i2c device

        :param rx_len: Number of characters (bytes) to read from i2c device
        :param i2c_address: Address of the i2c device
        :return: Raw data received from i2c device
        """
        if i2c_address is None:
            i2c_address = self.i2c_address
        return self.i2c.read(i2c_address, rx_len)

    def transaction(self, tx_data, rx_len, delay=10, i2c_address=None):
        """First send <tx_string> then read <rx_len> characters (bytes)

        :param tx_data: String to send to i2c device
        :param rx_len: Number of characters (bytes) to read from i2c device
        :param delay: Delay between read and write, must be some non-zero value (milliseconds)
        :param i2c_address: Address of the i2c device
        :return: Raw data received from i2c device
        """
        if isinstance(tx_data, str):
            self.write_string(tx_data, i2c_address)
        elif isinstance(tx_data, (list, tuple)):
            self.write_list(tx_data, i2c_address)
        self.bbio.delay(delay)
        return self.read(rx_len, i2c_address)

if __name__ == '__main__':
    import sys

    my_string = " ".join(sys.argv[1:])
    print my_string
    if len(my_string) < 1:
        my_string = "default test string"

    i2c = MyI2C(i2c_address=8, debug=True)
    i2c.close()
    i2c.open()

    # i2c.write(my_string)
    #
    # i2c.bbio.delay(10)
    # a = i2c.read(32)
    # print "RECEIVED BACK:", a
    # print "".join([chr(c) for c in a])

    print "Sending what user supplied..., return[0] should be 225"
    a = i2c.transaction(my_string, 8)
    print "Raw received:", a
    print "'char' received: " + "".join([chr(c) for c in a])

    print "\n"

    print "Sending predefined list of integers with 22 being last, causing return[0] of 1"
    a = i2c.transaction([1, 2, 3, 4, 22], 8)
    print "Raw received:", a
    print "'char' received: " + "".join([chr(c) for c in a])

    i2c.close()
