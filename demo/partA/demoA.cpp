#include <bits/stdc++.h>
using namespace std;

class Car {
private:
    string licensePlate;
    string owner;
    string brand;
    float parkingHours;
    float fee;

public:
    Car() : parkingHours(0), fee(0) {}
    Car(string lp, string o, string b, float h)
        : licensePlate(lp), owner(o), brand(b), parkingHours(h) {
        fee = calculateFee();
    }

    float calculateFee() const { return parkingHours * 5.0f; }

    void input() {
        cout << "Nhap bien so xe: ";
        cin >> licensePlate;
        cin.ignore();
        cout << "Nhap ten chu xe: ";
        getline(cin, owner);
        cout << "Nhap hang xe: ";
        getline(cin, brand);

        while (true) {
            cout << "Nhap so gio gui xe: ";
            if (cin >> parkingHours && parkingHours >= 0) break;
            cout << "Nhap sai! Vui long nhap lai.\n";
            cin.clear();
            cin.ignore(1000, '\n');
        }
        fee = calculateFee();
    }

    void display() const {
        cout << left << setw(12) << licensePlate
             << setw(20) << owner
             << setw(15) << brand
             << setw(10) << parkingHours
             << setw(10) << fee << endl;
    }

    string getLicensePlate() const { return licensePlate; }
    string getOwner() const { return owner; }
    string getBrand() const { return brand; }
    float getHours() const { return parkingHours; }
    float getFee() const { return fee; }

    void setOwner(const string &o) { owner = o; }
    void setBrand(const string &b) { brand = b; }
    void setHours(float h) { parkingHours = h; fee = calculateFee(); }

    friend ostream &operator<<(ostream &out, const Car &c) {
        out << c.licensePlate << '\n'
            << c.owner << '\n'
            << c.brand << '\n'
            << c.parkingHours << '\n';
        return out;
    }

    friend istream &operator>>(istream &in, Car &c) {
        getline(in, c.licensePlate);
        if (c.licensePlate.empty()) return in; // tránh lỗi khi EOF
        getline(in, c.owner);
        getline(in, c.brand);
        in >> c.parkingHours;
        in.ignore();
        c.fee = c.calculateFee();
        return in;
    }
};

class ParkingLot {
private:
    list<Car> cars;
    string dataFile;

public:
    ParkingLot(string filename = "cars_dataIn.txt") : dataFile(filename) {
        loadFromFile();
    }
    ~ParkingLot() { saveToFile(); }

    void loadFromFile() {
        ifstream file(dataFile);
        if (!file.is_open()) return;
        cars.clear();
        while (true) {
            Car c;
            file >> c;
            if (file.fail() || c.getLicensePlate().empty()) break;
            cars.push_back(c);
        }
        file.close();
    }

    void saveToFile() {
        ofstream file(dataFile);
        for (auto &c : cars)
            file << c;
        file.close();
    }

    bool exists(const string &lp) const {
        for (auto &c : cars)
            if (c.getLicensePlate() == lp)
                return true;
        return false;
    }

    void displayHeader() const {
        cout << left << setw(12) << "Bien so"
             << setw(20) << "Chu xe"
             << setw(15) << "Hang"
             << setw(10) << "Gio"
             << setw(10) << "Phi" << endl;
        cout << string(67, '-') << endl;
    }

    void displayAll() const {
        if (cars.empty()) {
            cout << "Khong co xe nao trong bai.\n";
            return;
        }
        displayHeader();
        for (auto &c : cars)
            c.display();
    }

    void addCar() {
        Car c;
        c.input();
        if (exists(c.getLicensePlate())) {
            cout << "Xe nay da ton tai.\n";
            return;
        }
        cars.push_back(c);
        cout << "Them xe thanh cong.\n";
    }

    void removeCar() {
        string lp;
        cout << "Nhap bien so can xoa: ";
        cin >> lp;
        for (auto it = cars.begin(); it != cars.end(); ++it) {
            if (it->getLicensePlate() == lp) {
                cars.erase(it);
                cout << "Da xoa xe.\n";
                return;
            }
        }
        cout << "Khong tim thay xe.\n";
    }

