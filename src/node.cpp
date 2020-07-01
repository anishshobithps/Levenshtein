#include <napi.h>
#include "./levenshtein.cpp"

Napi::Value Levenshtein(const Napi::CallbackInfo& info)
{
    Napi::Env env = info.Env();

    if (info.Length() < 2)
    {
        Napi::TypeError::New(env, "You need to provide 2 values.")
            .ThrowAsJavaScriptException();
        return env.Null();
    }

    if (!info[0].IsString() || !info[1].IsString())
    {
        Napi::TypeError::New(env, "Both the inputs inputed should be a type of string")
            .ThrowAsJavaScriptException();
        return env.Null();
    }

    auto str1 = info[0].As<Napi::String>().Utf16Value();
    auto str2 = info[1].As<Napi::String>().Utf16Value();
    int result = levenshtein(str1,str2);
    Napi::Number num = Napi::Number::New(env, result);

    return num;
}

Napi::Object Init(Napi::Env env, Napi::Object exports)
{
   exports.Set(Napi::String::New(env, "levenshtein"), Napi::Function::New(env, Levenshtein));
    return exports;
}

NODE_API_MODULE(addon, Init)
