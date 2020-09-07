/* 
    To test run the following
    npm update
    node-gyp clean
    node-gyp configure
    node-gyp build --debug
*/
var vgp = require('./');
/*
publicKey: 0a746fba360553d12a18e9253adba6e67df26d9c00464e81cf230b182297b6b4
privateSeed: 26b10d3da38c12763aeac5f981f436d858b4cc29d7ccf1aa0d01b20eede91591
*/
function toHexString(byteArray) {
    return Array.from(byteArray, function(byte) {
        return ('0' + (byte & 0xFF).toString(16)).slice(-2);
    }).join('')
}

// VGP encrypt example using ed25519 hex pubkey
var message = 'VGP is easy to use!';
var publicKey = "0a746fba360553d12a18e9253adba6e67df26d9c00464e81cf230b182297b6b4";
var cipherText = vgp.Encrypt(Buffer.from(publicKey, 'hex'), Buffer.from(message, 'utf8'));
console.log(toHexString(cipherText));
// VGP decrypt example using ed25519 hex private seed
var privateSeed = "26b10d3da38c12763aeac5f981f436d858b4cc29d7ccf1aa0d01b20eede91591";
var decryptedMessage = vgp.Decrypt(Buffer.from(privateSeed, 'hex'), Buffer.from(cipherText, 'utf8'));
console.log(decryptedMessage);
if (message == decryptedMessage) {
    console.log('VGP encrypt/decrypt successful!');
} else {
    console.log('VGP encrypt/decrypt failed!');
}