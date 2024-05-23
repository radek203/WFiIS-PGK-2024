///////////////////////////////////////////////////////////////////////////
// C++ code generated with wxFormBuilder (version 4.1.0-0-g733bf3d)
// http://www.wxformbuilder.org/
//
// PLEASE DO *NOT* EDIT THIS FILE!
///////////////////////////////////////////////////////////////////////////

#include "GUI.h"

///////////////////////////////////////////////////////////////////////////

MyFrame1::MyFrame1( wxWindow* parent, wxWindowID id, const wxString& title, const wxPoint& pos, const wxSize& size, long style ) : wxFrame( parent, id, title, pos, size, style )
{
	this->SetSizeHints( wxDefaultSize, wxDefaultSize );

	wxBoxSizer* bSizer1;
	bSizer1 = new wxBoxSizer( wxHORIZONTAL );

	wxBoxSizer* bSizer2;
	bSizer2 = new wxBoxSizer( wxVERTICAL );

	bSizer2->SetMinSize( wxSize( 300,-1 ) );
	btn_load = new wxButton( this, wxID_ANY, wxT("Wczytaj obrazek"), wxDefaultPosition, wxDefaultSize, 0 );
	bSizer2->Add( btn_load, 0, wxALL|wxALIGN_CENTER_HORIZONTAL, 5 );

	btn_censor = new wxButton( this, wxID_ANY, wxT("Cenzura"), wxDefaultPosition, wxDefaultSize, 0 );
	bSizer2->Add( btn_censor, 0, wxALL|wxALIGN_CENTER_HORIZONTAL, 5 );

	btn_erode = new wxButton( this, wxID_ANY, wxT("Erode"), wxDefaultPosition, wxDefaultSize, 0 );
	bSizer2->Add( btn_erode, 0, wxALL|wxALIGN_CENTER_HORIZONTAL, 5 );

	check_animation = new wxCheckBox( this, wxID_ANY, wxT("Animacja"), wxDefaultPosition, wxDefaultSize, 0 );
	bSizer2->Add( check_animation, 0, wxALL|wxALIGN_CENTER_HORIZONTAL, 5 );

	gauge_loader = new wxGauge( this, wxID_ANY, 100, wxDefaultPosition, wxDefaultSize, wxGA_HORIZONTAL );
	gauge_loader->SetValue( 0 );

	bSizer2->Add( gauge_loader, 0, wxALL|wxALIGN_CENTER_HORIZONTAL, 5 );

	text_data = new wxTextCtrl( this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxSize(0, -1), wxTE_MULTILINE | wxTE_NO_VSCROLL);
	bSizer2->Add( text_data, 1, wxALL|wxEXPAND, 5 );


	bSizer1->Add( bSizer2, 0, wxEXPAND, 5 );

	wxBoxSizer* bSizer3;
	bSizer3 = new wxBoxSizer( wxVERTICAL );

	img_panel = new wxPanel( this, wxID_ANY, wxDefaultPosition, wxSize(0, 0), wxTAB_TRAVERSAL );
	img_panel->SetBackgroundColour( wxSystemSettings::GetColour( wxSYS_COLOUR_WINDOWTEXT ) );

	bSizer3->Add( img_panel, 1, wxEXPAND | wxALL, 0 );


	bSizer1->Add( bSizer3, 1, wxEXPAND, 5 );


	this->SetSizer( bSizer1 );
	this->Layout();

	this->Centre( wxBOTH );

	// Connect Events
	this->Connect( wxEVT_SIZE, wxSizeEventHandler( MyFrame1::MyFrame1OnSize ) );
	this->Connect( wxEVT_UPDATE_UI, wxUpdateUIEventHandler( MyFrame1::MyFrame1OnUpdateUI) );
	btn_load->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( MyFrame1::btn_loadOnButtonClick ), NULL, this );
	btn_censor->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( MyFrame1::btn_censorOnButtonClick ), NULL, this );
	btn_erode->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( MyFrame1::btn_erodeOnButtonClick ), NULL, this );
	check_animation->Connect( wxEVT_COMMAND_CHECKBOX_CLICKED, wxCommandEventHandler( MyFrame1::check_animationOnCheckBox ), NULL, this );
}

MyFrame1::~MyFrame1()
{
	// Disconnect Events
	this->Disconnect( wxEVT_SIZE, wxSizeEventHandler( MyFrame1::MyFrame1OnSize ) );
	this->Disconnect(wxEVT_UPDATE_UI, wxUpdateUIEventHandler( MyFrame1::MyFrame1OnUpdateUI) );
	btn_load->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( MyFrame1::btn_loadOnButtonClick ), NULL, this );
	btn_censor->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( MyFrame1::btn_censorOnButtonClick ), NULL, this );
	btn_erode->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( MyFrame1::btn_erodeOnButtonClick ), NULL, this );
	check_animation->Disconnect( wxEVT_COMMAND_CHECKBOX_CLICKED, wxCommandEventHandler( MyFrame1::check_animationOnCheckBox ), NULL, this );

}
