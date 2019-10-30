/*
Se considera Class Nod{ int info; Nod* next;}
- constructori de inițializare și parametrizati pentru clasa Nod;
- destructor pentru clasa Nod;
Clasa Lista_circulara are:
- cel puțin un membru privat „Nod*” reprezentând nodul considerat prim;
- metoda publica de adaugare a unui element pe o poziție;
- supraincarcare a operatorului >>, realizata prin utilizarea succesiva a metodei decarata anterior;
- metoda publica de stergere a unui element de pe o poziție;
- metoda publica pentru inversarea legaturilor listei;
- metoda publica care primește parametrul întreg k și realizatea eliminarea elementelor listei circulare din k
în k pana la golirea acesteia (elementele vor fi afisate în ordinea în care sunt eliminate);
- supraincarcarea operatorului +, care sa efectueze concatenarea a doua liste circulare, rezultand într-o noua
lista circulara (ca în exemplul de mai jos).
Lista_circulara L1 = { 1 → 2 → 3 → 1} , L2 = {4 → 5 → 6 → 4}
L1 + L2 = { 1 → 2 → 3 → 4 → 5 → 6 → 1}

*/


#include <iostream>
#include <fstream>

using namespace std;

ofstream f("date.in");

class Nod
{
    int info;
    Nod* next;
    public:
    Nod()
    {
        info=0;
        next=NULL;
    }

    Nod(int inf)
    {
        info=inf;
        next=NULL;
    }
    public:
    int getInfo()
    {
        return info;;
    }

    Nod* getAdr()
    {
        return next;
    }
    void setInfo(int inf)
    {
        info=inf;
    }

    void setNext(Nod* nou)
    {
        next=nou;
    }

    void setNext()
    {
        next=NULL;
    }



    friend ostream& operator<< (ostream& out, Nod &n)
    {
    out<<n.info;
    return out;
    }

    friend istream &operator>>( istream  &in, Nod &n)
    {

    in>>n.info;
    return in;
    }
    friend class Lista_circulara;


};

class Lista_circulara
{
    Nod* prim;
    int lungime;            //am folosit un camp de lungime care a facut totul mai usor
    public:                 //probabil puteam sa fac citirea ca la liste simplu inlantuite
    Lista_circulara()       //dar ar fi fost nevoie sa gasesc o valoare de sfarsit pentru lista
    {                       //iar la parcurgeri trebuie sfarsitul listei era atunci cand
        prim=new Nod(0);    //pointerul de parcurgere devenea egal cu primul ???
        lungime=0;

    }

    void set_prim(Nod *p)
    {
        prim=p;
    }


    public:

   friend ostream& operator<< (ostream& out, Lista_circulara &l)
    {
        out<<endl<<"Lista este: "<<endl;
        int i;
        Nod* parcurg=l.prim;
        for(i=1;i<=l.lungime;i++)
        {
            out<<*parcurg<<" ";
            parcurg=parcurg->getAdr();
        }

        return out;
    }

    friend istream &operator>>( istream  &in, Lista_circulara &l)
    {
    int i=1;
    l.lungime=1;
    int n;
    cout<<"Lungime lista ";
    in>>n;
    int inf;
    //cout<<"elem 1";
    in>>inf;                    //citesc primul nod
    Nod *nou=new Nod(inf);
    l.prim=nou;
    l.prim->setNext(l.prim);
    for(i=2;i<=n;i++)
        {
            //cout<<"elem "<<i<<endl;
            in>>inf;                            //citesc fiecare nod si il adaug
            l.adaug_element(i,inf);             //la finalul listei folosind metoda
                                                //de adaugare de a unui nou nod
        }
    return in;
    }


    void citire_lista(int n, istream &in){      //neutilizata, ramasa de la inceput
        lungime=n;
        in>>*prim;
        cout<<*prim<<endl;
        Nod* aux=new Nod(0);
        aux=prim;
        for(int i=2;i<=n;i++)
        {
            Nod* nou=new Nod();
            in>>*nou;
            prim->setNext(nou);
            prim=nou;
            cout<<*nou<<" "<<*aux->getAdr()<<endl;
        }
        prim->setNext(aux);
        prim=aux;
    }

    void afisare_lista(){
        cout<<endl<<"Lista este: "<<endl;
        int i;
        Nod* parcurg=prim;
        for(i=1;i<=lungime;i++)
        {
            cout<<*parcurg<<endl;
            parcurg=parcurg->getAdr();
        }

    }

    void adaug_element(int poz,int info){
        if(poz==1)                              //daca trebuie adaugat la inceput
        {
            Nod* de_adaugat=new Nod(info);
            de_adaugat->setNext(prim);
            prim=de_adaugat;
        }
        else
        {
        int i=0;
        Nod* de_adaugat=prim;
        for(i=1;i<poz-1;i++)                     //daca nu trebuie adaugat la inceput parcurg lista pana
            de_adaugat=de_adaugat->getAdr();     //inainte de pozitia care trebuie
        //cout<<endl<<"Adaug dupa "<<*de_adaugat;

        Nod* nou=new Nod(info);
        Nod* urm=de_adaugat->getAdr();
        de_adaugat->setNext(nou);
        nou->setNext(urm);
        }
        lungime++;

    }

