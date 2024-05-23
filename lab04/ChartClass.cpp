#include <wx/dc.h>
#include <memory>

#include "ChartClass.h"
#include "vecmat.h"

int jednostkaWidth;
int jednostkaHeight;

ChartClass::ChartClass(std::shared_ptr<ConfigClass> c) {
    cfg = std::move(c);
    x_step = 200;
}

void ChartClass::Set_Range() {
	double xmin = 9999.9, xmax = -9999.9, ymin = 9999.9, ymax = -9999.9;
	double x, y, step;

	xmin=cfg->Get_x_start();
	xmax=cfg->Get_x_stop();

	step= (cfg->Get_x_stop()-cfg->Get_x_start()) / (double)x_step;
	x = cfg->Get_x_start();

	for (int i=0; i <= x_step; i++) {
		y = GetFunctionValue(x);
		if (y > ymax) ymax = y;
		if (y < ymin) ymin = y;
		x = x + step;
	}

	y_min = ymin;
	y_max = ymax;
	x_min = xmin;
	x_max = xmax;
}


double ChartClass::GetFunctionValue(double x) {
	if (cfg->Get_F_type()==1) return x*x;
	if (cfg->Get_F_type()==2) return 0.5*exp(4*x-3*x*x);
	return x+sin(x*4.0);
}

Matrix ChartClass::Set_Rotate(double alpha) {
	alpha = (-alpha * M_PI) / 180.0;

    Matrix m;
	m.data[0][0] = cos(alpha);
	m.data[0][1] = -sin(alpha);
	m.data[0][2] = 0;
	m.data[1][0] = sin(alpha);
	m.data[1][1] = cos(alpha);
	m.data[1][2] = 0;
	m.data[2][0] = 0;
	m.data[2][1] = 0;
	m.data[2][2] = 1;
	return m;
}

void ChartClass::Draw(wxDC *dc, int w, int h) {
	dc->SetBackground(wxBrush(RGB(255, 255, 255)));
	dc->Clear();
	dc->SetPen(wxPen(RGB(255, 0, 0)));
	dc->DrawRectangle(10, 10, w - 20, h - 20);

	dc->SetClippingRegion(11, 11, w - 22, h - 22);
	dc->SetPen(wxPen(RGB(0, 0, 255)));

	jednostkaWidth = (w - 20) / (std::abs(cfg->Get_x0()) + std::abs(cfg->Get_x1()));
	jednostkaHeight = (h - 20) / (std::abs(cfg->Get_y0()) + std::abs(cfg->Get_y1()));

	Matrix transformation = Set_Rotate(cfg->Get_Alpha());
	if (cfg->RotateScreenCenter()) {
		transformation = CenterRotate(transformation, 0 - cfg->Get_dX() - 10 + (w / 2.0) - jednostkaWidth * std::abs(cfg->Get_x0()), 0 - cfg->Get_dY() - 10 + (h / 2.0) - jednostkaHeight * std::abs(cfg->Get_y1()));
	}
	else {
		transformation = CenterRotate(transformation, 0, 0);
	}

	dc->SetDeviceOrigin(cfg->Get_dX() + jednostkaWidth * std::abs(cfg->Get_x0()) + 10, cfg->Get_dY() + jednostkaHeight * std::abs(cfg->Get_y1()) + 10);

	dc->SetPen(wxPen(RGB(0, 0, 255)));
	line2d(transformation, jednostkaWidth * cfg->Get_x_start(), 0, jednostkaWidth * cfg->Get_x_stop(), 0, dc); //Os X
	line2d(transformation, jednostkaWidth * cfg->Get_x_stop() - 10, 20, jednostkaWidth * cfg->Get_x_stop(), 0, dc); //Strzalka dolna
	line2d(transformation, jednostkaWidth * cfg->Get_x_stop() - 10, -20, jednostkaWidth * cfg->Get_x_stop(), 0, dc); //Strzalka gorna

	line2d(transformation, jednostkaWidth * cfg->Get_x_start() * (1.0/2.0), -5, jednostkaWidth * cfg->Get_x_start() * (1.0 / 2.0), 5, dc); //Wartosc X lewo 1/2
	text2dX(transformation, jednostkaWidth * cfg->Get_x_start() * (1.0 / 2.0), 5, dc);
	line2d(transformation, jednostkaWidth * cfg->Get_x_stop() * (1.0 / 3.0), -5, jednostkaWidth * cfg->Get_x_stop() * (1.0 / 3.0), 5, dc); //Wartosc X prawo 1/3
	text2dX(transformation, jednostkaWidth * cfg->Get_x_stop() * (1.0 / 3.0), 5, dc);
	line2d(transformation, jednostkaWidth * cfg->Get_x_stop() * (2.0 / 3.0), -5, jednostkaWidth * cfg->Get_x_stop() * (2.0 / 3.0), 5, dc); //Wartosc X prawo 2/3
	text2dX(transformation, jednostkaWidth * cfg->Get_x_stop() * (2.0 / 3.0), 5, dc);

	line2d(transformation, 0, -jednostkaHeight * Get_Y_max(), 0, -jednostkaHeight * Get_Y_min(), dc); //O� Y
	line2d(transformation, -20, -jednostkaHeight * Get_Y_max() + 10, 0, -jednostkaHeight * Get_Y_max(), dc); //Strza�ka lewo
	line2d(transformation, 20, -jednostkaHeight * Get_Y_max() + 10, 0, -jednostkaHeight * Get_Y_max(), dc); //Strza�ka prawo

	line2d(transformation, -5, -jednostkaHeight * Get_Y_min() * (1.0 / 2.0), 5, -jednostkaHeight * Get_Y_min() * (1.0 / 2.0), dc); //Wartosc Y dol 1/2
	text2dY(transformation, 5, -jednostkaHeight * Get_Y_min() * (1.0 / 2.0), dc);
	line2d(transformation, -5, -jednostkaHeight * Get_Y_max() * (1.0 / 3.0), 5, -jednostkaHeight * Get_Y_max() * (1.0 / 3.0), dc); //Wartosc Y gora 1/3
	text2dY(transformation, 5, -jednostkaHeight * Get_Y_max() * (1.0 / 3.0), dc);
	line2d(transformation, -5, -jednostkaHeight * Get_Y_max() * (2.0 / 3.0), 5, -jednostkaHeight * Get_Y_max() * (2.0 / 3.0), dc); //Wartosc Y gora 2/3
	text2dY(transformation, 5, -jednostkaHeight * Get_Y_max() * (2.0 / 3.0), dc);

	dc->SetPen(wxPen(RGB(0, 255, 0)));

	double step = (cfg->Get_x_stop() - cfg->Get_x_start()) / (double)x_step;
	for (double i = jednostkaWidth * cfg->Get_x_start(); i < jednostkaWidth * cfg->Get_x_stop(); i += step) {
		int r_value = (int)((GetFunctionValue(i / (1.0 * jednostkaWidth)) / Get_Y_max()) * 255);
		dc->SetPen(wxPen(RGB(r_value, 0, 255 - r_value)));

		line2d(transformation, i, -GetFunctionValue(i / (1.0 * jednostkaWidth)) * jednostkaHeight, i + step, -GetFunctionValue((i + step) / (1.0 * jednostkaWidth)) * jednostkaHeight, dc);
	}
}

