#ifndef TAODATA_H
#define TAODATA_H

#include "giaodich.h"
#include "ngansach.h"

/* Xóa toàn bộ và nạp kịch bản được chọn */
void TaoDataMau(GiaoDich** gdDau, NganSach** nsDau, int* idLonNhat);

/* Kịch bản riêng lẻ */
void KichBanSinhVien(GiaoDich** gdDau, NganSach** nsDau, int* idLonNhat);
void KichBanDiLam(GiaoDich** gdDau, NganSach** nsDau, int* idLonNhat);
void KichBanToiThieu(GiaoDich** gdDau, NganSach** nsDau, int* idLonNhat);
void KichBanLonNhieu(GiaoDich** gdDau, NganSach** nsDau, int* idLonNhat);

#endif /* TAODATA_H */
