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
            cout << left << setw(12) << license_plate << setw(25) << owner << setw(15) << brand << setw(10) << hours << setw(10) << fee << endl;
        }

        // Getters
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

        // Setters
        void setOwner(string &o){
            owner = o;
        }
        void setBrand(string &b){
            brand = b;
        }
        void setHours(float h){
            hours = h;
            fee = calFee();
        }

        // Operators
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
                << c.brand << "\n" << c.hours << "\n";
            return out;
        }

        bool operator<(const Car &other){
            return fee < other.fee;
        }
};

class Parking{
    private:
        list<Car> carList;
        string data;
    
    public:
        Parking(string filename = "cars_data.txt") : data(filename){
            loadFile();
        }

        ~Parking(){
            saveFileDefault();
        }
        
        void loadFile(){
            ifstream file(data);
            if(!file) return;
            while(true){
                Car c;
                file >> c;
                if(file.eof() || c.getLicense_Plate().empty()) break;
                carList.push_back(c);
            }
            file.close();
        }

        void saveFileDefault(){
            ofstream file(data);
            if(!file) return;
            for(auto &c: carList){
                file << c;
            }
            file.close();
        }

        void saveFileAnother(const string &filename){
            ofstream file(filename);
            if(!file) return;
            for(auto &c: carList){
                file << c;
            }
            file.close();
        }

        void displayAll(){
            if(carList.empty()){
                cout << "Bãi xe trống!\n";
                return;
            }
            cout << left << setw(12) << "Bien so" << setw(25) << "Chu xe" << setw(15) << "Hang" << setw(10) << "Gio" << setw(10) << "Phi" << endl;
            cout << string(75, '-') << endl;
            for(auto &c : carList){
                c.display();
            }
        }

        bool checkPlate(const string &lp){
            for(auto &c : carList){
                if(c.getLicense_Plate() == lp) return true;
            }
            return false;
        }

        void addCar(){
            Car c;
            c.input();
            while(checkPlate(c.getLicense_Plate())){
                cout << "Xe này đã tồn tại! Vui lòng nhập lại: ";
                c.input();
            }
            carList.push_back(c);
            cout << "Đã thêm thành công!\n";
        }

        void removeCar(){
            string lp;
            cout << "Nhập biển số xe cần xoá: ";
            cin >> lp;
            for(auto it = carList.begin(); it != carList.end(); ++it){
                if(it->getLicense_Plate() == lp){
                    carList.erase(it);
                    cout << "Đã xoá!\n";
                    return;
                }
            }
            cout << "Không tìm thấy xe cần xoá!\n";
        }

        void updateCar(){
            string lp;
            cout << "Nhập biển số của xe cần được cập nhật: ";
            cin >> lp;
            for(auto &c : carList){
                if(c.getLicense_Plate() == lp){
                    string newOwner, newBrand;
                    float newHours;
                    cin.ignore();
                    cout << "Nhập tên chủ xe mới: "; getline(cin, newOwner);
                    cout << "Nhập hãng xe mới: "; getline(cin, newBrand);
                    cout << "Nhập số giờ mới: "; cin >> newHours;
                    if(newHours <= 0){
                        cout << "Không hợp lệ! Vui lòng nhập lại số giờ mới: ";
                        cin >> newHours;
                    }

                    c.setOwner(newOwner);
                    c.setBrand(newBrand);
                    c.setHours(newHours);
                    cout << "Cập nhật thành công!\n";
                    return;
                }
            }
            cout << "Không tìm thấy xe cần sửa!\n";
        }

        void findPlate(){
            string lp;
            cout << "Nhập biển số xe cần tìm: ";
            cin >> lp;
            for(auto &c : carList){
                if(c.getLicense_Plate() == lp){
                    c.display();
                    return;
                }
            }
            cout << "Không tìm thấy!\n";
        }

        void findBrand(){
            string br;
            cout << "Nhập hãng xe cần tìm: "; cin.ignore();
            getline(cin, br);
            bool found = false;
            for(auto &c : carList){
                if(c.getBrand() == br){
                    c.display();
                    found = true;
                }
            }
            if(!found){

                cout << "Không có xe thuộc hãng này.\n";
            }
        }

        void sortFeeAscending(){
            if (carList.empty()) {
                cout << "Bãi xe trống!\n";
                return;
            }
            carList.sort(); // Sẽ tự động gọi operator< trong class Car
            saveFileAnother("sorted_fee.txt");
            cout << "Đã cập nhật file sorted_fee.txt!\n";

        }

