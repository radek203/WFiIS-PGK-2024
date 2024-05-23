#include "GUIMyFrame1.h"
#include <algorithm>
#include <cmath>

bool needToRefresh = false;

GUIMyFrame1::GUIMyFrame1( wxWindow* parent ) : MyFrame1( parent ) {
	m_staticText1->SetLabel(_(L"Jasno\u015B\u0107"));
	m_b_threshold->SetLabel(_(L"Pr\u00F3g 128"));
	this->SetBackgroundColour(wxColor(192, 192, 192));
	m_scrolledWindow->SetScrollbars(25, 25, 52, 40);
	m_scrolledWindow->SetBackgroundColour(wxColor(192, 192, 192));
}

void GUIMyFrame1::m_scrolledWindow_update( wxUpdateUIEvent& event ) {
	Repaint();
}

void GUIMyFrame1::m_b_grayscale_click( wxCommandEvent& event ) {
	Img_Cpy = Img_Org.Copy(); // Kopiujemy obrazek do Img_Cpy
	Img_Cpy = Img_Cpy.ConvertToGreyscale();

	needToRefresh = true;
}

void GUIMyFrame1::m_b_blur_click( wxCommandEvent& event ) {
	Img_Cpy = Img_Org.Copy(); // Kopiujemy obrazek do Img_Cpy
	Img_Cpy = Img_Cpy.Blur(5);

	needToRefresh = true;
}

void GUIMyFrame1::m_b_mirror_click( wxCommandEvent& event ) {
	Img_Cpy = Img_Org.Copy(); // Kopiujemy obrazek do Img_Cpy
	Img_Cpy = Img_Cpy.Mirror(true);

	needToRefresh = true;
}

void GUIMyFrame1::m_b_replace_click( wxCommandEvent& event ) {
	Img_Cpy = Img_Org.Copy(); // Kopiujemy obrazek do Img_Cpy
	Img_Cpy.Replace(254, 0, 0, 0, 0, 255);

	needToRefresh = true;
}

void GUIMyFrame1::m_b_rescale_click( wxCommandEvent& event ) {
	Img_Cpy = Img_Org.Copy(); // Kopiujemy obrazek do Img_Cpy
	Img_Cpy.Rescale(320, 240);

	needToRefresh = true;
}

void GUIMyFrame1::m_b_rotate_click( wxCommandEvent& event ) {
	Img_Cpy = Img_Org.Copy(); // Kopiujemy obrazek do Img_Cpy
	Img_Cpy = Img_Cpy.Rotate(30 * 3.14 / 180.0, wxPoint(0,0));

	needToRefresh = true;
}

void GUIMyFrame1::m_b_rotate_hue_click( wxCommandEvent& event ) {
	Img_Cpy = Img_Org.Copy(); // Kopiujemy obrazek do Img_Cpy
	Img_Cpy.RotateHue(0.5);

	needToRefresh = true;
}

void GUIMyFrame1::m_b_mask_click( wxCommandEvent& event ) {
	Img_Cpy = Img_Org.Copy(); // Kopiujemy obrazek do Img_Cpy
	Img_Cpy.SetMaskFromImage(Img_Mask, 0, 0, 0);

	needToRefresh = true;
}

void GUIMyFrame1::m_s_brightness_scroll( wxScrollEvent& event ) {
	Brightness(m_s_brightness->GetValue() - 100);
	Repaint();
}

void GUIMyFrame1::m_s_contrast_scroll( wxScrollEvent& event ) {
	Contrast(m_s_contrast->GetValue() - 100);
	Repaint();
}

