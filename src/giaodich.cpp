#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "giaodich.h"
#include "tienich.h"

#define FILE_GIAODICH "data/giaodich.txt"

/* Hàm nội bộ (static) */

static void InTieuDe(void) {
    printf("  %-4s %-12s %-5s %-12s %15s  %s\n",
           "ID", "Ngay", "Loai", "Danh muc", "So tien (VND)", "Ghi chu");
    InDuongKe('-', 72);
}

static void InMotGiaoDich(const GiaoDich* gd) {
    printf("  %-4d %02d/%02d/%04d  %-5s %-12s %15.0f  %s\n",
           gd->id, gd->ngay, gd->thang, gd->nam,
           TenLoai(gd->loai), TenDanhMuc(gd->danhMuc),
           gd->soTien, gd->ghiChu);
}

static DanhMuc ChonDanhMuc(void) {
    printf("\n  --- Danh muc ---\n");
    for (int i = 0; i < DM_COUNT; i++)
        printf("  %d. %s\n", i + 1, TenDanhMuc((DanhMuc)i));
    int chon = NhapSoNguyen("  Chon danh muc (1-9): ", 1, DM_COUNT);
    return (DanhMuc)(chon - 1);
}

static LoaiGiaoDich ChonLoai(void) {
    printf("  1. Thu\n  2. Chi\n");
    int chon = NhapSoNguyen("  Chon loai (1-2): ", 1, 2);
    return (chon == 1) ? LOAI_THU : LOAI_CHI;
}

static GiaoDich* TimTheoID(GiaoDich* dau, int id) {
    for (GiaoDich* p = dau; p != NULL; p = p->tiep)
        if (p->id == id) return p;
    return NULL;
}

/* Thêm giao dịch */

void ThemGiaoDich(GiaoDich** dau, int* idLonNhat) {
    GiaoDich* moi = (GiaoDich*)malloc(sizeof(GiaoDich));
    if (!moi) { printf("  [!] Het bo nho.\n"); return; }

    printf("\n--- THEM GIAO DICH MOI ---\n");
    NhapNgay(&moi->ngay, &moi->thang, &moi->nam);
    printf("  Loai giao dich:\n");
    moi->loai    = ChonLoai();
    moi->danhMuc = ChonDanhMuc();
    moi->soTien  = NhapSoThuc("  So tien (VND): ", 1.0);
    NhapChuoi("  Ghi chu: ", moi->ghiChu, MAX_GHICHU);

    moi->id   = ++(*idLonNhat);
    moi->tiep = NULL;

    /* Chèn cuối danh sách */
    if (*dau == NULL) {
        *dau = moi;
    } else {
        GiaoDich* duoi = *dau;
        while (duoi->tiep) duoi = duoi->tiep;
        duoi->tiep = moi;
    }
    printf("  [OK] Da them giao dich ID = %d.\n", moi->id);
}

/* Sửa giao dịch */

