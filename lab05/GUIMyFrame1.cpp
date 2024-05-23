#include "GUIMyFrame1.h"
#include <vector>
#include <fstream>
#include "vecmat.h"

struct Point {
	float x, y, z;
	Point(float _x, float _y, float _z) : x(_x), y(_y), z(_z) {}
};

struct Color {
	int R, G, B;
	Color(int _R, int _G, int _B) : R(_R), G(_G), B(_B) {}
};

struct Segment {
	Point begin, end;
	Color color;
	Segment(Point _begin, Point _end, Color _color) : begin(_begin), end(_end), color(_color) {}
};

std::vector<Segment> data;

GUIMyFrame1::GUIMyFrame1( wxWindow* parent ) : MyFrame1( parent ) {
	m_button_load_geometry->SetLabel(_("Wczytaj Geometri\u0119"));
	m_staticText25->SetLabel(_("Obr\u00F3t X:"));
	m_staticText27->SetLabel(_("Obr\u00F3t Y:"));
	m_staticText29->SetLabel(_("Obr\u00F3t Z:"));

	WxSB_TranslationX->SetRange(0, 200); WxSB_TranslationX->SetValue(100);
	WxSB_TranslationY->SetRange(0, 200); WxSB_TranslationY->SetValue(100);
	WxSB_TranslationZ->SetRange(0, 200); WxSB_TranslationZ->SetValue(100);

	WxSB_RotateX->SetRange(0, 360); WxSB_RotateX->SetValue(0);
	WxSB_RotateY->SetRange(0, 360); WxSB_RotateY->SetValue(0);
	WxSB_RotateZ->SetRange(0, 360); WxSB_RotateZ->SetValue(0);

	WxSB_ScaleX->SetRange(1, 200); WxSB_ScaleX->SetValue(100);
	WxSB_ScaleY->SetRange(1, 200); WxSB_ScaleY->SetValue(100);
	WxSB_ScaleZ->SetRange(1, 200); WxSB_ScaleZ->SetValue(100);
}

void GUIMyFrame1::WxPanel_Repaint( wxUpdateUIEvent& event ) {
	Repaint();
}

void GUIMyFrame1::m_button_load_geometry_click( wxCommandEvent& event ) {
	wxFileDialog WxOpenFileDialog(this, wxT("Choose a file"), wxT(""), wxT(""), wxT("Geometry file (*.geo)|*.geo"), wxFD_OPEN | wxFD_FILE_MUST_EXIST);

	if (WxOpenFileDialog.ShowModal() == wxID_OK) {
		double x1, y1, z1, x2, y2, z2;
		int r, g, b;

		std::ifstream in(WxOpenFileDialog.GetPath().ToAscii());
		if (in.is_open()) {
			data.clear();
			while (!in.eof()) {
				in >> x1 >> y1 >> z1 >> x2 >> y2 >> z2 >> r >> g >> b;
				data.push_back(Segment(Point(x1, y1, z1), Point(x2, y2, z2), Color(r, g, b)));
			}
			in.close();
		}
	}
}

void GUIMyFrame1::Scrolls_Updated( wxScrollEvent& event ) {
	WxST_TranslationX->SetLabel(wxString::Format(wxT("%g"), (WxSB_TranslationX->GetValue() - 100) / 50.0));
	WxST_TranslationY->SetLabel(wxString::Format(wxT("%g"), (WxSB_TranslationY->GetValue() - 100) / 50.0));
	WxST_TranslationZ->SetLabel(wxString::Format(wxT("%g"), (WxSB_TranslationZ->GetValue() - 100) / 50.0));

	WxST_RotateX->SetLabel(wxString::Format(wxT("%d"), WxSB_RotateX->GetValue()));
	WxST_RotateY->SetLabel(wxString::Format(wxT("%d"), WxSB_RotateY->GetValue()));
	WxST_RotateZ->SetLabel(wxString::Format(wxT("%d"), WxSB_RotateZ->GetValue()));

	WxST_ScaleX->SetLabel(wxString::Format(wxT("%g"), WxSB_ScaleX->GetValue() / 100.0));
	WxST_ScaleY->SetLabel(wxString::Format(wxT("%g"), WxSB_ScaleY->GetValue() / 100.0));
	WxST_ScaleZ->SetLabel(wxString::Format(wxT("%g"), WxSB_ScaleZ->GetValue() / 100.0));


	Repaint();
}