void GUIMyFrame1::m_b_prewitt_click(wxCommandEvent& event) {
	Img_Cpy = Img_Org.Copy(); // Kopiujemy obrazek do Img_Cpy

	double temp = 0;

	int width = Img_Cpy.GetWidth();
	int height = Img_Cpy.GetHeight();

	size_t size = 3 * width * height;

	unsigned char* data = Img_Cpy.GetData();
	unsigned char* copy = new unsigned char[size];

	memcpy(copy, data, size);

	for (int i = 1; i < height - 1; i++) {
		for (int j = 1; j < width - 1; j++) {
			for (int k = 0; k < 3; k++) {
				temp = 0;
				temp += copy[(i - 1) * width * 3 + (j - 1) * 3 + k] * -1; // G�rny lewy
				temp += copy[(i - 1) * width * 3 + (j + 1) * 3 + k] * 1;  // G�rny prawy

				temp += copy[i * width * 3 + (j - 1) * 3 + k] * -1;       // �rodkowy lewy
				temp += copy[i * width * 3 + (j + 1) * 3 + k] * 1;        // �rodkowy prawy

				temp += copy[(i + 1) * width * 3 + (j - 1) * 3 + k] * -1; // Dolny lewy
				temp += copy[(i + 1) * width * 3 + (j + 1) * 3 + k] * 1;  // Dolny prawy

				data[i * width * 3 + j * 3 + k] = std::clamp(std::fabs(temp) / 3.0, 0.0, 255.0);
			}
		}
	}

	delete[] copy;
}

void GUIMyFrame1::m_b_threshold_click( wxCommandEvent& event ) {
	Img_Cpy = Img_Org.Copy(); // Kopiujemy obrazek do Img_Cpy
	unsigned char* data = Img_Cpy.GetData();
	size_t size = 3 * Img_Cpy.GetWidth() * Img_Cpy.GetHeight();

	for (size_t i = 0; i < size; i++) {
		data[i] = data[i] > 128 ? 255 : 0;
	}
}


void GUIMyFrame1::Contrast(int value) {
	Img_Cpy = Img_Org.Copy(); // Kopiujemy obrazek do Img_Cpy
	unsigned char* data = Img_Cpy.GetData();
	size_t size = 3 * Img_Cpy.GetWidth() * Img_Cpy.GetHeight();

	// Przeliczenie value na zakres -1 do 1, gdzie 1 to 100, a -1 to -100
	float scaledValue = value / 100.0f;
	// Mapowanie przeskalowanej warto�ci kontrastu do silniejszego efektu
	float contrastFactor = (scaledValue + 1) / (value > 0 ? (1 - scaledValue) : 1);

	for (size_t i = 0; i < size; i++) {
		float pixelValue = data[i] / 255.0f; // Skalowanie warto�ci piksela do 0-1
		// Zastosowanie wzoru na kontrast i przeskalowanie z powrotem do 0-255
		pixelValue = (((pixelValue - 0.5f) * contrastFactor) + 0.5f) * 255.0f;
		data[i] = std::clamp(pixelValue, 0.0f, 255.0f);
	}
}

void GUIMyFrame1::Repaint() {
	wxBitmap bitmap(Img_Cpy);          // Tworzymy tymczasowa bitmape na podstawie Img_Cpy
	wxClientDC dc(m_scrolledWindow);   // Pobieramy kontekst okna
	m_scrolledWindow->DoPrepareDC(dc); // Musimy wywolac w przypadku wxScrolledWindow, zeby suwaki prawidlowo dzialaly
	if (needToRefresh) {
		dc.Clear(); // Czyscimy kontekst urzadzenia
		needToRefresh = false;
	}
	dc.DrawBitmap(bitmap, 0, 0, true); // Rysujemy bitmape na kontekscie urzadzenia
}

void GUIMyFrame1::Brightness(int value) {
	Img_Cpy = Img_Org.Copy(); // Kopiujemy obrazek do Img_Cpy
	unsigned char* data = Img_Cpy.GetData();
	size_t size = 3 * Img_Cpy.GetWidth() * Img_Cpy.GetHeight();

	for (size_t i = 0; i < size; i++) {
		int newValue = data[i] + value;
		data[i] = std::clamp(newValue, 0, 255);
	}
}