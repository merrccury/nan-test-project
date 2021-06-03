#include <nan.h>

class NanFibonacci: public Nan::ObjectWrap {
private:
    int counter;
    int fibonacci(int);
public:

  static NAN_MODULE_INIT(Init);
  static NAN_METHOD(New);
  static NAN_METHOD(Get);

  static Nan::Persistent<v8::FunctionTemplate> constructor;
};

int NanFibonacci::fibonacci(int number){
    if (number == 0)
        return 0;
    if (number == 1)
        return 1;
    return fibonacci(number-1) + fibonacci(number-2);
}

Nan::Persistent<v8::FunctionTemplate> NanFibonacci::constructor;

NAN_MODULE_INIT(NanFibonacci::Init) {
  v8::Local<v8::FunctionTemplate> ctor = Nan::New<v8::FunctionTemplate>(NanFibonacci::New);
  constructor.Reset(ctor);
  ctor->InstanceTemplate()->SetInternalFieldCount(1);
  ctor->SetClassName(Nan::New("NanFibonacci").ToLocalChecked());
  Nan::SetPrototypeMethod(ctor, "get", Get);
  Nan::Set(target, Nan::New("NanFibonacci").ToLocalChecked(), Nan::GetFunction(ctor).ToLocalChecked());
}

NAN_METHOD(NanFibonacci::New) {

  if(!info.IsConstructCall()) {
    return Nan::ThrowError(Nan::New("NanFibonacci::New - called without new keyword").ToLocalChecked());
  }

  if(info.Length() != 0) {
    return Nan::ThrowError(Nan::New("NanFibonacci::New - didn't expect any arguments").ToLocalChecked());
  }

  NanFibonacci* fib = new NanFibonacci();
  fib->Wrap(info.Holder());
  fib->counter = 0;
  info.GetReturnValue().Set(info.Holder());
}


NAN_METHOD(NanFibonacci::Get) {
  NanFibonacci * self = Nan::ObjectWrap::Unwrap<NanFibonacci>(info.This());

  if (Nan::New(NanFibonacci::constructor)->HasInstance(info[0])) {
    return Nan::ThrowError(Nan::New("NanFibonacci::Get - didn't expect argument to be instance of NanFibonacci").ToLocalChecked());
  }

   char *s = new char [60];
   ZeroMemory(s, 60);

   _itoa_s(self->fibonacci(self->counter), s, 59, 10);
   self->counter +=1;
   info.GetReturnValue().Set(Nan::New(s).ToLocalChecked());
   delete[] s;
}

NAN_MODULE_INIT(InitModule) {
  NanFibonacci::Init(target);
}

NODE_MODULE(NanFibonacci, InitModule);