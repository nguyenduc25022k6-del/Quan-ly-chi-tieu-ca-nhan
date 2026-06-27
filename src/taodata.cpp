#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "taodata.h"
#include "tienich.h"

/* Hàm nội bộ: thêm nhanh không hỏi người dùng */

static void ThemGD(GiaoDich** dau, int* id,
                   int ngay, int thang, int nam,
                   LoaiGiaoDich loai, DanhMuc dm,
                   double soTien, const char* ghiChu) {
    GiaoDich* gd = (GiaoDich*)malloc(sizeof(GiaoDich));
    if (!gd) return;
    gd->id      = ++(*id);
    gd->ngay    = ngay;  gd->thang = thang;  gd->nam = nam;
    gd->loai    = loai;
    gd->danhMuc = dm;
    gd->soTien  = soTien;
    strncpy(gd->ghiChu, ghiChu, MAX_GHICHU - 1);
    gd->ghiChu[MAX_GHICHU - 1] = '\0';
    gd->tiep = NULL;

    if (!*dau) { *dau = gd; return; }
    GiaoDich* p = *dau;
    while (p->tiep) p = p->tiep;
    p->tiep = gd;
}

static void ThemNS(NganSach** dau, DanhMuc dm,
                   int thang, int nam, double hanMuc) {
    NganSach* ns = (NganSach*)malloc(sizeof(NganSach));
    if (!ns) return;
    ns->danhMuc = dm;
    ns->thang   = thang;  ns->nam = nam;
    ns->hanMuc  = hanMuc;
    ns->tiep    = NULL;

    if (!*dau) { *dau = ns; return; }
    NganSach* p = *dau;
    while (p->tiep) p = p->tiep;
    p->tiep = ns;
}

/* Kịch bản 1: Sinh viên (3 tháng, có tháng vượt NS) */

