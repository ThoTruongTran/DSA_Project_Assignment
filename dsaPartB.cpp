#include<bits/stdc++.h>
using namespace std;

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
			
			if(head == nullptr){
				head = tail = current = newSong;
				cout << "Da them bai hat dau tien: " << title << endl;
				return;
			}
			
			if(position == -1){
				tail->next = newSong;
				newSong->prev = tail;
				tail = newSong;
				cout << "Da them bai hat vao cuoi playlist: " << title << endl;
				return;
			}
			
			if(position == 1){
				newSong->next= head;
				head->prev = newSong;
				head = newSong;
				cout << "Da them bai hat vao dau playlist: " << title << endl;
				return;
			}
			
			Song *temp = head;
			int index = 1;
			while(temp->next != nullptr && index < position -1){
				temp = temp->next;
				index++;
			}
			
			if(temp->next == nullptr){
				tail->next = newSong;
				newSong->prev = tail;
				tail = newSong;
				cout << "Da them bai hat vao cuoi playlist: " << title << endl;
			}
			else{
				newSong->next = temp->next;
				newSong->prev = temp;
				temp->next->prev = newSong;
				temp->next = newSong;
			}
		}
		
		void delSong(string title){
			if(head == nullptr){
				cout << "Playlist trong!" << endl;
				return;
			}
			
			Song *temp = head;
			while(temp != nullptr && temp->title != title){
				temp = temp->next;
			}
			
			if(temp == nullptr){
				cout << "Khong tim thay bai hat can xoa!" << endl;
				return;
			}
			
			if(temp == head){
				head = head->next;
				if(head != nullptr){
					head->prev = nullptr;
				}
			}
			else if(temp == tail){
				tail = tail->prev;
				if(tail != nullptr){
					tail->next = nullptr;
				}
			}
			else{
				temp->prev->next = temp->next;
				temp->next->prev = temp->prev;
			}
			
			if(current = temp){
				current = temp->next;
				if(current == nullptr){
					current = head;
				}
			}
			
			delete temp;
			cout << "Da xoa bai hat thanh cong!" << endl;
		}
		
		void currentSong(){
			if(current == nullptr){
				cout << "Danh sach trong!" << endl;
				return;
			}
			cout << "Dang phat: " << current->title << " - " << current->artist << " - "
				 << " (" << current->duration << ") " << endl;
		}
		
		void nextSong(){
			if(current->next == nullptr){
				cout << "Da den cuoi playlist, quay lai dau!" << endl;
				current = head;
			}
			else{
				current = current->next;
			}
			currentSong();
		}
		
		void prevSong(){
			if(current->prev == nullptr){
				cout << "Dang o dau playlist, chuyen den cuoi!" << endl;
				current = tail;
			}
			else{
				current = current->prev;
			}
			currentSong();
		}
		
		void display(){
			if(head == nullptr){
				cout << "Playlist trong!" << endl;
				return;
			}
			cout << "====DANH SACH BAI HAT====" << endl;
			Song *temp = head;
			int i = 1;
			while(temp != nullptr){
				cout << i++ << ". " << temp->title << " - "
					 << temp->artist << " - " << " (" << temp->duration << ") "  << endl;
				temp = temp->next;
			}
			cout << "====================" << endl;
		}
};

int main(){
	Playlist pl;
	int choice;
	string title, artist;
	float duration;
	int pos;
	
	do{
		cout << "\n==== PLAYLIST NGHE NHAC ====" << endl;
		cout << "1. Them bai hat" << endl;
		cout << "2. Phat bai tiep theo" << endl;
		cout << "3. Phat bai truoc do" << endl;
		cout << "4. Xoa bai hat" << endl;
		cout << "5. Hien thi danh sach" << endl;
		cout << "6. Thoat" << endl;
		cout << "Chon: ";
		cin >> choice;
		cin.ignore();
		
		switch(choice){
			case 1: 
				cout << "\nNhap ten bai hat: "; getline(cin, title);
				cout << "Nhap ten ca si: "; getline(cin, artist);
				cout << "Nhap thoi luong (phut): "; cin >> duration;
				cout << "Nhap vi tri can them (-1 neu them vao cuoi, 1 neu them vao dau): ";
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
				cout << "Nhap ten bai hat can xoa: "; getline(cin, title);
				pl.delSong(title);
				break;
			case 5: 
				pl.display();
				break;
			case 6:
				cout << "Goodbye!" << endl;
				break;
			default:
				cout << "Lua chon khong hop le!" << endl;
		}
	} while(choice != 6);
	return 0;
}
