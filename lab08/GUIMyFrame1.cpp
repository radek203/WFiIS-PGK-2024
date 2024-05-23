#include "GUIMyFrame1.h"

GUIMyFrame1::GUIMyFrame1( wxWindow* parent ) : MyFrame1( parent ) {
	gauge_loader->Hide();
}

void GUIMyFrame1::ScaleImage() {
	if (imgCopy.IsOk()) {
		imgCopy = imgCopy.Scale(img_panel->GetSize().x, img_panel->GetSize().y);
	}
}

void GUIMyFrame1::MyFrame1OnUpdateUI( wxUpdateUIEvent& event ) {
	wxSizeEvent e;
	MyFrame1OnSize(e);

	event.Skip();
}

void GUIMyFrame1::MyFrame1OnSize( wxSizeEvent& event ) {
	ScaleImage();
	if (imgCopy.IsOk()) {
		Repaint();
	}

	event.Skip();
}

void GUIMyFrame1::SwitchControls(bool status) {
	if (status) {
		btn_erode->Enable();
		btn_censor->Enable();
		check_animation->Enable();
	}
	else {
		btn_erode->Disable();
		btn_censor->Disable();
		check_animation->Disable();
	}
}

cimg_library::CImg<unsigned char> wxImageToCImg(wxImage image) {
	cimg_library::CImg<unsigned char> img(image.GetWidth(), image.GetHeight(), 1, 3);

	for (size_t x = 0; x < image.GetWidth(); x++) {
		for (size_t y = 0; y < image.GetHeight(); y++) {
			img(x, y, 0, 0) = image.GetRed(x, y);
			img(x, y, 0, 1) = image.GetGreen(x, y);
			img(x, y, 0, 2) = image.GetBlue(x, y);
		}
	}

	return img;
}
wxImage CImgTowxImage(cimg_library::CImg<unsigned char> image) {
	wxImage img(image.width(), image.height());

	for (size_t x = 0; x < img.GetWidth(); x++) {
		for (size_t y = 0; y < img.GetHeight(); y++) {
			img.SetRGB(x, y, image(x, y, 0, 0), image(x, y, 0, 1), image(x, y, 0, 2));
		}
	}

	return img;
}

void GUIMyFrame1::ProcessExif(const char* path) {
	FREE_IMAGE_FORMAT fif = FreeImage_GetFileType(path, 0);
	FIBITMAP* dib = FreeImage_Load(fif, path);

	text_data->Clear();
	text_data->AppendText(std::string("Rozmiar obrazka: ") + std::to_string(FreeImage_GetWidth(dib)) + "*" + std::to_string(FreeImage_GetHeight(dib)) + "\n");

	text_data->AppendText("EXIF Info:\n");
	if (FreeImage_GetMetadataCount(FIMD_EXIF_MAIN, dib)) {
		FITAG* tag = NULL;
		FIMETADATA* mdhandle = FreeImage_FindFirstMetadata(FIMD_EXIF_MAIN, dib, &tag);

		if (mdhandle) {
			do {
				text_data->AppendText(std::string(FreeImage_GetTagKey(tag)) + ": " + std::string(FreeImage_TagToString(FIMD_EXIF_MAIN, tag)) + "\n");

			} while (FreeImage_FindNextMetadata(mdhandle, &tag));
		}

		FreeImage_FindCloseMetadata(mdhandle);
	}
}

void GUIMyFrame1::btn_loadOnButtonClick( wxCommandEvent& event ) {
	wxFileDialog saveFileDialog(this, "Wybierz zdjecie", "", "", "JPG Files (*.jpg)|*.jpg", wxFD_FILE_MUST_EXIST);
	if (saveFileDialog.ShowModal() == wxID_CANCEL) return;

	auto path = saveFileDialog.GetPath().ToStdString();

	auto charPath = path.data();

	if (!imgOrg.LoadFile(path)) {
		this->Destroy();
		return;
	}
	imgCopy = imgOrg.Copy();

	erode = censor = animation_running = false;
	check_animation->SetValue(false);

	SwitchControls(true);

	ProcessExif(charPath);
	wxSizeEvent e;
	MyFrame1OnSize(e);

	event.Skip();
}

