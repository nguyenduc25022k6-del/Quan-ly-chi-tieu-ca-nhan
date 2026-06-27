# Quản Lý Chi Tiêu Cá Nhân

**Đề tài:** Hệ thống quản lý thu chi cá nhân sử dụng danh sách liên kết đơn  
**Môn:** Kỹ Thuật Lập Trình — MI3310 | ĐH Bách Khoa Hà Nội  
**Nhóm:** 12 | **GVHD:** Vũ Thành Nam | **Học kỳ:** 2025.2

---

## Yêu cầu hệ thống

- **g++** (GCC ≥ 7) — biên dịch code C/C++ chuẩn
Đây là toàn bộ nội dung raw Markdown — copy nguyên khối này dán vào file README.md trên GitHub là xong:
markdown# Quản Lý Chi Tiêu Cá Nhân

**Đề tài:** Hệ thống quản lý thu chi cá nhân sử dụng danh sách liên kết đơn  
**Môn:** Kỹ Thuật Lập Trình — MI3310 | ĐH Bách Khoa Hà Nội  
**Nhóm:** 12 | **GVHD:** Vũ Thành Nam | **Học kỳ:** 2025.2

---

## Yêu cầu hệ thống

- **g++** (GCC ≥ 7) — biên dịch code C/C++ chuẩn C++11
- Không cần cài thêm thư viện ngoài (chỉ dùng thư viện chuẩn C)

Kiểm tra phiên bản g++:
g++ --version

---

## Cách chạy chương trình

### Linux / macOS
cd quanlychitieu

make        # biên dịch

make run    # biên dịch + chạy ngay

make clean  # xóa file thực thi

### Windows
cd quanlychitieu

build.bat

> ⚠️ **Quan trọng:** Luôn chạy chương trình từ **thư mục gốc** của project (cùng cấp với thư mục `data/`). Nếu chạy từ thư mục khác, chương trình sẽ không tìm được file dữ liệu.

---

## Tạo dữ liệu mẫu (tùy chọn)

Muốn có sẵn dữ liệu khi mở chương trình lần đầu, vào **Menu → chọn 16**, sau đó chọn một trong 4 kịch bản:

| Kịch bản | Mô tả | Số lượng | Điểm kiểm thử |
|---|---|---|---|
| **1. Sinh viên** | 3 tháng (4–5–6/2025), có tháng vượt ngân sách | 48 GD, 10 NS | Menu 13 → tháng 5/2025 |
| **2. Đi làm full-time** | 1 tháng (1/2025), tất cả trong hạn mức | 13 GD, 5 NS | Menu 13 → tháng 1/2025 |
| **3. Tối thiểu** | 2 bản ghi, kiểm tra điều kiện biên (29/02 năm nhuận) | 2 GD, 1 NS | Menu 13 → tháng 3/2025 |
| **4. Dữ liệu lớn** | 12 tháng năm 2024, stress test | 108 GD, 60 NS | Menu 14 → quý / Menu 15 → năm 2024 |

---

## Cấu trúc dự án
quanlychitieu/

├── include/                  # Header files — khai báo kiểu dữ liệu và hàm

│   ├── tienich.h             # Hằng số, enum LoaiGiaoDich & DanhMuc, khai báo nhập liệu

│   ├── giaodich.h            # Kiểu GiaoDich (DSLK đơn) + khai báo CRUD

│   ├── ngansach.h            # Kiểu NganSach (DSLK đơn) + khai báo CRUD

│   ├── baocao.h              # Khai báo hàm báo cáo tháng/quý/năm, biểu đồ ASCII

│   └── taodata.h             # Khai báo hàm sinh dữ liệu mẫu (4 kịch bản)

│

├── src/                      # Source files — cài đặt logic

│   ├── main.cpp              # Điểm vào duy nhất — dispatch-table, không xử lý nghiệp vụ

│   ├── tienich.cpp           # Nhập liệu an toàn, ánh xạ enum ↔ chuỗi, kiểm tra ngày

│   ├── giaodich.cpp          # CRUD, tìm kiếm, lọc, sắp xếp, thống kê, file I/O

│   ├── ngansach.cpp          # CRUD ngân sách, file I/O

│   ├── baocao.cpp            # Báo cáo tháng/quý/năm, biểu đồ ASCII, cảnh báo hạn mức

│   └── taodata.cpp           # Sinh dữ liệu mẫu (4 kịch bản kiểm thử)

│

