/* Implementasi Method Breeding */

#include "Engimon.hpp"
#include <vector>

using std::vector;

bool isElementSimilar(Engimon& parent_a, Engimon& parent_b);
bool isElementAdvantageEqual(Engimon& parent_a, Engimon& parent_b);
bool isDualElement(Engimon& engi);
vector<Elements> sortElementAdvantage(Engimon& parent_a, Engimon& parent_b);
// Cara Sort : setiap elemen parent dibandingkan,

Engimon& breeding(Engimon& parent_a, Engimon& parent_b) 
{
    if (parent_a.level < 30 || parent_b.level < 30) {
        throw InvalidBreedingInsufficientLevel();
    }
    parent_a.level -= 30;
    parent_b.level -= 30;

    if (isElementSimilar(parent_a, parent_b)) {
        // Definisi similiar : ada element yang sama
        /* Jika elemen kedua parent sama, anak akan memiliki elemen yang sama dengan kedua parent. 
        Spesies anak dipilih dari parent A atau parent B secara bebas (boleh random atau aturan 
        spesifik tertentu). */
        
        

    } else {
        vector<Elements> listElement = sortElementAdvantage(parent_a,parent_b);
        /* Jika elemen kedua parent berbeda maka anak akan memiliki elemen dan spesies dari elemen 
        yang memiliki element advantage yang lebih tinggi. */
        if (!isElementAdvantageEqual(parent_a, parent_b)) {
            if (isDualElement(parent_a) && isDualElement(parent_b)) { // kedua parent dual elemen, anaknya juga dual elemen
                // ambil 2 terbesar dari sortElementAdvantage
            } else {
                // ambil 1 terbesar dari sortElementAdvantage
            }
        } else {
            /* a = b */
            /* Jika elemen kedua parent berbeda dan kedua elemen memiliki element advantage yang sama, 
            maka anak akan memiliki spesies berbeda dari kedua parent yang memiliki kedua elemen parent 
            (boleh dipilih random atau hardcoded). */
            // udah pasti dual element, ambil 2 terbesar dari sortElementAdvantage

        }    
    }  
}