void KichBanSinhVien(GiaoDich** gdDau, NganSach** nsDau, int* idLonNhat) {
    /* -- Tháng 4/2025 -- */
    ThemGD(gdDau, idLonNhat,  1,4,2025, LOAI_THU, DM_LUONG,    3000000, "Luong thang 4");
    ThemGD(gdDau, idLonNhat,  2,4,2025, LOAI_THU, DM_THUONG,   500000,  "Thuong hoan thanh du an nhom");
    ThemGD(gdDau, idLonNhat,  3,4,2025, LOAI_CHI, DM_ANUONG,   85000,   "Com trua");
    ThemGD(gdDau, idLonNhat,  5,4,2025, LOAI_CHI, DM_ANUONG,   120000,  "An toi sinh nhat ban");
    ThemGD(gdDau, idLonNhat,  7,4,2025, LOAI_CHI, DM_DICHUY,   45000,   "Xe buyt di truong");
    ThemGD(gdDau, idLonNhat,  8,4,2025, LOAI_CHI, DM_HOCTAP,   250000,  "Mua sach giao trinh");
    ThemGD(gdDau, idLonNhat, 10,4,2025, LOAI_CHI, DM_GIAITRI,  80000,   "Xem phim");
    ThemGD(gdDau, idLonNhat, 12,4,2025, LOAI_CHI, DM_ANUONG,   65000,   "Com trua");
    ThemGD(gdDau, idLonNhat, 14,4,2025, LOAI_CHI, DM_SINHHOAT, 150000,  "Tien dien phong tro");
    ThemGD(gdDau, idLonNhat, 15,4,2025, LOAI_CHI, DM_ANUONG,   90000,   "Com trua + ca phe");
    ThemGD(gdDau, idLonNhat, 17,4,2025, LOAI_CHI, DM_SUCKHOE,  200000,  "Kham benh");
    ThemGD(gdDau, idLonNhat, 20,4,2025, LOAI_CHI, DM_DICHUY,   30000,   "Xe om di vien");
    ThemGD(gdDau, idLonNhat, 22,4,2025, LOAI_CHI, DM_HOCTAP,   150000,  "In tai lieu on thi");
    ThemGD(gdDau, idLonNhat, 25,4,2025, LOAI_CHI, DM_ANUONG,   75000,   "Bun bo cho toi");
    ThemGD(gdDau, idLonNhat, 28,4,2025, LOAI_CHI, DM_GIAITRI,  120000,  "Mua game Steam");
    ThemGD(gdDau, idLonNhat, 30,4,2025, LOAI_CHI, DM_ANUONG,   100000,  "Lau vit cuoi thang");

    /* -- Tháng 5/2025 (vượt nhiều hạn mức) -- */
    ThemGD(gdDau, idLonNhat,  1,5,2025, LOAI_THU, DM_LUONG,    3000000, "Luong thang 5");
    ThemGD(gdDau, idLonNhat,  2,5,2025, LOAI_THU, DM_KHAC,     500000,  "Ban sach cu");
    ThemGD(gdDau, idLonNhat,  3,5,2025, LOAI_CHI, DM_ANUONG,   95000,   "Com trua");
    ThemGD(gdDau, idLonNhat,  5,5,2025, LOAI_CHI, DM_ANUONG,   200000,  "Tiec lop");
    ThemGD(gdDau, idLonNhat,  7,5,2025, LOAI_CHI, DM_HOCTAP,   500000,  "Hoc phi on thi TOEIC");
    ThemGD(gdDau, idLonNhat,  9,5,2025, LOAI_CHI, DM_GIAITRI,  250000,  "Bi-a + nuoc");
    ThemGD(gdDau, idLonNhat, 10,5,2025, LOAI_CHI, DM_ANUONG,   180000,  "Lau de nhom ban");
    ThemGD(gdDau, idLonNhat, 12,5,2025, LOAI_CHI, DM_DICHUY,   120000,  "Grab di sân bay");
    ThemGD(gdDau, idLonNhat, 14,5,2025, LOAI_CHI, DM_ANUONG,   310000,  "Tiec sinh nhat ban than");
    ThemGD(gdDau, idLonNhat, 16,5,2025, LOAI_CHI, DM_HOCTAP,   500000,  "Mua tai lieu on thi");
    ThemGD(gdDau, idLonNhat, 18,5,2025, LOAI_CHI, DM_SINHHOAT, 350000,  "Sua may tinh");
    ThemGD(gdDau, idLonNhat, 20,5,2025, LOAI_CHI, DM_ANUONG,   420000,  "An toi ngoai troi");
    ThemGD(gdDau, idLonNhat, 22,5,2025, LOAI_CHI, DM_GIAITRI,  230000,  "Karaoke");
    ThemGD(gdDau, idLonNhat, 25,5,2025, LOAI_CHI, DM_ANUONG,   300000,  "Buffet cuoi thang");
    ThemGD(gdDau, idLonNhat, 28,5,2025, LOAI_CHI, DM_DICHUY,   75000,   "Taxi ve que");
    ThemGD(gdDau, idLonNhat, 30,5,2025, LOAI_THU, DM_KHAC,     6400000, "Luong thuc tap");

    /* -- Tháng 6/2025 -- */
    ThemGD(gdDau, idLonNhat,  1,6,2025, LOAI_THU, DM_LUONG,    3000000, "Luong thang 6");
    ThemGD(gdDau, idLonNhat,  3,6,2025, LOAI_CHI, DM_ANUONG,   90000,   "Com trua");
    ThemGD(gdDau, idLonNhat,  5,6,2025, LOAI_CHI, DM_HOCTAP,   300000,  "Mua USB + cap sac");
    ThemGD(gdDau, idLonNhat,  8,6,2025, LOAI_CHI, DM_DICHUY,   55000,   "Xe buyt + grab");
    ThemGD(gdDau, idLonNhat, 10,6,2025, LOAI_CHI, DM_GIAITRI,  150000,  "Game online nap tien");
    ThemGD(gdDau, idLonNhat, 12,6,2025, LOAI_CHI, DM_ANUONG,   75000,   "Com trua");
    ThemGD(gdDau, idLonNhat, 15,6,2025, LOAI_CHI, DM_SUCKHOE,  120000,  "Mua thuoc");
    ThemGD(gdDau, idLonNhat, 18,6,2025, LOAI_CHI, DM_SINHHOAT, 100000,  "Mua do dung nha");
    ThemGD(gdDau, idLonNhat, 20,6,2025, LOAI_CHI, DM_ANUONG,   110000,  "Com + tra sua");
    ThemGD(gdDau, idLonNhat, 25,6,2025, LOAI_CHI, DM_KHAC,     200000,  "Qua sinh nhat ba");
    ThemGD(gdDau, idLonNhat, 28,6,2025, LOAI_CHI, DM_DICHUY,   40000,   "Xe buyt");
    ThemGD(gdDau, idLonNhat, 30,6,2025, LOAI_CHI, DM_ANUONG,   80000,   "Com chieu cuoi thang");

    /* -- Ngân sách -- */
    ThemNS(nsDau, DM_ANUONG,   5,2025, 600000);
    ThemNS(nsDau, DM_HOCTAP,   5,2025, 700000);
    ThemNS(nsDau, DM_GIAITRI,  5,2025, 400000);
    ThemNS(nsDau, DM_DICHUY,   5,2025, 300000);
    ThemNS(nsDau, DM_SINHHOAT, 5,2025, 500000);
    ThemNS(nsDau, DM_ANUONG,   6,2025, 700000);
    ThemNS(nsDau, DM_DICHUY,   6,2025, 200000);
    ThemNS(nsDau, DM_HOCTAP,   6,2025, 500000);
    ThemNS(nsDau, DM_GIAITRI,  6,2025, 300000);
    ThemNS(nsDau, DM_SUCKHOE,  6,2025, 200000);

    printf("  [OK] Da nap kich ban 'Sinh vien' — 48 GD, 10 NS\n");
    printf("       => Kiem thu: Menu 8 -> thang 5/2025 (co vuot ngan sach)\n");
}

