#include <eosiolib/eosio.hpp>
#include <eosiolib/print.hpp>

using namespace eosio;

CONTRACT helloworld : public contract {
  public:
    using contract::contract;
    helloworld(eosio::name receiver, eosio::name code, datastream<const char*> ds):contract(receiver, code, ds), customMessage(_self, _self.value) {}

    ACTION hi(name user);
    ACTION setmessage(name key, std::string message);
  
  private:
    TABLE tableStruct {
      name key;
      std::string name;
      auto primary_key() const { return key.value; }
    };
    typedef eosio::multi_index<"table"_n, tableStruct> table;
    
    table customMessage;
};

