import requests
from bs4 import BeautifulSoup
import re

url = "http://challenge01.root-me.org/programmation/ch1/"
answer_url = "http://challenge01.root-me.org/programmation/ch1/ep1_v.php?result="


def def_suite(expression, u_0):
    array_expression = re.split(r"[\[\]\*\=]", expression)

    a = int(array_expression[2].split(" + ")[0])
    b = int(array_expression[5])
    operation = array_expression[3].split()[0]

    print(f"Original : {expression}")
    print(f"Computed : Un+1 = [ {a} + Un ] {operation} [ n * {b} ]")

    operation = operation == "+"

    # def f(n):
    #     u = u_0
    #     for i in range(1, n + 1):
    #         if operation:
    #             u = a + u + ((n - 1) * b)
    #         else:
    #             u = a + u - ((n - 1) * b)
    #     print(i)
    #     return u

    def f(n):
        return (
            a * n + 1 / 2 * b * n * (n - 1) + u_0
            if operation
            else a * n - 1 / 2 * b * n * (n - 1) + u_0
        )

    return f


s = requests.session()

r = s.get(url)
soup = BeautifulSoup(r.text, "html.parser")
parsed_text = soup.get_text()
# print(parsed_text.split("\n"))

print(parsed_text)
expression = parsed_text.split("\n")[0]
u_0 = int(parsed_text.split("\n")[1].split(" = ")[1])
n = int(parsed_text.split("\n")[2].split("You")[1].split("find U")[1])
# print(u_0)
# print(re.split(r"[\[\]\+\*\=]", expression))

u_n = def_suite(expression, u_0)
print(f"U_0 = {u_0}")
print(f"n = {n}")
res = int(u_n(n))
print(res)

r = s.get(answer_url + str(res))
print(r.text)
