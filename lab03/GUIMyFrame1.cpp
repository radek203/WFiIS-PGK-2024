#include "GUIMyFrame1.h"
#include <wx/dcclient.h>
#include <wx/dcbuffer.h>
#include <wx/colordlg.h>
#include <wx/wxprec.h>
#include <wx/bitmap.h>

GUIMyFrame1::GUIMyFrame1( wxWindow* parent ) : MyFrame1( parent ) {

}

void GUIMyFrame1::Repaint() {
    wxClientDC clientDc(m_panel3);
    bitmap = wxBitmap(m_panel3->GetSize());
    wxBufferedDC dc(&clientDc, bitmap);
    dc.SetDeviceOrigin(m_panel3->GetSize().x / 2, m_panel3->GetSize().y / 2);
    dc.SetBackground(wxColor(255, 255, 255));
    dc.Clear();

    if (m_checkBox3->IsChecked()) {
        wxImage banan = bananbitmap.ConvertToImage();
        dc.DrawBitmap(banan, -60, 2 - (m_scrollBar2->GetThumbPosition() / 2.5));
    }

    dc.DrawLine(0, 0, 40, 20);
    dc.DrawLine(0, 0, -40, 20 - (m_scrollBar2->GetThumbPosition() / 2.5));

    dc.DrawLine(0, 0, 0, 60);
    dc.DrawLine(0, 0, 0, -20);

    dc.DrawLine(0, 60, 20, 80);
    dc.DrawLine(0, 60, -20, 80);

    dc.DrawCircle(0, -30, 20);

    dc.DrawEllipse(-14, -40, 10, 6);
    dc.DrawEllipse(2, -40, 10, 6);

    if (m_checkBox3->IsChecked()) {
        dc.DrawEllipticArc(wxPoint(-10, -22), wxSize(20, 5), 180, 360);
    }
    else {
        dc.DrawEllipticArc(wxPoint(-10, -22), wxSize(20, 5), 0, 180);
    }

    dc.DrawText(m_textCtrl2->GetValue(), -80, 80);

    int fontSize = 20; // Wielko�� czcionki
    wxFont font(fontSize, wxFONTFAMILY_SWISS, wxFONTSTYLE_ITALIC, wxFONTWEIGHT_BOLD, false, wxT("Unispace"));
    dc.SetFont(font);

    dc.DrawRotatedText(m_textCtrl2->GetValue(), 80, 80, 90);

    if (m_choice1->GetString(m_choice1->GetSelection()) == "gwiazdka") {
        wxPoint star[5] = { wxPoint(-110, -80), wxPoint(-70, -20), wxPoint(-160, -60), wxPoint(-60, -60), wxPoint(-150, -20) };
        dc.SetPen(wxPen(kolor, 1));
        dc.SetBrush(wxBrush(kolor));
        dc.DrawPolygon(5, star);
    } else if (m_choice1->GetString(m_choice1->GetSelection()) == "ksiezyc") {
        dc.SetPen(wxPen(*wxLIGHT_GREY, 1));
        dc.SetBrush(wxBrush(*wxLIGHT_GREY));
        dc.DrawCircle(wxPoint(-100, -60), wxCoord(40));

        dc.SetBrush(wxBrush(*wxWHITE));
        dc.SetPen(wxPen(*wxWHITE, 1));
        dc.DrawCircle(wxPoint(-120, -80), wxCoord(40));

        dc.SetPen(wxPen(*wxBLACK, 1));
        dc.SetBrush(wxBrush(*wxBLACK));
        dc.DrawCircle(wxPoint(-80, -70), wxCoord(5));

        dc.SetBrush(wxBrush(*wxBLACK));
        dc.DrawLine(wxPoint(-100, -50), wxPoint(-84, -44));
    }
    else if (m_choice1->GetString(m_choice1->GetSelection()) == "slonko") {
        dc.SetBrush(wxBrush(*wxYELLOW));
        dc.SetPen(wxPen(*wxYELLOW, 1));
		dc.DrawCircle(wxPoint(-100, -60), wxCoord(25));
    }
}


void GUIMyFrame1::m_panel3OnUpdateUI(wxUpdateUIEvent& event) {
    Repaint();
}

void GUIMyFrame1::m_button7OnButtonClick( wxCommandEvent& event ) {
    wxFileDialog zapisDialog(this, _("Wybierz rozszerzenie"), _(""), _(""), _(" Pliki .png |*.png;| Pliki .bmp |*.bmp;| Pliki .jpg |*.jpg;| Pliki .jpeg|*.jpeg"), wxFD_SAVE | wxFD_OVERWRITE_PROMPT);
    if (zapisDialog.ShowModal() == wxID_CANCEL) return;
    wxImage zapis_obrazka = bitmap.ConvertToImage();
    zapis_obrazka.SaveFile(zapisDialog.GetPath());
    Refresh();
}

void GUIMyFrame1::m_checkBox3OnCheckBox( wxCommandEvent& event ) {
    m_scrollBar2->Enable(m_checkBox3->IsChecked());
}

void GUIMyFrame1::m_scrollBar2OnScroll( wxScrollEvent& event ) {
    m_gauge2->SetValue(m_scrollBar2->GetThumbPosition() + 0.06 * m_scrollBar2->GetThumbPosition());
    Repaint();
}

void GUIMyFrame1::m_button8OnButtonClick( wxCommandEvent& event ) {
    wxColourDialog kolorDialog(this, nullptr);
    if (kolorDialog.ShowModal() == wxID_CANCEL) return;
    kolor = kolorDialog.GetColourData().GetColour();
    Repaint();
}

void GUIMyFrame1::m_textCtrl2OnText( wxCommandEvent& event ) {

}

void GUIMyFrame1::m_choice1OnChoice( wxCommandEvent& event ) {

}
