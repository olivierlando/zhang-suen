// zhang-suen.cc
#include <node.h>
#include <nan.h>
#include <vector>
#include <queue>

using namespace std;

#define P1(vect, x, y, width) ( (vect)[((x)   + (y)   * (width))] == 1 )
#define P2(vect, x, y, width) ( (vect)[((x)   + (y-1) * (width))] == 1 )
#define P3(vect, x, y, width) ( (vect)[((x+1) + (y-1) * (width))] == 1 )
#define P4(vect, x, y, width) ( (vect)[((x+1) + (y)   * (width))] == 1 )
#define P5(vect, x, y, width) ( (vect)[((x+1) + (y+1) * (width))] == 1 )
#define P6(vect, x, y, width) ( (vect)[((x)   + (y+1) * (width))] == 1 )
#define P7(vect, x, y, width) ( (vect)[((x-1) + (y+1) * (width))] == 1 )
#define P8(vect, x, y, width) ( (vect)[((x-1) + (y)   * (width))] == 1 )
#define P9(vect, x, y, width) ( (vect)[((x-1) + (y-1) * (width))] == 1 )

#define NEIGHBOURS(vect, x, y, width) ( (P2((vect), (x), (y), (width)) ? 1 : 0) + \
                                        (P3((vect), (x), (y), (width)) ? 1 : 0) + \
                                        (P4((vect), (x), (y), (width)) ? 1 : 0) + \
                                        (P5((vect), (x), (y), (width)) ? 1 : 0) + \
                                        (P6((vect), (x), (y), (width)) ? 1 : 0) + \
                                        (P7((vect), (x), (y), (width)) ? 1 : 0) + \
                                        (P8((vect), (x), (y), (width)) ? 1 : 0) + \
                                        (P9((vect), (x), (y), (width)) ? 1 : 0) )

#define TRANSITIONS(vect, x, y, width) ( ((!P2((vect), (x), (y), (width)) && P3((vect), (x), (y), (width))) ? 1 : 0) + \
                                         ((!P3((vect), (x), (y), (width)) && P4((vect), (x), (y), (width))) ? 1 : 0) + \
                                         ((!P4((vect), (x), (y), (width)) && P5((vect), (x), (y), (width))) ? 1 : 0) + \
                                         ((!P5((vect), (x), (y), (width)) && P6((vect), (x), (y), (width))) ? 1 : 0) + \
                                         ((!P6((vect), (x), (y), (width)) && P7((vect), (x), (y), (width))) ? 1 : 0) + \
                                         ((!P7((vect), (x), (y), (width)) && P8((vect), (x), (y), (width))) ? 1 : 0) + \
                                         ((!P8((vect), (x), (y), (width)) && P9((vect), (x), (y), (width))) ? 1 : 0) + \
                                         ((!P9((vect), (x), (y), (width)) && P2((vect), (x), (y), (width))) ? 1 : 0) )
                                        
namespace zhangsuen {

using v8::FunctionCallbackInfo;
using v8::Isolate;
using v8::Local;
using v8::Object;
using v8::Array;
using v8::Value;
using v8::Number;
using v8::Uint8Array;

void thin(const FunctionCallbackInfo<Value>& args) {
  Isolate* isolate = args.GetIsolate(); 

  assert(args[0]->IsUint8Array());
  Local<Uint8Array> myarr = args[0].As<Uint8Array>();
  Nan::TypedArrayContents<int8_t> pointsVector(myarr);
  int width = Local<Number>::Cast(args[1])->IntegerValue();
  int height = Local<Number>::Cast(args[2])->IntegerValue();

  bool needToContinue = false;
  do {
    needToContinue = false;
    vector<int> toWhite;

    for( int x = 1 ; x < width-1 ; x++) {
        for( int y = 1 ; y < height-1 ; y++) {
            if(!P1((*pointsVector), x, y, width)) continue;
            int n = NEIGHBOURS((*pointsVector), x, y, width);
            if(n < 2 || n > 6) continue;
            if(TRANSITIONS((*pointsVector), x, y, width) != 1) continue;
            if(P2((*pointsVector), x, y, width) && P4((*pointsVector), x, y, width) && P6((*pointsVector), x, y, width)) continue;
            if(P4((*pointsVector), x, y, width) && P6((*pointsVector), x, y, width) && P8((*pointsVector), x, y, width)) continue;

            toWhite.push_back(x + y * width);
        }
    }
    
    needToContinue = toWhite.size() > 0;
    for (unsigned int i = 0; i < toWhite.size(); i++ ) {
        (*pointsVector)[toWhite[i]] = 0;
    }
    toWhite.clear();
    for( int x = 1 ; x < width-1 ; x++) {
        for( int y = 1 ; y < height-1 ; y++) {
            if(!P1((*pointsVector), x, y, width)) continue;
            int n = NEIGHBOURS((*pointsVector), x, y, width);
            if(n < 2 || n > 6) continue;
            if(TRANSITIONS((*pointsVector), x, y, width) != 1) continue;
            if(P2((*pointsVector), x, y, width) && P4((*pointsVector), x, y, width) && P8((*pointsVector), x, y, width)) continue;
            if(P2((*pointsVector), x, y, width) && P6((*pointsVector), x, y, width) && P8((*pointsVector), x, y, width)) continue;

            toWhite.push_back(x + y * width);
        }
    }
    needToContinue = needToContinue || toWhite.size() > 0;
    for (unsigned int i = 0; i < toWhite.size(); i++ ) {
        (*pointsVector)[toWhite[i]] = 0;
    }
  } while(needToContinue);

  Local<Array> results = Array::New(isolate);
  for ( int i = 0; i < width * height; i++ ) {
    results->Set(i, Number::New(isolate, (*pointsVector)[i]));
  }
  args.GetReturnValue().Set(results);
} 

void init(Local<Object> exports) {
  NODE_SET_METHOD(exports, "thin", thin);
}

NODE_MODULE(addon, init)
}