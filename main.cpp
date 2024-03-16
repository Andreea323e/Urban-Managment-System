#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
using namespace std;

class Person{
public:
    string mName;
    uint16_t mAge;
    double mSalary;
    Person(string Name, uint16_t Age, double Salary):mName(Name), mAge(Age), mSalary(Salary){}
    Person(){
        mName='\0';
        mAge=0;
        mSalary=0;
    }
    bool operator==(const Person& pers) const{
        if(mName==pers.mName&&mAge==pers.mAge&&mSalary==pers.mSalary)
            return true;
        else return false;
    }
    bool operator<(const Person& pers) const{
        if(mName<pers.mName) return true;
        else return false;
    }
};

class Building{
protected:
    string mBuildingName;
    string mType;
    Person mCoordinator;
    vector <Person> mEmployees;
    vector <Person> mCitizens;
public:
    Building(string Name, string Type): mBuildingName(Name), mType(Type){}
    virtual void add(const Person& person)=0;
    virtual void remove(const Person& person)=0;
    virtual Building* operator+(const Person& person)=0;
    virtual Building* operator-(){
        return nullptr;
    }
    virtual Building* operator-(const Person& person){
        return nullptr;
    }
    string getBuildingName() const {return mBuildingName;}
    string getType() const {return mType;}
    uint16_t getEmployeesSize() const {return mEmployees.size();}
    uint16_t getCitizensSize() const {return mCitizens.size();}
    Person getEmployee(uint16_t index) const {return mEmployees[index];}
    Person getCitizen(uint16_t index) const {return mCitizens[index];}
    Person getCoordinator() const {return mCoordinator;}
};

class CityHall:public Building{
public:
    CityHall(string name): Building(name, "CityHall") {
        mCitizens.clear();
        mCoordinator=Person();
    }
    Building* operator+(const Person& person) override{
        if(mCoordinator==Person()) {
            mCoordinator=Person(person.mName, person.mAge, person.mSalary);
            return this;
        }
        else return this;
    }
    Building* operator-()override{
        mCoordinator=Person();
        return this;
    }
    void add(const Person& person) override {
        mCitizens.push_back(person);
    }
    void remove(const Person& person) override{
        for(int i=0; i<mCitizens.size(); i++){
            if(person.mName==mCitizens[i].mName){
                auto it=mCitizens.begin()+i;
                mCitizens.erase(it);
                break;
            }
        }
    }
};

class Hospital: public Building{
public:
    Hospital(string name): Building(name, "Hospital"){
        mCitizens.clear();
        mEmployees.clear();
    }
    Building* operator+(const Person& person) override{
        mEmployees.push_back(person);
        return this;
    }
    Building* operator-(const Person& person) override{
        for(int i=0; i<mEmployees.size();i++){
            if(person.mName==mEmployees[i].mName){
                auto it=mEmployees.begin()+i;
                mEmployees.erase(it);
                break;
            }
        }
        return this;
    }
    void add(const Person& person) override{
        mCitizens.push_back(person);
    }
    void remove(const Person& person) override{
        for(int i=0; i<mCitizens.size(); i++){
            if(person.mName==mCitizens[i].mName){
                auto it=mCitizens.begin()+i;
                mCitizens.erase(it);
                break;
            }
        }
    }
};

class PoliceStation: public Building{
public:
    PoliceStation(string name): Building(name, "PoliceStation"){
        mCitizens.clear();
        mEmployees.clear();
    }
    Building* operator+(const Person& person)override{
        mEmployees.push_back(person);
        return this;
    }
    Building* operator-(const Person& person)override{
        for(int i=0; i<mEmployees.size();i++){
            if(mEmployees[i].mName==person.mName){
                auto it=mEmployees.begin()+i;
                mEmployees.erase(it);
            }
        }
        return this;
    }
    virtual void add(const Person& person) override{
        mCitizens.push_back(person);
    }
    void remove(const Person& person) override{
        for(int i=0; i<mCitizens.size(); i++){
            if(person.mName==mCitizens[i].mName){
                auto it=mCitizens.begin()+i;
                mCitizens.erase(it);
            }
        }
    }
};

class House: public Building{
private:
    uint16_t mMaxNumber;
public:
    House(string name, uint16_t maxn): Building(name, "House"),mMaxNumber(maxn){
        mCitizens.clear();
        mEmployees.clear();
    }
    Building* operator+(const Person& person) override{
        if(mCoordinator==Person()) {
            mCoordinator=Person(person.mName, person.mAge, person.mSalary);
            return this;
        }
        else return this;
    }
    Building* operator-()override{
        mCoordinator=Person();
        return this;
    }
    void add(const Person& person) override{
        if(mCitizens.size()<mMaxNumber-1){
            mCitizens.push_back(person);
        }
    }
    void remove(const Person& person) override{
        for(int i=0; i<mCitizens.size(); i++){
            if(person==mCitizens[i]&&person.mAge>=18){
                auto it=mCitizens.begin()+i;
                mCitizens.erase(it);
            }
        }
    }
};

