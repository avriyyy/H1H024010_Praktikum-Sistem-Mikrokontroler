# Praktikum Sistem Mikrokontroler - Modul 5

## Real-Time Operating System (RTOS)

### Apriyudha | H1H024010 | Shift A

---

# 5.5.4 Pertanyaan Praktikum Percobaan 1

## 1. Apakah ketiga task berjalan secara bersamaan atau bergantian? Jelaskan mekanismenya!

Ketiga task tidak berjalan secara benar-benar bersamaan (parallel), melainkan berjalan secara bergantian (concurrent). Mekanisme ini diatur oleh scheduler dari FreeRTOS menggunakan metode preemptive scheduling.

Setiap task mendapatkan jatah waktu eksekusi dari CPU secara cepat sehingga terlihat seperti berjalan bersamaan. Ketika sebuah task menjalankan fungsi `vTaskDelay()`, task tersebut masuk ke kondisi blocked sehingga scheduler akan memberikan CPU kepada task lain yang siap dijalankan.

Pada program ini:

- `TaskBlink1` berjalan dengan delay 200 ms
- `TaskBlink2` berjalan dengan delay 300 ms
- `TaskPrint` berjalan dengan delay 500 ms

Karena semua task memiliki prioritas yang sama, scheduler membagi waktu eksekusi secara bergantian kepada setiap task.

---

## 2. Bagaimana cara menambahkan task keempat? Jelaskan langkahnya!

Langkah-langkah menambahkan task keempat pada FreeRTOS adalah sebagai berikut:

### 1. Membuat prototype function task baru

```cpp
void TaskBaru(void *pvParameters);
```

### 2. Membuat task menggunakan `xTaskCreate()`

Tambahkan pada fungsi `setup()`:

```cpp
xTaskCreate(TaskBaru, "task4", 128, NULL, 1, NULL);
```

### 3. Membuat isi function task

```cpp
void TaskBaru(void *pvParameters) {
  while (1) {
    Serial.println("Task4");
    vTaskDelay(1000 / portTICK_PERIOD_MS);
  }
}
```

### 4. Upload program ke Arduino

Setelah task baru dibuat, compile dan upload program ke Arduino agar scheduler FreeRTOS dapat menjalankan task tersebut bersama task lainnya.

---

## 3. Modifikasilah program dengan menambah sensor (misalnya potensiometer), lalu gunakan nilainya untuk mengontrol kecepatan LED! Bagaimana hasilnya? Jelaskan program pada file README.md.

### Program Modifikasi

```cpp
unsigned long prevTask1 = 0;
unsigned long prevTask2 = 0;
unsigned long prevPrint = 0;

int led1State = LOW;
int led2State = LOW;
int counter = 0;

const int led1 = 8;
const int led2 = 7;
const int potPin = A0;

int potValue = 0;
int delayLED = 200;

void setup() {
  Serial.begin(9600);

  pinMode(led1, OUTPUT);
  pinMode(led2, OUTPUT);
  pinMode(potPin, INPUT);
}

void loop() {
  unsigned long currentMillis = millis();

  // Membaca nilai potensiometer
  potValue = analogRead(potPin);

  // Mengubah nilai 0-1023 menjadi delay 100-1000 ms
  delayLED = map(potValue, 0, 1023, 100, 1000);

  // Task LED 1
  if (currentMillis - prevTask1 >= delayLED) {
    prevTask1 = currentMillis;

    led1State = !led1State;
    digitalWrite(led1, led1State);

    Serial.print("Task1 LED 1 | Delay: ");
    Serial.println(delayLED);
  }

  // Task LED 2
  if (currentMillis - prevTask2 >= delayLED + 100) {
    prevTask2 = currentMillis;

    led2State = !led2State;
    digitalWrite(led2, led2State);

    Serial.print("Task2 LED 2 | Delay: ");
    Serial.println(delayLED + 100);
  }

  // Task print counter
  if (currentMillis - prevPrint >= 500) {
    prevPrint = currentMillis;

    counter++;
    Serial.print("Counter: ");
    Serial.print(counter);
    Serial.print(" | Potensiometer: ");
    Serial.print(potValue);
    Serial.print(" | Delay LED: ");
    Serial.println(delayLED);
  }
}
```

### Penjelasan Hasil

Pada program modifikasi ini ditambahkan sebuah potensiometer yang terhubung ke pin analog A0. Nilai analog dari potensiometer dibaca menggunakan fungsi `analogRead()` dengan rentang nilai 0–1023.

Nilai tersebut kemudian diubah menjadi delay LED menggunakan fungsi `map()` dengan rentang 100–1000 ms. Semakin besar nilai potensiometer, maka delay LED akan semakin besar sehingga kedipan LED menjadi lebih lambat. Sebaliknya, jika nilai potensiometer kecil maka LED akan berkedip lebih cepat.

LED pertama menggunakan delay sesuai hasil pembacaan potensiometer, sedangkan LED kedua memiliki delay tambahan sebesar 100 ms sehingga kedipan kedua LED terlihat berbeda.

Serial Monitor menampilkan:

- Counter
- Nilai potensiometer
- Nilai delay LED

Dengan demikian perubahan posisi potensiometer dapat mempengaruhi kecepatan kedipan LED secara realtime.

### Link Simulasi dan Rangkaian

Simulasi Wokwi:
https://wokwi.com/projects/463702165465865217

---

# 5.6.4 Pertanyaan Praktikum Percobaan 2

## 1. Apakah kedua task berjalan secara bersamaan atau bergantian? Jelaskan mekanismenya!

Kedua task berjalan secara bergantian (concurrent), bukan benar-benar bersamaan (parallel). FreeRTOS menggunakan scheduler untuk mengatur pergantian eksekusi antar task.

