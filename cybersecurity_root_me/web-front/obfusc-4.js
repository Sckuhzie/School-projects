// https://www.root-me.org/fr/Challenges/Web-Client/Javascript-Obfuscation-4

var encodedString =
  "\x71\x11\x24\x59\x8d\x6d\x71\x11\x35\x16\x8c\x6d\x71\x0d\x39\x47\x1f\x36\xf1\x2f\x39\x36\x8e\x3c\x4b\x39\x35\x12\x87\x7c\xa3\x10\x74\x58\x16\xc7\x71\x56\x68\x51\x2c\x8c\x73\x45\x32\x5b\x8c\x2a\xf1\x2f\x3f\x57\x6e\x04\x3d\x16\x75\x67\x16\x4f\x6d\x1c\x6e\x40\x01\x36\x93\x59\x33\x56\x04\x3e\x7b\x3a\x70\x50\x16\x04\x3d\x18\x73\x37\xac\x24\xe1\x56\x62\x5b\x8c\x2a\xf1\x45\x7f\x86\x07\x3e\x63\x47";

function xor(x, y) {
  return x ^ y;
}

function getBitMask(y) {
  var mask = 0;
  for (var i = 0; i < y; i++) {
    mask += Math.pow(2, i);
  }
  return mask;
}

function getInverseBitMask(y) {
  var mask = 0;
  for (var i = 8 - y; i < 8; i++) {
    mask += Math.pow(2, i);
  }
  return mask;
}

function rotateLeft(x, y) {
  y = y % 8;
  var mask = getBitMask(y);
  mask = (x & mask) << (8 - y);
  return mask + (x >> y);
}

function rotateRight(x, y) {
  y = y % 8;
  var mask = getInverseBitMask(y);
  mask = (x & mask) >> (8 - y);
  return (mask + (x << y)) & 0x00ff;
}

function encryptChar(c, keyChar, prevChar) {
  var encryptedChar;
  if (prevChar !== undefined) {
    var t = prevChar % 2;
    switch (t) {
      case 0:
        encryptedChar = xor(c, keyChar);
        break;
      case 1:
        encryptedChar = rotateRight(c, keyChar);
        break;
    }
  } else {
    encryptedChar = xor(c, keyChar);
  }
  return encryptedChar;
}

function encryptString(input, key) {
  var encryptedString = "";
  for (var i = 0; i < input.length; i++) {
    var c = input.charCodeAt(i);
    var keyChar = key.charCodeAt(i % key.length);
    var prevChar = i > 0 ? encryptedString.charCodeAt(i - 1) : undefined;
    var encryptedChar = encryptChar(c, keyChar, prevChar);
    encryptedString += String.fromCharCode(encryptedChar);
  }
  return encryptedString;
}

function validatePassword(decryptedString) {
  var sum = 0;
  for (var i = 0; i < decryptedString.length; i++) {
    sum += decryptedString.charCodeAt(i);
  }
  if (sum == 8932) {
    // var newWindow = window.open("", "", "width=300,height=200");
    // newWindow.document.write(decryptedString);
    console.log("Bon mot de passe! : ", decryptedString);
    return true;
  } else {
    // console.log("Mauvais mot de passe!");
    return false;
  }
}

function generateRandomPassword(length) {
  var characters =
    "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789";
  var password = "";
  for (var i = 0; i < length; i++) {
    password += characters.charAt(
      Math.floor(Math.random() * characters.length)
    );
  }
  return password;
}

// function bruteForcePassword() {
//   characters = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789";
//   for (i = 0; 10; i++) {
//     for (j = 0; 10; j++) {
//       for (k = 0; 10; k++) {
//         for (l = 0; 10; l++) {
//           password =
//             characters[i] + characters[j] + characters[k] + characters[l];
//           decryptedString = encryptString(encodedString, password);
//           if (validatePassword(decryptedString)) {
//             return password;
//           }
//         }
//       }
//     }
//   }
// }

function bruteForcePassword() {
  var found = false;
  while (!found) {
    var password = generateRandomPassword(10);
    var decryptedString = encryptString(encodedString, password);
    if (validatePassword(decryptedString)) {
      console.log("Password found: ", password);
      found = true;
      return password;
    }
  }
}

bruteForcePassword();

// var password = "test"; //prompt("Mot de passe?");
// var decryptedString = encryptString(encodedString, password);
// var validatePassword = validatePassword(decryptedString);
// console.log(decryptedString);
