#include "portfolio.h"
#include<iostream>
#include "calculator.h"

BaseAccount::BaseAccount()
{
    auditcount_ = audit_.size() ;    
}

std::string BaseAccount::id()
{
    return std::string(id_) ;
}

long long BaseAccount::blance_Cents()
{
    return blance_cent_ ;
}

int BaseAccount::audit_size()
{
    return audit_.size() ;
}

const TxRecord *BaseAccount::getAudit_data()
{
    return audit_.data() ;
}

void BaseAccount::deposit(long long amount_cents, long long ts, std::string n)
{
    record(Deposit, amount_cents, ts, n) ;    
    blance_cent_ = apply_deposit(blance_cent_, amount_cents) ;
}

void BaseAccount::withdraw(long long amount_cents, long long ts, std::string n)
{
        record(Withdrawal, amount_cents, ts, n) ;
        blance_cent_ = apply_withdrawal(blance_cent_, amount_cents) ;
}

void BaseAccount::charge_fee(long long fee_cents, long long ts, std::string n)
{
    record(Fee, fee_cents, ts, n) ;    
    blance_cent_ = apply_fee(blance_cent_, fee_cents) ;
}

void BaseAccount::post_simple_interest(int days, int basis, long long ts, std::string n)
{
        record(Interest, basis, ts, n) ;    
        blance_cent_ += simple_interest(blance_cent_, settings_.apr, days ) ;

}

void BaseAccount::apply(const TxRecord &tx)
{
        switch (tx.kind)
    {
        case Deposit :
            deposit(tx.amount_cents, tx.timestamp, tx.note) ;
            break ;

        case Withdrawal :    
            withdraw(tx.amount_cents, tx.timestamp, tx.note) ;
            break ;
        
        case Fee :
            charge_fee(tx.amount_cents, tx.timestamp, tx.note) ;
            break ;

        default :
              std::cout<<"You have entered incorrect data! " << std::endl ;   
              break ;
    }       
}


void BaseAccount::record(TxKind kind, long long amount, long long ts, std::string note)
{
        if (auditcount_ < MaxAudit)
    {
        audit_[auditcount_].amount_cents = amount ;
        audit_[auditcount_].timestamp = ts ;
        audit_[auditcount_].note  = note ; 
        auditcount_ ++ ;

    }
    else 
    {
        auditcount_ = 0 ;
        audit_[auditcount_].amount_cents = amount ;
        audit_[auditcount_].timestamp = ts ;
        audit_[auditcount_].note  = note ; 
    }
}

AccountType CheckingAccount::type()
{
    return settings_.type = Checking ;
}

AccountType SavingsAccount::type()
{
    return settings_.type = Saving ;
}

void Portfolio::add(std::string id, std::unique_ptr<IAccount> account)
{
    account_.emplace(id, account)  ;
}

void Portfolio::apply_all(const std::vector<TxRecord> & acc)
{
    IAccount* apply ;
    for(int i = 0 ;i< acc.size(); i++)
    {
        switch (acc[i].kind)
        {
            case Deposit :
            apply->deposit(acc[i].amount_cents, acc[i].timestamp, acc[i].note) ;
            break;
            case Withdrawal :
             apply->withdraw(acc[i].amount_cents, acc[i].timestamp, acc[i].note) ;       
            break;
            case Fee :
            apply->charge_fee(acc[i].amount_cents, acc[i].timestamp, acc[i].note) ;        
            break;
            case Interest :
            apply->post_simple_interest(31, 365, acc[i].timestamp, acc[i].note) ;
            break;
            case TransferIn :

            break;
            case TransferOut :
            break;    
            default:
           break;
        }
    
    }
    
}

bool Portfolio::transfer(TransferRecord tr)
{
    if(account_.find(tr.from_id) != account_.end() && account_.find(tr.to_id) != account_.end())
       return true ;

    return false;
}

long long Portfolio::total_exposure()
{
    IAccount* Balance ;
    long long total_exposure = 0 ;
    for (auto it = account_.begin(); it != account_.end(); it++) 
    {
       Balance = get_account(it->first) ;
       total_exposure+= Balance->blance_Cents() ;
    }
    return total_exposure ;
}

IAccount* Portfolio::get_account(std::string ID)
{
    
    return account_.at(ID).get() ;
}

int Portfolio::getCountAccounts()
{
    return account_.size() ;
}
