#pragma once

#include <wx/wx.h>
#include <wx/graphics.h>
#include <wx/dcbuffer.h>

class MainFrame : public wxFrame
{
public:
	MainFrame(const std::string& title, const wxPoint& pos, const wxSize& size)
		: wxFrame(nullptr, wxID_ANY, title, pos, size)
	{
		this->SetBackgroundStyle(wxBG_STYLE_PAINT);

		Bind(wxEVT_PAINT, &MainFrame::OnPaint, this, wxID_ANY);
	}

	void Run()
	{
		while (true)
		{
			m_sign = m_MAXIMUM_DIF < m_dy ? -1 : m_sign;
			m_sign = m_MAXIMUM_DIF < 0 ? 1 : m_sign;
			m_dy += m_sign;
			Refresh();
		}
	}

private:
	void OnPaint(wxPaintEvent& evt)
	{
		wxAutoBufferedPaintDC dc(this);
		dc.Clear();

		wxGraphicsContext* gc = wxGraphicsContext::Create(dc);

        if (gc)
        {
			// Рисуем букву "Б"
			gc->SetBrush(*wxTRANSPARENT_BRUSH);
			gc->SetPen(wxPen(wxColor(0, 0, 0), 10));
            gc->DrawRectangle(50, 50, 10, 80);
            gc->DrawRectangle(50, 50, 50, 10);
            gc->DrawRectangle(50, 90, 40, 10);
			gc->DrawEllipse(50, 90, 40, 40);

			// Рисуем букву "М"
			gc->SetBrush(*wxTRANSPARENT_BRUSH);
			gc->SetPen(wxPen(wxColor(0, 0, 0), 10));
			gc->DrawRectangle(130, 50, 10, 80);
			gc->DrawRectangle(190, 50, 10, 80);
			gc->StrokeLine(130, 50, 160, 130);
			gc->StrokeLine(160, 130, 190, 50);

			// Рисуем букву "А"
			gc->SetBrush(*wxTRANSPARENT_BRUSH);
			gc->SetPen(wxPen(wxColor(0, 0, 0), 10));
			gc->StrokeLine(250, 50, 220, 130);
			gc->StrokeLine(250, 50, 280, 130);
			gc->DrawRectangle(230, 90, 40, 10);

            delete gc;
        }
	}

	int const m_MAXIMUM_DIF = 50;

	int m_sign = 1;
	int m_dy = 0;
};