void SuaGiaoDich(GiaoDich* dau) {
    if (!dau) { printf("  [!] Danh sach trong.\n"); return; }
    XemDanhSach(dau);

    int id = NhapSoNguyen("  Nhap ID can sua (0 = huy): ", 0, 999999);
    if (id == 0) return;
    GiaoDich* gd = TimTheoID(dau, id);
    if (!gd) { printf("  [!] Khong tim thay ID %d.\n", id); return; }

    printf("\n  Nhan Enter de giu nguyen gia tri cu.\n");

    /* Ngày */
    printf("  Ngay hien tai: %02d/%02d/%04d\n", gd->ngay, gd->thang, gd->nam);
    int doi = NhapSoNguyen("  Doi ngay? (1=Co / 0=Khong): ", 0, 1);
    if (doi) NhapNgay(&gd->ngay, &gd->thang, &gd->nam);

    /* Loại */
    printf("  Loai hien tai: %s\n", TenLoai(gd->loai));
    doi = NhapSoNguyen("  Doi loai? (1=Co / 0=Khong): ", 0, 1);
    if (doi) gd->loai = ChonLoai();

    /* Danh mục */
    printf("  Danh muc hien tai: %s\n", TenDanhMuc(gd->danhMuc));
    doi = NhapSoNguyen("  Doi danh muc? (1=Co / 0=Khong): ", 0, 1);
    if (doi) gd->danhMuc = ChonDanhMuc();

    /* Số tiền */
    printf("  So tien hien tai: %.0f VND\n", gd->soTien);
    doi = NhapSoNguyen("  Doi so tien? (1=Co / 0=Khong): ", 0, 1);
    if (doi) gd->soTien = NhapSoThuc("  So tien moi: ", 1.0);

    /* Ghi chú */
    printf("  Ghi chu hien tai: %s\n", gd->ghiChu);
    doi = NhapSoNguyen("  Doi ghi chu? (1=Co / 0=Khong): ", 0, 1);
    if (doi) NhapChuoi("  Ghi chu moi: ", gd->ghiChu, MAX_GHICHU);

    printf("  [OK] Da cap nhat giao dich ID = %d.\n", id);
}

/* Xóa giao dịch */

void XoaGiaoDich(GiaoDich** dau) {
    if (!*dau) { printf("  [!] Danh sach trong.\n"); return; }
    XemDanhSach(*dau);

    int id = NhapSoNguyen("  Nhap ID can xoa (0 = huy): ", 0, 999999);
    if (id == 0) return;

    GiaoDich* truoc = NULL;
    GiaoDich* hien  = *dau;
    while (hien && hien->id != id) { truoc = hien; hien = hien->tiep; }

    if (!hien) { printf("  [!] Khong tim thay ID %d.\n", id); return; }

    int xn = NhapSoNguyen("  Xac nhan xoa? (1=Co / 0=Khong): ", 0, 1);
    if (!xn) { printf("  Da huy.\n"); return; }

    if (truoc) truoc->tiep = hien->tiep;
    else       *dau        = hien->tiep;
    free(hien);
    printf("  [OK] Da xoa giao dich ID = %d.\n", id);
}

/* Xem danh sách */

void XemDanhSach(const GiaoDich* dau) {
    printf("\n--- DANH SACH GIAO DICH ---\n");
    if (!dau) { printf("  (Chua co giao dich nao.)\n\n"); return; }

    InTieuDe();
    int dem = 0;
    for (const GiaoDich* p = dau; p; p = p->tiep) {
        InMotGiaoDich(p);
        dem++;
    }
    InDuongKe('-', 72);
    printf("  Tong: %d giao dich\n\n", dem);
}

/* Tìm kiếm theo tháng */

void TimKiemTheoThang(const GiaoDich* dau) {
    int thang = NhapSoNguyen("  Thang (1-12): ", 1, 12);
    int nam   = NhapSoNguyen("  Nam (2000-2100): ", 2000, 2100);

    printf("\n--- GIAO DICH THANG %02d/%04d ---\n", thang, nam);
    InTieuDe();

    int dem = 0;
    for (const GiaoDich* p = dau; p; p = p->tiep) {
        if (p->thang == thang && p->nam == nam) {
            InMotGiaoDich(p);
            dem++;
        }
    }
    if (dem == 0) printf("  (Khong co giao dich nao trong thang nay.)\n");
    InDuongKe('-', 72);
    printf("  Tim thay: %d giao dich\n\n", dem);
}

/* Lọc theo danh mục */

void LocTheoDanhMuc(const GiaoDich* dau) {
    DanhMuc dm = ChonDanhMuc();
    printf("\n--- GIAO DICH DANH MUC: %s ---\n", TenDanhMuc(dm));
    InTieuDe();

    int dem = 0;
    for (const GiaoDich* p = dau; p; p = p->tiep) {
        if (p->danhMuc == dm) { InMotGiaoDich(p); dem++; }
    }
    if (dem == 0) printf("  (Khong co giao dich nao.\n");
    InDuongKe('-', 72);
    printf("  Tim thay: %d giao dich\n\n", dem);
}

