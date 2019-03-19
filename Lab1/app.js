const alphabet = require( "./alphabet.js" );
const affine = require( "./affine.js" );
const vigenere = require( "./vigenere.js" );

const letters = "абвгдеёжзийклмнопрстуфхцчшщъыьэюя";

const alphabetObj = new alphabet.Alphabet( letters );
const encryptedText = affine.encryptAffine(alphabetObj, new affine.AffineKey( 2, 14 ), "математика");
console.log(encryptedText);
const decryptedText = vigenere.decryptVigenere(alphabetObj, "ЩДР".toLowerCase(), "ЁДЮЭДБВС".toLowerCase());
console.log(decryptedText);
