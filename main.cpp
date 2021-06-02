#include <nan.h>

int counter = 0;

int fibonacci(int number)
{
    if (number == 0)
        return 0;
    if (number == 1)
        return 1;
    return fibonacci(number-1) + fibonacci(number-2);
}

void Method(const Nan::FunctionCallbackInfo<v8::Value>& info) {
    v8::Isolate* isolate = info.GetIsolate();

    if(info.Length() != 0 ){
        v8::Local<v8::String> errorMessage = Nan::New<v8::String>("The function takes no parameters").ToLocalChecked();
        isolate->ThrowException(v8::Exception::TypeError(errorMessage));
        return;
    }

    char *s = new char [60];
    ZeroMemory(s, 60);

    _itoa_s(fibonacci(counter++), s, 59, 10);
    info.GetReturnValue().Set(Nan::New(s).ToLocalChecked());
}

void Init(v8::Local<v8::Object> exports) {
  v8::Local<v8::Context> context = exports->CreationContext();
  exports->Set(context,
               Nan::New("get").ToLocalChecked(),
               Nan::New<v8::FunctionTemplate>(Method)
                   ->GetFunction(context)
                   .ToLocalChecked());
}

NODE_MODULE(get, Init)