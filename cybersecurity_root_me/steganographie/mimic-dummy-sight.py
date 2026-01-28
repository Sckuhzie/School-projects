with open("steganographie/ch23/ciphertext", "r") as f:
    data = f.read()

capital_letters = "".join([char for char in data if char.isupper()])
print(capital_letters.split("M"))
capital_letters = [len(word) for word in capital_letters.split("M")]
print(capital_letters)

for i in range(200):
    res = [chr(letter + i) for letter in capital_letters]
    print(res)
    print("".join(res))

# with open("steganographie/ch23/plaintext", "r") as f:
#     data = f.read()

# capital_letters = "".join([char for char in data if char.isupper()])
# print(capital_letters)
