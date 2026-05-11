
# Praktikum Sistem Mikrokontroler - Modul 3
## Protokol Komunikasi
Apriyudha  |  H1H024010  |  Shift A
---

# 3.5.4 Pertanyaan Praktikum Percobaan 3A

## 1) Jelaskan proses dari input keyboard hingga LED menyala atau mati!

### Jawaban:
Proses dimulai ketika pengguna mengetik karakter pada keyboard di Serial Monitor. Karakter tersebut dikirim dari komputer ke Arduino melalui komunikasi serial UART (USB).

Arduino kemudian menerima data tersebut melalui buffer serial. Program akan mengecek apakah ada data masuk menggunakan `Serial.available()`. Jika ada, maka data dibaca menggunakan `Serial.read()`.

Data yang diterima berupa karakter, misalnya:
- '1' untuk menyalakan LED
- '0' untuk mematikan LED

Setelah karakter dibaca, program melakukan pengecekan kondisi:
- Jika '1', maka Arduino memberikan logika HIGH pada pin LED sehingga LED menyala
- Jika '0', maka Arduino memberikan logika LOW sehingga LED mati

Alur lengkap:
Keyboard → Serial Monitor → UART → Arduino (Serial.available → Serial.read) → Logika kondisi → Digital Output → LED


## 2) Mengapa digunakan Serial.available() sebelum membaca data? Apa yang terjadi jika baris tersebut dihilangkan?

### Jawaban:
`Serial.available()` digunakan untuk memastikan bahwa terdapat data yang masuk di buffer serial sebelum dilakukan pembacaan.

Fungsi ini mengembalikan jumlah byte data yang tersedia untuk dibaca. Dengan demikian, program hanya akan membaca data jika benar-benar ada data yang dikirim.

Jika baris ini dihilangkan:
- Arduino tetap mencoba membaca data menggunakan `Serial.read()`
- Ketika tidak ada data, nilai yang dibaca bisa berupa -1 atau data tidak valid
- Hal ini dapat menyebabkan error logika atau perilaku tidak terduga pada program

Kesimpulannya, `Serial.available()` berfungsi sebagai pengaman agar pembacaan data valid.


## 3) Modifikasi program agar LED berkedip (blink) ketika menerima input '2' dengan kondisi jika '2' aktif maka LED akan terus berkedip sampai perintah selanjutnya diberikan dan berikan penjelasan disetiap baris kode nya dalam bentuk README.md!

### Jawaban:

### Program:
```cpp
#include <Arduino.h>

const int PIN_LED = 12;     // Menentukan pin LED
bool modeBlink = false;     // Status mode blink

void setup() {
  Serial.begin(9600);       // Memulai komunikasi serial
  pinMode(PIN_LED, OUTPUT); // Set pin LED sebagai output
}

void loop() {

  if (Serial.available() > 0) {  // Cek apakah ada data masuk
    char data = Serial.read();   // Baca data dari serial

    if (data == '1') {           
      modeBlink = false;         
      digitalWrite(PIN_LED, HIGH); // LED menyala
    }
    else if (data == '0') {      
      modeBlink = false;         
      digitalWrite(PIN_LED, LOW);  // LED mati
    }
    else if (data == '2') {      
      modeBlink = true;          // Aktifkan mode blink
    }
  }

  if (modeBlink) {               
    digitalWrite(PIN_LED, HIGH); 
    delay(500);                  
    digitalWrite(PIN_LED, LOW);  
    delay(500);                  
  }
}
```
### Penjelasan:

* `modeBlink` digunakan untuk menyimpan kondisi LED apakah berkedip atau tidak
* Jika menerima '2', LED masuk mode berkedip terus menerus
* Jika menerima '1' atau '0', mode blink dimatikan
* `delay(500)` mengatur kecepatan kedipan LED

## 4) Tentukan apakah menggunakan delay() atau millis()! Jelaskan pengaruhnya terhadap sistem

### Jawaban:

Program menggunakan `delay()`.

Pengaruh:

* Program berhenti sementara saat delay berjalan
* Arduino tidak bisa membaca input baru selama delay
* Sistem menjadi kurang responsif

Jika menggunakan `millis()`:

* Program tidak berhenti (non-blocking)
* Tetap bisa membaca input saat LED berkedip
* Lebih cocok untuk sistem real-time

Kesimpulan:

* `delay()` sederhana tapi kurang efisien
* `millis()` lebih optimal untuk sistem interaktif

---

# 3.6.4 Pertanyaan Praktikum Percobaan 3B

