#include <iostream>
#include <ctime>
#include <limits>
using namespace std;
int day[100], month[100], year[100], hour[100], minute[100];
string description[100];
string key[100];
int stt = 0;

// ADD
void ADD(){
    cout<<"Nhap ngay thang nam gio phut: ";
    cin>> day[stt] >> month[stt]>>year[stt]>>hour[stt]>>minute[stt];
    cin.ignore();
    cout<<"Nhap description: ";
    getline(cin, description[stt]);
    stt++;
}
// display
void Display(){
    for(int i = 0; i < stt; i++){
        cout<< i << "-->" << day[i] << "/" << month[i] << "/" << year[i] << " " << hour[i] << ":"<< minute[i] << "_"<< description[i]<<endl;
    }
}
// delete
void Delete(){
    int index;
    cout<< "Nhap stt need delete: ";
    cin>> index;
    if (index < 0 || index > stt){
        cout<<"Sai stt!\n";
        return;
    }
    for (int i = index ; i < stt -1 ; i++){
        day[i] = day[i + 1];
        month[i] = month[i + 1];
        year[i] = year[i + 1];
        hour[i] = hour[i + 1];
        minute[i] = minute[i + 1];
        description[i] = description[i + 1];
    }
    stt--;
}
// edit
void Edit(){
    int index;
    cout<<"Nhap index need edit: ";
    cin>> index;
    if ( index < 0 || index > stt){
        cout<<"Sai stt\n";
        return;
    }
    cout<< "Nhap ngay thang nam gio phut: ";
    cin>> day[index] >> month[index] >> year[index] >> hour[index] >> minute[index];
    cin.ignore();
    getline(cin, description[index]);
}
// countdown
void countDown(int i){
    tm cd = {};
    cd.tm_mday = day[i];
    cd.tm_mon = month[i] - 1;
    cd.tm_year = year[i] - 1900;
    cd.tm_hour = hour[i];
    cd.tm_min = minute[i];

    time_t timet = mktime(&cd);
    time_t now = time(0);

    double diff = difftime(timet, now);
    if (diff <= 0){
        cout<<"Da qua!\n";
        return;
    }
    int d = diff / (60 * 60 * 24); // 86400
    diff -= d * (60 * 60 * 24);

    int h = diff / (60 * 60);
    diff -= h * (60 * 60);
    
    int m = diff/ 60;

    cout<<" Con lai: "<< d <<"Ngay: "<< h <<" gio "<< m <<" phut\n";
}
void sort(){
    for (int i =0; i < stt -1 ; i++){
        int minIndex =i;
        for (int j = i + 1; j < stt; j++){
            // so sanh time
            if (year[j] < year[minIndex] || (year[i] == year[minIndex] && month[j] < month[minIndex])|| (year[j] == year[minIndex] && month[j] == month[minIndex] && day[j]< day[minIndex]) || (year[j] == year[minIndex] && month[j] == month[minIndex] && day[j] == day[minIndex] && hour[j] < hour[minIndex]) || (year[j] == year[minIndex] && month[j] == month[minIndex] && day[j] == day[minIndex] && hour[j] == hour[minIndex] && minute[j] < minute[minIndex])){
                minIndex = j;
            }
        }
        // swap  
        if(minIndex != i){
            int temp;
            temp = year[i];
            year[i] = year[minIndex];
            year[minIndex] = temp;

            temp = month[i];
            month[i] = month[minIndex];
            month[minIndex] = temp;

            temp = day[i];
            day[i] = day[minIndex];
            day[minIndex] = temp;

            temp = hour[i];
            hour[i] = hour[minIndex];
            hour[minIndex] = temp;

            temp = minute[i];
            minute[i] = minute[minIndex];
            minute[minIndex] = temp;

            string tempStr;
            tempStr = description[i];
            description[i] = description[minIndex];
            description[minIndex] = tempStr;
        }
    }
    for (int i =0; i < stt; i++){
        cout<< "Ngay: "<<day[i]<<" thang: "<< month[i]<<" nam: "<<year[i]<< " gio: "<<hour[i]<< " phut: "<<minute[i]<<" Description: "<<description<<"\n";
    }
}
void search(string key){
    
    if (key.empty()){
        cout<< "Chuoi can tim khong duoc de trong.\n";
        return;
    }
    bool found = false;
    for(int i = 0; i < stt; i++){
        size_t pos = description[i].find(key);
        while (pos != string::npos){
            cout<<"Tim thay tai stt "<< i<< " vi tri: "<<pos<<"\n";
            found = true;
            pos = description[i].find(key, pos + key.length());
        }
    }
    if (!found){
        cout<< "khong tim thay.\n";
    }
    return;
}
int main(){
    int chosen;
    time_t now = time(nullptr);//lay tg thuc
    tm *currentTime = localtime(&now);//chuyen sang thoi gian cau truc tm
    cout<<"Ngay hien tai: " <<currentTime ->tm_mday<<"/"<<currentTime->tm_mon+1 <<"/"<<currentTime->tm_year+1900<< "\n"<<" Thoi gian thuc: "<< currentTime->tm_hour << ":"<<currentTime->tm_min<<":"<<currentTime->tm_sec<<endl;



    while(1){
        cout<< "\n====Menu====\n";
        cout<< "1. Add\n";
        cout<< "2.Display\n";
        cout<< "3.Delete\n";
        cout<< "4.Edit\n";
        cout<< "5.CountDown\n";
        cout<< "6.sort\n";
        cout<< "7.Search\n";
        cout<< "0.Exit\n";
        cout<<"Enter chosen: ";
        cin>> chosen;
        switch (chosen)
        {
        case 1:
            ADD();
            break;
        case 2:
            Display();
            break;
        case 3:
            Delete();
            break;
        case 4:
            Edit();
            break;
        case 5:
            int i;
            cout<<"Nhap Index: ";
            cin>> i;
            if (i >= 0 && i < stt) countDown(i); 
            break;
        case 6:
            sort();
            break;
        case 7:
            search(key[100]);
            break;
        default:
            if (chosen == 0) return 0;
        }
    }
    return 0;
}