#include "GUIMyFrame1.h"

GUIMyFrame1::GUIMyFrame1( wxWindow* parent ) : MyFrame1( parent ) {

}

void GUIMyFrame1::m_button1_click( wxCommandEvent& event ) {
	fun = 1;
	Repaint();
}

void GUIMyFrame1::m_button2_click( wxCommandEvent& event ) {
	fun = 2;
	Repaint();
}

void GUIMyFrame1::m_button3_click( wxCommandEvent& event ) {
	fun = 3;
	Repaint();
}

void GUIMyFrame1::m_button4_click( wxCommandEvent& event ) {
	fun = 4;
	Repaint();
}

void GUIMyFrame1::m_cb_color_click( wxCommandEvent& event ) {
	colorChecked = m_cb_color->GetValue();
	Repaint();
}

void GUIMyFrame1::m_s_rotation_onscroll( wxScrollEvent& event ) {
	m_st_rotation->SetLabel(wxString::Format("Obrot: %d stopni.",m_s_rotation->GetValue()));
	Repaint();
}

void GUIMyFrame1::m_s_tilt_onscroll( wxScrollEvent& event ) {
	Repaint();
}

double FunctionData[100][3];
int NoPoints;

void PrepareData(int fun) {
	int i;
	float x, y;
	srand(376257);

	switch (fun) {
		case 0: NoPoints = 5;
			FunctionData[0][0] = -1.0;	FunctionData[0][1] = 1.0;	FunctionData[0][2] = 0.0;
			FunctionData[1][0] = 1.0;	FunctionData[1][1] = 1.0;	FunctionData[1][2] = 25.0;
			FunctionData[2][0] = 1.0;	FunctionData[2][1] = -1.0;	FunctionData[2][2] = 5.0;
			FunctionData[3][0] = -1.0;	FunctionData[3][1] = -1.0;	FunctionData[3][2] = 25.0;
			FunctionData[4][0] = 0.0;	FunctionData[4][1] = 0.0;	FunctionData[4][2] = 15.0;
			break;
		case 1: NoPoints = 20;
			for (i = 0; i < NoPoints; i++) {
				x = 4.8 * (float(rand()) / RAND_MAX) - 2.4;
				y = 4.8 * (float(rand()) / RAND_MAX) - 2.4;
				FunctionData[i][0] = x;
				FunctionData[i][1] = y;
				FunctionData[i][2] = 200 * (float(rand()) / RAND_MAX);
			}
			break;
		case 2: NoPoints = 100;
			for (i = 0; i < NoPoints; i++) {
				x = 4.8 * (float(rand()) / RAND_MAX) - 2.4;
				y = 4.8 * (float(rand()) / RAND_MAX) - 2.4;
				FunctionData[i][0] = x;
				FunctionData[i][1] = y;
				FunctionData[i][2] = x * (2 * x - 7) * (2 * y + 1) + 2 * y;
			}
			break;
		case 3: NoPoints = 10;
			for (i = 0; i < NoPoints; i++) {
				x = 4.8 * (float(rand()) / RAND_MAX) - 2.4;
				y = 4.8 * (float(rand()) / RAND_MAX) - 2.4;
				FunctionData[i][0] = x;
				FunctionData[i][1] = y;
				FunctionData[i][2] = x * sin(2 * y);
			}
			break;
		case 4: NoPoints = 100;
			for (i = 0; i < NoPoints; i++) {
				x = 2 * (float(rand()) / RAND_MAX) - 1;
				y = 2 * (float(rand()) / RAND_MAX) - 1;
				FunctionData[i][0] = x;
				FunctionData[i][1] = y;
				FunctionData[i][2] = sin(8 * (x * x + y * y));
			}
			break;
	}
}

Matrix Set_Rotate(double alpha) {
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

Matrix CenterRotate(Matrix t, double x0, double y0) {
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

double funWagowa(double x, double xk, double y, double yk) {
	return 1.0 / (pow(x - xk, 2) + pow(y - yk, 2)); // return 1.0 / pow(sqrt(pow(x-xk, 2) + pow(y-yk, 2)), 2);
}

void GUIMyFrame1::Repaint() {
	wxClientDC clientDc(m_panel1);
	wxBitmap bitmap = wxBitmap(m_panel1->GetSize());
	wxBufferedDC dc(&clientDc, bitmap);
	dc.SetBackground(wxColor(255, 255, 255));
	dc.Clear();

	PrepareData(fun);

	Matrix transformation = Set_Rotate(-(m_s_rotation->GetValue() + 180));
	transformation = CenterRotate(transformation, 0, 0);

	for (int i = 0; i < NoPoints; i++) {
		Vector v;
		v.data[0] = FunctionData[i][0];
		v.data[1] = FunctionData[i][1];
		v.data[2] = 1.0;

		Vector result = transformation * v;

		FunctionData[i][0] = result.data[0];
		FunctionData[i][1] = result.data[1];
	}

	double fmin = INT_MAX;
	double fmax = INT_MIN;

	for (int i = 0; i < NoPoints; i++) {
		fmin = std::min(fmin, FunctionData[i][2]);
		fmax = std::max(fmax, FunctionData[i][2]);
	}

	float x_min = 150;
	float x_max = 550;
	float y_min = 0;
	float y_max = 150;

	float tilt_normalized = 4 - 0.05 * m_s_tilt->GetValue();

	for (int x = 0; x < 100; x++) {
		for (int y = 0; y < 100; y++) {
			double nx = (5.0 / 100) * x - 2.5;
			double ny = (5.0 / 100) * y - 2.5;

			double waga = 0;
			double wXYSum1 = 0;
			double wXYSum2 = 0;
			for (int i = 0; i < NoPoints; i++) {
				waga = funWagowa(nx, FunctionData[i][0], ny, FunctionData[i][1]);
				if (i >= 1) {
					wXYSum1 += waga * FunctionData[i][2];
				}
				wXYSum2 += waga;
			}

			double z = wXYSum1 / (wXYSum2 != 0 ? wXYSum2 : 1);

			double z_normalized = (z - fmin) / (fmax - fmin);

			double colorValue = std::max(0.0, std::min(1.0, z_normalized));

			int colorIntensity = static_cast<int>(colorValue * 255.0);
			colorIntensity = std::max(0, std::min(255, colorIntensity));

			if (colorChecked) {
				dc.SetPen(wxPen(wxColor(colorIntensity, 0, 255 - colorIntensity)));
				dc.SetBrush(wxBrush(wxColor(colorIntensity, 0, 255 - colorIntensity)));
			}
			else {
				dc.SetPen(wxPen(wxColor(colorIntensity, colorIntensity, colorIntensity)));
				dc.SetBrush(wxBrush(wxColor(colorIntensity, colorIntensity, colorIntensity)));
			}

			z_normalized = z_normalized * (y_max - y_min);

			//5 - szerokosc prostokata
			//14 - magic number - korygujemy za mala wysokosc prostokata
			//50 - bo wartosci sa od 0 do 100, do polowy chcemy aby szly do gory, a od polowy do dolu
			dc.DrawRectangle(x_min + x * 5 - y, y_max - z_normalized + y * 5 - tilt_normalized * (y - 50), 5, z_normalized + 14);
		}
	}

}