Task `read_data` bertugas membaca data sensor DHT22 dan mengirimkannya ke queue menggunakan `xQueueSend()`. Setelah itu task akan delay selama 2 detik menggunakan `vTaskDelay()`.

Ketika task `read_data` berada dalam kondisi blocked karena delay, scheduler akan menjalankan task `display`. Task `display` akan menerima data dari queue menggunakan `xQueueReceive()` lalu menampilkan hasilnya pada Serial Monitor.

Proses pergantian task berlangsung sangat cepat sehingga terlihat seperti berjalan bersamaan.

---

## 2. Apakah program ini berpotensi mengalami race condition? Jelaskan!

Program ini tidak mengalami race condition karena komunikasi data antar task menggunakan queue FreeRTOS.

Queue bekerja sebagai media komunikasi yang aman karena:

- Data dikirim menggunakan `xQueueSend()`
- Data diterima menggunakan `xQueueReceive()`
- Queue hanya dapat diakses satu task pada satu waktu

Dengan mekanisme tersebut, data tidak dapat diakses secara bersamaan oleh dua task sehingga integritas data tetap terjaga dan race condition dapat dihindari.

---

## 3. Modifikasilah program dengan menggunakan sensor DHT sesungguhnya sehingga informasi yang ditampilkan dinamis. Bagaimana hasilnya? Jelaskan program pada file README.md.

### Program Modifikasi

```cpp
#include <Arduino_FreeRTOS.h>
#include <queue.h>
#include "DHT.h"

#define DHTPIN 2
#define DHTTYPE DHT22

DHT dht(DHTPIN, DHTTYPE);

struct readings {
  float temp;
  float h;
};

QueueHandle_t my_queue;

void setup() {
  Serial.begin(9600);
  dht.begin();

  my_queue = xQueueCreate(1, sizeof(struct readings));

  xTaskCreate(read_data, "read sensors", 128, NULL, 1, NULL);
  xTaskCreate(display, "display", 128, NULL, 1, NULL);
}

void loop() {
}

void read_data(void *pvParameters) {
  struct readings x;

  for (;;) {
    x.h = dht.readHumidity();
    x.temp = dht.readTemperature();

    if (isnan(x.h) || isnan(x.temp)) {
      Serial.println("Gagal membaca sensor DHT!");
    } else {
      xQueueSend(my_queue, &x, portMAX_DELAY);
    }

    vTaskDelay(2000 / portTICK_PERIOD_MS);
  }
}

void display(void *pvParameters) {
  struct readings x;

  for (;;) {
    if (xQueueReceive(my_queue, &x, portMAX_DELAY) == pdPASS) {
      Serial.print("--- Data Sensor Dinamis ---");

      Serial.print("\nTemperature: ");
      Serial.print(x.temp);

      Serial.print(" C\nHumidity: ");
      Serial.print(x.h);

      Serial.println(" %");
      Serial.println("---------------------------");
    }
  }
}
```

### Penjelasan Hasil

Pada program modifikasi ini digunakan sensor DHT22 sesungguhnya untuk membaca nilai suhu dan kelembaban secara realtime.

Task `read_data` membaca data suhu dan kelembaban menggunakan library DHT, kemudian data dimasukkan ke queue menggunakan `xQueueSend()`.

Task `display` menerima data dari queue menggunakan `xQueueReceive()` lalu menampilkan data sensor pada Serial Monitor.

Hasil yang diperoleh menunjukkan bahwa:

- Nilai suhu dan kelembaban berubah secara dinamis
- Data berhasil dikirim antar task menggunakan queue
- Tidak terjadi race condition
- Komunikasi antar task berjalan dengan baik

Delay pembacaan sensor dibuat 2 detik karena DHT22 memiliki sampling rate yang lambat.

### Link Simulasi dan Rangkaian

Simulasi Wokwi:
https://wokwi.com/projects/463146960431986689

---

# 5.7 Pertanyaan Praktikum

## 1. Jelaskan perbedaan antara loop() pada Arduino biasa dengan sistem yang menggunakan RTOS!

Pada Arduino biasa, seluruh program dijalankan secara sequential di dalam fungsi `loop()`. Semua instruksi dijalankan satu per satu secara berurutan sehingga jika terdapat delay maka proses lain harus menunggu.

Sedangkan pada sistem RTOS, program dijalankan dalam bentuk task-task terpisah yang diatur oleh scheduler. Setiap task dapat berjalan secara concurrent sehingga sistem mampu menangani banyak proses sekaligus dengan lebih efisien.

---

## 2. Mengapa fungsi loop() dibiarkan kosong?

Pada sistem FreeRTOS, seluruh program dijalankan oleh task yang telah dibuat menggunakan `xTaskCreate()` dan diatur oleh scheduler FreeRTOS.

Karena seluruh proses sudah ditangani oleh task, maka fungsi `loop()` tidak lagi digunakan sehingga dibiarkan kosong.

---

## 3. Apa insight utama yang Anda pelajari dari praktikum ini?

Insight utama yang diperoleh dari praktikum ini adalah memahami bagaimana RTOS bekerja dalam mengatur multitasking pada sistem embedded menggunakan FreeRTOS.

Praktikum ini menunjukkan bahwa:

- Beberapa task dapat berjalan secara concurrent
- Scheduler mengatur pembagian waktu eksekusi task
- Queue dapat digunakan untuk komunikasi antar task secara aman
- RTOS membuat sistem embedded lebih terstruktur dan efisien dibandingkan sistem sequential biasa

Selain itu, praktikum ini juga memberikan pemahaman mengenai pentingnya sinkronisasi data untuk menghindari race condition pada sistem multitasking.

---

Praktikum Sistem Mikrokontroler - Modul 5
