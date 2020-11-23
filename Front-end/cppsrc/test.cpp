#include "test.h"

std::string test::hello(){
    return "Hello World123";
}

int test::add(int a, int b){
  return a + b;
}

Napi::Number test::AddWrapped(const Napi::CallbackInfo& info) {
    Napi::Env env = info.Env();
    if (info.Length() < 2 || !info[0].IsNumber() || !info[1].IsNumber()) {
        Napi::TypeError::New(env, "Number expected").ThrowAsJavaScriptException();
    } 

    Napi::Number first = info[0].As<Napi::Number>();
    Napi::Number second = info[1].As<Napi::Number>();

    int returnValue = test::add(first.Int32Value(), second.Int32Value());
    
    return Napi::Number::New(env, returnValue);
}

Napi::String test::HelloWrapped(const Napi::CallbackInfo &info)
{
    Napi::Env env = info.Env();
    Napi::String returnValue = Napi::String::New(env, test::hello());

    return returnValue;
}

Napi::Object test::Init(Napi::Env env, Napi::Object exports)
{
    exports.Set(
        "hello", Napi::Function::New(env, test::HelloWrapped));
        exports.Set("add", Napi::Function::New(env, test::AddWrapped));
    return exports;
}