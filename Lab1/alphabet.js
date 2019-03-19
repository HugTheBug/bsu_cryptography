class Alphabet {
    constructor( alphabetString ) {
        this.letterMap = {};
        for ( let i = 0; i < alphabetString.length; i++ )
        {
            this.letterMap[alphabetString[i]] = i;
        }
        
        this.letters = alphabetString;
        this.size = alphabetString.length;
    }

    getLetter( index ) {
        if ( index < 0 ) {
            index += this.size;
        }
        return this.letters[index % this.size];
    }

    getIndex( letter ) {
        return this.letterMap[letter];
    }
}

module.exports = {
    Alphabet: Alphabet,
};