/* Sắp xếp Selection Sort theo số tiền */

void SapXepTheoSoTien(GiaoDich* dau) {
    if (!dau) return;
    int tang = NhapSoNguyen("  Sap xep (1=Tang dan / 2=Giam dan): ", 1, 2);
    for (GiaoDich* i = dau; i; i = i->tiep) {
        GiaoDich* min_max = i;
        for (GiaoDich* j = i->tiep; j; j = j->tiep) {
            int cond = (tang == 1) ? (j->soTien < min_max->soTien)
                                   : (j->soTien > min_max->soTien);
            if (cond) min_max = j;
        }
        if (min_max != i) {
            /* Hoán vị dữ liệu, không đổi con trỏ */
            GiaoDich tmp = *i;
            int      id  = i->id;
            GiaoDich* tp = i->tiep;

            *i       = *min_max;
            i->id    = id;
            i->tiep  = tp;

            *min_max       = tmp;
            min_max->id    = tmp.id;
            min_max->tiep  = min_max->tiep; /* giữ nguyên liên kết */
        }
    }

    /* Hoán vị đúng — viết lại đơn giản hơn */
    for (GiaoDich* i = dau; i; i = i->tiep) {
        GiaoDich* best = i;
        for (GiaoDich* j = i->tiep; j; j = j->tiep) {
            int cond = (tang == 1) ? (j->soTien < best->soTien)
                                   : (j->soTien > best->soTien);
            if (cond) best = j;
        }
        if (best != i) {
            double  tmpTien  = i->soTien;  i->soTien  = best->soTien;  best->soTien  = tmpTien;
            int     tmpNgay  = i->ngay;    i->ngay    = best->ngay;    best->ngay    = tmpNgay;
            int     tmpThang = i->thang;   i->thang   = best->thang;   best->thang   = tmpThang;
            int     tmpNam   = i->nam;     i->nam     = best->nam;     best->nam     = tmpNam;
            int     tmpId    = i->id;      i->id      = best->id;      best->id      = tmpId;
            LoaiGiaoDich tmpLoai = i->loai; i->loai   = best->loai;    best->loai    = tmpLoai;
            DanhMuc tmpDM        = i->danhMuc; i->danhMuc = best->danhMuc; best->danhMuc = tmpDM;
            char    tmpGC[MAX_GHICHU];
            strcpy(tmpGC, i->ghiChu); strcpy(i->ghiChu, best->ghiChu); strcpy(best->ghiChu, tmpGC);
        }
    }
    printf("  [OK] Da sap xep.\n");
}

/* Sắp xếp theo ngày */

void SapXepTheoNgay(GiaoDich* dau) {
    if (!dau) return;
    for (GiaoDich* i = dau; i; i = i->tiep) {
        GiaoDich* best = i;
        for (GiaoDich* j = i->tiep; j; j = j->tiep) {
            int ngayI = best->nam * 10000 + best->thang * 100 + best->ngay;
            int ngayJ = j->nam * 10000 + j->thang * 100 + j->ngay;
            if (ngayJ < ngayI) best = j;
        }
        if (best != i) {
            double  tmpTien  = i->soTien;  i->soTien  = best->soTien;  best->soTien  = tmpTien;
            int     tmpNgay  = i->ngay;    i->ngay    = best->ngay;    best->ngay    = tmpNgay;
            int     tmpThang = i->thang;   i->thang   = best->thang;   best->thang   = tmpThang;
            int     tmpNam   = i->nam;     i->nam     = best->nam;     best->nam     = tmpNam;
            int     tmpId    = i->id;      i->id      = best->id;      best->id      = tmpId;
            LoaiGiaoDich tmpLoai = i->loai; i->loai   = best->loai;    best->loai    = tmpLoai;
            DanhMuc tmpDM        = i->danhMuc; i->danhMuc = best->danhMuc; best->danhMuc = tmpDM;
            char    tmpGC[MAX_GHICHU];
            strcpy(tmpGC, i->ghiChu); strcpy(i->ghiChu, best->ghiChu); strcpy(best->ghiChu, tmpGC);
        }
    }
    printf("  [OK] Da sap xep theo ngay.\n");
}