        void sortHours(){
            if(carList.empty()){
                cout << "Bãi xe trống!\n";
                return;
            }
            int option;
            cout << "Sắp xếp tăng dần (1)\nSắp xếp giảm dần (2)\nChọn: ";
            cin >> option;
            if(option == 1){
                carList.sort([](Car &a, Car &b) {return a.getHours() < b.getHours();});
                saveFileAnother("sorted_hours_ascending.txt");
                cout << "Đã cập nhật file sorted_hours_ascending.txt\n";
            }
            else{
                carList.sort([](Car &a, Car &b) {return a.getHours() > b.getHours();});
                saveFileAnother("sorted_hours_descending.txt");
                cout << "Đã cập nhật file sorted_hours_descending.txt\n";
            }

        }

        void findLongest(){
            if(carList.empty()){
                cout << "Bãi xe trống!\n";
                return;
            }
            float maxHours = max_element(carList.begin(), carList.end(), [](Car &a, Car &b) {return a.getHours() < b.getHours();})->getHours();
            cout << "Xe gửi lâu nhất:\n";
            cout << left << setw(12) << "Bien so" << setw(25) << "Chu xe" << setw(15) << "Hang" << setw(10) << "Gio" << setw(10) << "Phi" << endl;
            cout << string(75, '-') << endl;
            for(auto &c : carList){
                if(c.getHours() == maxHours){
                        c.display();
                }
            }
        }

        void findShortest(){
            if(carList.empty()){
                cout << "Bãi xe trống!\n";
                return;
            }
            float minHours = min_element(carList.begin(), carList.end(), [](Car &a, Car &b) {return a.getHours() < b.getHours();})->getHours();
            cout << "Xe gửi ít thời gian nhất:\n";
            cout << left << setw(12) << "Bien so" << setw(25) << "Chu xe" << setw(15) << "Hang" << setw(10) << "Gio" << setw(10) << "Phi" << endl;
            cout << string(75, '-') << endl;
            for(auto &c : carList){
                if(c.getHours() == minHours){
                        c.display();
                }
            }
        }

        void countCars(){
            cout << "Số xe hiện có là: " << carList.size() << " chiếc!" << endl;
        }

        void totalFee(){
            bool found  = false;
            float total = 0;
            string lp;
            cout << "Nhập biển số xe cần tính phí: ";
            cin >> lp;
            for(auto &c : carList){
                if(c.getLicense_Plate() == lp){
                    total =  c.getFee();
                    found = true;
                    break;
                }
            }
            if(found){
                cout << "Tổng tiền phí là: " << total << " VNĐ.\n";
            }
            else{
                cout << "Không tìm thấy xe cần tìm!\n";
            }
        }

};

class App{
    private:
        Parking p;
    
    public:
        void menu(){
            cout << "\n===== QUẢN LÝ BÃI ĐỖ XE =====\n";
            cout << "1. Danh sách xe hiện đang trong bãi đỗ xe\n";
            cout << "2. Thêm xe vào bãi\n";
            cout << "3. Xoá xe rời bãi\n";
            cout << "4. Cập nhật thông tin xe\n";
            cout << "5. Tìm xe theo biển số\n";
            cout << "6. Tìm xe theo hãng\n";
            cout << "7. Sắp xếp theo phí gửi tăng dần\n";
            cout << "8. Sắp xếp theo giờ gửi\n";
            cout << "9. Tìm xe gửi lâu nhất\n";
            cout << "10. Tìm xe gửi ít thời gian nhất\n";
            cout << "11. Đếm số xe có trong bãi\n";
            cout << "12. Tính phí gửi theo xe\n";
            cout << "0. Thoát\n";
            cout << "==============================\n";
            cout << "Chọn: ";
        }

        void run(){
            int choice;
            do{
                menu();
                cin >> choice;
                switch(choice){
                    case 1: p.displayAll(); break;
                    case 2: p.addCar(); break;
                    case 3: p.removeCar(); break;
                    case 4: p.updateCar(); break;
                    case 5: p.findPlate(); break;
                    case 6: p.findBrand(); break;
                    case 7: p.sortFeeAscending(); break;
                    case 8: p.sortHours(); break;
                    case 9: p.findLongest(); break;
                    case 10: p.findShortest(); break;
                    case 11: p.countCars(); break;
                    case 12: p.totalFee(); break;
                    case 0: cout << "Goodbye!\n"; break;
                    default: 
                        cout << "Lựa chọn không hợp lệ. Vui lòng chọn lại!\n";
                }
            } while(choice != 0);
        }
};

int main(){
    App a;
    a.run();
    return 0;
}