# **VGP (Very Good Privacy) NodeJS Package**

![DYN logo](https://github.com/duality-solutions/Dynamic/blob/master/src/qt/res/icons/drk/about.png?raw=true)

**Copyright (c) 2020-present [Duality Blockchain Solutions](https://duality.solutions/)**

What is VGP-Node?
-----------------------------
A Node.js module for the VGP encryption library.


Installation Instructions
-------------------------

### Windows prerequisites for install
1. Install Python version [2.7.18](https://www.python.org/downloads/release/python-2718/) from https://www.python.org. You can install just for your local user account or for all users. Version 2.7.x is required for building the VGP native code package. Set the path to python.exe in the PYTHON environment variable.
1. Install Visual Studio 2019 Build Tools from https://www.visualstudio.com/thank-you-downloading-visual-studio/?sku=BuildTools&rel=16

```$ npm install --python=python2.7``` 
```$ npm install --global --production windows-build-tools``` 

It is available to install via the Node.js Package Manager (NPM) by using the command:

```$ npm install vgp```

or by cloning from Github and installing locally using NPM:

```$ git clone https://github.com/duality-solutions/node-vgp; cd node-vgp; git submodule update --init --recursive```

Linux:

```$ npm install```

Windows (using [Chocolatey](https://chocolatey.org/install) and [NVM](https://github.com/coreybutler/nvm-windows/releases)):

```$ npm install -g node-gyp; npm update; node-gyp clean; node-gyp configure; node-gyp build```

Usage
-----
Encrypt and decrypt a string using VGP
```js
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
```

[License](https://github.com/duality-solutions/VGP/blob/master/LICENSE.md)

