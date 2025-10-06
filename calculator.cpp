#include<iostream>
#include <cmath> 
#include "calculator.h" 
#define num_currency   4


float fix_convert[num_currency] = {.01,0.48,0.009 ,0.0074}; 
/*
USD = .01
EGP = 0.48 
EUR = 0.009 
GBP = 0.0074 
*/

int apply_deposit(int balance,int amount){
    return (balance+amount);
}

int apply_withdrawal(int balance,int amount){
    return (balance-amount);
}


int apply_fee(int balance,int fee){
    return (balance-fee);
}


int simple_interest(int base,double apr,int days){
    long double Inter =base*(apr)*(days/365.0);
    return (nearbyint(Inter));
}


int compound_amount(int principal,double apr,int  years,int compounds_per_year){
    double base=1+((apr)/compounds_per_year);
    long double compound= principal*(pow(base,(compounds_per_year*years)));
    return (nearbyint(compound));
}

int fx_convert(int amount,std::string to_currency){

    if(to_currency=="USD")
            return (nearbyint((amount * fix_convert[0])));
    else if(to_currency== "EGP")
        return (nearbyint((amount * fix_convert[1])));
    else if(to_currency=="EUR")
        return (nearbyint((amount * fix_convert[2])));
    else if(to_currency=="GBP")
        return (nearbyint((amount * fix_convert[3])));
    else   
       return 0;             
}


int percent_of(int amount,float rate){
    long double fee=amount*(rate/100.0);
    return (nearbyint(fee));
}


bool validate_rate(float rate){
    if((rate/100)>=0 && ((rate/100)<=1 ))
       return true;
    else
      return false;   
}

bool validate_non_negative(int amount){
    if(amount>=0)
       return true;
    else
        return false;   
}