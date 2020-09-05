#include <node.h>
#include <node_buffer.h>
#include <v8.h>
#include <stdint.h>
#include "nan.h"

extern "C" {
    #include "vgp/include/encryption.h"
}

#define THROW_ERROR_EXCEPTION(x) Nan::ThrowError(x)
#define THROW_ERROR_EXCEPTION_WITH_STATUS_CODE(x, y) NanThrowError(x, y)

using namespace node;
using namespace v8;

/**
 * @brief Encrypts a piece of data using BDAP for a set of recipient's public-keys.
 * 
 * @param vchPubKeys The set of recipients Ed25519 public-keys, 32 bytes each
 * @param vchData The input data to be encrypted
 * @param vchCipherText The output ciphertext
 * @param strErrorMessage The string containing error-message in the event of failure
 * @return true on success
 * @return false on failure

bool EncryptBDAPData(const vCharVector& vchPubKeys,
                     const CharVector& vchData,
                     CharVector& vchCipherText,
                     std::string& strErrorMessage);
 */
void encrypt(const v8::FunctionCallbackInfo<v8::Value>& args) {
    v8::Isolate* isolate = args.GetIsolate();

    if (args.Length() < 2) {
       isolate->ThrowException(Exception::TypeError(String::NewFromUtf8(isolate, "Wrong number of arguments")));
       return;
    }
    /*
    Local<Object> objPubKeys = args[0]->ToObject();
    if(!Buffer::HasInstance(objPubKeys)) {
       isolate->ThrowException(Exception::TypeError(String::NewFromUtf8(isolate,"Argument should be a buffer object.")));
       return;
    }
    const std::vector<std::vector<unsigned char>> vPubKeys = (std::vector<std::vector<unsigned char>>)Buffer::Data(objPubKeys);

    Local<Object> objData = args[1]->ToObject();
    if(!Buffer::HasInstance(objPubKeys)) {
       isolate->ThrowException(Exception::TypeError(String::NewFromUtf8(isolate,"Argument should be a buffer object.")));
       return;
    }
    const std::vector<unsigned char> vchData = (std::vector<unsigned char>)Buffer::Data(objData);
    
    std::vector<unsigned char> output;
    std::string strErrorMessage
    if !(EncryptBDAPData(vPubKeys, vchData, output, strErrorMessage)) {
        isolate->ThrowException(Exception::TypeError(String::NewFromUtf8(isolate, strErrorMessage)));
        return;
    }
    */
    // return raw vchCipherText
    unsigned char* output = (unsigned char*) malloc(sizeof(unsigned char) * 32);
    v8::Local<v8::Value> returnValue = Nan::CopyBuffer(((char*)output), 32).ToLocalChecked();
    
    args.GetReturnValue().Set(returnValue);
}
/**
 * @brief Decrypts a piece of BDAP encrypted ciphertext using a Ed25519 private-key seed.
 * 
 * @param vchPrivKeySeed The Ed25519 private-key seed, 32 bytes
 * @param vchCipherText The input BDAP ciphertext
 * @param vchData The decrypted output
 * @param strErrorMessage The string containing error-message in the event of failure
 * @return true on success
 * @return false on failure

bool DecryptBDAPData(const CharVector& vchPrivKeySeed,
                     const CharVector& vchCipherText,
                     CharVector& vchData,
                     std::string& strErrorMessage);
 */
void decrypt(const v8::FunctionCallbackInfo<v8::Value>& args) {
    v8::Isolate* isolate = args.GetIsolate();

    if (args.Length() < 2) {
       isolate->ThrowException(Exception::TypeError(String::NewFromUtf8(isolate, "Wrong number of arguments")));
       return;
    }
    /*
    // Get Private Key Seed Argument
    Local<Object> objPrivKeySeed = args[0]->ToObject();
    if(!Buffer::HasInstance(objPrivKeySeed)) {
       isolate->ThrowException(Exception::TypeError(String::NewFromUtf8(isolate," Private Key Seed Argument should be a buffer object.")));
       return;
    }
    const std::vector<unsigned char> vchPrivKeySeed = (std::vector<unsigned char>)Buffer::Data(objPrivKeySeed);
    // Get CipherText Argument
    Local<Object> objCipherText = args[1]->ToObject();
    if(!Buffer::HasInstance(objCipherText)) {
       isolate->ThrowException(Exception::TypeError(String::NewFromUtf8(isolate,"Cipher Text Argument should be a buffer object.")));
       return;
    }
    const std::vector<unsigned char> vchCipherText = (std::vector<unsigned char>)Buffer::Data(objCipherText);

    std::vector<unsigned char> output;
    std::string strErrorMessage;
    if !(DecryptBDAPData(vchPrivKeySeed, vchCipherText, output, strErrorMessage)) {
        isolate->ThrowException(Exception::TypeError(String::NewFromUtf8(isolate, strErrorMessage)));
        return;
    }
    */
    unsigned char* output = (unsigned char*) malloc(sizeof(unsigned char) * 32);
    v8::Local<v8::Value> returnValue = Nan::CopyBuffer(((char*)output), 32).ToLocalChecked();
    args.GetReturnValue().Set(returnValue);
}

void init(v8::Local<v8::Object> target) {
    NODE_SET_METHOD(target, "Encrypt", encrypt);
    NODE_SET_METHOD(target, "Decrypt", decrypt);
}

NODE_MODULE(vgp, init)
