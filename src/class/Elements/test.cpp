#include "Elements.hpp"
#include <vector>
#include <iostream>

using std::string;
using std::vector;
using std::cout;
using std::endl;
using std::ostream;

vector<Elements> sortElementAdvantage(vector<Elements> parent_a, vector<Elements> parent_b) {
    vector<Elements> elementVector;
    vector<float> elementAdvantageVector;
    vector<Elements>::iterator it1;
    vector<float>::iterator it2;
    float elAdv;
    bool found;
    

    for (int i = 0; i < parent_a.size(); i++)
    {
        
        elAdv = 0;
        for (int j = 0; j < parent_b.size(); j++)
        {
            elAdv += ElementAdvantage[parent_a[i]][parent_b[j]];
        }

        it1 = elementVector.begin();
        it2 = elementAdvantageVector.begin();
        found = false;
        while (it2 != elementAdvantageVector.end() && !found)
        {
            if ((*it2) <= elAdv) {
                found = true;
            } else {
                it1++;
                it2++;
            }
        }
        elementAdvantageVector.insert(it2,elAdv);
        elementVector.insert(it1,parent_a.at(i));     
    }



    for (int i = 0; i < parent_b.size(); i++)
    {
        elAdv = 0;
        for (int j = 0; j < parent_a.size(); j++)
        {
            elAdv += ElementAdvantage[parent_b[i]][parent_a[j]];
        }
        it1 = elementVector.begin();
        it2 = elementAdvantageVector.begin();
        found = false;
        while (it2 != elementAdvantageVector.end() && !found)
        {
            if ((*it2) <= elAdv) {
                found = true;
            } else {
                it1++;
                it2++; 
            }
        }

        elementAdvantageVector.insert(it2,elAdv);
        elementVector.insert(it1,parent_b.at(i)); 
        
    }

    
    return elementVector;
    
}

int main()
{

    cout << "t1" << endl;

    vector<Elements>::iterator it;
    vector<Elements> el1 = {Fire,Water};
    vector<Elements> el2 = {Water,Electric};
    cout << "t2 " << el2.size() << endl;
    vector<Elements> elSorted = sortElementAdvantage(el1,el2);
    cout << "t3" << endl;
    for (it = elSorted.begin(); it < elSorted.end(); it++) 
    cout << elementName(*it) << " ";


    return 0;
}
