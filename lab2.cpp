#include <iostream>
using namespace std;

#include <cstdint>

struct ConstructionTracker
{
    ConstructionTracker()
    {
        ++defaults;
        ++live;
    }
    ConstructionTracker(const ConstructionTracker&)
    {
        ++copies;
        ++live;
    }
    ConstructionTracker(ConstructionTracker&&) noexcept
    {
        ++moves;
        ++live;
    }
    ConstructionTracker& operator=(const ConstructionTracker&)
    {
        ++cp_asgn;
        return *this;
    }
    ConstructionTracker& operator=(ConstructionTracker&&) noexcept
    {
        ++mv_asgn;
        return *this;
    }
    ~ConstructionTracker()
    {
        ++destr;
        --live;
    }

    static size_t defaults, copies, moves, cp_asgn, mv_asgn, destr, live;

    static void resetCount()
    {
        defaults = 0;
        copies   = 0;
        moves    = 0;
        cp_asgn  = 0;
        mv_asgn  = 0;
        destr    = 0;
        live     = 0;
    }
};

size_t ConstructionTracker::defaults = 0;
size_t ConstructionTracker::copies   = 0;
size_t ConstructionTracker::moves    = 0;
size_t ConstructionTracker::cp_asgn  = 0;
size_t ConstructionTracker::mv_asgn  = 0;
size_t ConstructionTracker::destr    = 0;
size_t ConstructionTracker::live     = 0;

#include <algorithm>
#include <array>
#include <random>

//#include "ConstructionTracker.hpp"

struct Resource : ConstructionTracker
{
    static constexpr size_t size = 1'000'000'0u;
    static const size_t     get_index;

    Resource()
    {
        std::random_device                       rd;
        std::mt19937                             gen(rd());
        std::uniform_real_distribution< double > dist(0, 1);
        std::generate(tab.begin(), tab.end(), [&]() { return dist(gen); });
    }

    double get() { return tab.at(get_index); }

    std::array< double, size > tab;
};

const size_t Resource::get_index = []() {
    std::random_device                      rd;
    std::mt19937                            gen(rd());
    std::uniform_int_distribution< size_t > dist(0, size - 1);
    return dist(gen);
}();

class ResourceManager
{
public:
    ResourceManager() : res(*new Resource) {}

    ResourceManager(const ResourceManager& arg) : res(*new Resource = arg.res) {}

    ResourceManager(ResourceManager&& arg) : res(arg.res) {}

    ResourceManager& operator=(const ResourceManager& arg)
    {
        res = arg.res;
        return *this;
    }

    ResourceManager& operator=(ResourceManager&&) { return *this; }

    ~ResourceManager() { delete &res; }

    Resource& res;

    double get() { return (res.get()); }
};

int main()
{
    {
        ResourceManager rm1;
        ResourceManager rm2{rm1};
        cout << "rm1get " << rm1.get() << " == " << rm2.get() << " rm2get" << endl;
        ResourceManager rm3;
        rm3 = rm2;
        cout << "rm3get " << rm3.get() << " == " << rm2.get() << " rm2get" << endl;
    }
    cout << "ConstructionTracker.live == " << ConstructionTracker::live << endl;

    return 0;
}

/*class Wektor
{
public:
    Wektor(int n) : dlugosc{n}, pojemnosc{n}
    {
        tablica = new double[n];
        for (int i = 0; i < n; i++) {
            tablica[i] = 0.;
        }
        // dlugosc = n;
        // pojemnosc = n;
    }

    Wektor(Wektor&& vector) { *this = vector; }

    ~Wektor() { delete[] tablica; }

    // Operator przypisania
    Wektor& operator=(const Wektor& other)
    {
        // Sprawdzenie czy nie przypisujemy obiektu do samego siebie
        if (this != &other) {
            std::cout << "assign" << endl;
        }
        // Zwrócenie referencji do samego siebie
        return *this;
    }

    // double* tablica;
    int get_dl()
    {
        // cout << "Dlugosc wektora " << dlugosc << endl;
        return dlugosc;
    }

    void print_dl() { cout << "Dlugosc wektora " << dlugosc << endl; }

    int get_poj()
    {
        cout << "Pojemnosc wektora " << pojemnosc << endl;
        return pojemnosc;
    }

    void print()
    {
        for (int i = 0; i < dlugosc; i++) {
            cout << "Element " << i << " - " << tablica[i] << endl;
        }
    }

    void zmienDlugosc(int n)
    {
        if (n <= pojemnosc) {
            for (int i = n; i < dlugosc; i++)
                tablica[i] = 0;
            dlugosc = n;
        }
        else {
            double* tablica2 = tablica;
            tablica          = new double[n];
            for (int i = 0; i < dlugosc; i++)
                tablica[i] = tablica2[i];
            delete[] tablica2;
            for (int i = dlugosc; i < n; i++)
                tablica[i] = 0;
            dlugosc = n;
        }
    }

    double& operator[](const int i)
    {
        if (i < this->dlugosc) {
            double& el_tab = this->tablica[i];
            return el_tab;
        }
        else {
            this->zmienDlugosc(i);
            double& el_tab = this->tablica[i];
            return el_tab;
        }
    }

private:
    int     dlugosc;
    int     pojemnosc;
    double* tablica;
};

int main()
{
    Wektor vect(10);
    Wektor vect2(2);

    for (int i = 0; i < vect.get_dl(); i++)
        vect[i] = i;

    vect.print_dl();
    vect.print();
    vect.get_poj();

    vect.zmienDlugosc(7);
    vect.print_dl();
    vect.print();
    vect.get_poj();

    vect.zmienDlugosc(15);
    vect.print_dl();
    vect.print();
    vect.get_poj();

    double& a = vect[3];
    a++;
    cout << "a = " << a << " vect[3] = " << vect[3] << endl;
    vect.print_dl();
    vect.get_poj();
    double& b = vect[18];
    b++;
    cout << "b = " << b << " vect[18] = " << vect[18] << endl;
    vect.print_dl();
    vect.get_poj();

    vect2.print();
    vect2 = vect;
    vect2.print();

    cout << "Dziala" << endl;
    return 0;
}*/