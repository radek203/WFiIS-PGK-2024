///////////////////////////////////////////////////////////////////////////
// C++ code generated with wxFormBuilder (version 4.1.0-0-g733bf3d)
// http://www.wxformbuilder.org/
//
// PLEASE DO *NOT* EDIT THIS FILE!
///////////////////////////////////////////////////////////////////////////

#pragma once

#include <wx/artprov.h>
#include <wx/xrc/xmlres.h>
#include <wx/button.h>
#include <wx/string.h>
#include <wx/bitmap.h>
#include <wx/image.h>
#include <wx/icon.h>
#include <wx/gdicmn.h>
#include <wx/font.h>
#include <wx/colour.h>
#include <wx/settings.h>
#include <wx/checkbox.h>
#include <wx/gauge.h>
#include <wx/textctrl.h>
#include <wx/sizer.h>
#include <wx/panel.h>
#include <wx/frame.h>

///////////////////////////////////////////////////////////////////////////


///////////////////////////////////////////////////////////////////////////////
/// Class MyFrame1
///////////////////////////////////////////////////////////////////////////////
class MyFrame1 : public wxFrame
{
	private:

	protected:
		wxButton* btn_load;
		wxButton* btn_censor;
		wxButton* btn_erode;
		wxCheckBox* check_animation;
		wxGauge* gauge_loader;
		wxTextCtrl* text_data;
		wxPanel* img_panel;

		// Virtual event handlers, override them in your derived class
		virtual void MyFrame1OnUpdateUI( wxUpdateUIEvent& event ) { event.Skip(); }
		virtual void MyFrame1OnSize(wxSizeEvent& event) { event.Skip(); }
		virtual void btn_loadOnButtonClick( wxCommandEvent& event ) { event.Skip(); }
		virtual void btn_censorOnButtonClick( wxCommandEvent& event ) { event.Skip(); }
		virtual void btn_erodeOnButtonClick( wxCommandEvent& event ) { event.Skip(); }
		virtual void check_animationOnCheckBox( wxCommandEvent& event ) { event.Skip(); }


	public:

		MyFrame1( wxWindow* parent, wxWindowID id = wxID_ANY, const wxString& title = wxT("Lab 08"), const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxSize( 1100,533 ), long style = wxDEFAULT_FRAME_STYLE|wxTAB_TRAVERSAL );

		~MyFrame1();

};

