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
// VGP encrypt example using ed25519 hex pubkey
var message = 'VGP is easy to use!';
var publicKey = "0a746fba360553d12a18e9253adba6e67df26d9c00464e81cf230b182297b6b4";
var cipherText = vgp.Encrypt(Buffer.from(publicKey, 'hex'), Buffer.from(message, 'utf8'));
// VGP decrypt example using ed25519 hex private seed
var privateSeed = "26b10d3da38c12763aeac5f981f436d858b4cc29d7ccf1aa0d01b20eede91591";
var decryptedMessage = vgp.Decrypt(Buffer.from(privateSeed, 'hex'), Buffer.from(cipherText, 'utf8'));
console.log(decryptedMessage);
if (message == decryptedMessage) {
    console.log('VGP encrypt/decrypt with successful!');
} else {
    console.log('VGP encrypt/decrypt with failed!');
}
```

[License](https://github.com/duality-solutions/VGP/blob/master/LICENSE.md)

