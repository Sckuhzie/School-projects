import PIL.Image as Image
import numpy as np

# https://www.root-me.org/fr/Challenges/Steganographie/Points-jaunes

# blue = Image.open("steganographie/ch18.png").split()[2]
# blue.point(lambda x: (256 - x) ** 2).show()

dots = [
    [1, 0, 1, 1, 1, 0, 1, 1, 1, 0, 1, 0, 1, 0, 1],
    [1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0],
    [1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0],
    [1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 1, 1, 0, 0],
    [0, 0, 0, 0, 1, 1, 0, 1, 0, 0, 1, 1, 1, 0, 0],
    [0, 1, 0, 0, 0, 0, 1, 1, 0, 0, 1, 1, 1, 1, 0],
    [0, 0, 0, 0, 1, 1, 1, 1, 0, 0, 1, 0, 0, 1, 0],
    [1, 1, 0, 0, 1, 1, 1, 0, 0, 0, 0, 1, 0, 0, 0],
]


def binary_to_dec(binary):
    res = 0
    for i, bit in enumerate(reversed(binary)):
        # print(f"{i} : {bit} - {2**i}")
        res += bit * (2**i)
    return res


def convert_to_str(integer):
    if integer < 10:
        return "0" + str(integer)
    else:
        return str(integer)


dots = np.array(dots)


minutes = convert_to_str(binary_to_dec(dots[1:, 1]))
hour = convert_to_str(binary_to_dec(dots[1:, 4]))
day = convert_to_str(binary_to_dec(dots[1:, 5]))
month = convert_to_str(binary_to_dec(dots[1:, 6]))
year = binary_to_dec(dots[1:, 7]) + 2000
serial1 = convert_to_str(binary_to_dec(dots[1:, 10]))
serial2 = convert_to_str(binary_to_dec(dots[1:, 11]))
serial3 = convert_to_str(binary_to_dec(dots[1:, 12]))
serial4 = convert_to_str(binary_to_dec(dots[1:, 13]))


print(f"{hour}:{minutes} {day}/{month}/{year} {serial4}{serial3}{serial2}{serial1}")
print(f"{hour}:{minutes} {day}/{month}/{year} {serial1}{serial2}{serial3}{serial4}")
# 11:05 27/07/2014 06922930
# 11:05 27/07/2014 30299206
