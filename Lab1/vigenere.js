function decryptVigenere( alphabet, key, text ) {
    let decryptedText = "";
    for ( let i = 0; i < text.length; ++i ) {
        let number = alphabet.getIndex( text[i] );
        if ( number != null ) {
            number -= alphabet.getIndex( key[i % key.length] );
            decryptedText += alphabet.getLetter( number );
        } else {
            decryptedText += text[i];
        }
    }
    return decryptedText;
}

module.exports = {
    decryptVigenere: decryptVigenere,
};