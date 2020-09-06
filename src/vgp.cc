#include <node.h>
#include <node_buffer.h>
#include <nan.h>

#include <encryption.h>
#include <hex.h>

#include <stdlib.h>

using namespace node;
using namespace v8;

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
    v8::Local<v8::Object> pubkeysObj;
    if (!info[0]->ToObject(Nan::GetCurrentContext()).ToLocal(&pubkeysObj) || !Buffer::HasInstance(pubkeysObj)) {
        return Nan::ThrowError("Encrypt first parameter [pubkeys] error");
    }
    v8::Local<v8::Object> messageObj;
    if (!info[1]->ToObject(Nan::GetCurrentContext()).ToLocal(&messageObj) || !Buffer::HasInstance(messageObj)) {
        return Nan::ThrowError("Encrypt second parameter [message] error");
    }
    std::vector<uint8_t> vchData;
    const uint8_t* messageData = (uint8_t*)Buffer::Data(messageObj);
    int size = Buffer::Length(messageObj);
    std::vector<uint8_t> vchMessage(messageData, messageData+size);
    std::vector<std::vector<uint8_t>> vvchPubKeys;
    std::vector<uint8_t> vchCipherText;
    std::string strErrorMessage = "";
    if (!EncryptBDAPData(vvchPubKeys, vchMessage, vchCipherText, strErrorMessage)) {
        strErrorMessage = "Encrypt error " + strErrorMessage;
        return Nan::ThrowError(strErrorMessage.c_str());
    }
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
    Nan::HandleScope scope;
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
    std::vector<uint8_t> vchData;
    const uint8_t* cipherTextData = (uint8_t*)Buffer::Data(cipherTextObj);
    int size = Buffer::Length(cipherTextObj);
    std::vector<uint8_t> vchCipherText(cipherTextData, cipherTextData+size);
    std::string strErrorMessage = "";
    if (!DecryptBDAPData(vchPrivKeySeed, vchCipherText, vchData, strErrorMessage)) {
        strErrorMessage = "Decrypt error " + strErrorMessage;
        return Nan::ThrowError(strErrorMessage.c_str());
    }

    v8::Local<v8::Object> clearText = Nan::NewBuffer(vchData.size()).ToLocalChecked();
    unsigned char* clearTextData = (unsigned char*)Buffer::Data(clearText);
	for (int i = 0; i < vchData.size(); i++) {
		clearTextData[i] = vchData[i];
	}
    info.GetReturnValue().Set(clearText);
}

void InitModule(v8::Local<v8::Object> exports) {
    Nan::SetMethod(exports, "Encrypt", Encrypt);
    Nan::SetMethod(exports, "Decrypt", Decrypt);
}

NODE_MODULE(vgp, InitModule)
