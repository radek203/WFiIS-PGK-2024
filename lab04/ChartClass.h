#ifndef __ChartClass__
#define __ChartClass__

#include <memory>
#include "ConfigClass.h"
class Matrix;

class ChartClass
{
    private:
        std::shared_ptr<ConfigClass> cfg;
        int x_step;         // liczba odcinkow z jakich bedzie sie skladal wykres
        double x_min,x_max; // zakres zmiennej x
        double y_min,y_max; // zakres wartosci przyjmowanych przez funkcje
        double GetFunctionValue(double x); // zwraca wartosci rysowanej funkcji
        Matrix Set_Rotate(double alpha); // zwraca macierz obrotu o kat alpha
        Matrix CenterRotate(Matrix t, double x0, double y0); // przesuwa srodek ukladu do punktu x0,y0
        void line2d(Matrix t, double x1, double y1, double x2, double y2, wxDC* dc);
        void text2dX(Matrix t, double x1, double y1, wxDC* dc);
        void text2dY(Matrix t, double x1, double y1, wxDC* dc);
        void text2d(Matrix t, double x1, double y1, wxString str, wxDC* dc);
       
    public:
        ChartClass(std::shared_ptr<ConfigClass> c);
        void Set_Range();   // ustala wartosci zmiennych x_min,y_min,x_max,y_max
        double Get_Y_min(); // zwraca y_min
        double Get_Y_max(); // zwraca y_max
        void Draw(wxDC *dc, int w, int h);  // rysuje wykres
};

#endif
