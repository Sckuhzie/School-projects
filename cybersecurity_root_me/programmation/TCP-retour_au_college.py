import socket
import math
import re


def main():
    host = "challenge01.root-me.org"
    port = 52002

    # Create a TCP/IP socket
    sock = socket.socket(socket.AF_INET, socket.SOCK_STREAM)

    try:
        # Connect to the server
        sock.connect((host, port))

        # Receive the data from the server
        data = sock.recv(1024).decode("utf-8")
        print(f"Received: {data}")

        # Extract numbers from the received data
        numbers = re.findall(r"[-+]?\d*\.\d+|\d+", data)
        print(f"Extracted numbers: {numbers}")
        number1 = float(numbers[1])
        number2 = float(numbers[2])

        # # Calculate the result
        result = round(math.sqrt(number1) * number2, 2)

        # Send the result back to the server
        print(f"Sending result: {result}")
        sock.sendall((str(result) + "\n").encode())
        print("Result sent")
        # print("maybe", res)

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
