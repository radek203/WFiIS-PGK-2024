///////////////////////////////////////////////////////////////////////////
// C++ code generated with wxFormBuilder (version 3.10.1-0-g8feb16b3)
// http://www.wxformbuilder.org/
//
// PLEASE DO *NOT* EDIT THIS FILE!
///////////////////////////////////////////////////////////////////////////

#include "GUI.h"

///////////////////////////////////////////////////////////////////////////

MyFrame1::MyFrame1( wxWindow* parent, wxWindowID id, const wxString& title, const wxPoint& pos, const wxSize& size, long style ) : wxFrame( parent, id, title, pos, size, style )
{
	this->SetSizeHints( wxDefaultSize, wxSize( 730,650 ) );

	wxBoxSizer* bSizer1;
	bSizer1 = new wxBoxSizer( wxVERTICAL );

	m_panel1 = new wxPanel( this, wxID_ANY, wxDefaultPosition, wxSize( 700,500 ), wxTAB_TRAVERSAL );
	m_panel1->SetBackgroundColour( wxSystemSettings::GetColour( wxSYS_COLOUR_BTNHIGHLIGHT ) );
	m_panel1->SetMinSize( wxSize( 700,500 ) );
	m_panel1->SetMaxSize( wxSize( 700,500 ) );

	bSizer1->Add( m_panel1, 1, wxEXPAND | wxALL, 5 );

	wxBoxSizer* bSizer2;
	bSizer2 = new wxBoxSizer( wxHORIZONTAL );

	wxStaticBoxSizer* sbSizer1;
	sbSizer1 = new wxStaticBoxSizer( new wxStaticBox( this, wxID_ANY, wxT("Wybor Funkcji:") ), wxHORIZONTAL );

	m_button1 = new wxButton( sbSizer1->GetStaticBox(), wxID_ANY, wxT("1"), wxDefaultPosition, wxDefaultSize, 0 );
	m_button1->SetMinSize( wxSize( 40,40 ) );
	m_button1->SetMaxSize( wxSize( 40,40 ) );

	sbSizer1->Add( m_button1, 0, wxALL, 5 );

	m_button2 = new wxButton( sbSizer1->GetStaticBox(), wxID_ANY, wxT("2"), wxDefaultPosition, wxDefaultSize, 0 );
	m_button2->SetMinSize( wxSize( 40,40 ) );
	m_button2->SetMaxSize( wxSize( 40,40 ) );

	sbSizer1->Add( m_button2, 0, wxALL, 5 );

	m_button3 = new wxButton( sbSizer1->GetStaticBox(), wxID_ANY, wxT("3"), wxDefaultPosition, wxDefaultSize, 0 );
	m_button3->SetMinSize( wxSize( 40,40 ) );

	sbSizer1->Add( m_button3, 0, wxALL, 5 );

	m_button4 = new wxButton( sbSizer1->GetStaticBox(), wxID_ANY, wxT("4"), wxDefaultPosition, wxDefaultSize, 0 );
	m_button4->SetMinSize( wxSize( 40,40 ) );
	m_button4->SetMaxSize( wxSize( 40,40 ) );

	sbSizer1->Add( m_button4, 0, wxALL, 5 );


	bSizer2->Add( sbSizer1, 0, 0, 5 );

	wxBoxSizer* bSizer4;
	bSizer4 = new wxBoxSizer( wxVERTICAL );

	wxBoxSizer* bSizer5;
	bSizer5 = new wxBoxSizer( wxHORIZONTAL );


	bSizer5->Add( 10, 0, 0, 0, 5 );

	m_st_rotation = new wxStaticText( this, wxID_ANY, wxT("Obrot: 0 stopni"), wxDefaultPosition, wxDefaultSize, 0 );
	m_st_rotation->Wrap( -1 );
	bSizer5->Add( m_st_rotation, 0, wxALIGN_CENTER_VERTICAL|wxALIGN_LEFT, 5 );


	bSizer5->Add( 0, 0, 1, wxEXPAND, 5 );

	m_cb_color = new wxCheckBox( this, wxID_ANY, wxT("kolor"), wxDefaultPosition, wxDefaultSize, 0 );
	bSizer5->Add( m_cb_color, 1, wxALIGN_CENTER_VERTICAL, 5 );


	bSizer4->Add( bSizer5, 1, wxEXPAND, 5 );

	m_s_rotation = new wxSlider( this, wxID_ANY, 0, 0, 360, wxDefaultPosition, wxDefaultSize, wxSL_HORIZONTAL );
	bSizer4->Add( m_s_rotation, 1, wxALL|wxEXPAND, 5 );


	bSizer2->Add( bSizer4, 1, wxEXPAND, 5 );


	bSizer1->Add( bSizer2, 0, wxEXPAND, 5 );

	m_s_tilt = new wxSlider( this, wxID_ANY, 50, 0, 100, wxDefaultPosition, wxDefaultSize, wxSL_HORIZONTAL );
	bSizer1->Add( m_s_tilt, 0, wxALL|wxEXPAND, 5 );


	this->SetSizer( bSizer1 );
	this->Layout();

	this->Centre( wxBOTH );

	// Connect Events
	m_button1->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( MyFrame1::m_button1_click ), NULL, this );
	m_button2->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( MyFrame1::m_button2_click ), NULL, this );
	m_button3->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( MyFrame1::m_button3_click ), NULL, this );
	m_button4->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( MyFrame1::m_button4_click ), NULL, this );
	m_cb_color->Connect( wxEVT_COMMAND_CHECKBOX_CLICKED, wxCommandEventHandler( MyFrame1::m_cb_color_click ), NULL, this );
	m_s_rotation->Connect( wxEVT_SCROLL_TOP, wxScrollEventHandler( MyFrame1::m_s_rotation_onscroll ), NULL, this );
	m_s_rotation->Connect( wxEVT_SCROLL_BOTTOM, wxScrollEventHandler( MyFrame1::m_s_rotation_onscroll ), NULL, this );
	m_s_rotation->Connect( wxEVT_SCROLL_LINEUP, wxScrollEventHandler( MyFrame1::m_s_rotation_onscroll ), NULL, this );
	m_s_rotation->Connect( wxEVT_SCROLL_LINEDOWN, wxScrollEventHandler( MyFrame1::m_s_rotation_onscroll ), NULL, this );
	m_s_rotation->Connect( wxEVT_SCROLL_PAGEUP, wxScrollEventHandler( MyFrame1::m_s_rotation_onscroll ), NULL, this );
	m_s_rotation->Connect( wxEVT_SCROLL_PAGEDOWN, wxScrollEventHandler( MyFrame1::m_s_rotation_onscroll ), NULL, this );
	m_s_rotation->Connect( wxEVT_SCROLL_THUMBTRACK, wxScrollEventHandler( MyFrame1::m_s_rotation_onscroll ), NULL, this );
	m_s_rotation->Connect( wxEVT_SCROLL_THUMBRELEASE, wxScrollEventHandler( MyFrame1::m_s_rotation_onscroll ), NULL, this );
	m_s_rotation->Connect( wxEVT_SCROLL_CHANGED, wxScrollEventHandler( MyFrame1::m_s_rotation_onscroll ), NULL, this );
	m_s_tilt->Connect( wxEVT_SCROLL_TOP, wxScrollEventHandler( MyFrame1::m_s_tilt_onscroll ), NULL, this );
	m_s_tilt->Connect( wxEVT_SCROLL_BOTTOM, wxScrollEventHandler( MyFrame1::m_s_tilt_onscroll ), NULL, this );
	m_s_tilt->Connect( wxEVT_SCROLL_LINEUP, wxScrollEventHandler( MyFrame1::m_s_tilt_onscroll ), NULL, this );
	m_s_tilt->Connect( wxEVT_SCROLL_LINEDOWN, wxScrollEventHandler( MyFrame1::m_s_tilt_onscroll ), NULL, this );
	m_s_tilt->Connect( wxEVT_SCROLL_PAGEUP, wxScrollEventHandler( MyFrame1::m_s_tilt_onscroll ), NULL, this );
	m_s_tilt->Connect( wxEVT_SCROLL_PAGEDOWN, wxScrollEventHandler( MyFrame1::m_s_tilt_onscroll ), NULL, this );
	m_s_tilt->Connect( wxEVT_SCROLL_THUMBTRACK, wxScrollEventHandler( MyFrame1::m_s_tilt_onscroll ), NULL, this );
	m_s_tilt->Connect( wxEVT_SCROLL_THUMBRELEASE, wxScrollEventHandler( MyFrame1::m_s_tilt_onscroll ), NULL, this );
	m_s_tilt->Connect( wxEVT_SCROLL_CHANGED, wxScrollEventHandler( MyFrame1::m_s_tilt_onscroll ), NULL, this );
}

