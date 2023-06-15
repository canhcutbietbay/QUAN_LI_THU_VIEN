// lay max width, height cua man hinh
int w = GetSystemMetrics(SM_CXSCREEN);
int h = GetSystemMetrics(SM_CYSCREEN);

#define BG_COLOR 0
#define BG_EDITTEXT_COLOR 2
#define TEXT_TITLE_COLOR 14
#define TEXT_COLOR 9
#define BORDER_COLOR 11
#define TEXT_EDIITEXT_TITLE_COLOR 14
#define TEXT_EDIITEXT_HINT_COLOR 7
#define TEXT_EDITTEXT_COLOR 14

#define BG_BUTTON_DEFAULT 7
#define BG_BUTTON_SELECT 9

#define TEXT_BUTTON_SELECT 15
#define TEXT_BUTTON_DEFAULT 0

#define LINE 3
#define TIPS 14

#define MAX_SIZE_DAUSACH 300
#define MAX_DOC_GIA 200
#define QUEUE_CAPACITY 200
#define START_ID_DG 1e4
#define END_ID_DG 1e5

const int ENTER = 13;
const int BACKSPACE = 8;
const int SPACE = 32;

char MuonSachCode[][25] = {"MUON SACH THANH CONG",
                           "DA MUON 3 SACH",
                           "MUON 1 SACH QUA 7 NGAY",//
                           "MUON CUNG 1 DAU SACH",//
                           "SACH DA CHO MUON",//
                           "SACH DA THANH LY",//
                           "MA SACH KHONG TON TAI",//
                           "THE DA BI KHOA"};//
