__author__ = 'Lesko'
# Documentation is like sex.
# When it's good, it's very good.
# When it's bad, it's better than nothing.
# When it lies to you, it may be a while before you realize something's wrong.

from common.mySerial import MySerial
import Adafruit_BBIO.UART as UART
import time
import random

"""

command format:
 command m_num par

 commands: [get counter,
            reset counter,
            alive,
            set speed,
            set direction]

"""


class MotorControl(object):
    GET_COUNTER = "1"
    RESET_COUNTER = "2"
    ALIVE = "5 0 0"
    SET_SPEED = "6"
    SET_DIRECTION = "7"

    VALID_MOTORS = [1, 2, 3, 4]
    VALID_SIDES = [1, 2]

    def __init__(self, ser, debug=False):
        self.ser = ser
        self.debug = debug

    def _debug(self, my_str):
        if self.debug:
            print "++dbg:", repr(my_str)

    def set_speed(self, motor, speed):
        if motor not in self.VALID_MOTORS:
            raise ValueError("No valid motor supplied.")
        command = self.compile_command(self.SET_SPEED, motor, speed)
        self.ser.send(command)
        return True

    def set_direction(self, motor, direction):
        if motor not in self.VALID_MOTORS:
            raise ValueError("No valid motor supplied.")
        command = self.compile_command(self.SET_DIRECTION, motor, direction)
        self.ser.send(command)
        return True

    def reset_counter(self, side):
        if side not in self.VALID_SIDES:
            raise ValueError("No valid side supplied.")
        command = self.compile_command(self.RESET_COUNTER, side, 0)
        self.ser.send(command)
        return True

    def wait_for_alive(self, timeout=5):
        start_time = time.time()
        while True:
            if time.time() - start_time > timeout:
                return None
            ans = ard1.send(self.ALIVE)
            if ans is None:
                continue
            if "ALIVE" in ans:
                self._debug("{me} is ALIVE!".format(me=str(self.ser)))
                break
        return True

    @staticmethod
    def compile_command(*args):
        args = [str(x) for x in args]
        return " ".join(args)

UART.setup("UART1")

ard1 = MySerial("/dev/ttyO1", baudrate=115200, prompt=">>", debug=True)
ard1.connect()
a = MotorControl(ard1, debug=True)

a.wait_for_alive()

a.set_speed(1, 250)
a.set_direction(1, 1)
time.sleep(2)

a.set_direction(1, 2)
a.set_speed(1, 190)
time.sleep(2)

a.set_speed(1, 0)

a.wait_for_alive(10)


while True:
    try:
        speed = str(random.randint(120, 255))
        direction = random.choice([1, 2])
        a.set_direction(1, direction)
        a.set_speed(1, speed)
        time.sleep(2)
    except KeyboardInterrupt:
        break

a.set_speed(1, 0)
ard1.close()

