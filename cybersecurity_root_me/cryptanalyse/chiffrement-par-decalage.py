# https://www.root-me.org/fr/Challenges/Cryptanalyse/Chiffrement-par-decalage?action_solution=voir&debut_affiche_solutions=1#pagination_affiche_solutions

# import os


# def decrypt_caesar_cipher(data, shift):
#     """Decrypts data using the Caesar cipher with a given shift."""
#     decrypted = ""
#     for byte in data:
#         # print(byte)
#         # Decrypt assuming the data represents ASCII characters
#         if 32 <= byte <= 126:  # Printable ASCII range
#             new_char = chr((byte - shift - 32) % 95 + 32)
#             decrypted += new_char
#         else:
#             decrypted += chr(byte)  # Non-printable, leave as is
#     return decrypted


# def decrypt_bin_file(file_path, shift):
#     """Reads an encrypted binary file and decrypts its Caesar cipher contents."""
#     try:
#         with open(file_path, "rb") as file:
#             encrypted_data = file.read()
#             print(f"Encrypted data (binary): {encrypted_data}")
#             # Convert bynary to string
#             encrypted_data = list(encrypted_data)
#             print(f"Encrypted data (list): {encrypted_data}")
#             char_data = "".join([chr(byte) for byte in encrypted_data])
#             print(f"Encrypted data (string): {char_data}")

#             # Decrypt data
#             decrypted_text = decrypt_caesar_cipher(encrypted_data, shift)
#             return decrypted_text
#     except FileNotFoundError:
#         print(f"Error: File '{file_path}' not found.")
#         return None


# # Example usage:
# binary_file_path = "ch7.bin"  # Replace with your file's path
# for shift_value in range(42, 43):
#     decrypted_message = decrypt_bin_file(binary_file_path, shift_value)

#     if decrypted_message:
#         print("Decrypted Message: " + str(shift_value))
#         print(decrypted_message)


def decrypt_cesar(code, shift):
    return "".join([chr((ord(c) - shift - 32) % 95 + 32) for c in code])


# with open("ch7.bin", "rb") as file:
#     data = file.read()
#     print(data)
#     code = data.decode("utf-8")

code = "L|k\x80y+*^\x7f*zo\x7f\x82*\x80kvsno|*k\x80om*vo*zk}}*cyvksr\x7f"

print(code)
print(decrypt_cesar(code, 10))
