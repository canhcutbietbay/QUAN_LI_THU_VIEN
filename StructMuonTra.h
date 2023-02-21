struct Date
{
    char Ngay[3], Thang[3], Nam[5];
};

struct MuonTra
{
    char MaSach[15];
    int TrangThai;
    Date NgayMuon, NgayTra;
    /*
     * 0: Dang muon
     * 1: Da tra
     * 2: Lam mat sach
     */
};
struct NodeMuonTra
{
    MuonTra muontra;
    NodeMuonTra *Left;
    NodeMuonTra *Right;
};
struct DS_MuonTra
{
    NodeMuonTra *First;
    NodeMuonTra *Last;
};