├── data/                     # File dữ liệu — tự động tạo/cập nhật khi chạy

│   ├── giaodich.txt          # Danh sách giao dịch thu/chi (pipe-delimited)

│   └── ngansach.txt          # Danh sách ngân sách theo danh mục (pipe-delimited)

│

├── build/                    # Output biên dịch (bị .gitignore, không push lên Git)

├── Makefile                  # Build cho Linux / macOS

├── build.bat                 # Build cho Windows

├── .gitignore

└── README.md

---

## Kiến trúc module
main (dispatch-table, không xử lý nghiệp vụ)

├── tienich   — lớp nền: nhập liệu an toàn, enum ↔ chuỗi, kiểm tra ngày hợp lệ

├── giaodich  — CRUD, tìm kiếm theo tháng, lọc danh mục, sắp xếp, thống kê, file I/O

├── ngansach  — CRUD hạn mức chi theo (danh mục, tháng, năm), file I/O

├── baocao    — báo cáo tháng/quý/năm, biểu đồ ASCII, cảnh báo vượt hạn mức

└── taodata   — sinh dữ liệu mẫu (4 kịch bản kiểm thử)

Nguyên tắc **top-down, không có biến toàn cục**: mỗi module chỉ biết những gì nó cần; `main` chỉ đọc file, gọi menu qua dispatch-table, ghi file rồi thoát.

---

## Hướng dẫn sử dụng

Sau khi chạy chương trình, menu chính hiển thị:
======================================================

CHUONG TRINH QUAN LY CHI TIEU CA NHAN
--- GIAO DICH ---

Them giao dich
Sua giao dich
Xoa giao dich
Xem danh sach giao dich
Tim kiem theo thang
Loc theo danh muc
Sap xep theo so tien
Sap xep theo ngay

--- NGAN SACH ---

9.  Thiet lap / cap nhat ngan sach

10. Sua ngan sach

11. Xoa ngan sach

12. Xem danh sach ngan sach
--- BAO CAO ---

13. Bao cao tong hop theo thang

14. Bao cao theo quy  [MOI]

15. Bao cao tong ket nam [MOI]
--- TIEN ICH ---

16. Tao du lieu mau (kiem thu)

0.  Luu va thoat

| Menu | Chức năng | Mô tả |
|---|---|---|
| **1** | Thêm giao dịch | Nhập ngày, loại (Thu/Chi), danh mục (9 loại), số tiền, ghi chú. ID tự động sinh. |
| **2** | Sửa giao dịch | Hiển thị danh sách, nhập ID, hỏi từng trường có muốn đổi không. |
| **3** | Xóa giao dịch | Xác nhận bằng ID trước khi xóa, tự động giải phóng bộ nhớ. |
| **4** | Xem danh sách | In toàn bộ giao dịch kèm tổng số bản ghi. |
| **5** | Tìm kiếm theo tháng | Lọc và hiển thị giao dịch theo tháng/năm nhập vào. |
| **6** | Lọc theo danh mục | Chỉ hiển thị giao dịch của một danh mục được chọn. |
| **7** | Sắp xếp theo số tiền | Selection Sort tăng dần hoặc giảm dần. |
| **8** | Sắp xếp theo ngày | Selection Sort theo thứ tự ngày tháng năm. |
| **9** | Thiết lập ngân sách | Đặt hạn mức chi cho (danh mục, tháng, năm). Tự cập nhật nếu đã tồn tại. |
| **10** | Sửa ngân sách | Cập nhật hạn mức của một bộ khóa đã có. |
| **11** | Xóa ngân sách | Xóa hạn mức theo (danh mục, tháng, năm). |
| **12** | Xem ngân sách | Danh sách toàn bộ hạn mức đã thiết lập. |
| **13** | Báo cáo tháng | Tổng thu/chi/số dư + biểu đồ ASCII `#` tỷ lệ % + cảnh báo `[VUOT]`/`[SAP HET]`. |
| **14** | Báo cáo quý *(mới)* | Tổng hợp 3 tháng trong quý, bảng so sánh thu/chi/số dư từng tháng. |
| **15** | Báo cáo năm *(mới)* | Tổng kết 12 tháng, biểu đồ cột ASCII `\|` tỷ lệ động. |
| **16** | Dữ liệu mẫu | Chọn 1 trong 4 kịch bản, xóa dữ liệu cũ và nạp mới vào bộ nhớ. |
| **0** | Lưu và thoát | Ghi toàn bộ dữ liệu xuống file rồi giải phóng bộ nhớ. |

