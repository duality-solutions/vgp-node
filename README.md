# **VGP (Very Good Privacy) NodeJS Package**

![DYN logo](https://github.com/duality-solutions/Dynamic/blob/master/src/qt/res/icons/drk/about.png?raw=true)

**Copyright (c) 2020-present [Duality Blockchain Solutions](https://duality.solutions/)**

What is VGP-Node?
-----------------------------
A Node.js module for the VGP encryption library.


Installation Instructions
-------------------------

It is available to install via the Node.js Package Manager (NPM) by using the command:

```$ npm install vgp```

or by cloning from Github and installing locally using NPM:

```$ git clone https://github.com/duality-solutions/node-vgp; cd node-vgp; git submodule update --init --recursive```

Linux:

```$ npm install```

Windows (using [Chocolatey](https://chocolatey.org/install) and [NVM](https://github.com/coreybutler/nvm-windows/releases)):

```$ npm install -g npm-check-updates; ncu -u; npm install -g node-gyp; npm install; node-gyp rebuild```

Usage
-----
to create a raw hash from a string of data 
```js
var vgp = require('vgp-node');
var buf = Buffer.from("someString", 'utf8');
var cipherText = vgp.Encrypt(buf);
console.log(cipherText);
//should return <Buffer 0d 01 c4 09 bd 11 f1 07 d0 e9 41 ca c3 bd bf 3e ed 02 0f 9e ca d2 2b 8a 8f a0 eb 3a e2 2c b1 e0>
```

License
-------

