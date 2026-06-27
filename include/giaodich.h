#ifndef GIAODICH_H
#define GIAODICH_H

#include "tienich.h"

/* Struct nút DSLK đơn */
typedef struct GiaoDich {
    int           id;
    int           ngay, thang, nam;
    LoaiGiaoDich  loai;
    DanhMuc       danhMuc;
    double        soTien;
    char          ghiChu[MAX_GHICHU];
    struct GiaoDich* tiep;
} GiaoDich;

/* CRUD */
void ThemGiaoDich(GiaoDich** dau, int* idLonNhat);
void SuaGiaoDich(GiaoDich* dau);
void XoaGiaoDich(GiaoDich** dau);
void XemDanhSach(const GiaoDich* dau);

/* Tìm kiếm & lọc */
void TimKiemTheoThang(const GiaoDich* dau);
void LocTheoDanhMuc(const GiaoDich* dau);

/* Sắp xếp */
void SapXepTheoSoTien(GiaoDich* dau);
void SapXepTheoNgay(GiaoDich* dau);

/* Thống kê */
double TongThuThang(const GiaoDich* dau, int thang, int nam);
double TongChiThang(const GiaoDich* dau, int thang, int nam);
double TongChiDanhMucThang(const GiaoDich* dau, DanhMuc dm, int thang, int nam);
int    IDLonNhat(const GiaoDich* dau);

/* File I/O */
void DocFileGiaoDich(GiaoDich** dau, int* idLonNhat);
void GhiFileGiaoDich(const GiaoDich* dau);

/* Giải phóng bộ nhớ */
void GiaiPhongGiaoDich(GiaoDich** dau);

#endif /* GIAODICH_H */
