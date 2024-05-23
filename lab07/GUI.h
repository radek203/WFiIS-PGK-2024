///////////////////////////////////////////////////////////////////////////
// C++ code generated with wxFormBuilder (version 3.10.1-0-g8feb16b3)
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
#include <wx/button.h>
#include <wx/bitmap.h>
#include <wx/image.h>
#include <wx/icon.h>
#include <wx/sizer.h>
#include <wx/statbox.h>
#include <wx/stattext.h>
#include <wx/checkbox.h>
#include <wx/slider.h>
#include <wx/frame.h>

///////////////////////////////////////////////////////////////////////////


///////////////////////////////////////////////////////////////////////////////
/// Class MyFrame1
///////////////////////////////////////////////////////////////////////////////
class MyFrame1 : public wxFrame
{
	private:

	protected:
		wxPanel* m_panel1;
		wxButton* m_button1;
		wxButton* m_button2;
		wxButton* m_button3;
		wxButton* m_button4;
		wxStaticText* m_st_rotation;
		wxCheckBox* m_cb_color;
		wxSlider* m_s_rotation;
		wxSlider* m_s_tilt;

		// Virtual event handlers, override them in your derived class
		virtual void m_button1_click( wxCommandEvent& event ) { event.Skip(); }
		virtual void m_button2_click( wxCommandEvent& event ) { event.Skip(); }
		virtual void m_button3_click( wxCommandEvent& event ) { event.Skip(); }
		virtual void m_button4_click( wxCommandEvent& event ) { event.Skip(); }
		virtual void m_cb_color_click( wxCommandEvent& event ) { event.Skip(); }
		virtual void m_s_rotation_onscroll( wxScrollEvent& event ) { event.Skip(); }
		virtual void m_s_tilt_onscroll( wxScrollEvent& event ) { event.Skip(); }


	public:

		MyFrame1( wxWindow* parent, wxWindowID id = wxID_ANY, const wxString& title = _("Lab07"), const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxSize(730, 650), long style = wxDEFAULT_FRAME_STYLE | wxBORDER_NONE | wxTAB_TRAVERSAL);

		~MyFrame1();

};

