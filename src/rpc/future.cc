#include "connection.h"
#include "future.h"

#include <string>

namespace rtm {
namespace rpc {
Future::Future() :
    deadline_(-1),
    connection(NULL),
    id(-1),
    status(kCallPending) {
}

Future::~Future() {
//  Log_Warn("TODO: block if this future hasn't been waited for.");
}

void Future::init(Connection* socket, int64_t id) {
  this->connection = socket;
  this->id = id;
}

void Future::readHeader(Decoder* d) {
  d->read(reinterpret_cast<int*>(&status));
  if (status != kCallSuccess) {
    marshal::read(d, &errorTrace);
  }
}

void Future::wait() {
  if (status == kCallPending) {
    Log_Assert(connection != NULL, "Tried to wait on uninitialized future.");
    connection->wait(this);
  }
}

} // namespace rpc
} // namespace rtm
