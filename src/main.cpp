/* main.cpp — Điểm vào duy nhất, điều phối menu
 * Nguyên tắc: main chỉ đọc file, gọi menu, ghi file rồi thoát */

#include <stdio.h>
#include "tienich.h"
#include "giaodich.h"
#include "ngansach.h"
#include "baocao.h"
#include "taodata.h"

/* Hàm in menu */

static void InMenu(void) {
    printf("\n");
    InDuongKe('=', 54);
    printf("     CHUONG TRINH QUAN LY CHI TIEU CA NHAN\n");
    InDuongKe('=', 54);
    printf("\n");
    printf("  --- GIAO DICH ---\n");
    printf("  1.  Them giao dich\n");
    printf("  2.  Sua giao dich\n");
    printf("  3.  Xoa giao dich\n");
    printf("  4.  Xem danh sach giao dich\n");
    printf("  5.  Tim kiem theo thang\n");
    printf("  6.  Loc theo danh muc\n");
    printf("  7.  Sap xep theo so tien\n");
    printf("  8.  Sap xep theo ngay\n");
    printf("\n");
    printf("  --- NGAN SACH ---\n");
    printf("  9.  Thiet lap / cap nhat ngan sach\n");
    printf("  10. Sua ngan sach\n");
    printf("  11. Xoa ngan sach\n");
    printf("  12. Xem danh sach ngan sach\n");
    printf("\n");
    printf("  --- BAO CAO ---\n");
    printf("  13. Bao cao tong hop theo thang\n");
    printf("  14. Bao cao theo quy  [MOI]\n");
    printf("  15. Bao cao tong ket nam [MOI]\n");
    printf("\n");
    printf("  --- TIEN ICH ---\n");
    printf("  16. Tao du lieu mau (kiem thu)\n");
    printf("  0.  Luu va thoat\n");
    InDuongKe('-', 54);
}

/*  Dispatch-table: mỗi phần tử là con trỏ hàm */

typedef struct {
    int ma;
    void (*xu_ly)(GiaoDich**, NganSach**, int*);
} MucMenu;

/* Wrapper để khớp chữ ký hàm */
static void _xemDanhSach(GiaoDich** gd, NganSach** ns, int* id)
    { (void)ns; (void)id; XemDanhSach(*gd); }

static void _themGD(GiaoDich** gd, NganSach** ns, int* id)
    { (void)ns; ThemGiaoDich(gd, id); }

static void _suaGD(GiaoDich** gd, NganSach** ns, int* id)
    { (void)ns; (void)id; SuaGiaoDich(*gd); }

static void _xoaGD(GiaoDich** gd, NganSach** ns, int* id)
    { (void)ns; (void)id; XoaGiaoDich(gd); }

static void _timKiem(GiaoDich** gd, NganSach** ns, int* id)
    { (void)ns; (void)id; TimKiemTheoThang(*gd); }

static void _locDM(GiaoDich** gd, NganSach** ns, int* id)
    { (void)ns; (void)id; LocTheoDanhMuc(*gd); }

static void _sapXepTien(GiaoDich** gd, NganSach** ns, int* id)
    { (void)ns; (void)id; SapXepTheoSoTien(*gd); }

static void _sapXepNgay(GiaoDich** gd, NganSach** ns, int* id)
    { (void)ns; (void)id; SapXepTheoNgay(*gd); }

static void _thietLapNS(GiaoDich** gd, NganSach** ns, int* id)
    { (void)gd; (void)id; ThietLapNganSach(ns); }

static void _suaNS(GiaoDich** gd, NganSach** ns, int* id)
    { (void)gd; (void)id; SuaNganSach(*ns); }

static void _xoaNS(GiaoDich** gd, NganSach** ns, int* id)
    { (void)gd; (void)id; XoaNganSach(ns); }

static void _xemNS(GiaoDich** gd, NganSach** ns, int* id)
    { (void)gd; (void)id; XemDanhSachNganSach(*ns); }

static void _baoCaoThang(GiaoDich** gd, NganSach** ns, int* id)
    { (void)id; BaoCaoThang(*gd, *ns); }

static void _baoCaoQuy(GiaoDich** gd, NganSach** ns, int* id)
    { (void)ns; (void)id; BaoCaoQuy(*gd); }

static void _baoCaoNam(GiaoDich** gd, NganSach** ns, int* id)
    { (void)ns; (void)id; BaoCaoNam(*gd); }

static void _taoData(GiaoDich** gd, NganSach** ns, int* id)
    { TaoDataMau(gd, ns, id); }

static const MucMenu BANG_MENU[] = {
    { 1,  _themGD       },
    { 2,  _suaGD        },
    { 3,  _xoaGD        },
    { 4,  _xemDanhSach  },
    { 5,  _timKiem      },
    { 6,  _locDM        },
    { 7,  _sapXepTien   },
    { 8,  _sapXepNgay   },
    { 9,  _thietLapNS   },
    { 10, _suaNS        },
    { 11, _xoaNS        },
    { 12, _xemNS        },
    { 13, _baoCaoThang  },
    { 14, _baoCaoQuy    },
    { 15, _baoCaoNam    },
    { 16, _taoData      },
};

#define SO_MUC_MENU  (int)(sizeof(BANG_MENU) / sizeof(BANG_MENU[0]))

/* main */

int main(void) {
    GiaoDich* gdDau    = NULL;
    NganSach* nsDau    = NULL;
    int       idLonNhat = 0;

    /* Nạp dữ liệu từ file */
    DocFileGiaoDich(&gdDau, &idLonNhat);
    DocFileNganSach(&nsDau);

    /* Đếm bản ghi đã nạp */
    int demGD = 0, demNS = 0;
    for (const GiaoDich* p = gdDau; p; p = p->tiep) demGD++;
    for (const NganSach* p = nsDau; p; p = p->tiep) demNS++;
    if (demGD > 0 || demNS > 0)
        printf("  Da nap %d giao dich va %d ngan sach tu file.\n",
               demGD, demNS);

    /* Vòng lặp menu chính */
    while (1) {
        InMenu();
        int chon = NhapSoNguyen("  Nhap lua chon (0-16): ", 0, 16);

        if (chon == 0) break;

        int timThay = 0;
        for (int i = 0; i < SO_MUC_MENU; i++) {
            if (BANG_MENU[i].ma == chon) {
                BANG_MENU[i].xu_ly(&gdDau, &nsDau, &idLonNhat);
                timThay = 1;
                break;
            }
        }
        if (!timThay) printf("  [!] Lua chon khong hop le.\n");
    }

    /* Lưu file và giải phóng bộ nhớ */
    GhiFileGiaoDich(gdDau);
    GhiFileNganSach(nsDau);
    printf("\n  Da luu du lieu. Tam biet!\n\n");

    GiaiPhongGiaoDich(&gdDau);
    GiaiPhongNganSach(&nsDau);
    return 0;
}
