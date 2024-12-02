#include <iostream>
#include <vector>

using namespace std;

// Инкапсуляция: Все данные устройства скрыты в приватных полях классов, и доступ к ним можно получить только через публичные методы.
class PeripheralDevice {
public:
    virtual void printInfo() const = 0;  // Виртуальная функция вывода информации
    virtual string getName() const = 0;  // Функция для получения названия устройства
    virtual ~PeripheralDevice() = default;
};

// Наследование Классы `Headphones`, `Microphone`, `Keyboard` наследуют абстрактный класс `PeripheralDevice`.
// Они обязаны реализовать методы `printInfo` и `getName` для вывода информации об устройстве.
class Headphones : public PeripheralDevice {
private:
    string model;
    string brand;
    double price;
    string constructionType;
    string mountingMethod;

public:
    // Инкапсуляция Данные скрыты в закрытых полях класса
    Headphones(const string& model, const string& brand, double price,
               const string& constructionType, const string& mountingMethod)
        : model(model), brand(brand), price(price),
          constructionType(constructionType), mountingMethod(mountingMethod) {}

    void printInfo() const override {
        cout << "Наушники: " << brand << " " << model << "\n"
             << "Цена: " << price << " руб.\n"
             << "Тип конструкции: " << constructionType << "\n"
             << "Метод крепления: " << mountingMethod << "\n\n";
    }

    string getName() const override {
        return "Наушники: " + brand + " " + model;
    }
};

class Microphone : public PeripheralDevice {
private:
    string model;
    string brand;
    double price;
    string frequencyRange;
    string sensitivity;

public:
    Microphone(const string& model, const string& brand, double price,
               const string& frequencyRange, const string& sensitivity)
        : model(model), brand(brand), price(price),
          frequencyRange(frequencyRange), sensitivity(sensitivity) {}

    void printInfo() const override {
        cout << "Микрофон: " << brand << " " << model << "\n"
             << "Цена: " << price << " руб.\n"
             << "Частотный диапазон: " << frequencyRange << "\n"
             << "Чувствительность: " << sensitivity << "\n\n";
    }

    string getName() const override {
        return "Микрофон: " + brand + " " + model;
    }
};

class Keyboard : public PeripheralDevice {
private:
    string model;
    string brand;
    double price;
    string switchType;
    string interfaceType;

public:
    Keyboard(const string& model, const string& brand, double price,
             const string& switchType, const string& interfaceType)
        : model(model), brand(brand), price(price),
          switchType(switchType), interfaceType(interfaceType) {}

    void printInfo() const override {
        cout << "Клавиатура: " << brand << " " << model << "\n"
             << "Цена: " << price << " руб.\n"
             << "Тип выключателя: " << switchType << "\n"
             << "Интерфейс: " << interfaceType << "\n\n";
    }

    string getName() const override {
        return "Клавиатура: " + brand + " " + model;
    }
};

// Абстрактная фабрика Класс для создания объектов разных типов устройств.
class DeviceFactory {
public:
    virtual PeripheralDevice* createDevice() const = 0; // Поменяли на обычный указатель
    virtual ~DeviceFactory() = default;
};

// Фабрики для создания устройств (наушников, микрофонов, клавиатур)
class HeadphonesFactory : public DeviceFactory {
private:
    string model;
    string brand;
    double price;
    string constructionType;
    string mountingMethod;

public:
    HeadphonesFactory(const string& model, const string& brand, double price,
                      const string& constructionType, const string& mountingMethod)
        : model(model), brand(brand), price(price),
          constructionType(constructionType), mountingMethod(mountingMethod) {}

    PeripheralDevice* createDevice() const override {
        return new Headphones(model, brand, price, constructionType, mountingMethod);
    }
};

class MicrophoneFactory : public DeviceFactory {
private:
    string model;
    string brand;
    double price;
    string frequencyRange;
    string sensitivity;

public:
    MicrophoneFactory(const string& model, const string& brand, double price,
                      const string& frequencyRange, const string& sensitivity)
        : model(model), brand(brand), price(price),
          frequencyRange(frequencyRange), sensitivity(sensitivity) {}

    PeripheralDevice* createDevice() const override {
        return new Microphone(model, brand, price, frequencyRange, sensitivity);
    }
};

class KeyboardFactory : public DeviceFactory {
private:
    string model;
    string brand;
    double price;
    string switchType;
    string interfaceType;

public:
    KeyboardFactory(const string& model, const string& brand, double price,
                    const string& switchType, const string& interfaceType)
        : model(model), brand(brand), price(price),
          switchType(switchType), interfaceType(interfaceType) {}

    PeripheralDevice* createDevice() const override {
        return new Keyboard(model, brand, price, switchType, interfaceType);
    }
};

// Менеджер устройств Класс `DeviceManager` управляет коллекцией устройств и инкапсулирует логику добавления и отображения устройств.
class DeviceManager {
private:
    vector<PeripheralDevice*> devices;  // Теперь используем указатели

public:
    ~DeviceManager() {
        // Освобождаем память, выделенную для всех устройств
        for (auto device : devices) {
            delete device;
        }
    }

    void addDevice(PeripheralDevice* device) {
        devices.push_back(device);
    }

    void showDevices() const {
        cout << "Список устройств:\n";
        for (size_t i = 0; i < devices.size(); ++i) {
            cout << i + 1 << ". " << devices[i]->getName() << "\n";
        }
    }

    void showDeviceInfo(int index) const {
        if (index >= 0 && index < devices.size()) {
            devices[index]->printInfo();
        } else {
            cout << "Устройство не найдено.\n";
        }
    }
};

int main() {
    setlocale(LC_ALL, "Russian");
    DeviceManager manager;

    // Создаем устройства через фабрики
    HeadphonesFactory headphonesFactory("HD202", "Sennheiser", 5000.0, "Обычные", "Оголовье");
    MicrophoneFactory microphoneFactory("AT2020", "Audio-Technica", 8000.0, "20Hz - 20kHz", "34 мВ/Па");
    KeyboardFactory keyboardFactory("K95", "Corsair", 15000.0, "Механические", "USB");

    // Добавляем устройства в менеджер
    manager.addDevice(headphonesFactory.createDevice());
    manager.addDevice(microphoneFactory.createDevice());
    manager.addDevice(keyboardFactory.createDevice());

    // Полиморфизм Мы используем полиморфизм для вызова метода `printInfo` через базовый указатель на `PeripheralDevice`.
    manager.showDevices();

    // Запрашиваем у пользователя, какое устройство он хочет просмотреть
    int choice;
    cout << "Введите номер устройства для вывода информации (0 - для выхода): ";
    cin >> choice;

    if (choice == 0) {
        cout << "Выход из программы.\n";
    } else {
        manager.showDeviceInfo(choice - 1);  // Индексация с 0
    }

    return 0;
}
