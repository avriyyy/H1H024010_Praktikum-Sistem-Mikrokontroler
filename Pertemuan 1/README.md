# Praktikum Sistem Mikrokontroler - Modul 1
## Percabangan dan Perulangan
---

# 1.5.4 Pertanyaan Praktikum Percobaan 1 Percabangan:

## 1. Pada kondisi apa program masuk ke blok if?

Program akan masuk ke blok `if` ketika kondisi bernilai benar (true), yaitu saat nilai:

```cpp
timeDelay <= 100
```

Hal ini menunjukkan bahwa delay sudah mencapai batas minimum sehingga program akan melakukan reset.

---

## 2. Pada kondisi apa program masuk ke blok else?

Program akan masuk ke blok `else` ketika kondisi pada `if` bernilai salah (false), yaitu saat:

```cpp
timeDelay > 100
```

Artinya program masih berada dalam proses percepatan kedipan LED.

---

## 3. Apa fungsi dari perintah delay(timeDelay)?

Perintah `delay(timeDelay)` berfungsi untuk memberikan jeda waktu dalam satuan milidetik. Fungsi ini mengatur kecepatan LED berkedip:

* Nilai besar → LED berkedip lambat
* Nilai kecil → LED berkedip cepat

---

## 4. Jika program yang dibuat memiliki alur mati → lambat → cepat → reset (mati), ubah menjadi LED tidak langsung reset → tetapi berubah dari cepat → sedang → mati dan berikan penjelasan disetiap baris kode nya dalam bentuk README.md!

### Kode Program

```cpp
const int ledPin = 6;
int timeDelay = 1000;

void setup() {
  pinMode(ledPin, OUTPUT);
}

void loop() {
  digitalWrite(ledPin, HIGH);
  delay(timeDelay);

  digitalWrite(ledPin, LOW);
  delay(timeDelay);

  if (timeDelay > 300) {
    timeDelay -= 100;
  } else if (timeDelay > 100) {
    timeDelay -= 50;
  } else {
    digitalWrite(ledPin, LOW);
    delay(3000);
    timeDelay = 1000;
  }
}
```

### Penjelasan setiap baris kode

* `const int ledPin = 6;` menentukan pin LED yang digunakan.
* `int timeDelay = 1000;` menentukan nilai awal delay (lambat).
* `pinMode(ledPin, OUTPUT);` mengatur pin sebagai output.
* `digitalWrite(ledPin, HIGH);` menyalakan LED.
* `delay(timeDelay);` memberi jeda sesuai nilai delay.
* `digitalWrite(ledPin, LOW);` mematikan LED.
* `if (timeDelay > 300)` mengatur fase dari lambat ke cepat.
* `else if (timeDelay > 100)` mengatur fase sedang.
* `else` digunakan saat LED sudah cepat, kemudian dimatikan dan di-reset.
* `timeDelay -= ...` digunakan untuk mengurangi delay sehingga LED semakin cepat.

---

# 1.6.4 Pertanyaan Praktikum percobaan 2 perulangan

## 1. Gambarkan rangkaian schematic 5 LED running yang digunakan pada percobaan!

Rangkaian terdiri dari 5 LED yang masing-masing terhubung ke pin digital Arduino melalui resistor, kemudian ke GND.

```
Pin 2 ---- LED ---- Resistor ---- GND
Pin 3 ---- LED ---- Resistor ---- GND
Pin 4 ---- LED ---- Resistor ---- GND
Pin 5 ---- LED ---- Resistor ---- GND
Pin 6 ---- LED ---- Resistor ---- GND
```

---

## 2. Jelaskan bagaimana program membuat efek LED berjalan dari kiri ke kanan!

Efek LED dari kiri ke kanan dibuat menggunakan perulangan `for` dengan nilai pin yang meningkat:

```cpp
for (int ledPin = 2; ledPin <= 7; ledPin++)
```

Setiap iterasi akan menyalakan LED secara berurutan dari pin kecil ke pin besar sehingga terlihat seperti bergerak dari kiri ke kanan.

---

## 3. Jelaskan bagaimana program membuat LED kembali dari kanan ke kiri!

Efek LED dari kanan ke kiri dibuat menggunakan perulangan `for` dengan nilai pin yang menurun:

```cpp
for (int ledPin = 7; ledPin >= 2; ledPin--)
```

Setiap iterasi akan menyalakan LED dari pin besar ke kecil sehingga terlihat seperti bergerak dari kanan ke kiri.

---

## 4. Buatkan program agar LED menyala tiga LED kanan dan tiga LED kiri secara bergantian dan berikan penjelasan disetiap baris kode nya dalam bentuk README.md!

### Kode Program

```cpp
int timer = 200;

void setup() {
  for (int i = 2; i <= 7; i++) {
    pinMode(i, OUTPUT);
  }
}

void loop() {
  digitalWrite(2, HIGH);
  digitalWrite(3, HIGH);
  digitalWrite(4, HIGH);
  delay(timer);

  digitalWrite(2, LOW);
  digitalWrite(3, LOW);
  digitalWrite(4, LOW);

  digitalWrite(5, HIGH);
  digitalWrite(6, HIGH);
  digitalWrite(7, HIGH);
  delay(timer);

  digitalWrite(5, LOW);
  digitalWrite(6, LOW);
  digitalWrite(7, LOW);
}
```

### Penjelasan setiap baris kode

* `int timer = 200;` menentukan waktu jeda.
* `for (int i = 2; i <= 7; i++)` menginisialisasi pin sebagai output.
* `digitalWrite(..., HIGH)` menyalakan LED.
* `digitalWrite(..., LOW)` mematikan LED.
* Pin 2–4 digunakan untuk LED kiri.
* Pin 5–7 digunakan untuk LED kanan.
* Program membuat kedua kelompok LED menyala secara bergantian.

---

# 1.7 Pertanyaan Analisis

## Jawablah pertanyaan berikut sebagai bahan dalam laporan praktikum pada Bagian Hasil dan Analisis

### 1. Uraikan hasil tugas pada praktikum yang telah dilakukan pada setiap percobaan!

Pada percobaan percabangan, LED dapat berubah kecepatan berdasarkan nilai delay. Pada percobaan perulangan, LED dapat menyala secara berurutan dan bolak-balik sesuai dengan logika perulangan.

---

### 2. Bagaimana pengaruh penggunaan struktur perulangan (seperti for dan while) terhadap jalannya program pada Arduino?

Perulangan memungkinkan program berjalan secara terus-menerus dan berulang tanpa harus menulis kode yang sama. Hal ini membuat program lebih efisien dan mempermudah pembuatan pola seperti LED running.

---

### 3. Bagaimana cara kerja percabangan (if-else) dalam menentukan kondisi LED menyala atau mati berdasarkan input yang diberikan?

Percabangan bekerja dengan mengevaluasi kondisi. Jika kondisi benar maka blok `if` dijalankan, jika salah maka blok `else` dijalankan. Dalam Arduino, ini digunakan untuk mengontrol kapan LED menyala atau mati.

---

### 4. Bagaimana kombinasi antara perulangan dan percabangan dapat digunakan untuk membuat sistem Arduino yang responsif terhadap perubahan kondisi lingkungan?

Perulangan digunakan untuk menjalankan program secara terus-menerus, sedangkan percabangan digunakan untuk mengambil keputusan berdasarkan kondisi tertentu. Kombinasi keduanya memungkinkan sistem merespons perubahan secara real-time, seperti perubahan nilai sensor.

---
Praktikum Sistem Mikrokobtroler - Modul 1
