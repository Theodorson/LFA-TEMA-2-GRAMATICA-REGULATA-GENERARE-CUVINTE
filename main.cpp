#include <iostream>
#include <fstream>
#include <string.h>
using namespace std;

struct Gramatica_regulata
{
    string neterminala_inceput;
    string terminala;
    string neterminala_sfarsit;
};

void citire_gramatica (Gramatica_regulata **A, int &nr_productii)
{
    ifstream f("date.txt");
    f>>nr_productii;
    (*A)=new Gramatica_regulata[nr_productii];

    for (int i=0; i<nr_productii; i++)
    {
        f>>(*A)[i].neterminala_inceput;
        f>>(*A)[i].terminala;
        f>>(*A)[i].neterminala_sfarsit;
    }
}

void afisare_gramatica(Gramatica_regulata *A,int nr_productii)
{
     cout<<"Simbolul '*' este destinat lui lambda, iar '!' corespunde productiilor de tipul S->a!.\n";
    cout<<"Gramatica:\n";
    for (int i=0; i<nr_productii; i++)
    {
        cout<<A[i].neterminala_inceput<<"->";
        cout<<A[i].terminala<<A[i].neterminala_sfarsit<<endl;
    }

}

bool neterminala_lambda (Gramatica_regulata* A, int nr_productii, string neterminala)
{
    for (int i=0; i<nr_productii; i++)
     if (A[i].neterminala_inceput==neterminala)
       {
         if (A[i].terminala=="*")
           return true;
       }
     return false;
}

bool producere_doar_terminala (Gramatica_regulata *A, int nr_productii, string neterminala)
{
    for (int i=0; i<nr_productii; i++)
     if (A[i].neterminala_inceput==neterminala)
       {
         if (A[i].terminala=="!")
           return true;
       }
     return false;
}

void generare_cuvinte (Gramatica_regulata* A, int nr_productii, string neterminala, string cuvant, int contor_cuvant, int lungime_maxima_cuvant)
{
    string cuvant_generat_de_aceasta_productie;

    if ((contor_cuvant==lungime_maxima_cuvant && neterminala_lambda(A,nr_productii,neterminala))||
       (contor_cuvant==lungime_maxima_cuvant && producere_doar_terminala(A,nr_productii,neterminala)))
      {
        cout<<cuvant<<" ";
        return;
      }

    if (contor_cuvant<lungime_maxima_cuvant)
    {
      for (int i=0; i<nr_productii; i++)
        if (A[i].neterminala_inceput==neterminala && A[i].terminala!="*")
        {
            cuvant_generat_de_aceasta_productie="";
            cuvant_generat_de_aceasta_productie=cuvant_generat_de_aceasta_productie + A[i].terminala;
            contor_cuvant=(cuvant+cuvant_generat_de_aceasta_productie).size();
            if (A[i].neterminala_sfarsit!="!")
            generare_cuvinte(A,nr_productii, A[i].neterminala_sfarsit, cuvant+cuvant_generat_de_aceasta_productie, contor_cuvant, lungime_maxima_cuvant);

            if (contor_cuvant==lungime_maxima_cuvant && A[i].neterminala_sfarsit=="!")
                cout<<cuvant+cuvant_generat_de_aceasta_productie<<" ";

        }

    }


}

int main()
{
    int lungime_maxima_cuvant,nr_productii;
    string cuvant;
    Gramatica_regulata *A;
    citire_gramatica (&A,nr_productii);
    afisare_gramatica (A,nr_productii);
    cout<<"Dati lungimea maxima a cuvintelor: ";
    cin>>lungime_maxima_cuvant;
    cout<<"Cuvintele de lungime "<<lungime_maxima_cuvant<<":\n";
    generare_cuvinte(A, nr_productii, "S", cuvant, 0, lungime_maxima_cuvant);
    return 0;
}