### Ví dụ output — Báo cáo tháng (Menu 13)
======================================================

BAO CAO TONG HOP THANG 05/2025
Tong thu :      9900000 VND

Tong chi :      2975000 VND

So du    :      6925000 VND
--- TY LE CHI TIEU THANG 05/2025 (tong chi: 2975000 VND) ---

An uong         50.6%  ####################

Hoc tap         33.6%  #############

Giai tri        16.1%  ######

Di chuyen        9.8%  ####

Sinh hoat       13.1%  #####
--- CANH BAO NGAN SACH THANG 05/2025 ---

[VUOT]    An uong   da chi  1505000 / han muc   600000 (vuot  905000 | 251%)

[VUOT]    Hoc tap   da chi  1000000 / han muc   700000 (vuot  300000 | 143%)

[VUOT]    Giai tri  da chi   480000 / han muc   400000 (vuot   80000 | 120%)

### Ví dụ output — Báo cáo quý (Menu 14)
======================================================

BAO CAO QUY 2/2025  (thang 04 - 06)
Tong thu :     21400000 VND

Tong chi :      5535000 VND

So du    :     15865000 VND
Chi tiet theo thang:

Thang            Thu             Chi          So du

04/2025      3500000         1560000        1940000

05/2025      9900000         2975000        6925000

06/2025      8000000         1000000        7000000

---

## Định dạng file dữ liệu

Dữ liệu được lưu dưới dạng text thuần, phân tách bằng `|` để tránh lỗi khi nội dung có khoảng trắng.

**`data/giaodich.txt`**
id|ngay|thang|nam|loai|danhMuc|soTien|ghiChu

1|1|4|2025|Thu|Luong|3000000.00|Luong thang 4

2|3|4|2025|Chi|An uong|85000.00|Com trua

3|5|4|2025|Chi|An uong|120000.00|An toi sinh nhat ban

**`data/ngansach.txt`**
danhMuc|thang|nam|hanMuc

An uong|5|2025|600000.00

Di chuyen|5|2025|300000.00

Hoc tap|5|2025|700000.00

---

## Các điểm kỹ thuật nổi bật

| Chủ đề | Cài đặt cụ thể |
|---|---|
| **DSLK đơn** | `GiaoDich.tiep` và `NganSach.tiep` — thêm cuối O(n), xóa bất kỳ O(n), duyệt tuyến tính |
| **Enum thay chuỗi thô** | `LoaiGiaoDich` (LOAI_THU/LOAI_CHI) và `DanhMuc` (9 giá trị + `DM_COUNT`) — an toàn kiểu, duyệt vòng lặp qua `DM_COUNT` |
| **Selection Sort** | `SapXepTheoSoTien` và `SapXepTheoNgay`: hoán vị dữ liệu (data-swap), không đổi con trỏ `tiep` |
| **Dispatch-table** | `BANG_MENU[]` trong `main.cpp` — mảng `{ma, *xu_ly}`, tra tuyến tính, không cần `if-else` |
| **Lập trình phòng ngừa** | `NhapSoNguyen`, `NhapSoThuc`, `NhapNgay` đều có `while(1)` + kiểm tra biên + `LamSachBoDem()` |
| **Hàm `static` nội bộ** | `InMotGiaoDich`, `ChonLoai`, `ChonDanhMuc`, `TimTheoID` — ẩn hoàn toàn với module khác |
| **File I/O** | `sscanf` với `%199[^\n]` đọc được ghi chú có khoảng trắng; bỏ qua dòng lỗi định dạng |
| **Không memory leak** | `GiaiPhongGiaoDich` + `GiaiPhongNganSach` được gọi trong `main` trước `return 0` |

---

## Lưu ý quan trọng

- **Dữ liệu chỉ lưu khi chọn [0] Lưu và thoát** — tắt cửa sổ đột ngột sẽ mất thay đổi.
- **Lần đầu chạy** khi chưa có file: chương trình tự bắt đầu với danh sách rỗng, không báo lỗi.
- **Xóa toàn bộ dữ liệu:** xóa nội dung hai file trong thư mục `data/` hoặc chọn kịch bản mới ở Menu 16.
- **Mã ID giao dịch** được sinh tự động bằng `IDLonNhat + 1`, không bao giờ trùng trong một phiên.
- **Không chạy hai instance** chương trình cùng lúc trên cùng thư mục — có thể gây xung đột file.

---
