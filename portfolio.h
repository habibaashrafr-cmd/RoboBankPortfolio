#ifndef _PORTFOLIO_H
#define _PORTFOLIO_H

#include<string>
#include<vector>
#include<unordered_map>
#include<memory>
#define MaxAudit  256

//Enumerations
enum AccountType {Checking , Saving} ;
enum TxKind {Deposit, Withdrawal, Fee, Interest, TransferIn, TransferOut} ;
//Structs
struct AccountSettings
{
   AccountType type ;
   double apr ;
   long long fee_flat_cents ;
};

struct TxRecord
{
   TxKind kind ;
   long long amount_cents ;
   long long timestamp ;
   std::string note ;
   std::string account_id ;
};

struct TransferRecord
{
    std::string from_id ;
    std::string to_id ;
    long long amount_cents ;
    long long timestamp ;
    std::string note ;
};

//Class Design

class IAccount
{
public :
    virtual std::string id() = 0 ;
    virtual AccountType type() = 0 ;
    virtual long long blance_Cents() = 0 ;
    virtual int audit_size() = 0 ;
    virtual const TxRecord* getAudit_data() = 0 ; 
    virtual void deposit(long long amount_cents, long long ts, std::string n) = 0 ;
    virtual void withdraw(long long amount_cents, long long ts, std::string n) = 0  ;
    virtual void charge_fee(long long fee_cents, long long ts, std::string n) = 0 ;
    virtual void post_simple_interest(int days, int basis, long long ts, std::string n) = 0 ;
    virtual void Transfarin(TransferRecord t) = 0 ;
    virtual void Transfarout(TransferRecord t) = 0 ;
    virtual void apply(const TxRecord& tx) ;    
};

class BaseAccount :  public IAccount
{
public :
    BaseAccount() ;
    virtual AccountType type() = 0 ;
    std::string id() override ;
    long long blance_Cents() override ;
    int audit_size() override ;
    const TxRecord* getAudit_data() override ; 
    void deposit(long long amount_cents, long long ts, std::string n) override ;
    void withdraw(long long amount_cents, long long ts, std::string n) override  ;
    void charge_fee(long long fee_cents, long long ts, std::string n) override ;
    void post_simple_interest(int days, int basis, long long ts, std::string n) override ;
    void apply(const TxRecord& tx) ;
    void Transfarin(TransferRecord t)  ;
    void Transfarout(TransferRecord t)  ;
 
    
 
protected :
    std::string id_ ;
    long long blance_cent_ ;
    AccountSettings settings_ ;   
    std::vector<TxRecord> audit_ ;
    int auditcount_ ;
    void record(TxKind kind, long long amount, long long ts, std::string note) ;
};

class CheckingAccount : public BaseAccount

{
public :
    AccountType type() override ;
};

class SavingsAccount : public BaseAccount
{
public :
    AccountType type() override ;
};

class Portfolio
{
public :
    IAccount* get_account(std::string ID) ;
    int getCountAccounts() ;
    void add(std::string id, std::unique_ptr<IAccount> account) ;
    void apply_all(const std::vector<TxRecord>& acc) ;
    bool transfer(TransferRecord tr) ;
    long long total_exposure() ;



private :
    std::unordered_map<std::string, std::unique_ptr<IAccount>> account_ ;
    std::vector<TxRecord> batches ;
};








































#endif  // _PORTFOLIO_H