/* Kịch bản 2: Đi làm full-time (1 tháng, trong hạn mức) */

void KichBanDiLam(GiaoDich** gdDau, NganSach** nsDau, int* idLonNhat) {
    ThemGD(gdDau, idLonNhat,  1,1,2025, LOAI_THU, DM_LUONG,    15000000,"Luong thang 1");
    ThemGD(gdDau, idLonNhat,  1,1,2025, LOAI_THU, DM_THUONG,   3000000, "Thuong tet duong lich");
    ThemGD(gdDau, idLonNhat,  5,1,2025, LOAI_CHI, DM_ANUONG,   250000,  "An sang + trua van phong");
    ThemGD(gdDau, idLonNhat,  8,1,2025, LOAI_CHI, DM_DICHUY,   180000,  "Xang xe thang");
    ThemGD(gdDau, idLonNhat, 10,1,2025, LOAI_CHI, DM_SINHHOAT, 2500000, "Tien thue nha thang 1");
    ThemGD(gdDau, idLonNhat, 12,1,2025, LOAI_CHI, DM_ANUONG,   350000,  "An toi gia dinh");
    ThemGD(gdDau, idLonNhat, 15,1,2025, LOAI_CHI, DM_GIAITRI,  450000,  "Du lich cuoi tuan");
    ThemGD(gdDau, idLonNhat, 18,1,2025, LOAI_CHI, DM_HOCTAP,   800000,  "Khoa hoc online");
    ThemGD(gdDau, idLonNhat, 20,1,2025, LOAI_CHI, DM_SUCKHOE,  300000,  "Kham suc khoe dinh ky");
    ThemGD(gdDau, idLonNhat, 22,1,2025, LOAI_CHI, DM_ANUONG,   200000,  "Com trua ca tuan");
    ThemGD(gdDau, idLonNhat, 25,1,2025, LOAI_CHI, DM_KHAC,     500000,  "Mua qua tet som");
    ThemGD(gdDau, idLonNhat, 28,1,2025, LOAI_CHI, DM_GIAITRI,  200000,  "Xem phim + mua sam");
    ThemGD(gdDau, idLonNhat, 30,1,2025, LOAI_CHI, DM_ANUONG,   320000,  "Tiec cuoi thang dong nghiep");

    ThemNS(nsDau, DM_ANUONG,   1,2025, 2000000);
    ThemNS(nsDau, DM_DICHUY,   1,2025, 500000);
    ThemNS(nsDau, DM_SINHHOAT, 1,2025, 3000000);
    ThemNS(nsDau, DM_GIAITRI,  1,2025, 1000000);
    ThemNS(nsDau, DM_HOCTAP,   1,2025, 1000000);

    printf("  [OK] Da nap kich ban 'Di lam full-time' — 13 GD, 5 NS\n");
    printf("       => Kiem thu: Menu 8 -> thang 1/2025\n");
}

/* Kịch bản 3: Tối thiểu (kiểm tra điều kiện biên) */

