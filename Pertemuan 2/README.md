# Praktikum Sistem Mikrokontroler - Modul 2
## Pemrograman GPIO
Apriyudha  |  H1H024010  |  Shift A
---

# **2.5.4 Pertanyaan Praktikum**

### **1. Gambarkan rangkaian schematic yang digunakan pada percobaan!**

Rangkaian menggunakan **7-Segment Common Anode** yang dihubungkan ke Arduino Uno.

* Pin segment (a–g, dp) → Arduino pin: 7, 6, 5, 11, 10, 8, 9, 4
* Common Anode → VCC (5V)
* Setiap segment diberi resistor (220Ω – 330Ω)

---

### **2. Apa yang terjadi jika nilai num lebih dari 15?**

Akan terjadi **error tampilan** karena array `digitPattern` hanya memiliki indeks dari 0–15. Jika lebih dari 15, maka program mengakses data di luar array (out of bounds).

---

### **3. Apakah program ini menggunakan common cathode atau common anode? Jelaskan alasanya!**

Program menggunakan **Common Anode**, karena:

* Logika output dibalik menggunakan `!digitPattern[num][i]`
* Pada Common Anode, LED menyala saat diberi logika **LOW**

---

### **4. Modifikasi program agar tampilan berjalan dari F ke 0 dan berikan penjelasan disetiap baris kode nya dalam bentuk README.md!**

```cpp
#include <Arduino.h>

// Pin segment
const int segmentPins[8] = {7, 6, 5, 11, 10, 8, 9, 4};

// Pola digit
byte digitPattern[16][8] = {
  {1,1,1,1,1,1,0,0},{0,1,1,0,0,0,0,0},{1,1,0,1,1,0,1,0},{1,1,1,1,0,0,1,0},
  {0,1,1,0,0,1,1,0},{1,0,1,1,0,1,1,0},{1,0,1,1,1,1,1,0},{1,1,1,0,0,0,0,0},
  {1,1,1,1,1,1,1,0},{1,1,1,1,0,1,1,0},{1,1,1,0,1,1,1,0},{0,0,1,1,1,1,1,0},
  {1,0,0,1,1,1,0,0},{0,1,1,1,1,0,1,0},{1,0,0,1,1,1,1,0},{1,0,0,0,1,1,1,0}
};

// Fungsi tampil digit
void displayDigit(int num){
  for(int i=0;i<8;i++){
    digitalWrite(segmentPins[i], !digitPattern[num][i]); // logika dibalik (CA)
  }
}

void setup(){
  for(int i=0;i<8;i++){
    pinMode(segmentPins[i], OUTPUT); // set pin sebagai output
  }
}

void loop(){
  for(int i=15;i>=0;i--){ // hitung mundur dari F ke 0
    displayDigit(i); // tampilkan digit
    delay(1000); // delay 1 detik
  }
}
```

---

# **2.6.4 Pertanyaan Praktikum**

### **1. Gambarkan rangkaian schematic yang digunakan pada percobaan!**

* 7-Segment sama seperti percobaan 1
* Push button:

  * Satu kaki ke pin 2 Arduino
  * Satu kaki ke GND
  * Menggunakan **INPUT_PULLUP** (tanpa resistor eksternal)

---

### **2. Mengapa pada push button digunakan mode INPUT_PULLUP pada Arduino Uno? Apa keuntungannya dibandingkan rangkaian biasa?**

Karena:

* Tidak perlu resistor tambahan (internal pull-up sudah tersedia)
* Input lebih stabil (tidak floating)
* Rangkaian lebih sederhana

---

### **3. Jika salah satu LED segmen tidak menyala, apa saja kemungkinan penyebabnya dari sisi hardware maupun software?**

**Hardware:**

* LED segment rusak
* Kabel tidak terhubung
* Resistor rusak
* Salah wiring

**Software:**

* Kesalahan pada array `digitPattern`
* Pin tidak sesuai mapping
* PinMode belum diset OUTPUT

---

### **4. Modifikasi rangkaian dan program dengan dua push button yang berfungsi sebagai penambahan (increment) dan pengurangan (decrement) pada sistem counter dan berikan penjelasan disetiap baris kode nya dalam bentuk README.md!**

```cpp
#include <Arduino.h>

// Pin segment
const int segmentPins[8] = {7,6,5,11,10,8,9,4};

// Tombol
const int btnUp = 2;
const int btnDown = 3;

// Counter
int counter = 0;

// State tombol
bool lastUp = HIGH;
bool lastDown = HIGH;

// Pola digit
byte digitPattern[16][8] = {
  {1,1,1,1,1,1,0,0},{0,1,1,0,0,0,0,0},{1,1,0,1,1,0,1,0},{1,1,1,1,0,0,1,0},
  {0,1,1,0,0,1,1,0},{1,0,1,1,0,1,1,0},{1,0,1,1,1,1,1,0},{1,1,1,0,0,0,0,0},
  {1,1,1,1,1,1,1,0},{1,1,1,1,0,1,1,0},{1,1,1,0,1,1,1,0},{0,0,1,1,1,1,1,0},
  {1,0,0,1,1,1,0,0},{0,1,1,1,1,0,1,0},{1,0,0,1,1,1,1,0},{1,0,0,0,1,1,1,0}
};

// Fungsi tampil digit
void displayDigit(int num){
  for(int i=0;i<8;i++){
    digitalWrite(segmentPins[i], !digitPattern[num][i]);
  }
}

void setup(){
  for(int i=0;i<8;i++){
    pinMode(segmentPins[i], OUTPUT); // set pin segment
  }

  pinMode(btnUp, INPUT_PULLUP);   // tombol naik
  pinMode(btnDown, INPUT_PULLUP); // tombol turun

  displayDigit(counter); // tampil awal
}

void loop(){
  bool upState = digitalRead(btnUp);
  bool downState = digitalRead(btnDown);

  // tombol naik
  if(lastUp == HIGH && upState == LOW){
    counter++;
    if(counter > 15) counter = 0;
    displayDigit(counter);
    delay(200);
  }

  // tombol turun
  if(lastDown == HIGH && downState == LOW){
    counter--;
    if(counter < 0) counter = 15;
    displayDigit(counter);
    delay(200);
  }

  lastUp = upState;
  lastDown = downState;
}
```

---

# **2.7 Pertanyaan Praktikum**

### **1. Uraikan hasil tugas pada praktikum yang telah dilakukan pada setiap percobaan!**

* Percobaan 1: Seven segment berhasil menampilkan angka 0–F secara otomatis
* Percobaan 2: Counter berhasil dikontrol menggunakan push button

---

### **2. Bagaimana prinsip kerja dari Seven Segment Display dalam menampilkan angka dan karakter?**

Seven segment bekerja dengan menyalakan kombinasi LED (a–g) untuk membentuk angka/karakter tertentu sesuai pola yang ditentukan.

---

### **3. Jelaskan bagaimana sistem counter bekerja pada program tersebut!**

Counter bekerja dengan:

* Mendeteksi perubahan tombol (HIGH → LOW)
* Menambah atau mengurangi nilai variabel `counter`
* Menampilkan nilai tersebut ke seven segment menggunakan fungsi `displayDigit()`

---
Praktikum Sistem Mikrokobtroler - Modul 2