Matrix ChartClass::CenterRotate(Matrix t, double x0, double y0) {
	Matrix move1, move2;
	move1.data[0][0] = 1;
	move1.data[0][1] = 0;
	move1.data[0][2] = x0;
	move1.data[1][0] = 0;
	move1.data[1][1] = 1;
	move1.data[1][2] = y0;
	move1.data[2][0] = 0;
	move1.data[2][1] = 0;
	move1.data[2][2] = 1;

	move2.data[0][0] = 1;
	move2.data[0][1] = 0;
	move2.data[0][2] = -x0;
	move2.data[1][0] = 0;
	move2.data[1][1] = 1;
	move2.data[1][2] = -y0;
	move2.data[2][0] = 0;
	move2.data[2][1] = 0;
	move2.data[2][2] = 1;

	return move1 * t * move2;
}

void ChartClass::line2d(Matrix t, double x1, double y1, double x2, double y2, wxDC *dc) {
	Vector v1, v2;
	v1.Set(x1, y1);
	v2.Set(x2, y2);
	v1 = t * v1;
	v2 = t * v2;
	dc->DrawLine(v1.GetX(), v1.GetY(), v2.GetX(), v2.GetY());
}

void ChartClass::text2dX(Matrix t, double x1, double y1, wxDC* dc) {
	text2d(t, x1, y1, wxString::Format(wxT("%.2f"), x1 / jednostkaWidth), dc);
}

void ChartClass::text2dY(Matrix t, double x1, double y1, wxDC* dc) {
	text2d(t, x1, y1, wxString::Format(wxT("%.2f"), -y1 / jednostkaHeight), dc);
}

void ChartClass::text2d(Matrix t, double x1, double y1, wxString str, wxDC* dc) {
	Vector v1;
	v1.Set(x1, y1);
	v1 = t * v1;
	dc->DrawRotatedText(str, v1.GetX(), v1.GetY(), cfg->Get_Alpha());
}

double ChartClass::Get_Y_min() {
    Set_Range();
    return y_min;
}

double ChartClass::Get_Y_max() {
    Set_Range();
    return y_max;
}