void KichBanToiThieu(GiaoDich** gdDau, NganSach** nsDau, int* idLonNhat) {
    ThemGD(gdDau, idLonNhat, 29,2,2028, LOAI_THU, DM_KHAC,    1,     "1 dong - toi thieu");
    ThemGD(gdDau, idLonNhat, 31,3,2025, LOAI_CHI, DM_ANUONG,  1,     "Chi 1 dong - bien");
    ThemNS(nsDau, DM_ANUONG, 3,2025, 1);

    printf("  [OK] Da nap kich ban 'Toi thieu' — 2 GD, 1 NS\n");
    printf("       => Kiem thu: Menu 8 -> thang 3/2025, nam nhuan 2028\n");
}

/* Kịch bản 4: Dữ liệu lớn (stress test) */

void KichBanLonNhieu(GiaoDich** gdDau, NganSach** nsDau, int* idLonNhat) {
    static const double mucChi[] = {
        80000, 120000, 50000, 200000, 350000, 90000, 110000
    };
    static const DanhMuc dsDM[] = {
        DM_ANUONG, DM_DICHUY, DM_GIAITRI, DM_HOCTAP, DM_SINHHOAT, DM_SUCKHOE, DM_KHAC
    };
    static const char* ghiChu[] = {
        "Com trua", "Di lai", "Giai tri", "Hoc tap", "Sinh hoat", "Suc khoe", "Khac"
    };
    int n = (int)(sizeof(dsDM) / sizeof(dsDM[0]));

    /* 12 tháng năm 2024, mỗi tháng 10 giao dịch thu + 10 chi */
    for (int t = 1; t <= 12; t++) {
        ThemGD(gdDau, idLonNhat, 1,t,2024, LOAI_THU, DM_LUONG,  12000000, "Luong");
        ThemGD(gdDau, idLonNhat, 5,t,2024, LOAI_THU, DM_THUONG,  2000000, "Thuong");
        for (int j = 0; j < n; j++) {
            int ngay = (j + 1) * 3 % 28 + 1;
            ThemGD(gdDau, idLonNhat, ngay, t, 2024,
                   LOAI_CHI, dsDM[j], mucChi[j] * (1 + t % 3), ghiChu[j]);
        }
    }

    /* Ngân sách cho 12 tháng */
    for (int t = 1; t <= 12; t++) {
        ThemNS(nsDau, DM_ANUONG,   t,2024, 1500000);
        ThemNS(nsDau, DM_DICHUY,   t,2024, 500000);
        ThemNS(nsDau, DM_GIAITRI,  t,2024, 600000);
        ThemNS(nsDau, DM_HOCTAP,   t,2024, 800000);
        ThemNS(nsDau, DM_SINHHOAT, t,2024, 2000000);
    }

    printf("  [OK] Da nap kich ban 'Du lieu lon' — 108 GD, 60 NS (nam 2024)\n");
    printf("       => Kiem thu: Menu 8 -> bao cao quy / bao cao nam 2024\n");
}

/* Hàm chính: chọn kịch bản và nạp */

void TaoDataMau(GiaoDich** gdDau, NganSach** nsDau, int* idLonNhat) {
    printf("\n--- TAO DU LIEU MAU ---\n");
    printf("  1. Sinh vien (3 thang, co vuot ngan sach)    — 48 GD, 10 NS\n");
    printf("  2. Di lam full-time (1 thang, trong han muc) — 13 GD,  5 NS\n");
    printf("  3. Toi thieu (kiem tra dieu kien bien)       —  2 GD,  1 NS\n");
    printf("  4. Du lieu lon / stress test (12 thang 2024) — 108 GD, 60 NS\n");
    printf("  0. Huy\n");

    int chon = NhapSoNguyen("  Chon kich ban (0-4): ", 0, 4);
    if (chon == 0) { printf("  Da huy.\n"); return; }

    /* Xóa dữ liệu cũ */
    GiaiPhongGiaoDich(gdDau);
    GiaiPhongNganSach(nsDau);
    *idLonNhat = 0;

    switch (chon) {
        case 1: KichBanSinhVien(gdDau, nsDau, idLonNhat);  break;
        case 2: KichBanDiLam(gdDau, nsDau, idLonNhat);     break;
        case 3: KichBanToiThieu(gdDau, nsDau, idLonNhat);  break;
        case 4: KichBanLonNhieu(gdDau, nsDau, idLonNhat);  break;
    }
}
