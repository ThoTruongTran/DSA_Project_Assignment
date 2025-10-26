#include <bits/stdc++.h>
using namespace std;

// Song ~ Node
class Song{
	public:
		string title; 
		string artist;
		float duration;
		Song *prev;
		Song *next;
		
		Song(string t, string a, float d){
			title = t;
			artist = a;
			duration = d;
			prev = next = nullptr;
		}
};

// Playlist ~ Linked List
class Playlist{
	private:
		Song *head;
		Song *tail;
		Song *current;
	
	public:
		Playlist(){
			head = tail = current = nullptr;
		}
		
		void addSong(string title, string artist, float duration, int position = -1){
			Song *newSong = new Song(title, artist, duration);
			
			// Nếu Playlist trống
			if(head == nullptr){
				head = tail = current = newSong; // Current là bài hát đầu tiên được khởi tạo trong Main
				cout << "Đã thêm bài hát đầu tiên: " << title << endl;
				return;
			}
			
			/*
			Thêm vào cuối có 2 cách:
			C1: Nhập -1
			C2: Nhập số lớn hơn số bài hát đang có trong Playlist
			*/
			if(position == -1){
				tail->next = newSong;
				newSong->prev = tail;
				tail = newSong;
				cout << "Đã thêm bài hát vào cuối playlist: " << title << endl;
				return;
			}
			
			/*
			Thêm vào đầu có 2 cách:
			C1: Nhập 1
			C2: Nhập 0 hoặc các số âm ngoại trừ -1
			*/
			if(position <= 1){
				newSong->next= head;
				head->prev = newSong;
				head = newSong;
				cout << "Đã thêm bài hát vào đầu playlist: " << title << endl;
				return;
			}
			
			Song *temp = head;
			int index = 1;
			while(temp->next != nullptr && index < position -1){ // Duyệt đến vị trí Node K-1 (Với K là vị trí muốn thêm Node mới)
				temp = temp->next;
				index++;
			}
			
			if(temp->next == nullptr){
				tail->next = newSong;
				newSong->prev = tail;
				tail = newSong;
				cout << "Đã thêm bài hát vào cuối playlist: " << title << endl;
			}
			else{
				newSong->next = temp->next;
				newSong->prev = temp;
				temp->next->prev = newSong;
				temp->next = newSong;
				cout << "Đã thêm bài hát vào vị trí " << position << ": " << title << endl;
			}
		}
		
		void delSong(string title){
			// Nếu Playlist trống
			if(head == nullptr){
				cout << "Playlist trống!" << endl;
				return;
			}
			
			Song *temp = head;
			while(temp != nullptr && temp->title != title){
				temp = temp->next;
			}
			
			// Nếu duyệt đến hết -> temp = nullptr
			if(temp == nullptr){
				cout << "Không tìm thấy bài hát cần xoá!" << endl;
				return;
			}
			
			
			if(temp == head){ // Xoá đầu
				head = head->next; // Nếu chỉ có 1 Node thì head->next = nullptr thì head = nullptr, tự xoá
				if(head != nullptr){
					head->prev = nullptr; // Nếu có trên 2 Node thì chỉ cần cập nhật Node trước head rỗng là xoá được
				}
			}
			else if(temp == tail){ // Xoá cuối, tương tự xoá đầu
				tail = tail->prev; 
				if(tail != nullptr){
					tail->next = nullptr;
				}
			}
			else{ // Xoá bất kì
				temp->prev->next = temp->next;
				temp->next->prev = temp->prev;
			}
			
			// Nếu Node hiện tại là bài hát đang được phát thì cập nhật lại Current sang bài tiếp theo
			if(current == temp){
				current = temp->next;
				if(current == nullptr){
					current = head;
				}
			}
			
			delete temp;
			cout << "Đã xoá bài hát thành công!" << endl;
		}
		
		// Bài hát hiện tại
		void currentSong(){
			if(current == nullptr){
				cout << "Playlist trống!" << endl;
				return;
			}
			cout << "Đang phát: " << current->title << " - " << current->artist
				 << " (" << current->duration << " phút)" << endl;
		}
		
		// Bài hát tiếp theo
		void nextSong(){
			if(current == nullptr){
				cout << "Playlist trống!" << endl;
				return;
			}
			if(current->next == nullptr){
				cout << "Đã đến cuối playlist, quay lại đầu!" << endl;
				current = head;
			} 
			else {
				current = current->next;
			}
			currentSong();
		}
		
		// Bài hát trước đó
		void prevSong(){
			if(current == nullptr){
				cout << "Playlist trống!" << endl;
				return;
			}
			if(current->prev == nullptr){
				cout << "Đang ở đầu playlist, chuyển đến cuối!" << endl;
				current = tail;
			} 
			else {
				current = current->prev;
			}
			currentSong();
		}
		
		// Hiển thị danh sách
		void display(){
			if(head == nullptr){
				cout << "Playlist trống!" << endl;
				return;
			}
			cout << "==== DANH SÁCH BÀI HÁT ====" << endl;
			Song *temp = head;
			int i = 1;
			while(temp != nullptr){
				cout << i++ << ". " << temp->title << " - "
					 << temp->artist << " - (" << temp->duration << " phút)" << endl;
				temp = temp->next;
			}
			cout << "===========================" << endl;
		}
};

int main(){
	Playlist pl;
	
	pl.addSong("Haru Haru", "BigBang", 4.2); // Đây là bài hát Current
	pl.addSong("Chi Mong Em Hanh Phuc", "Hoang Dung", 3.8);
	pl.addSong("Nevada", "Vicetone", 3.5);
	pl.addSong("Lac Troi", "Son Tung M-TP", 4.0);
	
	int choice;
	string title, artist;
	float duration;
	int pos;
	
	do{
		cout << "\n==== PLAYLIST NGHE NHẠC ====" << endl;
		cout << "1. Thêm bài hát" << endl;
		cout << "2. Phát bài tiếp theo" << endl;
		cout << "3. Phát bài trước đó" << endl;
		cout << "4. Xoá bài hát" << endl;
		cout << "5. Hiển thị danh sách" << endl;
		cout << "6. Thoát" << endl;
		cout << "Chọn: ";
		cin >> choice;
		cin.ignore();
		
		switch(choice){
			case 1: 
				cout << "\nNhập tên bài hát: "; getline(cin, title);
				cout << "Nhập tên ca sĩ: "; getline(cin, artist);
				cout << "Nhập thời lượng (phút): "; cin >> duration;
				cout << "Nhập vị trí cần thêm (-1 nếu thêm vào cuối, 1 nếu thêm vào đầu): ";
				cin >> pos;
				pl.addSong(title, artist, duration, pos);
				break;
			case 2:
				pl.nextSong();
				break;
			case 3:
				pl.prevSong();
				break;
			case 4: 
				cout << "Nhập tên bài hát cần xoá: "; getline(cin, title);
				pl.delSong(title);
				break;
			case 5: 
				pl.display();
				break;
			case 6:
				cout << "Goodbye!" << endl;
				break;
			default:
				cout << "Lựa chọn không hợp lệ!" << endl;
		}
	} while(choice != 6);
	return 0;
}