MyFrame1::~MyFrame1()
{
	// Disconnect Events
	m_button1->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( MyFrame1::m_button1_click ), NULL, this );
	m_button2->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( MyFrame1::m_button2_click ), NULL, this );
	m_button3->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( MyFrame1::m_button3_click ), NULL, this );
	m_button4->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( MyFrame1::m_button4_click ), NULL, this );
	m_cb_color->Disconnect( wxEVT_COMMAND_CHECKBOX_CLICKED, wxCommandEventHandler( MyFrame1::m_cb_color_click ), NULL, this );
	m_s_rotation->Disconnect( wxEVT_SCROLL_TOP, wxScrollEventHandler( MyFrame1::m_s_rotation_onscroll ), NULL, this );
	m_s_rotation->Disconnect( wxEVT_SCROLL_BOTTOM, wxScrollEventHandler( MyFrame1::m_s_rotation_onscroll ), NULL, this );
	m_s_rotation->Disconnect( wxEVT_SCROLL_LINEUP, wxScrollEventHandler( MyFrame1::m_s_rotation_onscroll ), NULL, this );
	m_s_rotation->Disconnect( wxEVT_SCROLL_LINEDOWN, wxScrollEventHandler( MyFrame1::m_s_rotation_onscroll ), NULL, this );
	m_s_rotation->Disconnect( wxEVT_SCROLL_PAGEUP, wxScrollEventHandler( MyFrame1::m_s_rotation_onscroll ), NULL, this );
	m_s_rotation->Disconnect( wxEVT_SCROLL_PAGEDOWN, wxScrollEventHandler( MyFrame1::m_s_rotation_onscroll ), NULL, this );
	m_s_rotation->Disconnect( wxEVT_SCROLL_THUMBTRACK, wxScrollEventHandler( MyFrame1::m_s_rotation_onscroll ), NULL, this );
	m_s_rotation->Disconnect( wxEVT_SCROLL_THUMBRELEASE, wxScrollEventHandler( MyFrame1::m_s_rotation_onscroll ), NULL, this );
	m_s_rotation->Disconnect( wxEVT_SCROLL_CHANGED, wxScrollEventHandler( MyFrame1::m_s_rotation_onscroll ), NULL, this );
	m_s_tilt->Disconnect( wxEVT_SCROLL_TOP, wxScrollEventHandler( MyFrame1::m_s_tilt_onscroll ), NULL, this );
	m_s_tilt->Disconnect( wxEVT_SCROLL_BOTTOM, wxScrollEventHandler( MyFrame1::m_s_tilt_onscroll ), NULL, this );
	m_s_tilt->Disconnect( wxEVT_SCROLL_LINEUP, wxScrollEventHandler( MyFrame1::m_s_tilt_onscroll ), NULL, this );
	m_s_tilt->Disconnect( wxEVT_SCROLL_LINEDOWN, wxScrollEventHandler( MyFrame1::m_s_tilt_onscroll ), NULL, this );
	m_s_tilt->Disconnect( wxEVT_SCROLL_PAGEUP, wxScrollEventHandler( MyFrame1::m_s_tilt_onscroll ), NULL, this );
	m_s_tilt->Disconnect( wxEVT_SCROLL_PAGEDOWN, wxScrollEventHandler( MyFrame1::m_s_tilt_onscroll ), NULL, this );
	m_s_tilt->Disconnect( wxEVT_SCROLL_THUMBTRACK, wxScrollEventHandler( MyFrame1::m_s_tilt_onscroll ), NULL, this );
	m_s_tilt->Disconnect( wxEVT_SCROLL_THUMBRELEASE, wxScrollEventHandler( MyFrame1::m_s_tilt_onscroll ), NULL, this );
	m_s_tilt->Disconnect( wxEVT_SCROLL_CHANGED, wxScrollEventHandler( MyFrame1::m_s_tilt_onscroll ), NULL, this );

}
