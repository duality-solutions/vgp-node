#include <node.h>
#include <node_buffer.h>
#include <nan.h>

#include <ed25519.h>
#include <encryption.h>

#include <stdlib.h>
#include <string>
#include <vector>

using namespace node;
using namespace v8;

std::string stringFromVch(const std::vector<uint8_t>& vch) {
    std::string res;
    std::vector<uint8_t>::const_iterator vi = vch.begin();
    while (vi != vch.end()) {
        res += (char) (*vi);
        vi++;
    }
    return res;
}

/**
 * Encrypt(pubkeys, message)
 * Buffer pubkey
 * Buffer message
 * returns: Buffer cipherText
 **/
NAN_METHOD(Encrypt) { 
    // Check parameter length
    if (info.Length() < 2) {
        return Nan::ThrowError("Encrypt requires at least two parameters");
    }
    // get ed25519 pubkey parameter
    v8::Local<v8::Object> pubkeyObj;
    if (!info[0]->ToObject(Nan::GetCurrentContext()).ToLocal(&pubkeyObj) || !Buffer::HasInstance(pubkeyObj)) {
        return Nan::ThrowError("Encrypt first parameter pubkey error");
    }
    // todo: declare public key size constant variable instead of hard coding below.
    int pubkeySize = Buffer::Length(pubkeyObj);
    if (pubkeySize != ED25519_PUBLIC_KEY_SIZE) {
        std::string strErrorMessage = "Encrypt pubkey invalid length = " + std::to_string(pubkeySize) + " error";
        return Nan::ThrowError(strErrorMessage.c_str());
    }
    const uint8_t* pubkeyData = (uint8_t*)Buffer::Data(pubkeyObj);
    const std::vector<uint8_t> vchPubKey(pubkeyData, pubkeyData+pubkeySize);
    if (vchPubKey.size() != ED25519_PUBLIC_KEY_SIZE) {
        std::string strErrorMessage = "Encrypt pubkey vector invalid length = " + std::to_string(vchPubKey.size()) + " error";
        return Nan::ThrowError(strErrorMessage.c_str());
    }
    const std::vector<std::vector<uint8_t>> vvchPubKeys = {vchPubKey};
    // get message string parameter
    v8::Local<v8::Object> messageObj;
    if (!info[1]->ToObject(Nan::GetCurrentContext()).ToLocal(&messageObj) || !Buffer::HasInstance(messageObj)) {
        return Nan::ThrowError("Encrypt second parameter [message] error");
    }
    // convert message data to uint8_t vector
    const uint8_t* messageData = (uint8_t*)Buffer::Data(messageObj);
    const int messageSize = Buffer::Length(messageObj);
    const std::vector<uint8_t> vchMessage(messageData, messageData+messageSize);
    // encrypt VGP message data to cipher text
    std::string strErrorMessage = "";
    std::vector<uint8_t> vchCipherText;
    if (!EncryptBDAPData(vvchPubKeys, vchMessage, vchCipherText, strErrorMessage)) {
        strErrorMessage = "Encrypt error " + strErrorMessage;
        return Nan::ThrowError(strErrorMessage.c_str());
    }
    // convert cipher text data to output value
    v8::Local<v8::Object> cipherText = Nan::NewBuffer(vchCipherText.size()).ToLocalChecked();
    unsigned char* cipherTextData = (unsigned char*)Buffer::Data(cipherText);
    for (unsigned int i = 0; i < vchCipherText.size(); i++) {
        cipherTextData[i] = vchCipherText[i];
    }
    info.GetReturnValue().Set(cipherText);
}

 /**
 * Decrypt(privatekey, cipherText)
 * Buffer privatekey
 * Buffer cipherText
 * returns: Buffer clearText
 **/
NAN_METHOD(Decrypt) {
    // Check parameter length
    if (info.Length() < 2) {
        return Nan::ThrowError("Decrypt requires at least two parameters");
    }
    // get private key parameter
    v8::Local<v8::Object> privateKeyObj;
    if (!info[0]->ToObject(Nan::GetCurrentContext()).ToLocal(&privateKeyObj) || !Buffer::HasInstance(privateKeyObj)) {
        return Nan::ThrowError("Decrypt first parameter [privatekey] error");
    }
    int privkeySize = Buffer::Length(privateKeyObj);
    if (privkeySize != ED25519_PRIVATE_KEY_SEED_SIZE) {
        std::string strErrorMessage = "Encrypt private key seed invalid length = " + std::to_string(privkeySize) + " error";
        return Nan::ThrowError(strErrorMessage.c_str());
    }
    const char* privKey = (char*)Buffer::Data(privateKeyObj);
    const std::vector<uint8_t> vchPrivKeySeed(privKey, privKey+privkeySize);
    if (vchPrivKeySeed.size() != ED25519_PRIVATE_KEY_SEED_SIZE) {
        std::string strErrorMessage = "Decrypt private key seed vector invalid length = " + std::to_string(vchPrivKeySeed.size()) + " error";
        return Nan::ThrowError(strErrorMessage.c_str());
    }
    // get cipher text parameter
    v8::Local<v8::Object> cipherTextObj;
    if (!info[1]->ToObject(Nan::GetCurrentContext()).ToLocal(&cipherTextObj) || !Buffer::HasInstance(cipherTextObj)) {
        return Nan::ThrowError("Decrypt second parameter [cipher text] error");
    }
    // convert cipher text to uint8_t vector
    const uint8_t* cipherTextData = (uint8_t*)Buffer::Data(cipherTextObj);
    const int size = Buffer::Length(cipherTextObj);
    const std::vector<uint8_t> vchCipherText(cipherTextData, cipherTextData+size);
    // decrypt VGP cipher text to clear text
    std::vector<uint8_t> vchClearTextData;
    std::string strErrorMessage = "";
    if (!DecryptBDAPData(vchPrivKeySeed, vchCipherText, vchClearTextData, strErrorMessage)) {
        strErrorMessage = "Decrypt error " + strErrorMessage;
        return Nan::ThrowError(strErrorMessage.c_str());
    }
    // convert clear text data to output value
    v8::Local<v8::Object> clearText = Nan::NewBuffer(vchClearTextData.size()).ToLocalChecked();
    unsigned char* clearTextData = (unsigned char*)Buffer::Data(clearText);
    for (unsigned int i = 0; i < vchClearTextData.size(); i++) {
        clearTextData[i] = vchClearTextData[i];
    }
    info.GetReturnValue().Set(clearText);
}

void InitModule(v8::Local<v8::Object> exports) {
    Nan::SetMethod(exports, "Encrypt", Encrypt);
    Nan::SetMethod(exports, "Decrypt", Decrypt);
}

NODE_MODULE(vgp, InitModule)
