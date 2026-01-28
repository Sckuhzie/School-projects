with open("cryptanalyse/ch11.txt", "r") as file:
    data = file.read()
    # print(data)
    code = data

alphabet = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz"


def decrypt_vigenere(code, key):
    decrypted = ""
    key_length = len(key)
    i = 0
    for c in code:
        if c in alphabet:
            decrypted += chr((ord(c) - ord(key[i % key_length])) % 26 + 65)
            i += 1
        else:
            decrypted += c
    return decrypted


# def decrypt_vigenere_brute_force(code):
#     for i in range(1, 11):
#         key = "A" * i
#         print(f"Key: {key}")
#         print(decrypt_vigenere(code, key))
#         print("\n")

print(decrypt_vigenere(code, "THEMENTOR"))
