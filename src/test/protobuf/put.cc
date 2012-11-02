#include <stdio.h>
#include <iostream>
#include <fstream>
#include "kv.pb.h"

using namespace std;
using namespace examples;
using namespace kv;

int main() {
  GOOGLE_PROTOBUF_VERIFY_VERSION;

  KV kv;
  kv.set_key("key1");
  kv.set_value("value1");
  fstream out("kv.pb", ios::out | ios::binary | ios::trunc);
  kv.SerializeToOstream(&out);
  out.close();
}

