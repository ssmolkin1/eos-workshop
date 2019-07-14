#include <wallet.hpp>

ACTION wallet::hi(name user) {
  require_auth(user);
  print("Hello, ", name{user});
}
