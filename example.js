/* 
    To test run the following
    npm update
    node-gyp clean
    node-gyp configure
    node-gyp build --debug
*/
var vgp = require('./');

// VGP Encrypt using multiple keys
// http://ed25519.herokuapp.com/
// Ed25519 seed: 23ce201beb9d303ae3b5ae80f703837f1c1c312c6af2fe25f0ebbf2a67a2fbbe
// Ed25519 base64 public key: Gnr5MUIzf8LmaWx3FBTHA/ab8XsnPbqdUZk9KFdtXLk=
// Ed25519 hex public key: 1a7af93142337fc2e6696c771414c703f69bf17b273dba9d51993d28576d5cb9
// Ed25519 base64 private key: iZvHOuRkZoqGWeENSSkuWZf4M8eKfu11jg4zZ/nZciAaevkxQjN/wuZpbHcUFMcD9pvxeyc9up1RmT0oV21cuQ==
// Ed25519 hex private key: 899bc73ae464668a8659e10d49292e5997f833c78a7eed758e0e3367f9d972201a7af93142337fc2e6696c771414c703f69bf17b273dba9d51993d28576d5cb9

// Ed25519 seed: ba858559258f3b75539d4b23de907d82cc83d49988b2f346d51141775dd76108
// Ed25519 base64 public key: vNLXWsyUtMvEQJCCUOFCB+zuTh4aqcxUed+wdYTjjjQ=
// Ed25519 hex public key: bcd2d75acc94b4cbc440908250e14207ecee4e1e1aa9cc5479dfb07584e38e34
// Ed25519 base64 private key: lf+fJlsHxaNB+GR7vb/XANDFGiywsgXqzi4XjSYVP6e80tdazJS0y8RAkIJQ4UIH7O5OHhqpzFR537B1hOOONA==
// Ed25519 hex private key: 95ff9f265b07c5a341f8647bbdbfd700d0c51a2cb0b205eace2e178d26153fa7bcd2d75acc94b4cbc440908250e14207ecee4e1e1aa9cc5479dfb07584e38e34

var publicKeys = [
    "1a7af93142337fc2e6696c771414c703f69bf17b273dba9d51993d28576d5cb9", 
    "bcd2d75acc94b4cbc440908250e14207ecee4e1e1aa9cc5479dfb07584e38e34",
];
var message = 'VGP is easy to use!';
var cipherText = vgp.Encrypt(Buffer.from(publicKeys, 'utf8'), Buffer.from(message, 'utf8'));

// VGP decrypt example using the first private key
var privateSeed1 = "23ce201beb9d303ae3b5ae80f703837f1c1c312c6af2fe25f0ebbf2a67a2fbbe";
var decryptedMessage1 = vgp.Decrypt(Buffer.from(privateSeed1, 'utf8'), Buffer.from(cipherText, 'utf8'));
if (message == decryptedMessage1) {
    console.log('VGP encrypt/decrypt with first private key successful!');
} else {
    console.log('VGP encrypt/decrypt with first private key failed!');
}

// VGP decrypt example using the second private key
var privateSeed2 = "ba858559258f3b75539d4b23de907d82cc83d49988b2f346d51141775dd76108";
var decryptedMessage2 = vgp.Decrypt(Buffer.from(privateSeed2, 'utf8'), Buffer.from(cipherText, 'utf8'));
if (message == decryptedMessage2) {
    console.log('VGP encrypt/decrypt with second private key successful!');
} else {
    console.log('VGP encrypt/decrypt with second private key failed!');
}