void GUIMyFrame1::btn_censorOnButtonClick( wxCommandEvent& event ) {
	if (!animation_running && !censor) {
		censor = true;

		imgCopy = imgOrg.Copy();
		auto img = wxImageToCImg(imgCopy);

		int x0 = 460, y0 = 10, dx = 120, dy = 80;

		auto cropped = img.get_crop(x0, y0, x0 + dx, y0 + dy).blur(3);
		img.draw_image(x0, y0, cropped);
		imgCopy = CImgTowxImage(img);
		ScaleImage();

		erode = false;
	}

	event.Skip();
}

void GUIMyFrame1::btn_erodeOnButtonClick( wxCommandEvent& event ) {
	if (!animation_running && !erode) {
		erode = true;

		imgCopy = imgOrg.Copy();
		auto img = wxImageToCImg(imgCopy);
		img.erode(6);
		imgCopy = CImgTowxImage(img);
		ScaleImage();

		censor = false;
	}

	event.Skip();
}

int hz = 180;
int speed_counter = 0;
int frame = 0;

void GUIMyFrame1::check_animationOnCheckBox( wxCommandEvent& event ) {
	erode = false;
	censor = false;

	if (check_animation->IsChecked() && imgOrg.IsOk()) {
		animation_running = true;

		gauge_loader->Show();

		imgCopy = imgOrg.Copy();
		ScaleImage();
		const int height = imgCopy.GetSize().y;
		const int width = imgCopy.GetSize().x;

		auto copy = wxImageToCImg(imgCopy);

		float sigma = 140.0f;
		float color[3] = { 1, 1, 1 };
		float opacity = 1.0f;

		for (int i = 0; i < hz; i++) {
			gauge_loader->SetValue((i / (float)hz) * 100.0);

			auto gauss1 = cimg_library::CImg<float>(width, height, 1, 3);
			auto gauss2 = cimg_library::CImg<float>(width, height, 1, 3);

			// 0.5 * width i 0.5 * height to srodek obrazka
			gauss1.draw_gaussian(0.5 * width + (0.4 * width) * cos(i * M_PI / 60.f), 0.5 * height + (0.4 * height) * sin(i * M_PI / 60.f), sigma, color, opacity);

			gauss2.draw_gaussian(0.5 * width + (0.4 * width) * cos((i + 60.f) * M_PI / 60.f), 0.5 * height + (0.4 * height) * sin((i + 60.f) * M_PI / 60.f), sigma, color, opacity);

			cimg_library::CImg<float> copyCopy = copy;
			copyCopy.mul(gauss1 + gauss2);
			auto frame = CImgTowxImage(copyCopy);

			animationFrames[hz - 1 - i] = wxBitmap(frame);
		}


		gauge_loader->Hide();
	}
	else {
		animation_running = false;
		check_animation->SetValue(false);
	}

	event.Skip();
}

void GUIMyFrame1::Repaint() {
	wxClientDC clientDc(img_panel);
	wxBitmap bitmap = wxBitmap(img_panel->GetSize());
	wxBufferedDC dc(&clientDc, bitmap);
	dc.SetBackground(wxColor(0, 0, 0));
	dc.Clear();

	if (imgCopy.IsOk()) {
		if (animation_running) {
			dc.DrawBitmap(animationFrames[frame], 0, 0);
			if (speed_counter == 10) {
				frame++;
				frame = frame % hz;
				speed_counter = 0;
			}
			speed_counter++;
			//Refresh();
			RefreshRect(wxRect(1, 1, 1, 1), false);
		}
		else {
			wxBitmap bitmap(imgCopy);
			dc.DrawBitmap(bitmap, 0, 0, true);
		}
	}
}