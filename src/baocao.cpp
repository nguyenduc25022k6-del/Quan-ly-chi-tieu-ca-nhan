#include <stdio.h>
#include <string.h>
#include "baocao.h"

#define BAR_MAX 40   /* Chiều rộng tối đa biểu đồ ASCII */

/* Hàm nội bộ */

static void InThanh(double phan_tram, int do_rong) {
    int so_thang = (int)(phan_tram / 100.0 * do_rong + 0.5);
    for (int i = 0; i < so_thang; i++) putchar('#');
}

/* Biểu đồ tỷ lệ chi tiêu theo danh mục */

void BieuDoChiTieu(const GiaoDich* dau, int thang, int nam) {
    double tongChi = TongChiThang(dau, thang, nam);
    if (tongChi <= 0) {
        printf("  (Khong co chi tieu trong thang nay.)\n");
        return;
    }

    printf("\n--- TY LE CHI TIEU THANG %02d/%04d (tong chi: %.0f VND) ---\n",
           thang, nam, tongChi);

    for (int i = 0; i < DM_COUNT; i++) {
        double chi = TongChiDanhMucThang(dau, (DanhMuc)i, thang, nam);
        if (chi <= 0) continue;
        double pct = chi / tongChi * 100.0;
        printf("  %-14s %5.1f%%  ", TenDanhMuc((DanhMuc)i), pct);
        InThanh(pct, BAR_MAX);
        putchar('\n');
    }
}

/* Cảnh báo vượt hạn mức */

void CanhBaoNganSach(const GiaoDich* gdDau, const NganSach* nsDau,
                     int thang, int nam) {
    printf("\n--- CANH BAO NGAN SACH THANG %02d/%04d ---\n", thang, nam);

    int coCanh = 0;
    for (int i = 0; i < DM_COUNT; i++) {
        double hanMuc = LayHanMuc(nsDau, (DanhMuc)i, thang, nam);
        if (hanMuc <= 0) continue;

        double daChi = TongChiDanhMucThang(dau, (DanhMuc)i, thang, nam);
        double pct   = daChi / hanMuc * 100.0;

        if (daChi > hanMuc) {
            printf("  [VUOT]   %-12s  da chi %10.0f / han muc %10.0f"
                   "  (vuot %10.0f | %.0f%%)\n",
                   TenDanhMuc((DanhMuc)i), daChi, hanMuc,
                   daChi - hanMuc, pct);
            coCanh = 1;
        } else if (pct >= 80.0) {
            printf("  [SAP HET] %-12s  da chi %10.0f / han muc %10.0f"
                   "  (%.0f%% - can than!)\n",
                   TenDanhMuc((DanhMuc)i), daChi, hanMuc, pct);
            coCanh = 1;
        }
    }
    if (!coCanh) printf("  Tat ca danh muc trong han muc. Tuyet voi!\n");
}

/* Báo cáo tháng */

void BaoCaoThang(const GiaoDich* gdDau, const NganSach* nsDau) {
    int thang = NhapSoNguyen("  Thang (1-12): ", 1, 12);
    int nam   = NhapSoNguyen("  Nam (2000-2100): ", 2000, 2100);

    double tongThu = TongThuThang(gdDau, thang, nam);
    double tongChi = TongChiThang(gdDau, thang, nam);
    double soDu    = tongThu - tongChi;

    printf("\n");
    InDuongKe('=', 54);
    printf("  BAO CAO TONG HOP THANG %02d/%04d\n", thang, nam);
    InDuongKe('=', 54);
    printf("  Tong thu : %15.0f VND\n", tongThu);
    printf("  Tong chi : %15.0f VND\n", tongChi);
    printf("  So du    : %15.0f VND", soDu);
    if (soDu < 0) printf("  <<< AM !");
    printf("\n");
    InDuongKe('=', 54);

    /* Chi tiết thu theo danh mục */
    printf("\n  [Thu theo danh muc]\n");
    for (int i = 0; i < DM_COUNT; i++) {
        double thu = 0;
        for (const GiaoDich* p = gdDau; p; p = p->tiep)
            if (p->loai == LOAI_THU && p->danhMuc == (DanhMuc)i &&
                p->thang == thang && p->nam == nam)
                thu += p->soTien;
        if (thu > 0)
            printf("  %-14s %15.0f VND\n", TenDanhMuc((DanhMuc)i), thu);
    }

    BieuDoChiTieu(gdDau, thang, nam);
    CanhBaoNganSach(gdDau, nsDau, thang, nam);
    InDuongKe('=', 54);
}

