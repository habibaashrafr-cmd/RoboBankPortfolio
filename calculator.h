#ifndef _CALCULATOR_H
#define _CALCULATOR_H


#include<string>

//1.Balance Operations
int apply_deposit(int balance,int  amount);
int apply_withdrawal(int balance,int amount);
int apply_fee(int balance,int fee);

//2.Interest
int simple_interest(int base,double apr,int days);
int  compound_amount(int principal,int apr,int  years,int compounds_per_year);

// 3. Currency Conversion
int fx_convert(int amount,std::string from_currency,std::string to_currency);


//4. Utilities
int percent_of(int amount,float rate);
bool validate_rate(float rate);
bool validate_non_negative(int amount);


#endif //  _CALCULATOR_H