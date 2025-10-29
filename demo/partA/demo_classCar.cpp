#include<bits/stdc++.h>
using namespace std;

class Car{
    private:
        string license_plate, owner, brand;
        float hours;
        float fee;
    
    public:
        Car(){
            hours = 0;
            fee = 0;
        }

        Car(string lp, string o, string b, float h){
            license_plate = lp;
            owner =  o;
            brand = b;
            hours = h;
            fee = calFee();
        }

        float calFee(){
            return hours * 3500.0f;
        }
        
        void input(){
            cout << "Nhập biển số xe: "; cin >> license_plate; cin.ignore();
            cout << "Nhập tên chủ xe: "; getline(cin, owner);
            cout << "Nhập hãng xe: "; getline(cin, brand);
            cout << "Nhập số giờ gửi xe: "; cin >> hours;
            while(hours <= 0){
                cout << "Số giờ gửi không hợp lệ! Vui lòng nhập lại: ";
                cin >> hours;
            }
            fee = calFee();
        }

        void display(){
            cout << left << setw(12) << license_plate << setw(30) << owner << setw(25) << brand << setw(10) << hours << setw(10) << fee << endl;
        }

        string getLicense_Plate(){
            return license_plate;
        }
        string getOwner(){
            return owner;
        }
        string getBrand(){
            return brand;
        }
        float getHours(){
            return hours;
        }
        float getFee(){
            return fee;
        }

        friend istream &operator>>(istream &in, Car &c){
            getline(in, c.license_plate);
            getline(in, c.owner);
            getline(in, c.brand);
            in >> c.hours;
            in.ignore();
            c.fee = c.calFee();
            return in;
        }

        friend ostream &operator<<(ostream &out, const Car &c){
            out << c.license_plate << "\n" << c.owner << "\n"
                << c.brand << "\n" << c.hours << "\n" << c.fee << "\n";
            return out;
        }

        void readFile(list<Car> &carList, const string &filename){
            ifstream fin(filename);
            if(!fin){
                cout << "Không tìm thấy file cars_dataIn.txt!\n";
                return;
            }
            while(true){
                Car c;
                fin >> c;
                if (fin.eof() || c.getLicense_Plate().empty()) break;
                carList.push_back(c);
            }
            fin.close();
        }

        void writeFile(list<Car> &carList, const string &filename){
            ofstream fout(filename);
            if(!fout){
                cout << "Không tìm thấy file cars_dataOut.txt!\n";
                return;
            }
            for(auto &c : carList) fout << c;
            fout.close();
        }

        void displayAll(list<Car> &carList){
            if(carList.empty()){
                cout << "Danh sách trống!\n";
            }
            else{
                cout << left << setw(12) << "Bien so"
                     << setw(30) << "Chu xe"
                     << setw(25) << "Hang"
                     << setw(10) << "Gio"
                     << setw(10) << "Phi" << endl;
                cout << string(85, '-') << endl;
                for(auto &c : carList){
                    c.display();
                }
            }
        }
};

int main() {
    list<Car> carList;
    Car temp; // Dùng để gọi các hàm

    // Đọc dữ liệu từ file
    temp.readFile(carList, "cars_dataIn.txt");

    // Hiển thị danh sách xe đã đọc
    cout << "\nDanh sách xe hiện có trong file:\n";
    temp.displayAll(carList);

    // Thêm xe mới từ bàn phím
    char choice;
    do {
        Car newCar;
        cout << "\nNhập thông tin xe mới:\n";
        newCar.input();
        carList.push_back(newCar);

        cout << "Bạn có muốn thêm xe khác không? (y/n): ";
        cin >> choice;
        cin.ignore();
    } while(choice == 'y' || choice == 'Y');

    // Hiển thị lại danh sách sau khi thêm
    cout << "\nDanh sách xe sau khi thêm:\n";
    temp.displayAll(carList);

    // Ghi danh sách ra file
    temp.writeFile(carList, "cars_dataOut.txt");
    cout << "\nĐã lưu danh sách xe vào file cars_dataOut.txt\n";

    return 0;
}