/* Báo cáo quý */

void BaoCaoQuy(const GiaoDich* dau) {
    int quy = NhapSoNguyen("  Quy (1-4): ", 1, 4);
    int nam  = NhapSoNguyen("  Nam (2000-2100): ", 2000, 2100);

    int thangDau = (quy - 1) * 3 + 1;
    int thangCuoi = thangDau + 2;

    double tongThu = 0, tongChi = 0;
    for (int t = thangDau; t <= thangCuoi; t++) {
        tongThu += TongThuThang(dau, t, nam);
        tongChi += TongChiThang(dau, t, nam);
    }

    printf("\n");
    InDuongKe('=', 54);
    printf("  BAO CAO QUY %d/%04d  (thang %02d - %02d)\n",
           quy, nam, thangDau, thangCuoi);
    InDuongKe('=', 54);
    printf("  Tong thu : %15.0f VND\n", tongThu);
    printf("  Tong chi : %15.0f VND\n", tongChi);
    printf("  So du    : %15.0f VND\n", tongThu - tongChi);

    printf("\n  Chi tiet theo thang:\n");
    printf("  %-10s %15s %15s %15s\n", "Thang", "Thu", "Chi", "So du");
    InDuongKe('-', 60);
    for (int t = thangDau; t <= thangCuoi; t++) {
        double thu = TongThuThang(dau, t, nam);
        double chi = TongChiThang(dau, t, nam);
        printf("  %02d/%04d   %15.0f %15.0f %15.0f\n",
               t, nam, thu, chi, thu - chi);
    }
    InDuongKe('=', 54);
}

/* Báo cáo năm */

void BaoCaoNam(const GiaoDich* dau) {
    int nam = NhapSoNguyen("  Nam (2000-2100): ", 2000, 2100);

    double tongThu = 0, tongChi = 0;
    for (int t = 1; t <= 12; t++) {
        tongThu += TongThuThang(dau, t, nam);
        tongChi += TongChiThang(dau, t, nam);
    }

    printf("\n");
    InDuongKe('=', 60);
    printf("  BAO CAO TONG KET NAM %04d\n", nam);
    InDuongKe('=', 60);
    printf("  Tong thu ca nam : %15.0f VND\n", tongThu);
    printf("  Tong chi ca nam : %15.0f VND\n", tongChi);
    printf("  So du ca nam    : %15.0f VND\n", tongThu - tongChi);

    printf("\n  Bien dong theo thang:\n");
    printf("  %-8s %15s %15s %10s\n", "Thang", "Thu", "Chi", "So du");
    InDuongKe('-', 54);

    /* Biểu đồ ASCII theo tháng */
    double maxChi = 1;
    for (int t = 1; t <= 12; t++) {
        double chi = TongChiThang(dau, t, nam);
        if (chi > maxChi) maxChi = chi;
    }

    for (int t = 1; t <= 12; t++) {
        double thu = TongThuThang(dau, t, nam);
        double chi = TongChiThang(dau, t, nam);
        if (thu == 0 && chi == 0) continue;
        int bar = (int)(chi / maxChi * 20 + 0.5);
        printf("  T%-7d %15.0f %15.0f %10.0f  ", t, thu, chi, thu - chi);
        for (int b = 0; b < bar; b++) putchar('|');
        putchar('\n');
    }
    InDuongKe('=', 60);
}