## 1) Jelaskan bagaimana cara kerja komunikasi I2C antara Arduino dan LCD pada rangkaian tersebut!

### Jawaban:

I2C menggunakan dua jalur:

* SDA (data)
* SCL (clock)

Arduino sebagai master mengirim alamat LCD (misalnya 0x27), kemudian LCD merespons.

Data dikirim melalui SDA dan disinkronkan oleh SCL. LCD kemudian menampilkan data tersebut.

Keunggulan:

* Hanya menggunakan 2 kabel
* Bisa digunakan untuk banyak perangkat

## 2) Apakah pin potensiometer harus seperti itu? Jelaskan yang terjadi apabila pin kiri dan pin kanan tertukar!

### Jawaban:

Tidak harus, tetapi posisi menentukan arah perubahan nilai.

Jika pin kiri dan kanan ditukar:

* Nilai tetap terbaca
* Arah menjadi terbalik (putar kanan jadi kecil, putar kiri jadi besar)

## 3) Modifikasi program dengan menggabungkan UART dan I2C sehingga data tampil di LCD dan Serial Monitor serta berikan penjelasan disetiap baris kode nya dalam bentuk README.md!

### Jawaban:

### Program:

```cpp
#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <Arduino.h>

LiquidCrystal_I2C lcd(0x27, 16, 2); // Inisialisasi LCD
const int pinPot = A0;              // Pin potensiometer

void setup() {
  Serial.begin(9600);   // Memulai serial
  lcd.init();           // Inisialisasi LCD
  lcd.backlight();      // Menyalakan lampu LCD
}

void loop() {
  int nilai = analogRead(pinPot);     // Baca ADC
  float volt = nilai * (5.0 / 1023.0); // Konversi ke volt
  int persen = map(nilai, 0, 1023, 0, 100); // Konversi ke persen

  // Tampilkan ke Serial
  Serial.print("ADC: ");
  Serial.print(nilai);
  Serial.print(" Volt: ");
  Serial.print(volt);
  Serial.print(" V Persen: ");
  Serial.print(persen);
  Serial.println("%");

  // Tampilkan ke LCD
  lcd.setCursor(0, 0);
  lcd.print("ADC: ");
  lcd.print(nilai);
  lcd.print(" ");
  lcd.print(persen);
  lcd.print("%   ");

  lcd.setCursor(0, 1);
  int bar = map(nilai, 0, 1023, 0, 16);

  for (int i = 0; i < 16; i++) {
    if (i < bar) {
      lcd.print((char)255);
    } else {
      lcd.print(" ");
    }
  }

  delay(200);
}
```

### Penjelasan:

* Data analog dibaca dari potensiometer
* Nilai dikonversi menjadi volt dan persen
* Output ditampilkan ke Serial Monitor dan LCD

## 4) Lengkapi tabel berikut berdasarkan pengamatan pada Serial Monitor

### Jawaban:

| ADC | Volt (V) | Persen (%) |
| --- | -------- | ---------- |
| 1   | 0.00     | 0%         |
| 21  | 0.10     | 2%         |
| 49  | 0.24     | 4%         |
| 74  | 0.36     | 7%         |
| 96  | 0.47     | 9%         |

---

# 3.7 Pertanyaan Praktikum

## 1. Sebutkan dan jelaskan keuntungan dan kerugian menggunakan UART dan I2C!

### Jawaban:

UART:
Keuntungan:

* Sederhana
* Mudah digunakan
* Jarak lebih jauh

Kerugian:

* Hanya dua perangkat (point-to-point)

I2C:
Keuntungan:

* Hemat pin (2 saja)
* Bisa banyak device

Kerugian:

* Jarak pendek
* Lebih lambat

## 2. Bagaimana peran alamat I2C pada LCD (misalnya 0x27 vs 0x20)? Berikan penjelasan!

### Jawaban:

Alamat I2C digunakan untuk menentukan perangkat tujuan.

Jika alamat tidak sesuai:

* LCD tidak akan menampilkan data

Perbedaan alamat tergantung modul yang digunakan.

## 3. Jika UART dan I2C digabung dalam satu sistem, bagaimana alur kerja sistem tersebut? Bagaimana Arduino mengelola dua protokol sekaligus?

### Jawaban:

Alur:

1. Input dari Serial Monitor (UART)
2. Arduino membaca data
3. Data diproses
4. Output ditampilkan ke LCD (I2C)

Arduino menjalankan keduanya dalam loop secara bergantian dengan sangat cepat sehingga terlihat berjalan bersamaan.

---
Praktikum Sistem Mikrokobtroler - Modul 3