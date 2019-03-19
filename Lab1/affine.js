class AffineKey {
    constructor( a, b ) {
        this.a = a;
        this.b = b;
    }
}

function encryptAffine( alphabet, key, text ) {
    let encryptedText = "";
    for ( const chr of text ) {
        let number = alphabet.getIndex( chr );
        if ( number != null) {
            number = ( number * key.a + key.b );
            encryptedText += alphabet.getLetter( number );
        } else {
            encryptedText += chr;
        }
    }
    return encryptedText;
}

module.exports = {
    AffineKey: AffineKey,
    encryptAffine: encryptAffine,
};