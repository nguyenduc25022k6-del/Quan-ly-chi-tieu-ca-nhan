
#include <stdio.h>
#include <string.h>
#include "tienich.h"

/* Tra cứu chuỗi tên */

static const char* BANG_DANHMUC[DM_COUNT] = {
    "Luong", "Thuong", "An uong", "Di chuyen",
    "Hoc tap", "Giai tri", "Sinh hoat", "Suc khoe", "Khac"
};

static const char* BANG_LOAI[2] = { "Thu", "Chi" };

const char* TenDanhMuc(DanhMuc dm) {
    if (dm < 0 || dm >= DM_COUNT) return "Khac";
    return BANG_DANHMUC[dm];
}

const char* TenLoai(LoaiGiaoDich loai) {
    return BANG_LOAI[loai & 1];
}

DanhMuc DocDanhMuc(const char* ten) {
    for (int i = 0; i < DM_COUNT; i++) {
        if (strcmp(ten, BANG_DANHMUC[i]) == 0) return (DanhMuc)i;
    }
    return DM_KHAC;
}

LoaiGiaoDich DocLoai(const char* ten) {
    return (strcmp(ten, "Thu") == 0) ? LOAI_THU : LOAI_CHI;
}

/* Tiện ích nội bộ */

void LamSachBoDem(void) {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

int NgayHopLe(int ngay, int thang, int nam) {
    if (thang < 1 || thang > 12) return 0;
    if (ngay < 1)                 return 0;
    int soNgay[] = {0,31,28,31,30,31,30,31,31,30,31,30,31};
    /* Năm nhuận */
    if ((nam % 4 == 0 && nam % 100 != 0) || nam % 400 == 0)
        soNgay[2] = 29;
    return ngay <= soNgay[thang];
}

void InDuongKe(char ky, int so) {
    for (int i = 0; i < so; i++) putchar(ky);
    putchar('\n');
}

/* Nhập dữ liệu an toàn */

int NhapSoNguyen(const char* nhacNho, int min, int max) {
    int gt;
    while (1) {
        printf("%s", nhacNho);
        if (scanf("%d", &gt) == 1 && gt >= min && gt <= max) {
            LamSachBoDem();
            return gt;
        }
        LamSachBoDem();
        printf("  [!] Gia tri phai trong khoang [%d, %d]. Vui long nhap lai.\n",
               min, max);
    }
}

double NhapSoThuc(const char* nhacNho, double min) {
    double gt;
    while (1) {
        printf("%s", nhacNho);
        if (scanf("%lf", &gt) == 1 && gt >= min) {
            LamSachBoDem();
            return gt;
        }
        LamSachBoDem();
        printf("  [!] Gia tri phai >= %.0f. Vui long nhap lai.\n", min);
    }
}

void NhapChuoi(const char* nhacNho, char* buf, int maxLen) {
    printf("%s", nhacNho);
    if (fgets(buf, maxLen, stdin)) {
        int len = (int)strlen(buf);
        if (len > 0 && buf[len - 1] == '\n') buf[len - 1] = '\0';
    }
}

int NhapNgay(int* ngay, int* thang, int* nam) {
    while (1) {
        printf("  Nhap ngay (dd mm yyyy): ");
        if (scanf("%d %d %d", ngay, thang, nam) == 3) {
            LamSachBoDem();
            if (NgayHopLe(*ngay, *thang, *nam)) return 1;
        } else {
            LamSachBoDem();
        }
        printf("  [!] Ngay khong hop le. Vui long nhap lai.\n");
    }
}
