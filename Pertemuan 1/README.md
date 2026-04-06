# README Praktikum Modul 1

## Percabangan dan Perulangan (Arduino)

---

# 1. Percobaan 1 – Percabangan

## 1.5.4 Pertanyaan dan Jawaban

### 1. Pada kondisi apa program masuk ke blok `if`?

Program akan masuk ke blok `if` ketika kondisi bernilai benar (true), yaitu saat:

```
timeDelay <= 100
```

Artinya nilai delay sudah mencapai batas minimum sehingga perlu dilakukan reset.

---

### 2. Pada kondisi apa program masuk ke blok `else`?

Program akan masuk ke blok `else` ketika kondisi pada `if` bernilai salah (false), yaitu:

```
timeDelay > 100
```

Artinya program masih berada pada fase percepatan LED.

---

### 3. Apa fungsi dari perintah `delay(timeDelay)`?

Perintah `delay(timeDelay)` digunakan untuk memberikan jeda waktu dalam satuan milidetik. Fungsi ini mengatur kecepatan nyala dan mati LED:

* Nilai besar → LED berkedip lambat
* Nilai kecil → LED berkedip cepat

---

### 4. Modifikasi Program (cepat → sedang → mati)

#### Kode Program

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

#### Penjelasan

* `ledPin` digunakan untuk menentukan pin output LED.
* `timeDelay` menyimpan nilai jeda waktu.
* `pinMode` mengatur pin sebagai output.
* `digitalWrite(HIGH)` menyalakan LED.
* `digitalWrite(LOW)` mematikan LED.
* Kondisi `if` digunakan untuk mengatur perubahan kecepatan LED dari lambat ke cepat.
* `else if` digunakan untuk fase transisi (sedang).
* `else` digunakan untuk menghentikan LED dan mengatur ulang nilai delay.

---

# 2. Percobaan 2 – Perulangan

## 1.6.4 Pertanyaan dan Jawaban

### 1. Gambaran rangkaian 5 LED running

Setiap LED dihubungkan ke pin digital Arduino melalui resistor, kemudian ke GND.

```
Pin 2 ---- LED ---- Resistor ---- GND
Pin 3 ---- LED ---- Resistor ---- GND
Pin 4 ---- LED ---- Resistor ---- GND
Pin 5 ---- LED ---- Resistor ---- GND
Pin 6 ---- LED ---- Resistor ---- GND
```

---

### 2. Cara kerja LED dari kiri ke kanan

Program menggunakan perulangan `for` dengan nilai pin yang meningkat:

```cpp
for (int ledPin = 2; ledPin <= 7; ledPin++)
```

Setiap iterasi akan menyalakan LED secara berurutan dari pin kecil ke besar.

---

### 3. Cara kerja LED dari kanan ke kiri

Program menggunakan perulangan `for` dengan nilai pin yang menurun:

```cpp
for (int ledPin = 7; ledPin >= 2; ledPin--)
```

Setiap iterasi akan menyalakan LED dari pin besar ke kecil.

---

### 4. Program 3 LED kanan dan kiri bergantian

#### Kode Program

```cpp
int timer = 200;

void setup() {
  for (int i = 2; i <= 7; i++) {
    pinMode(i, OUTPUT);
  }
}

void loop() {
  // LED kiri (pin 2, 3, 4)
  digitalWrite(2, HIGH);
  digitalWrite(3, HIGH);
  digitalWrite(4, HIGH);
  delay(timer);

  digitalWrite(2, LOW);
  digitalWrite(3, LOW);
  digitalWrite(4, LOW);

  // LED kanan (pin 5, 6, 7)
  digitalWrite(5, HIGH);
  digitalWrite(6, HIGH);
  digitalWrite(7, HIGH);
  delay(timer);

  digitalWrite(5, LOW);
  digitalWrite(6, LOW);
  digitalWrite(7, LOW);
}
```

#### Penjelasan

* Perulangan `for` digunakan untuk menginisialisasi semua pin sebagai output.
* LED dibagi menjadi dua kelompok: kiri (2–4) dan kanan (5–7).
* Setiap kelompok dinyalakan secara bergantian dengan jeda waktu tertentu.
* Pola ini akan terus berulang di dalam fungsi `loop`.

---

# 3. Analisis

## 1. Hasil Praktikum

* Percobaan percabangan menunjukkan perubahan kecepatan LED berdasarkan kondisi tertentu.
* Percobaan perulangan menunjukkan pola LED berjalan secara berurutan dan bolak-balik.

---

## 2. Pengaruh Perulangan terhadap Program Arduino

Perulangan seperti `for` dan `while` memungkinkan eksekusi kode secara berulang tanpa harus menulis kode yang sama berkali-kali. Hal ini membuat program lebih efisien dan mudah dikembangkan, terutama untuk pola seperti LED running.

---

## 3. Cara Kerja Percabangan (if-else)

Percabangan digunakan untuk mengambil keputusan berdasarkan kondisi:

* Jika kondisi benar, maka blok `if` dijalankan.
* Jika kondisi salah, maka blok `else` dijalankan.

Dalam konteks LED, percabangan digunakan untuk menentukan kapan LED berubah kecepatan atau berhenti.

---

## 4. Kombinasi Perulangan dan Percabangan

Perulangan digunakan untuk menjalankan program secara terus-menerus, sedangkan percabangan digunakan untuk menentukan kondisi tertentu dalam setiap siklus. Kombinasi keduanya memungkinkan sistem Arduino merespons perubahan kondisi secara dinamis, misalnya berdasarkan nilai sensor atau waktu.

---

# Kesimpulan

Percabangan dan perulangan merupakan struktur dasar dalam pemrograman Arduino. Keduanya digunakan untuk mengontrol alur program dan perilaku perangkat keras sehingga sistem dapat bekerja secara otomatis dan terstruktur.