Matrix4 ScaleMatrix(double sx, double sy, double sz) {
	Matrix4 result;
	result.data[0][0] = sx;
	result.data[1][1] = sy;
	result.data[2][2] = sz;
	return result;
}

Matrix4 RotateX(double angle) {
	Matrix4 result;
	result.data[0][0] = 1;
	result.data[1][1] = cos(angle);
	result.data[1][2] = sin(angle);
	result.data[2][1] = -sin(angle);
	result.data[2][2] = cos(angle);
	//result.data[3][3] = 1;
	return result;
}

Matrix4 RotateY(double angle) {
	Matrix4 result;
	result.data[0][0] = cos(angle);
	result.data[0][2] = -sin(angle);
	result.data[1][1] = 1;
	result.data[2][0] = sin(angle);
	result.data[2][2] = cos(angle);
	//result.data[3][3] = 1;
	return result;
}

Matrix4 RotateZ(double angle) {
	Matrix4 result;
	result.data[0][0] = cos(angle);
	result.data[0][1] = sin(angle);
	result.data[1][0] = -sin(angle);
	result.data[1][1] = cos(angle);
	result.data[2][2] = 1;
	//result.data[3][3] = 1;
	return result;
}

Matrix4 Translate(double tx, double ty, double tz) {
	Matrix4 result;
	result.data[0][0] = 1;
	result.data[1][1] = 1;
	result.data[2][2] = 1;
	//result.data[3][3] = 1;
	result.data[0][3] = tx;
	result.data[1][3] = ty;
	result.data[2][3] = tz;
	return result;
}

