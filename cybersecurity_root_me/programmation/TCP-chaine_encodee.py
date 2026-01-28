import socket
import math
import re
import base64
from time import time


def main():
    host = "challenge01.root-me.org"
    port = 52023

    # Create a TCP/IP socket
    sock = socket.socket(socket.AF_INET, socket.SOCK_STREAM)

    try:
        # Connect to the server
        sock.connect((host, port))

        # Receive the data from the server
        tic = time()
        data = sock.recv(1024).decode("utf-8")
        print(f"Received: {data}")
        print(data.split("'")[1])
        result = base64.b64decode(data.split("'")[1]).decode()

        # Send the result back to the server
        print(f"Sending result: {result}")
        sock.sendall((str(result) + "\n").encode())
        print("Result sent")
        print(f"Time taken: {time() - tic}")

        # Receive the final response from the server
        final_response = sock.recv(1024).decode()
        print(f"Final response: {final_response}")

    except Exception as e:
        print(f"Error: {e}")

    finally:
        # Close the socket
        sock.close()


if __name__ == "__main__":
    main()
