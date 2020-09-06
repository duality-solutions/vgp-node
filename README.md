# **VGP (Very Good Privacy) NodeJS Package**

![DYN logo](https://github.com/duality-solutions/Dynamic/blob/master/src/qt/res/icons/drk/about.png?raw=true)

**Copyright (c) 2020-present [Duality Blockchain Solutions](https://duality.solutions/)**

What is VGP-Node?
-----------------------------
A Node.js module for the VGP encryption library.


Installation Instructions
-------------------------

### Windows prerequisites for install
1. Install Python version [3.8.5](https://www.python.org/ftp/python/3.8.5/python-3.8.5.exe) from https://www.python.org. You can install just for your local user account or for all users. Version 3.8.5 is required for building the VGP native code package. Set the path to python.exe in the PYTHON environment variable.
1. Install Visual Studio 2019 Build Tools from https://www.visualstudio.com/thank-you-downloading-visual-studio/?sku=BuildTools&rel=16

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
var message = 'VGP is easy to use!';
// VGP encrypt example using multiple hex encoded ed25519 public keys
var publicKeys = [
    "1a7af93142337fc2e6696c771414c703f69bf17b273dba9d51993d28576d5cb9", 
    "bcd2d75acc94b4cbc440908250e14207ecee4e1e1aa9cc5479dfb07584e38e34"
];
var cipherText = vgp.Encrypt(Buffer.from(publicKeys, 'utf8'), Buffer.from(message, 'utf8'));
// VGP decrypt example using the first hex encoded private key
var privateSeed = "23ce201beb9d303ae3b5ae80f703837f1c1c312c6af2fe25f0ebbf2a67a2fbbe";
var decryptedMessage = vgp.Decrypt(Buffer.from(privateSeed, 'utf8'), Buffer.from(cipherText, 'utf8'));
if (message == decryptedMessage) {
    console.log('VGP encrypt/decrypt with first private key successful!');
} else {
    console.log('VGP encrypt/decrypt with first private key failed!');
}
```

[License](https://github.com/duality-solutions/VGP/blob/master/LICENSE.md)

