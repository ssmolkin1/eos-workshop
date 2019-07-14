#include <eosiolib/eosio.hpp>
#include <eosiolib/print.hpp>

using namespace eosio;

CONTRACT wallet : public contract {
  public:
    using contract::contract;
    wallet(eosio::name receiver, eosio::name code, datastream<const char*> ds):contract(receiver, code, ds), limits(_self, _self.value), balances(_self, _self.value) {}

    ACTION setdaylimit(name user, asset limit);
    ACTION withdraw(name user, name to, asset quantity);
    
    [[eosio::on_notify("eosio.token::transfer")]] void transfer(name from, name to,  asset quantity, std::string memo);
  
  private:
    TABLE tableStruct {
      name key;
      asset amount;
      
      auto primary_key() const { return key.value; }
    };
    typedef eosio::multi_index<"table"_n, tableStruct> table;
    
    table limits;
    table balances;
};
