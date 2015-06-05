__author__ = 'Lesko'
# Documentation is like sex.
# When it's good, it's very good.
# When it's bad, it's better than nothing.
# When it lies to you, it may be a while before you realize something's wrong.
from ri2c import MyI2C
import csv

"""
Script to explore between call time dependency of i2c bus

For now it looks like the longer the pause between calls less time is needed to get the correct answer.

"""

i2c = MyI2C(i2c_address=8, debug=False)
i2c.close()

us = 2500
n = 0
fails = []
i2c.open()
try:
    # Test sleep times to 1s range
    for sleep in range(5000, 0, -10):
        print "\nSleep time", sleep
        # Repeat 10 times for every test time
        for repeats in range(10):
            print "Repeats:", repeats + 1
            # Test
            while us > 0:

                a = i2c.transaction([1, 2, 3, 4, 22], 8, delay_microseconds=us)

                if a[0] != 1:
                    print "Failed at {}us!".format(us)
                    fails.append(us)
                    with open("results.csv", "a") as csv_f:
                        writer = csv.writer(csv_f, delimiter=";")
                        writer.writerow([sleep, us])
                    us = 2500
                    n += 1
                    break
                i2c.delay_micros(sleep)
                us -= 5
except KeyboardInterrupt:
    avg = sum(fails)/len(fails)
    print "\nN:", n
    print "MIN\tMAX\tAVG"
    print "{}\t{}\t{}".format(min(fails),
                              max(fails),
                              avg)

i2c.close()
