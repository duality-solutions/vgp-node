#include <node.h>
#include <node_buffer.h>
#include <nan.h>

#include <encryption.h>
#include <hex.h>

#include <stdlib.h>
#include <string>
#include <vector>

using namespace node;
using namespace v8;

/**
 * Encrypt(pubkeys, message)
 * Buffer[] pubkeys
 * Buffer message
 * returns: Buffer cipherText
 **/
NAN_METHOD(Encrypt) { 
    // Check parameter length
    if (info.Length() < 2) {
        return Nan::ThrowError("Encrypt requires at least two parameters");
    }
    // get public key array parameter
    std::vector<std::vector<uint8_t>> vvchPubKeys;
    Local<Value> val;
    if (info[0]->IsArray()) {
        Isolate* isolate = info.GetIsolate();
        Local<Array> jsArray = Local<Array>::Cast(info[0]);
        for (int i = 0; i < jsArray->Length(); i++) {
            val = jsArray->Get(Integer::New(isolate, i)); 
            std::vector<uint8_t> vchPubKey = FromHex(std::string(*String::Utf8Value(isolate, val)));
            vvchPubKeys.push_back(vchPubKey);
        }
    } else {
        return Nan::ThrowError("Encrypt pubkeys parameters is not an array");
    }
    // get message string parameter
    v8::Local<v8::Object> messageObj;
    if (!info[1]->ToObject(Nan::GetCurrentContext()).ToLocal(&messageObj) || !Buffer::HasInstance(messageObj)) {
        return Nan::ThrowError("Encrypt second parameter [message] error");
    }
    // convert message data to uint8_t vector
    const uint8_t* messageData = (uint8_t*)Buffer::Data(messageObj);
    int size = Buffer::Length(messageObj);
    std::vector<uint8_t> vchMessage(messageData, messageData+size);
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
    for (int i = 0; i < vchCipherText.size(); i++) {
        cipherTextData[i] = vchCipherText[i];
    }
    info.GetReturnValue().Set(cipherText);
}

 /**
 * Decrypt(privatekey, cipherText)
 * Buffer privatekey (hex)
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
    const char* hexPrivKey = (char*)Buffer::Data(privateKeyObj);
    std::vector<uint8_t> vchPrivKeySeed = FromHex(hexPrivKey);
    // get cipher text parameter
    v8::Local<v8::Object> cipherTextObj;
    if (!info[1]->ToObject(Nan::GetCurrentContext()).ToLocal(&cipherTextObj) || !Buffer::HasInstance(cipherTextObj)) {
        return Nan::ThrowError("Decrypt second parameter [cipher text] error");
    }
    // convert cipher text to uint8_t vector
    std::vector<uint8_t> vchClearTextData;
    const uint8_t* cipherTextData = (uint8_t*)Buffer::Data(cipherTextObj);
    int size = Buffer::Length(cipherTextObj);
    // decrypt VGP cipher text to clear text
    std::string strErrorMessage = "";
    std::vector<uint8_t> vchCipherText(cipherTextData, cipherTextData+size);
    if (!DecryptBDAPData(vchPrivKeySeed, vchCipherText, vchClearTextData, strErrorMessage)) {
        strErrorMessage = "Decrypt error " + strErrorMessage;
        return Nan::ThrowError(strErrorMessage.c_str());
    }
    // convert clear text data to output value
    v8::Local<v8::Object> clearText = Nan::NewBuffer(vchClearTextData.size()).ToLocalChecked();
    unsigned char* clearTextData = (unsigned char*)Buffer::Data(clearText);
    for (int i = 0; i < vchClearTextData.size(); i++) {
        clearTextData[i] = vchClearTextData[i];
    }
    info.GetReturnValue().Set(clearText);
}

void InitModule(v8::Local<v8::Object> exports) {
    Nan::SetMethod(exports, "Encrypt", Encrypt);
    Nan::SetMethod(exports, "Decrypt", Decrypt);
}

NODE_MODULE(vgp, InitModule)
