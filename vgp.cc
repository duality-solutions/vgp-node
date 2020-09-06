#include <node.h>
#include <node_buffer.h>

#include <nan.h>
#include <stdlib.h>

extern "C" {
    #include "vgp/include/encryption.h"
}

using namespace node;
using namespace v8;

/*
bool EncryptBDAPData(const vCharVector& vchPubKeys,
                     const CharVector& vchData,
                     CharVector& vchCipherText,
                     std::string& strErrorMessage);
*/
 
/**
 * Encrypt(pubkeys, message)
 * Buffer[] pubkeys
 * Buffer message
 * returns: Buffer cipherText
 **/
NAN_METHOD(Encrypt) {
    Nan::HandleScope scope;

    v8::Local<v8::Value> bufferObj;
    if (info.Length() < 2) {
        return Nan::ThrowError("Encrypt requires at least two parameters");
    }

    v8::Local<v8::Object> messageObj;
    if (!info[1]->ToObject(Nan::GetCurrentContext()).ToLocal(&messageObj) || !Buffer::HasInstance(messageObj)) {
        return Nan::ThrowError("Encrypt second parameter [message] error");
    }
    v8::Local<v8::Object> cipherText = Nan::NewBuffer(64).ToLocalChecked();
    info.GetReturnValue().Set(cipherText);
}
/*
bool DecryptBDAPData(const CharVector& vchPrivKeySeed,
                     const CharVector& vchCipherText,
                     CharVector& vchData,
                     std::string& strErrorMessage);
 */
 /**
 * Decrypt(privatekey, cipherText)
 * Buffer privatekey
 * Buffer cipherText
 * returns: Buffer clearText
 **/
NAN_METHOD(Decrypt) {
    Nan::HandleScope scope;

    v8::Local<v8::Value> bufferObj;
    if (info.Length() < 2) {
        return Nan::ThrowError("Decrypt requires at least two parameters");
    }
    // get private key parameter
    v8::Local<v8::Object> privateKeyObj;
    if (!info[0]->ToObject(Nan::GetCurrentContext()).ToLocal(&privateKeyObj) || !Buffer::HasInstance(privateKeyObj)) {
        return Nan::ThrowError("Decrypt first parameter [privatekey] error");
    }
    // get cipher text parameter
    v8::Local<v8::Object> cipherTextObj;
    if (!info[1]->ToObject(Nan::GetCurrentContext()).ToLocal(&cipherTextObj) || !Buffer::HasInstance(cipherTextObj)) {
        return Nan::ThrowError("Decrypt second parameter [cipher text] error");
    }
    v8::Local<v8::Object> clearText = Nan::NewBuffer(64).ToLocalChecked();
    info.GetReturnValue().Set(clearText);
}

void InitModule(v8::Local<v8::Object> exports) {
    Nan::SetMethod(exports, "Encrypt", Encrypt);
    Nan::SetMethod(exports, "Decrypt", Decrypt);
}

NODE_MODULE(vgp, InitModule)