    void updateCar() {
        string lp;
        cout << "Nhap bien so xe can cap nhat: ";
        cin >> lp;
        for (auto &c : cars) {
            if (c.getLicensePlate() == lp) {
                string newOwner, newBrand;
                float newHours;
                cin.ignore();
                cout << "Chu xe moi: ";
                getline(cin, newOwner);
                cout << "Hang xe moi: ";
                getline(cin, newBrand);
                while (true) {
                    cout << "So gio moi: ";
                    if (cin >> newHours && newHours >= 0) break;
                    cout << "Nhap sai!\n";
                    cin.clear();
                    cin.ignore(1000, '\n');
                }
                c.setOwner(newOwner);
                c.setBrand(newBrand);
                c.setHours(newHours);
                cout << "Cap nhat thanh cong.\n";
                return;
            }
        }
        cout << "Khong tim thay xe.\n";
    }

    void findByPlate() const {
        string lp;
        cout << "Nhap bien so can tim: ";
        cin >> lp;
        for (auto &c : cars)
            if (c.getLicensePlate() == lp) {
                displayHeader();
                c.display();
                return;
            }
        cout << "Khong tim thay.\n";
    }

    void findByBrand() const {
        string br;
        cout << "Nhap hang xe can tim: ";
        cin.ignore();
        getline(cin, br);
        bool found = false;
        displayHeader();
        for (auto &c : cars)
            if (c.getBrand() == br) {
                c.display();
                found = true;
            }
        if (!found)
            cout << "Khong co xe thuoc hang nay.\n";
    }

    void sortByHours(bool ascending) {
        cars.sort([ascending](const Car &a, const Car &b) {
            return ascending ? a.getHours() < b.getHours()
                             : a.getHours() > b.getHours();
        });
        cout << "Da sap xep theo gio gui (" << (ascending ? "tang" : "giam") << ").\n";
    }

    void findLongest() const {
        if (cars.empty()) {
            cout << "Khong co xe trong bai.\n";
            return;
        }
        auto it = max_element(cars.begin(), cars.end(),
                              [](const Car &a, const Car &b) {
                                  return a.getHours() < b.getHours();
                              });
        cout << "Xe gui lau nhat:\n";
        displayHeader();
        it->display();
    }

    void countCars() const {
        cout << "So xe hien co: " << cars.size() << endl;
    }

    void totalFee() const {
        float sum = 0;
        for (auto &c : cars) sum += c.getFee();
        cout << "Tong tien phi: " << sum << " nghin dong.\n";
    }
};

class App {
private:
    ParkingLot lot;

public:
    void menu() {
        cout << "\n===== QUAN LY BAI DO XE =====\n";
        cout << "1. Hien thi danh sach\n";
        cout << "2. Them xe moi\n";
        cout << "3. Xoa xe\n";
        cout << "4. Cap nhat xe\n";
        cout << "5. Tim theo bien so\n";
        cout << "6. Tim theo hang\n";
        cout << "7. Sap xep theo gio gui\n";
        cout << "8. Xe gui lau nhat\n";
        cout << "9. Dem so xe\n";
        cout << "10. Tong phi gui\n";
        cout << "0. Thoat\n";
        cout << "=============================\n";
        cout << "Nhap lua chon: ";
    }

    void run() {
        int choice;
        do {
            menu();
            while (!(cin >> choice)) {
                cout << "Nhap sai! Vui long nhap lai: ";
                cin.clear();
                cin.ignore(1000, '\n');
            }

            switch (choice) {
                case 1: lot.displayAll(); break;
                case 2: lot.addCar(); break;
                case 3: lot.removeCar(); break;
                case 4: lot.updateCar(); break;
                case 5: lot.findByPlate(); break;
                case 6: lot.findByBrand(); break;
                case 7: {
                    int opt;
                    cout << "1. Tang dan\n2. Giam dan\n=> ";
                    cin >> opt;
                    lot.sortByHours(opt == 1);
                    lot.displayAll();
                    break;
                }
                case 8: lot.findLongest(); break;
                case 9: lot.countCars(); break;
                case 10: lot.totalFee(); break;
                case 0: cout << "Thoat chuong trinh va luu du lieu.\n"; break;
                default: cout << "Lua chon khong hop le.\n";
            }
        } while (choice != 0);
    }
};

int main() {
    App app;
    app.run();
    return 0;
}
