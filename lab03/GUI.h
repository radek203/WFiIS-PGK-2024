///////////////////////////////////////////////////////////////////////////
// C++ code generated with wxFormBuilder (version 4.1.0-0-g733bf3d)
// http://www.wxformbuilder.org/
//
// PLEASE DO *NOT* EDIT THIS FILE!
///////////////////////////////////////////////////////////////////////////

#pragma once

#include <wx/artprov.h>
#include <wx/xrc/xmlres.h>
#include <wx/panel.h>
#include <wx/gdicmn.h>
#include <wx/font.h>
#include <wx/colour.h>
#include <wx/settings.h>
#include <wx/string.h>
#include <wx/sizer.h>
#include <wx/button.h>
#include <wx/bitmap.h>
#include <wx/image.h>
#include <wx/icon.h>
#include <wx/checkbox.h>
#include <wx/scrolbar.h>
#include <wx/gauge.h>
#include <wx/textctrl.h>
#include <wx/choice.h>
#include <wx/frame.h>

///////////////////////////////////////////////////////////////////////////


///////////////////////////////////////////////////////////////////////////////
/// Class MyFrame1
///////////////////////////////////////////////////////////////////////////////
class MyFrame1 : public wxFrame
{
	private:

	protected:
		wxPanel* m_panel3;
		wxButton* m_button7;
		wxCheckBox* m_checkBox3;
		wxScrollBar* m_scrollBar2;
		wxGauge* m_gauge2;
		wxButton* m_button8;
		wxTextCtrl* m_textCtrl2;
		wxChoice* m_choice1;
		wxColour kolor = wxColour(0, 0, 0);
		wxBitmap bananbitmap;

		// Virtual event handlers, override them in your derived class
		virtual void m_panel3OnUpdateUI(wxUpdateUIEvent& event) { event.Skip(); }
		virtual void m_button7OnButtonClick( wxCommandEvent& event ) { event.Skip(); }
		virtual void m_checkBox3OnCheckBox( wxCommandEvent& event ) { event.Skip(); }
		virtual void m_scrollBar2OnScroll( wxScrollEvent& event ) { event.Skip(); }
		virtual void m_button8OnButtonClick( wxCommandEvent& event ) { event.Skip(); }
		virtual void m_textCtrl2OnText( wxCommandEvent& event ) { event.Skip(); }
		virtual void m_choice1OnChoice( wxCommandEvent& event ) { event.Skip(); }


	public:

		MyFrame1( wxWindow* parent, wxWindowID id = wxID_ANY, const wxString& title = "GFK Lab 03", const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxSize(600, 400), long style = wxDEFAULT_FRAME_STYLE | wxTAB_TRAVERSAL);

		~MyFrame1();

};