class Block:public Building{
private:
    uint16_t mMaxNumberPerFloor;
public:
    Block(string name, uint16_t floors, uint16_t maxpeopleperfloor): Building(name, "Block"), mMaxNumberPerFloor(maxpeopleperfloor){
        mCitizens.clear();
        mEmployees.clear();
        for(int i=0; i<floors*maxpeopleperfloor;i++) mCitizens.push_back(Person());
    }
    Building* operator+(const Person& person) override{
        if(mCoordinator==Person()) mCoordinator=Person(person.mName, person.mAge, person.mSalary);
        return this;
    }
    Building* operator-() override{
        mCoordinator=Person();
        return this;
    }
    void add(const Person& person){
        int i=0;
        while(!(mCitizens[i]==Person())){
            i++;
        }
        mCitizens[i]=Person(person.mName, person.mAge, person.mSalary);
//        for(int i=0; i<mCitizens.size();i++){
//            if(mCitizens[i]==Person()) mCitizens[i]=Person(person.mName, person.mAge, person.mSalary);
//        }
    }
    void remove(const Person& person) override{
        if(person.mAge>=18) {
            for (int i=0; i<mCitizens.size();i++) {
                if (person== mCitizens[i]) {
                    mCitizens[i] = Person();
                }
            }
        }
    }
};
int main() {
    vector<Building*> Buildings;
    string comanda;
    string tip;
    string name_build;
    uint16_t max_pers;
    uint16_t floors;
    while(cin>>comanda>>tip){
        if(tip=="CityHall"){
            cin>>name_build;
            Buildings.push_back(new CityHall(name_build));
        }
        if(tip=="Hospital"){
            cin>>name_build;
            Buildings.push_back(new Hospital(name_build));
        }
        if(tip=="PoliceStation"){
            cin>>name_build;
            Buildings.push_back(new PoliceStation(name_build));
        }
        if(tip=="House"){
            cin>>name_build;
            cin>>max_pers;
            Buildings.push_back(new House(name_build, max_pers));
        }
        if(tip=="Block"){
            cin>>name_build;
            cin>>floors;
            cin>>max_pers;
            Buildings.push_back(new Block(name_build, floors, max_pers));
        }
        string name_pers;
        uint16_t age_pers;
        double salary_pers;
        string build_p;
        if(comanda=="add"){
            if(tip=="coordinator"){
                cin>>name_pers>>age_pers>>salary_pers>>build_p;
                Person person_rd(name_pers, age_pers, salary_pers);
                for(auto & it : Buildings){
                    if(build_p==it->getBuildingName()) {
                        it->operator+(person_rd);
                        break;
                    }
                }
            }
            if(tip=="employee"){
                cin>>name_pers>>age_pers>>salary_pers>>build_p;
                Person person_rd(name_pers, age_pers, salary_pers);
                for(auto & it : Buildings){
                    if(build_p==it->getBuildingName()) {
                        it->operator+(person_rd);
                        break;
                    }
                }
            }
            if(tip=="citizen"){
                cin>>name_pers>>age_pers>>salary_pers;
                cin>>build_p;
                Person person_rd(name_pers, age_pers, salary_pers);
                for(int i=0; i<Buildings.size();i++){
                    if(build_p==Buildings[i]->getBuildingName()) {
                        Buildings[i]->add(person_rd);
                        break;
                    }
                }
            }
        }
        if(comanda=="remove"){
            if(tip=="coordinator"){
                cin>>name_pers>>build_p;
                Person person_rd(name_pers, age_pers, salary_pers);
                for(auto & it : Buildings){
                    if(build_p==it->getBuildingName()) {
                        it->operator-();
                        break;
                    }
                }
            }
            if(tip=="employee"){
                cin>>name_pers>>build_p;
                Person person_rd(name_pers, 0, 0);
                for(auto & it : Buildings){
                    if(build_p==it->getBuildingName()) {
                        it->operator-(person_rd);
                        break;
                    }
                }
            }
            if(tip=="citizen"){
                cin>>name_pers>>build_p;
                Person person_rd;
                for(int i=0; i<Buildings.size();i++){
                    if(build_p==Buildings[i]->getBuildingName()) {
                        for(int k=0; k<Buildings[i]->getCitizensSize();k++){
                            if(name_pers==Buildings[i]->getCitizen(k).mName)
                                person_rd=Person(name_pers,Buildings[i]->getCitizen(k).mAge , Buildings[i]->getCitizen(k).mSalary);
                        }
                        Buildings[i]->remove(person_rd);
                    }
                }
            }
        }
    }
    int cit_count=0, hosp_count=0,plc_count=0,house_count=0, blk_count=0;
    int number_doc=0, number_cops=0, number_mayors=0, number_hall_employees=0, number_busted=0;
    int number_patients=0;
    double average_salary_doc=0, average_salary_cops=0, average_salary_mayors=0, average_salary_hall_employees=0 ;
    double average_busted_age=0;
    for(int i=0;i<Buildings.size();i++){
        if(Buildings[i]->getType()=="CityHall") {
            cit_count+=1;
            if(Buildings[i]->getCoordinator()==Person()) number_mayors+=0;
            else{
                average_salary_mayors+=Buildings[i]->getCoordinator().mSalary;
                number_mayors+=1;
            }
            for(int j=0;j<Buildings[i]->getCitizensSize();j++){
                average_salary_hall_employees+=Buildings[i]->getCitizen(j).mSalary;
            }
            number_hall_employees+=Buildings[i]->getCitizensSize();
        }
        if(Buildings[i]->getType()=="Hospital") {
            hosp_count+=1;
            number_patients+=Buildings[i]->getCitizensSize();
            for(int j=0;j<Buildings[i]->getEmployeesSize();j++){
                average_salary_doc+=Buildings[i]->getEmployee(j).mSalary;
            }
            number_doc+=Buildings[i]->getEmployeesSize();
        }
        if(Buildings[i]->getType()=="PoliceStation") {
            plc_count+=1;
            for(int j=0;j<Buildings[i]->getEmployeesSize();j++){
                average_salary_cops+=Buildings[i]->getEmployee(j).mSalary;
            }
            number_cops+=Buildings[i]->getEmployeesSize();
            for(int j=0; j<Buildings[i]->getCitizensSize();j++){
                average_busted_age+=Buildings[i]->getCitizen(j).mAge;
            }
            number_busted+=Buildings[i]->getCitizensSize();
        }
        if(Buildings[i]->getType()=="House") house_count+=1;
        if(Buildings[i]->getType()=="Block") blk_count+=1;
    }

    if(average_salary_doc!=0) average_salary_doc/=number_doc;
    if(average_salary_cops!=0) average_salary_cops/=number_cops;
    if(average_salary_mayors!=0) average_salary_mayors/=number_mayors;
    if(average_salary_hall_employees!=0) average_salary_hall_employees/=number_hall_employees;
    if(average_busted_age!=0) average_busted_age/=number_busted;

    if(cit_count>=3&&hosp_count>=2&&plc_count>=3&&house_count>=8&&blk_count>=4)
        cout<<"Type: Capital"<<endl;
    else if(cit_count>=2&&hosp_count>=1&&plc_count>=2&&house_count>=4&&blk_count>=1)
        cout<<"Type: Town"<<endl;
    else cout<<"Type: Village"<<endl;

    cout<<"Number of patients in hospitals: "<<number_patients<<endl;
    cout<<"Average salary for doctors: "<<average_salary_doc<<endl;
    cout<<"Average salary for cops: "<<average_salary_cops<<endl;
    cout<<"Average salary for mayors: "<<average_salary_mayors<<endl;
    cout<<"Average salary for city hall employees: "<<average_salary_hall_employees<<endl;
    cout<<"Average age of busted in police stations: "<<average_busted_age<<endl;
    for(int i=0; i<Buildings.size();i++){
        int number_ppl=0;
        if(Buildings[i]->getType()=="House"){
            if(Buildings[i]->getCoordinator().mAge!=0) number_ppl+=1;
            for(int j=0;j<Buildings[i]->getCitizensSize();j++)
                if(Buildings[i]->getCitizen(j).mAge!=0) number_ppl+=1;
//            number_ppl+=Buildings[i]->getCitizensSize();
            cout<<"Number of people in House "<<Buildings[i]->getBuildingName()<<": "<<number_ppl<<endl;
        }
        if(Buildings[i]->getType()=="Block"){
            if(Buildings[i]->getCoordinator().mAge!=0) number_ppl+=1;
            for(int j=0;j<Buildings[i]->getCitizensSize();j++){
                if(Buildings[i]->getCitizen(j).mAge!=0) number_ppl+=1;
            }
            cout<<"Number of people in Block "<<Buildings[i]->getBuildingName()<<": "<<number_ppl<<endl;
        }
    }
    vector <string> administrators;
    for(int i=0; i<Buildings.size();i++){
        string name_both="\0";
        if(Buildings[i]->getType()=="House") {
            if (Buildings[i]->getCoordinator().mAge != 0) {
                for (int j = 0; j < Buildings.size(); j++) {
                    if (Buildings[j]->getType() == "Block") {
                        if (Buildings[j]->getCoordinator().mAge != 0)
                            if(Buildings[i]->getCoordinator()==Buildings[j]->getCoordinator()) {
                                name_both = (Buildings[i]->getCoordinator().mName);
                                if(name_both!="\0") administrators.push_back(name_both);
                            }
                    }
                }
            }
        }
    }
    if(administrators.empty()) administrators.push_back("Nobody");
    cout<<"Administrators of house and block: ";
    for(int i=0;i<administrators.size();i++){
        cout<<administrators[i];
        if(i!=administrators.size()) cout<<" ";
    }
    return 0;
}