/* Thống kê */

double TongThuThang(const GiaoDich* dau, int thang, int nam) {
    double tong = 0;
    for (const GiaoDich* p = dau; p; p = p->tiep)
        if (p->loai == LOAI_THU && p->thang == thang && p->nam == nam)
            tong += p->soTien;
    return tong;
}

double TongChiThang(const GiaoDich* dau, int thang, int nam) {
    double tong = 0;
    for (const GiaoDich* p = dau; p; p = p->tiep)
        if (p->loai == LOAI_CHI && p->thang == thang && p->nam == nam)
            tong += p->soTien;
    return tong;
}

double TongChiDanhMucThang(const GiaoDich* dau, DanhMuc dm, int thang, int nam) {
    double tong = 0;
    for (const GiaoDich* p = dau; p; p = p->tiep)
        if (p->loai == LOAI_CHI && p->danhMuc == dm &&
            p->thang == thang && p->nam == nam)
            tong += p->soTien;
    return tong;
}

int IDLonNhat(const GiaoDich* dau) {
    int max = 0;
    for (const GiaoDich* p = dau; p; p = p->tiep)
        if (p->id > max) max = p->id;
    return max;
}

/* File I/O */

void DocFileGiaoDich(GiaoDich** dau, int* idLonNhat) {
    FILE* f = fopen(FILE_GIAODICH, "r");
    if (!f) return;   /* Lần đầu chưa có file — bình thường */

    char dong[512];
    fgets(dong, sizeof(dong), f); /* Bỏ dòng header */

    while (fgets(dong, sizeof(dong), f)) {
        GiaoDich* gd = (GiaoDich*)malloc(sizeof(GiaoDich));
        if (!gd) break;

        char tenLoai[16], tenDM[MAX_DANHMUC];
        int  ok = sscanf(dong,
            "%d|%d|%d|%d|%15[^|]|%63[^|]|%lf|%199[^\n]",
            &gd->id, &gd->ngay, &gd->thang, &gd->nam,
            tenLoai, tenDM, &gd->soTien, gd->ghiChu);

        if (ok < 7) { free(gd); continue; }
        if (ok == 7) gd->ghiChu[0] = '\0';

        gd->loai    = DocLoai(tenLoai);
        gd->danhMuc = DocDanhMuc(tenDM);
        gd->tiep    = NULL;

        if (*idLonNhat < gd->id) *idLonNhat = gd->id;

        /* Chèn cuối */
        if (!*dau) {
            *dau = gd;
        } else {
            GiaoDich* p = *dau;
            while (p->tiep) p = p->tiep;
            p->tiep = gd;
        }
    }
    fclose(f);
}

void GhiFileGiaoDich(const GiaoDich* dau) {
    FILE* f = fopen(FILE_GIAODICH, "w");
    if (!f) { printf("  [!] Khong the ghi file giao dich.\n"); return; }

    fprintf(f, "id|ngay|thang|nam|loai|danhMuc|soTien|ghiChu\n");
    for (const GiaoDich* p = dau; p; p = p->tiep) {
        fprintf(f, "%d|%d|%d|%d|%s|%s|%.2f|%s\n",
                p->id, p->ngay, p->thang, p->nam,
                TenLoai(p->loai), TenDanhMuc(p->danhMuc),
                p->soTien, p->ghiChu);
    }
    fclose(f);
}

/* Giải phóng bộ nhớ */

void GiaiPhongGiaoDich(GiaoDich** dau) {
    GiaoDich* p = *dau;
    while (p) {
        GiaoDich* tiep = p->tiep;
        free(p);
        p = tiep;
    }
    *dau = NULL;
}
