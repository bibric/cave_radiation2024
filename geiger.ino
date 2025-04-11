#include <SPI.h>
#include <SD.h>

const int geigerPin = 2; // Пин, к которому подключен счётчик Гейгера
const int chipSelect = 5; // Пин для CS SD карты
volatile int pulseCount = 0; // Переменная для хранения количества импульсов
unsigned long startTime; // Время начала измерения

void setup() {
  pinMode(geigerPin, INPUT); // Устанавливаем пин как вход
  attachInterrupt(digitalPinToInterrupt(geigerPin), countPulse, RISING); // Настраиваем прерывание на пине
  Serial.begin(9600); // Запускаем последовательный порт для вывода результатов

  // Инициализация SD карты
  Serial.println("Инициализация SD карты...");
  if (!SD.begin(chipSelect)) {
    Serial.println("Ошибка инициализации SD карты!");
    return;
  }
  Serial.println("SD карта инициализирована.");
  // Считывание файла и вывод его содержимого в последовательный порт
    Serial.println("Чтение данных из файла...");
    File dataFile1 = SD.open("/kanji/number.txt"); // Открываем файл для чтения
    if (dataFile1) {
      while (dataFile1.available()) {
        Serial.write(dataFile1.read()); // Выводим данные в последовательный порт
      }
      dataFile1.close(); // Закрываем файл
      Serial.println("Чтение данных завершено.");
    } else {
      Serial.println("Ошибка открытия файла для чтения.");
    }

  startTime = millis(); // Запоминаем время начала измерения
}

void loop() {
  unsigned long currentTime = millis(); // Текущее время
  if (currentTime - startTime >= 300000) { // Если прошло 5 минут (300000 миллисекунд)
    String dataString = String(currentTime/60000) + "m " + String(pulseCount); // Формируем строку с количеством импульсов
    //Serial.println(dataString);
    //Serial.println("Попытка открыть файл для записи...");
    digitalWrite(LED_BUILTIN, HIGH);  // turn the LED on (HIGH is the voltage level) 
    File dataFile = SD.open("data3.txt", FILE_WRITE); // Открываем файл для записи
    if (dataFile) {
      //Serial.println("Файл успешно открыт. Запись данных...");
      dataFile.println(dataString); // Записываем данные в файл
      dataFile.close(); // Закрываем файл
      digitalWrite(LED_BUILTIN, LOW);
      //Serial.println("Данные записаны на SD карту.");
    } else {
      Serial.println("Ошибка открытия файла для записи.");
      digitalWrite(LED_BUILTIN, LOW);
      delay(1000);
      digitalWrite(LED_BUILTIN, HIGH);
      delay(1000);
      digitalWrite(LED_BUILTIN, LOW);
      delay(1000);
      digitalWrite(LED_BUILTIN, HIGH);
      delay(1000);
      digitalWrite(LED_BUILTIN, LOW);
      delay(1000);
      digitalWrite(LED_BUILTIN, HIGH);
      delay(1000);
      digitalWrite(LED_BUILTIN, LOW);
      delay(1000);
      digitalWrite(LED_BUILTIN, HIGH);
      delay(1000);
      digitalWrite(LED_BUILTIN, LOW);
    }
    pulseCount = 0; // Сбрасываем счётчик импульсов
    startTime = currentTime; // Обновляем время начала измерения
  }
}

void countPulse() {
  pulseCount++; // Увеличиваем счётчик импульсов
}