void GUIMyFrame1::Repaint() {
    wxClientDC clientDc(WxPanel);
    wxBitmap bitmap = wxBitmap(WxPanel->GetSize());
    wxBufferedDC dc(&clientDc, bitmap);
    dc.SetBackground(wxColor(255, 255, 255));
    dc.Clear();

    dc.SetClippingRegion(0, 0, WxPanel->GetSize().x, WxPanel->GetSize().y);


    //Przeliczenie na radiany, znak minusa - zmieniamy kierunek obrotu
    double alphaX = WxSB_RotateX->GetValue() * M_PI / 180.0;
    double alphaY = WxSB_RotateY->GetValue() * M_PI / 180.0;
    double alphaZ = WxSB_RotateZ->GetValue() * M_PI / 180.0;

    //Skalowanie w zakresie -2 : 2, -2 : 2, -2 : 2
    Matrix4 scale_matrix = ScaleMatrix(WxSB_ScaleX->GetValue() / 100.0, WxSB_ScaleY->GetValue() / 100.0, WxSB_ScaleZ->GetValue() / 100.0);
    //Obroty
    Matrix4 rotate_matrix_x = RotateX(alphaX);
    Matrix4 rotate_matrix_y = RotateY(alphaY);
    Matrix4 rotate_matrix_z = RotateZ(alphaZ);
    //Przesuniecie w zakresie -2 : 2, -2 : 2, -2 : 2 ( -100 bo wartosc domyslna to 100)
    Matrix4 translate_matrix = Translate((WxSB_TranslationX->GetValue() - 100) / 50.0, (WxSB_TranslationY->GetValue() - 100) / 50.0, (WxSB_TranslationZ->GetValue() - 100) / 50.0);

    //Sk�adanie macierzy
    Matrix4 transformation_matrix = translate_matrix * rotate_matrix_x * rotate_matrix_y * rotate_matrix_z * scale_matrix;

    //Macierz rzutu perspektywicznego
    Matrix4 perspective_matrix;
    perspective_matrix.data[0][0] = 1.0;
    perspective_matrix.data[1][1] = 1.0;
    perspective_matrix.data[3][2] = 1.0 / 2.0;
    //perspective_matrix.data[3][3] = 1.0;

    //Macierz przeskalowania do rozmiaru okna
    Matrix4 window_scale = ScaleMatrix(WxPanel->GetSize().GetWidth() / 2.0, -WxPanel->GetSize().GetHeight() / 2.0, 1.0);

    //Przesuniecie do srodka okna
    Matrix4 window_translate = Translate(WxPanel->GetSize().GetWidth() / 2.0, WxPanel->GetSize().GetHeight() / 2.0, 0.0);
    Matrix4 window_matrix = window_translate * window_scale * perspective_matrix;

    int y_max = WxPanel->GetSize().GetHeight();
    int y_min = 0;
    int x_max = WxPanel->GetSize().GetWidth();
    int x_min = 0;

	double cameraLocation = -2.0;

    for (Segment &seg : data) {
        dc.SetPen(wxPen(wxColour(seg.color.R, seg.color.G, seg.color.B)));

        Vector4 startPoint;

        startPoint.Set(seg.begin.x, seg.begin.y, seg.begin.z);
        startPoint = transformation_matrix * startPoint;

        Vector4 endPoint;
        endPoint.Set(seg.end.x, seg.end.y, seg.end.z);
        endPoint = transformation_matrix * endPoint;

        //Po przemnozeniu przez macierz transformacji, dzielimy wszystkie wspolrzedne przez czynnik normalizujacy (czwarta wspolrzedna)
        for (int i = 0; i < 3; i++) {
            startPoint.data[i] /= startPoint.data[3];
            endPoint.data[i] /= endPoint.data[3];
        }

		/*
        if (!(startPoint.GetZ() >= -2 && endPoint.GetZ() >= -2)) {
            continue;
		}*/

		if ((endPoint.GetZ() > cameraLocation && startPoint.GetZ() <= cameraLocation) || (startPoint.GetZ() > cameraLocation && endPoint.GetZ() <= cameraLocation)) {
			//Wybieramy ktory punkt jest poza ekranem
			Vector4 offScreen = endPoint.GetZ() <= cameraLocation ? endPoint : startPoint;
			//Wybieramy ktory punkt jest na ekranie
			Vector4 inScreen = endPoint.GetZ() <= cameraLocation ? startPoint : endPoint;

			//To co jest za duzo na ekranie (Z), dzielimy przez odleglosc miedzy punktami (Z)
			double ratio = abs((cameraLocation - offScreen.GetZ()) / (inScreen.GetZ() - offScreen.GetZ()));
			offScreen.data[0] = (inScreen.GetX() - offScreen.GetX()) * ratio + offScreen.GetX();
			offScreen.data[1] = (inScreen.GetY() - offScreen.GetY()) * ratio + offScreen.GetY();
			offScreen.data[2] = -1.98f;

			startPoint = inScreen;
			endPoint = offScreen;
		}
		else if (startPoint.GetZ() <= cameraLocation && endPoint.GetZ() <= cameraLocation) {
			continue;
		}

        startPoint = window_matrix * startPoint;
        endPoint = window_matrix * endPoint;

        //Ponownie normalizujemy
        for (int i = 0; i < 3; i++) {
            startPoint.data[i] /= startPoint.data[3];
            endPoint.data[i] /= endPoint.data[3];
        }

        if (startPoint.GetX() < x_min && endPoint.GetX() < x_min) continue;
        if (startPoint.GetX() > x_max && endPoint.GetX() > x_max) continue;
        if (startPoint.GetY() < y_min && endPoint.GetY() < y_min) continue;
        if (startPoint.GetY() > y_max && endPoint.GetY() > y_max) continue;

        dc.DrawLine(startPoint.GetX(), startPoint.GetY(), endPoint.GetX(), endPoint.GetY());
    }
}
