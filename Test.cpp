#include "doctest.h"
#include "OrgChart.hpp"

using namespace std;
using namespace ariel;

TEST_CASE("BUILD"){
    OrgChart organization;

    CHECK_NOTHROW(organization.add_root("CEO"));
    CHECK_NOTHROW(organization.add_sub("CEO", "CTO"));         
    CHECK_NOTHROW(organization.add_sub("CEO", "CFO"));         
    CHECK_NOTHROW(organization.add_sub("CEO", "COO"));         
    CHECK_NOTHROW(organization.add_sub("CTO", "VP_SW"));
    CHECK_NOTHROW(organization.add_sub("COO", "VP_BI"));
    CHECK_THROWS(organization.add_sub("ALON", "CTO"));
    CHECK_THROWS(organization.add_sub("CEE", "ALON"));
    CHECK_NOTHROW(organization.add_root("NEW CEO"));
    
}

TEST_CASE("LEVEL ORDER"){

    // build an organization
    OrgChart organization;
    organization.add_root("Principle")
      .add_sub("Principle", "Vice Principle")         
      .add_sub("Principle", "Vice Principle2")         
      .add_sub("Vice Principle", "Teacher1")         
      .add_sub("Vice Principle", "Teacher2") 
      .add_sub("Vice Principle2", "Teacher3")
      .add_sub("Vice Principle2", "Teahcer4");  

    /*
        Principle
        | ---------------------------------------|
        Vice Principle                      Vice Principle2
        | ------------|                    |-----------------|
        Teahcer1    Teacher2              Teacher3         Teacher4
    */   

    vector<string> arr = {"Principle", "Vice Principle", "VIce Principle2", "Teacher1", "Teacher2", "Teacher3", "Teacher4"};
    size_t i = 0;
    for (auto it = organization.begin_level_order(); /*it != organization.end_level_order() &&*/ i < arr.size(); ++it)
    {
       CHECK((*it)->getName() == arr.at(i));
       i++;
    }


}


TEST_CASE("REVERSE LEVEL ORDER"){

    // build an organization
    OrgChart organization;
    organization.add_root("Principle")
      .add_sub("Principle", "Vice Principle")         
      .add_sub("Principle", "Vice Principle2")         
      .add_sub("Vice Principle", "Teacher1")         
      .add_sub("Vice Principle", "Teacher2") 
      .add_sub("Vice Principle2", "Teacher3")
      .add_sub("Vice Principle2", "Teahcer4");  

    /*
        Principle
        | ---------------------------------------|
        Vice Principle                      Vice Principle2
        | ------------|                    |-----------------|
        Teahcer1    Teacher2              Teacher3         Teacher4
    */   

    vector<string> arr = {"Principle", "Vice Principle", "VIce Principle2", "Teacher1", "Teacher2", "Teacher3", "Teacher4"};
    size_t i = arr.size()-1;
    for (auto it = organization.begin_reverse_order(); /*it != organization.reverse_order() ||*/ i > 0; ++it)
    {
        CHECK((*it)->getName() == arr.at(i));
        i--;
    }

}


TEST_CASE("PREORDER"){

    // build an organization
    OrgChart organization;
    organization.add_root("Principle")
      .add_sub("Principle", "Vice Principle")         
      .add_sub("Principle", "Vice Principle2")         
      .add_sub("Vice Principle", "Teacher1")         
      .add_sub("Vice Principle", "Teacher2") 
      .add_sub("Vice Principle2", "Teacher3")
      .add_sub("Vice Principle2", "Teahcer4");  

    /*
        Principle
        | ---------------------------------------|
        Vice Principle                      Vice Principle2
        | ------------|                    |-----------------|
        Teahcer1    Teacher2              Teacher3         Teacher4
    */   

    vector<string> arr = {"Principle", "Vice Principle", "Teacher1", "Teacher2","VIce Principle2", "Teacher3", "Teacher4"};
    size_t i = 0;
    for (auto it = organization.begin_reverse_order(); /*it != organization.reverse_order() ||*/ i < arr.size() ; ++it)
    {
        CHECK((*it)->getName() == arr.at(i));
        i++;
    }

}




