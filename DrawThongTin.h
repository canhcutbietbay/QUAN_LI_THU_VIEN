void RunThongTin()
{
	ClearScreen();
	ButtonBack.draw();
	// ve giao dien
	setcolor(YELLOW);					   // chon mau chu
	settextstyle(BOLD_FONT, HORIZ_DIR, 3); // chon font chu, huong ve chu (direction), size chu

	char uni[] = "Hoc vien Cong nghe Buu Chinh Vien Thong - TPHCM";
	char nam[] = "-- 2023 --";
	char title[] = "* Mon hoc : ";
	char title2[] = "Cau Truc Du Lieu & Giai Thuat";
	char gv[] = "* Giang vien : ";
	char gv2[] = "Luu Nguyen Ky Thu";
	char doan[] = "* Do An : ";
	char doan2[] = "Quan Ly Thu Vien";
	char sv[] = "* Sinh vien :";
	char author1[] = "1. Nguyen Tan Loc - N21DCCN049 - D21CQCN01-N";
	char author2[] = "2. Huynh Ngoc Tan - N21DCCN074 - D21CQCN01-N";

	settextstyle(BOLD_FONT, HORIZ_DIR, 5);
	outtextxy(w / 2 - textwidth(uni) / 2, 50, uni);
	outtextxy(w / 2 - textwidth(nam) / 2, h - 250, nam);

	settextstyle(BOLD_FONT, HORIZ_DIR, 3);
	outtextxy(w / 2 - 500, 200, title);
	outtextxy(w / 2 - 500, 280, gv);
	outtextxy(w / 2 - 500, 360, doan);
	outtextxy(w / 2 - 500, 440, sv);

	outtextxy(w / 2 - 250, 200, title2);
	outtextxy(w / 2 - 250, 280, gv2);
	outtextxy(w / 2 - 250, 360, doan2);

	outtextxy(w / 2 - 250, 440, author1);
	outtextxy(w / 2 - 250, 520, author2);
}