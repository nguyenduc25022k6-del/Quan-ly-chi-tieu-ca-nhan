#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "ngansach.h"

#define FILE_NGANSACH "data/ngansach.txt"

/* Hàm nội bộ (static) */

static NganSach* Tim(NganSach* dau, DanhMuc dm, int thang, int nam) {
    for (NganSach* p = dau; p; p = p->tiep)
        if (p->danhMuc == dm && p->thang == thang && p->nam == nam) return p;
    return NULL;
}

static DanhMuc ChonDanhMucNS(void) {
    printf("\n  --- Danh muc ---\n");
    for (int i = 0; i < DM_COUNT; i++)
        printf("  %d. %s\n", i + 1, TenDanhMuc((DanhMuc)i));
    int chon = NhapSoNguyen("  Chon danh muc (1-9): ", 1, DM_COUNT);
    return (DanhMuc)(chon - 1);
}

/* Thiết lập / cập nhật ngân sách */

void ThietLapNganSach(NganSach** dau) {
    printf("\n--- THIET LAP NGAN SACH ---\n");
    DanhMuc dm  = ChonDanhMucNS();
    int     thang = NhapSoNguyen("  Thang (1-12): ", 1, 12);
    int     nam   = NhapSoNguyen("  Nam (2000-2100): ", 2000, 2100);
    double  hanMuc = NhapSoThuc("  Han muc chi (VND): ", 1.0);

    NganSach* cu = Tim(*dau, dm, thang, nam);
    if (cu) {
        cu->hanMuc = hanMuc;
        printf("  [OK] Da cap nhat han muc '%s' thang %02d/%04d: %.0f VND.\n",
               TenDanhMuc(dm), thang, nam, hanMuc);
        return;
    }

    NganSach* moi = (NganSach*)malloc(sizeof(NganSach));
    if (!moi) { printf("  [!] Het bo nho.\n"); return; }
    moi->danhMuc = dm;
    moi->thang   = thang;
    moi->nam     = nam;
    moi->hanMuc  = hanMuc;
    moi->tiep    = NULL;

    if (!*dau) {
        *dau = moi;
    } else {
        NganSach* p = *dau;
        while (p->tiep) p = p->tiep;
        p->tiep = moi;
    }
    printf("  [OK] Da them ngan sach '%s' thang %02d/%04d: %.0f VND.\n",
           TenDanhMuc(dm), thang, nam, hanMuc);
}

/* Sửa ngân sách */

void SuaNganSach(NganSach* dau) {
    if (!dau) { printf("  [!] Chua co ngan sach nao.\n"); return; }
    XemDanhSachNganSach(dau);

    DanhMuc dm    = ChonDanhMucNS();
    int     thang = NhapSoNguyen("  Thang (1-12): ", 1, 12);
    int     nam   = NhapSoNguyen("  Nam (2000-2100): ", 2000, 2100);

    NganSach* ns = Tim(dau, dm, thang, nam);
    if (!ns) { printf("  [!] Khong tim thay ngan sach can sua.\n"); return; }

    printf("  Han muc hien tai: %.0f VND\n", ns->hanMuc);
    ns->hanMuc = NhapSoThuc("  Han muc moi (VND): ", 1.0);
    printf("  [OK] Da cap nhat han muc.\n");
}

/* Xóa ngân sách */

void XoaNganSach(NganSach** dau) {
    if (!*dau) { printf("  [!] Chua co ngan sach nao.\n"); return; }
    XemDanhSachNganSach(*dau);

    DanhMuc dm    = ChonDanhMucNS();
    int     thang = NhapSoNguyen("  Thang (1-12): ", 1, 12);
    int     nam   = NhapSoNguyen("  Nam (2000-2100): ", 2000, 2100);

    NganSach* truoc = NULL;
    NganSach* hien  = *dau;
    while (hien && !(hien->danhMuc == dm && hien->thang == thang && hien->nam == nam)) {
        truoc = hien; hien = hien->tiep;
    }
    if (!hien) { printf("  [!] Khong tim thay.\n"); return; }

    int xn = NhapSoNguyen("  Xac nhan xoa? (1=Co / 0=Khong): ", 0, 1);
    if (!xn) { printf("  Da huy.\n"); return; }

    if (truoc) truoc->tiep = hien->tiep;
    else       *dau        = hien->tiep;
    free(hien);
    printf("  [OK] Da xoa ngan sach.\n");
}

/* Xem danh sách ngân sách */

void XemDanhSachNganSach(const NganSach* dau) {
    printf("\n--- DANH SACH NGAN SACH ---\n");
    if (!dau) { printf("  (Chua co ngan sach nao.)\n\n"); return; }

    printf("  %-14s %8s %15s\n", "Danh muc", "Thang/Nam", "Han muc (VND)");
    InDuongKe('-', 44);
    int dem = 0;
    for (const NganSach* p = dau; p; p = p->tiep) {
        printf("  %-14s %02d/%04d  %15.0f\n",
               TenDanhMuc(p->danhMuc), p->thang, p->nam, p->hanMuc);
        dem++;
    }
    InDuongKe('-', 44);
    printf("  Tong: %d ngan sach\n\n", dem);
}

/* Truy vấn hạn mức */

double LayHanMuc(const NganSach* dau, DanhMuc dm, int thang, int nam) {
    for (const NganSach* p = dau; p; p = p->tiep)
        if (p->danhMuc == dm && p->thang == thang && p->nam == nam)
            return p->hanMuc;
    return 0.0;
}

/* File I/O */

void DocFileNganSach(NganSach** dau) {
    FILE* f = fopen(FILE_NGANSACH, "r");
    if (!f) return;

    char dong[256];
    fgets(dong, sizeof(dong), f); /* Bỏ header */

    while (fgets(dong, sizeof(dong), f)) {
        NganSach* ns = (NganSach*)malloc(sizeof(NganSach));
        if (!ns) break;

        char tenDM[MAX_DANHMUC];
        int ok = sscanf(dong, "%63[^|]|%d|%d|%lf",
                        tenDM, &ns->thang, &ns->nam, &ns->hanMuc);
        if (ok < 4) { free(ns); continue; }

        ns->danhMuc = DocDanhMuc(tenDM);
        ns->tiep    = NULL;

        if (!*dau) {
            *dau = ns;
        } else {
            NganSach* p = *dau;
            while (p->tiep) p = p->tiep;
            p->tiep = ns;
        }
    }
    fclose(f);
}

void GhiFileNganSach(const NganSach* dau) {
    FILE* f = fopen(FILE_NGANSACH, "w");
    if (!f) { printf("  [!] Khong the ghi file ngan sach.\n"); return; }

    fprintf(f, "danhMuc|thang|nam|hanMuc\n");
    for (const NganSach* p = dau; p; p = p->tiep)
        fprintf(f, "%s|%d|%d|%.2f\n",
                TenDanhMuc(p->danhMuc), p->thang, p->nam, p->hanMuc);
    fclose(f);
}

/* Giải phóng bộ nhớ */

void GiaiPhongNganSach(NganSach** dau) {
    NganSach* p = *dau;
    while (p) {
        NganSach* tiep = p->tiep;
        free(p);
        p = tiep;
    }
    *dau = NULL;
}
