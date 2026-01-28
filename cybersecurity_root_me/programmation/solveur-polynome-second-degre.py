import socket
import math
import re
import base64
from time import time
import codecs


def round3(number):
    res = str(round(number, 3))
    zero_to_add = 3 - len(res.split(".")[1])
    return res + "0" * zero_to_add


def main():
    host = "challenge01.root-me.org"
    port = 52018

    # Create a TCP/IP socket
    sock = socket.socket(socket.AF_INET, socket.SOCK_STREAM)

    try:
        # Connect to the server
        sock.connect((host, port))
        data = sock.recv(1024).decode("utf-8")

        while True:

            # print(f"Received: {data}")

            equation = data.split("please: ")[1].split("\n")[0]
            coefficients = equation.split(" ")
            print(equation, coefficients)
            a = int(coefficients[0].split(".")[0])
            b = int(coefficients[2].split(".")[0])
            c = int(coefficients[4].split(".")[0])
            d = int(coefficients[6])

            if coefficients[1] == "-":
                b = -b
            if coefficients[3] == "-":
                c = -c

            print(a, b, c, d)

            c = c - d
            delta = b**2 - 4 * a * c
            if delta < 0:
                result = "Not possible"
            elif delta == 0:
                result = f"x: {round3(-b / (2 * a))}"
            else:
                result = f"x1: {round3((-b - math.sqrt(delta)) / (2 * a))} ; x2: {round3((-b + math.sqrt(delta)) / (2 * a))}"

            # Send the result back to the server
            print(f"Sending result: {result}")
            sock.sendall((str(result) + "\n").encode())
            print("Result sent")

            print("\n\n")
            # Receive the final response from the server
            final_response = sock.recv(1024).decode()
            print(f"Final response: {final_response}")
            data = final_response

    except Exception as e:
        print(f"Error: {e}")

    finally:
        # Close the socket
        sock.close()


if __name__ == "__main__":
    main()

# Output example for two roots => x1: -1337.777 ; x2: -7331.777
# Output example for one root => x: -1337.990
# Output example for no root => Not possible
