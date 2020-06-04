#include "phone_number.h"
#include <string>
#include <sstream>
#include <stdexcept>
PhoneNumber::PhoneNumber(const string &international_number)
{
    istringstream s(international_number);
    bool ok = true;
    char format=0;
    string country_code, city_code, local_number;

    ok = ok && (s >> format);
    ok = ok && format == '+';

    getline(s, country_code, '-');
    ok = ok && s;

    getline(s, city_code, '-');
    ok = ok && s;

    ok = ok && (s >> local_number);

    if (!ok)
    {
        throw invalid_argument("Bad format: " + international_number);
    }
    country_code_ = country_code;
    city_code_ = city_code;
    local_number_ = local_number;
}

string PhoneNumber::GetCountryCode() const
{
    return country_code_;
}
string PhoneNumber::GetCityCode() const
{
    return city_code_;
}
string PhoneNumber::GetLocalNumber() const
{
    return local_number_;
}
string PhoneNumber::GetInternationalNumber() const
{
    return "+"+country_code_+"-"+city_code_+"-"+local_number_;
}
