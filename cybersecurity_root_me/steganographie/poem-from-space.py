with open("steganographie/ch19.txt", "r") as f:
    data = f.read()
    # print(data)


data = data.split("\n")
# print(data)


res = []
for line in data:
    temp_res = ""
    for char in reversed(line):
        if char == " " or char == "\t":
            temp_res += char
        else:
            break
    res.append("".join(reversed(temp_res)))

res = "\n".join(res)
print(res)

with open("steganographie/ch19-res.txt", "w") as f:
    f.write(res)
