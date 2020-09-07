/* 
    To test run the following
    npm update
    node-gyp clean
    node-gyp configure
    node-gyp build --debug
*/
var vgp = require('./');

// VGP encrypt example using ed25519 hex encoded pubkey
var message = 'VGP is easy to use!';
var publicKey = "bdc7d62d2bf3987fba434af854a2473935f12519909b3552a1b41e253aee4855";
var cipherText = vgp.Encrypt(Buffer.from(publicKey, 'hex'), Buffer.from(message, 'utf8'));
console.log("original message: " + message + ", cipher text byte size: " + cipherText.byteLength.toString());
// VGP decrypt example using ed25519 hex encoded private seed
var privateSeed = "8e05b7251e25ddc7369c071437b3175d9bb00ac4a89082398bb6f8bb68455cca";
var decryptedMessage = vgp.Decrypt(Buffer.from(privateSeed, 'hex'), cipherText);
console.log("decrypted message: " + decryptedMessage.toString());
if (message == decryptedMessage) {
    console.log('Complete. VGP encrypt/decrypt successful!');
} else {
    console.log('Complete. VGP encrypt/decrypt failed!');
}