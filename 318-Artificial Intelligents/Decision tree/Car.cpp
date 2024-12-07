#include<bits/stdc++.h>
using namespace std;
class Car{
    // --class values

    // unacc, acc, good, vgood

    // --attributes

    // buying:   vhigh, high, med, low.
    // maint:    vhigh, high, med, low.
    // doors:    2, 3, 4, 5more.
    // persons:  2, 4, more.
    // lug_boot: small, med, big.
    // safety:   low, med, high.
    public:
    unordered_map<string,string> attributes;
    // string buying;
    // string maint;
    // string doors;
    // string persons;
    // string lug_boot;
    // string safety;
    // string accpetancy;

    Car(string buy,string maint,string doors,string persons,
            string lug_boot,string safety,string accpetancy){
                // this->buying = buy;
                // this->maint = maint;
                // this->doors = doors;
                // this->persons = persons;
                // this->lug_boot = lug_boot;
                // this->safety = safety;
                // this->accpetancy = accpetancy;
                attributes["buying"] = buy;
                attributes["maint"] = maint;
                attributes["doors"] = doors;
                attributes["persons"] = persons;
                attributes["lug_boot"] = lug_boot;
                attributes["safety"] = safety;
                attributes["acceptancy"] = accpetancy;
            }
    void printDetails(){
        cout<<"Buying : "<<attributes["buying"]<<endl;
        cout<<"Maint : "<<attributes["maint"]<<endl;
        cout<<"Doors : "<<attributes["doors"]<<endl;
        cout<<"Persons : "<<attributes["persons"]<<endl;
        cout<<"Lug Boot : "<<attributes["lug_boot"]<<endl;
        cout<<"Safety : "<<attributes["safety"]<<endl;
        cout<<"Accpetancy : "<<attributes["acceptancy"]<<endl;
    }
};