    void sterg_element(int poz){

        int i;
        Nod* de_sters=new Nod();
        de_sters->setNext(prim);
        if(poz!=1)                              //ma mut cu nodul de_sters cu o pozitie in spatele nodului ce trebuie sters
            for(i=1;i<poz;i++)
                de_sters=de_sters->getAdr();
        else
            for(i=1;i<=lungime;i++)             //in cazul in care trebuie sa sterg primul nod am nevoie sa merg pana la capat
                de_sters=de_sters->getAdr();    //pentru a putea pastra circularitatea

        Nod* urm=(de_sters->getAdr())->getAdr();
        Nod* sterg=de_sters->getAdr();
        de_sters->setNext(urm);
        if(poz==1)                              //reactualizez capul listei in cazul in care anteriorul a fost sters
            prim=prim->getAdr();
        cout<<sterg->getInfo()<<endl;
        delete sterg;
        lungime--;
        if(lungime==0) prim=NULL;

    }

    friend Lista_circulara operator +(Lista_circulara &l1, Lista_circulara &l2) //metoda de concatenare
    {
        Nod* prim1=l1.prim;
        Nod* prim2=l2.prim;
        Lista_circulara* conc;
        int i=0,j=0;

        if(prim1->getInfo() <prim2->getInfo())                  //aproape la fel ca o concatenare de vectori
        {                                                       //aleg primul nod al listei concatenate
            i++;
            conc->prim->setInfo(prim1->getInfo());
            //cout<<"ADAUG "<<conc->prim->getInfo()<<endl;
            prim1=prim1->getAdr();
        }
        else
        {
            j++;
            conc->prim->setInfo(prim2->getInfo());
            //cout<<"ADAUG "<<conc->prim->getInfo()<<endl;
            prim2=prim2->getAdr();
        }


        Nod* parcurg=conc->prim;
        conc->lungime=l1.lungime+l2.lungime+1;

        while(i<l1.lungime && j<l2.lungime)                     //cat timp nici o lista nu a ajuns la final
        {                                                       //aleg cel mai mic dintre cele doua noduri
            Nod* nou=new Nod;                                   //si il adaug la lista concatenata apoi ma mut
            nou->setNext();                                     //cu parcurgerea listei corespunzatoare mai departe
            if(prim1->getInfo()<prim2->getInfo())
            {
            i++;
            nou->setInfo(prim1->getInfo());
            //cout<<"ADAUG "<<nou->getInfo()<<endl;
            prim1=prim1->getAdr();
            }
            else
            {
            j++;
            nou->setInfo(prim2->getInfo());
            //cout<<"ADAUG "<<nou->getInfo()<<endl;
            prim2=prim2->getAdr();
            }
            parcurg->setNext(nou);
            parcurg=parcurg->getAdr();


        }
        while(i<l1.lungime)                                 //dupa ce am iesit din primul while
        {                                                   //merg cu fiecare lista pana la capat si copiez
            Nod* nou=new Nod;                               //ce a ramas in lista concatenata
            nou->setInfo(prim1->getInfo());
            //cout<<"ADAUG "<<nou->getInfo()<<endl;           //doar unul dintre aceste 2 while-uri se va executa
            prim1=prim1->getAdr();
            parcurg->setNext(nou);
            parcurg=parcurg->getAdr();
            i++;
        }

        while(j<l2.lungime)
        {
            Nod* nou=new Nod;
            nou->setInfo(prim2->getInfo());
            //cout<<"ADAUG "<<nou->getInfo()<<endl;
            prim2=prim2->getAdr();
            parcurg->setNext(nou);
            parcurg=parcurg->getAdr();
            j++;
        }
        parcurg->setNext(conc->prim);                   //leg ultimul nod la primul pentru a mentine circularitatea



        //cout<<conc;
        return *conc;
    }

    void inversare_legaturi()
    {

        int i=0;
        Nod *p=prim;
        Nod *inv1=prim->getAdr();
        Nod *ramas=inv1->getAdr();

        for(i=0;i<lungime;i++)                         //am mers cu cate 2 noduri si un al 3lea "ramas"
        {                                              //pentru a nu pierde legatura cu lista
            inv1->setNext(prim);                       //la fiecare pas nodul i+1 se leaga de nodul i
            prim=inv1;                                 //iar apoi se trece mai departe nodul i devenind
            inv1=ramas;                                //i+1 iar i+2(ramas) devenind i+1 pana la finalul listei
            ramas=ramas->getAdr();
        }
        prim=prim->getAdr();    //folosit pentru a reveni la capul listei

    }

    void elimin_k(int k)
    {
        int poz_curr=0;
        while(prim!=NULL)
        {
            poz_curr+=k;
            for(int i=0;i<k;i++,prim=prim->getAdr());       //sar de fiecare data cu capul listei peste k elemente
             f<<prim->getInfo()<<" ";                       //afisez elementul
            sterg_element(1);                               //folosesc metoda de stergere anterioara pentru a sterge
                                                            //capul listei
        }
    }


};





int main()
{
  Lista_circulara l1;
  Lista_circulara l2;
  cin>>l1;
  cin>>l2;
  cout<<l1<<endl;
  cout<<"Adaug elementul 5 pe poz 3: ";
  l1.adaug_element(3,5);
  cout<<l1<<endl;
  cout<<"Sterg elementul de pe pozitia 2: ";
  l1.sterg_element(2);
  cout<<l1<<endl;
  cout<<"Lista 2"<<endl;
  cout<<"k pt eliminare din k in k pe lista2";
  int k;
  cin>>k;
  l2.elimin_k(k);
  cout<<endl<<"Pt concatenare"<<endl;
  Lista_circulara l3;
  Lista_circulara conc1;
  cin>>conc1;
  Lista_circulara conc2;
  cin>>conc2;
  cout<<"l1+l2"<<endl;
  l3=conc1+conc2;
  cout<<l3;





    return 0;
}
