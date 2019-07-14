#include <helloworld.hpp>

ACTION helloworld::hi(name user) {
  require_auth(user);
  print("Hello, ", name{user});
  
  const uint64_t index = user.value;
  
  const auto msgItr = customMessage.find(index);
  
  const auto ram_payer = _self;
  
  if ( msgItr != customMessage.end() ) {
    print(name{msgItr->name});
  } 
}

ACTION helloworld::setmessage(name key, std::string message) {
  require_auth(key);
  
  const uint64_t index = key.value;
  
  const auto msgItr = customMessage.find(index);
  
  const auto ram_payer = _self;
  
  if ( msgItr == customMessage.end() ) {
    customMessage.emplace(ram_payer, [&](tableStruct &t) {
        t.key = key;
        t.name = message;
    });
  } else {
    customMessage.modify(msgItr, ram_payer, [&](tableStruct &t) {
      t.name = message;  
    });
  }
}