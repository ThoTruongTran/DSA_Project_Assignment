#include<bits/stdc++.h>
using namespace std;

class Car{ // Đối tượng quản lý Car
    private:
        string license_plate, owner, brand; // Quản lý thông qua: biển số, chủ xe, hãng, số giờ gửi và phí
        float hours;
        float fee;
    
    public:
        Car(){ // Hàm tạo không đối 
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

        string toLower(string s){
            for(auto &c : s) c = tolower(c);
            return s;
        }

        string toUpper(string s){
            for(auto &c : s) c = toupper(c);
            return s;
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
                if(toUpper(c.getLicense_Plate()) == toUpper(lp)) return true;
            }
            return false;
        }

        void addCar(){
            Car c;
            c.input();
            while(checkPlate(c.getLicense_Plate())){
                cout << "Xe này đã tồn tại! Vui lòng nhập lại!\n";
                c.input();
            }
            carList.push_back(c);
            cout << "Đã thêm thành công!\n";
            saveFileDefault();
        }

        void removeCar(){
            string lp;
            cout << "Nhập biển số xe cần xoá: ";
            cin >> lp;
            for(auto it = carList.begin(); it != carList.end(); ++it){
                if(it->getLicense_Plate() == lp){
                    carList.erase(it);
                    cout << "Đã xoá!\n";
                    saveFileDefault();
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
                if(toLower(c.getLicense_Plate()) == toLower(lp)){
                    string newOwner, newBrand;
                    float newHours;
                    cin.ignore();

                    string oldOwner = c.getOwner();
                    string oldBrand = c.getBrand();
                    float oldHours = c.getHours();
                    cout << "Thông tin cũ:\n";
                    cout << left << setw(12) << "Bien so" << setw(25) << "Chu xe" << setw(15) << "Hang" << setw(10) << "Gio" << setw(10) << "Phi" << endl;
                    cout << string(75, '-') << endl;
                    c.display();
                    
                    cout << "Nhập tên chủ xe mới: "; getline(cin, newOwner);
                    if(newOwner.empty()) newOwner = oldOwner;
                    cout << "Nhập hãng xe mới: "; getline(cin, newBrand);
                    if(newBrand.empty()) newBrand = oldBrand;
                    cout << "Nhập số giờ mới: ";
                    string tempHours; getline(cin, tempHours);
                    if(tempHours.empty()) newHours = oldHours;
                    if(newHours <= 0){
                        cout << "Không hợp lệ! Vui lòng nhập lại số giờ mới: ";
                        cin >> newHours;
                    }

                    c.setOwner(newOwner);
                    c.setBrand(newBrand);
                    c.setHours(newHours);
                    cout << "Cập nhật thành công!\n";
                    displayAll();
                    saveFileDefault();
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
                if(toLower(c.getLicense_Plate()) == toLower(lp)){
                    c.display();
                    return;
                }
            }
            cout << "Không tìm thấy!\n";
        }
        
        void saveBrand(const string &filename, const string &brand){
            ofstream file(filename);
            if(!file) return;
            for(auto &c: carList){
                if(toLower(c.getBrand()) == toLower(brand)){
                    file << c;
                }
            }
            file.close();
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

        void findOwner(){
            string ow;
            cout << "Nhập tên chủ xe cần tìm: "; cin.ignore();
            getline(cin, ow);
            bool found = false;
            for(auto &c : carList){
                if(toUpper(c.getOwner()) == toUpper(ow)){
                    cout << left << setw(12) << "Bien so" << setw(25) << "Chu xe" << setw(15) << "Hang" << setw(10) << "Gio" << setw(10) << "Phi" << endl;
                    cout << string(75, '-') << endl;
                    c.display();
                    found = true;
                }
            }
            if(!found){
                cout << "Không có xe thuộc chủ xe này.\n";
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

        void sortFeeDescending(){
            if(carList.empty()){
                cout << "Bãi xe trống!\n";
                return;
            }
            carList.sort([](Car &a, Car &b) {return a.getFee() > b.getFee();}); // Lamda expression để sắp xếp giảm dần (hàm ẩn danh)
            saveFileAnother("sorted_fee.txt");
            cout << "Đã cập nhật file sorted_fee.txt\n";
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
            else if(option == 2){
                carList.sort([](Car &a, Car &b) {return a.getHours() > b.getHours();});
                saveFileAnother("sorted_hours_descending.txt");
                cout << "Đã cập nhật file sorted_hours_descending.txt\n";
            }
            else{
                cout << "Sắp xếp không hợp lệ. Vui lòng chọn lại!\n";
                sortHours();
            }

        }

        void sortHours2(){
            if(carList.empty()){
                cout << "Bãi xe trống!\n";
                return;
            }
            int option;
            cout << "Sắp xếp tăng dần (1)\nSắp xếp giảm dần (2)\nChọn: ";
            cin >> option;
            if(option == 1){
                carList.sort([](Car &a, Car &b) {return a.getHours() < b.getHours();});
            }
            else if(option == 2){
                carList.sort([](Car &a, Car &b) {return a.getHours() > b.getHours();});
            }
            else{
                cout << "Sắp xếp không hợp lệ. Vui lòng chọn lại!\n";
                sortHours2();
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
                if(toLower(c.getLicense_Plate()) == toLower(lp)){
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

        void totalFeeAll(){
            float total = 0;
            for(auto &c : carList){
                total += c.getFee();
            }
            cout << "Tổng phí gửi của tất cả xe là: " << total << " VNĐ.\n";
        }

        void totalHoursAll(){
            float total = 0;
            for(auto &c : carList){
                total += c.getHours();
            }
            cout << "Tổng số giờ gửi của tất cả xe là: " << total << " giờ.\n";
        }

        void findCarInHourRange(float minhrs, float maxhrs){
            cout << "Nhập khoảng thời gian gửi xe (giờ): \n";
            cout << "Từ: "; cin >> minhrs;
            cout << "Đến: "; cin >> maxhrs;
            bool found = false;
            for(auto &c : carList){
                if(c.getHours() >= minhrs && c.getHours() <= maxhrs){
                    c.display();
                    saveFileAnother("cars_in_hour_range.txt");
                    found = true;
                }
            }
            if(!found){
                cout << "Không tìm thấy xe nào trong khoảng thời gian này.\n";
            }
        }

        void topCarsByHours(int n){
            if(carList.empty()){
                cout << "Bãi xe trống!\n";
                return;
            }
            cout << "Nhập số lượng xe cần sắp xếp: ";
            cin >> n;
            sortHours2();
            for(int i = 0; i < n && i < carList.size(); ++i){
                auto it = carList.begin();
                advance(it, i); // Di chuyển iterator đến vị trí i
                it->display();
            }
        }

        void topCarsByHours2(int n){
            if(carList.empty()){
                cout << "Bãi xe trống!\n";
                return;
            }
            cout << "Nhập số lượng xe cần sắp xếp: ";
            cin >> n;
            int count = 0;
            sortHours2();
            for(auto it = carList.begin(); it != carList.end() && count < n; ++it){
                it->display();
                count++;
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
            cout << "7. Tìm xe theo chủ xe\n";
            cout << "8. Tìm xe có thời gian gửi trong khoảng\n";
            cout << "9. Sắp xếp theo phí gửi tăng dần\n";
            cout << "10. Sắp xếp theo phí gửi giảm dần\n";
            cout << "11. Sắp xếp theo giờ gửi\n";
            cout << "12. Tìm xe gửi lâu nhất\n";
            cout << "13. Tìm xe gửi ít nhất\n";
            cout << "14. Đếm số xe có trong bãi\n";
            cout << "15. Tính phí gửi theo xe\n";
            cout << "16. Tính tổng phí gửi của tất cả xe\n";
            cout << "17. Tính tổng số giờ gửi của tất cả xe\n";
            cout << "18. Sắp xếp n xe có thời gian gửi lâu nhất/ ít nhất\n";
            cout << "0. Thoát\n";
            cout << "==============================\n";
            cout << "Chọn(0-18): ";
        }

        void run(){
            int choice, n, type;
            float minhrs, maxhrs;

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
                    case 7: p.findOwner(); break;
                    case 8: p.findCarInHourRange(minhrs, maxhrs); break;
                    case 9: p.sortFeeAscending(); break;
                    case 10: p.sortFeeDescending(); break;
                    case 11: p.sortHours(); break;
                    case 12: p.findLongest(); break;
                    case 13: p.findShortest(); break;
                    case 14: p.countCars(); break;
                    case 15: p.totalFee(); break;
                    case 16: p.totalFeeAll(); break;
                    case 17: p.totalHoursAll(); break;
                    case 18: p.topCarsByHours(n); break;
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