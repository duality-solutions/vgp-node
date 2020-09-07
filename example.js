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
var publicKey = "8953dff05898b6a0a4830fd66b963ff1d30b39cdce8fe6bd198e9c8b01fa7580";
var cipherText = vgp.Encrypt(Buffer.from(publicKey, 'hex'), Buffer.from(message, 'utf8'));
console.log("original message: " + message + ", cipher text byte size: " + cipherText.byteLength.toString());
// VGP decrypt example using ed25519 hex encoded private seed
var privateSeed = "d6beb70350c8bdeb7d628a4ae39acf8d67bb2de08c3f53ab5c380a526cc149c3";
var decryptedMessage = vgp.Decrypt(Buffer.from(privateSeed, 'hex'), cipherText);
console.log(decryptedMessage.toString());
if (message == decryptedMessage) {
    console.log('VGP encrypt/decrypt successful!');
} else {
    console.log('VGP encrypt/decrypt failed!');
}