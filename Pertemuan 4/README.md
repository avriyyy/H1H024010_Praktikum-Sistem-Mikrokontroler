# Praktikum Sistem Mikrokontroler - Modul 4
## ADC dan PWM
Apriyudha  |  H1H024010  |  Shift A
---

## Percobaan 1: Analog to Digital Converter (ADC)

### Pertanyaan 1
Apa fungsi perintah analogRead() pada rangkaian praktikum ini?

**Jawaban:**
Fungsi `analogRead()` digunakan untuk membaca nilai tegangan analog dari pin input analog (A0-A5 pada Arduino Uno). Fungsi ini mengubah tegangan input analog (rentang 0V hingga 5V) menjadi nilai digital diskrit dengan resolusi 10-bit, yang menghasilkan rentang angka antara 0 hingga 1023.

### Pertanyaan 2
Mengapa diperlukan fungsi map() dalam program tersebut?

**Jawaban:**
Fungsi `map()` diperlukan karena adanya perbedaan rentang (skala) antara input nilai ADC dan output yang dibutuhkan. Nilai ADC hasil pembacaan potensiometer memiliki rentang 0 hingga 1023, sedangkan motor servo umumnya dikendalikan dengan parameter sudut dalam rentang 0 hingga 180. Fungsi `map()` melakukan pemetaan linear sehingga nilai input dari potensiometer dapat dikonversi secara proporsional ke rentang sudut servo.

### Pertanyaan 3
Modifikasi program berikut agar servo hanya bergerak dalam rentang 30° hingga 150°, meskipun potensiometer tetap memiliki rentang ADC 0–1023. Jelaskan program pada file README.md.

**Jawaban:**
Berikut adalah modifikasi kode pada bagian pemetaan nilai:

```cpp
#include <Servo.h>

Servo myservo;
int potPin = A0;
int val;

void setup() {
  myservo.attach(9);
}

void loop() {
  val = analogRead(potPin);
  // Mengubah rentang output dari 0-180 menjadi 30-150
  val = map(val, 0, 1023, 30, 150); 
  myservo.write(val);
  delay(15);
}
```

**Penjelasan Program:**
Program di atas membaca nilai analog dari potensiometer melalui pin A0. Nilai mentah (0-1023) kemudian diproses menggunakan fungsi `map(val, 0, 1023, 30, 150)`. Hal ini membatasi nilai variabel `val` agar tidak pernah kurang dari 30 dan tidak pernah lebih dari 150. Hasil pemetaan tersebut dikirim ke motor servo melalui perintah `myservo.write()`, sehingga pergerakan fisik servo terbatas pada rentang 30° hingga 150°.

---

## Percobaan 2: Pulse Width Modulation (PWM)

### Pertanyaan 1
Jelaskan mengapa LED dapat diatur kecerahannya menggunakan fungsi analogWrite()!

**Jawaban:**
LED dapat diatur kecerahannya melalui `analogWrite()` karena fungsi tersebut menerapkan teknik Pulse Width Modulation (PWM). PWM memanipulasi rata-rata tegangan yang diterima LED dengan cara menghidupkan dan mematikan arus dengan frekuensi yang sangat cepat (siklus kerja/duty cycle). Karena frekuensi yang sangat tinggi, mata manusia tidak melihat kedipan, melainkan persepsi perubahan intensitas cahaya berdasarkan lamanya durasi kondisi "ON" dibandingkan "OFF".

### Pertanyaan 2
Apa hubungan antara nilai ADC (0–1023) dan nilai PWM (0–255)?

**Jawaban:**
Hubungan keduanya terletak pada resolusi bit yang digunakan. ADC pada Arduino Uno memiliki resolusi 10-bit ($2^{10} = 1024$), sedangkan PWM memiliki resolusi 8-bit ($2^8 = 256$). Oleh karena itu, perbandingannya adalah 4:1. Untuk mengonversi nilai ADC menjadi nilai PWM secara langsung, nilai ADC harus dibagi dengan 4 atau menggunakan fungsi `map(nilai, 0, 1023, 0, 255)`.

### Pertanyaan 3
Modifikasilah program berikut agar LED hanya menyala pada rentang kecerahan sedang, yaitu hanya ketika nilai PWM berada pada rentang 50 sampai 200. Jelaskan program pada file README.md.

**Jawaban:**
Berikut adalah modifikasi kodenya:

```cpp
int ledPin = 9;
int potPin = A0;
int val;

void setup() {
  pinMode(ledPin, OUTPUT);
}

void loop() {
  val = analogRead(potPin);
  int pwmVal = map(val, 0, 1023, 0, 255);
  
  // Logika pembatasan menyala hanya pada rentang 50-200
  if (pwmVal >= 50 && pwmVal <= 200) {
    analogWrite(ledPin, pwmVal);
  } else {
    analogWrite(ledPin, 0);
  }
}
```

**Penjelasan Program:**
Program membaca input analog dan mengonversinya ke skala PWM (0-255). Terdapat struktur kendali `if` yang memeriksa apakah nilai `pwmVal` berada di dalam rentang 50 hingga 200. Jika benar, LED akan menyala sesuai nilai intensitas tersebut. Jika nilai berada di bawah 50 atau di atas 200, perintah `analogWrite(ledPin, 0)` akan dijalankan sehingga LED mati.

---

## Modul 4: Integrasi ADC dan PWM

### Pertanyaan 1
Bagaimana proses konversi sinyal analog menjadi digital pada Arduino? Jelaskan!

**Jawaban:**
Proses konversi dilakukan oleh komponen bernama Successive Approximation Register (SAR) ADC. Tahapannya meliputi:
1. **Sampling:** Menangkap nilai tegangan analog pada satu waktu tertentu.
2. **Quantization:** Membagi rentang tegangan referensi (misal 5V) ke dalam tingkat-tingkat diskrit (1024 tingkatan untuk 10-bit).
3. **Encoding:** Menetapkan angka biner/digital yang paling mendekati nilai tegangan hasil sampling tersebut.

### Pertanyaan 2
Faktor apa saja yang dapat mempengaruhi keakuratan pembacaan ADC?

**Jawaban:**
Beberapa faktor utama meliputi:
* **Tegangan Referensi (VREF):** Jika tegangan sumber tidak stabil, hasil konversi akan berfluktuasi.
* **Noise/Gangguan Listrik:** Interferensi elektromagnetik pada jalur kabel input.
* **Impedansi Sumber:** Sumber sinyal dengan impedansi terlalu tinggi dapat memperlambat pengisian kapasitor internal ADC.
* **Kualitas Koneksi:** Kontak fisik pada breadboard atau kabel jumper yang longgar.

### Pertanyaan 3
Apa kendala yang mungkin terjadi saat mengintegrasikan ADC dan PWM dalam satu sistem?

**Jawaban:**
Kendala yang sering muncul adalah adanya *noise* elektrikal yang dihasilkan oleh beban PWM (seperti motor atau LED daya tinggi) yang masuk ke jalur analog ADC. Hal ini dapat menyebabkan pembacaan ADC menjadi tidak stabil atau "melompat-lompat". Selain itu, keterbatasan kecepatan pemrosesan (latency) dalam loop program dapat menyebabkan keterlambatan respon sistem antara perubahan input analog terhadap perubahan output PWM.
---
Praktikum Sistem Mikrokobtroler - Modul 4