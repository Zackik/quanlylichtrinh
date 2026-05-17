#include <iostream>
#include <ctime>
#include <queue>
#include <fstream>
#include <cmath>
#include <cassert>
#include <iomanip>
using namespace std;
//mang cua tung bien trong quan ly lich trinh gom ngay thang nam gio phut gioi han la 100 mang.
int day[200], month[200], year[200], hour[200], minute[200];
string description[200];
string address[200];
string person_to_meet[200];
string email[200];
bool state[200];//boolean
string priority[200];
string category[200];
int statistics[200];
int duration[200];
int revenue;
int q[200];
int front =0;
int rear = -1;
string places[7] = {"Sunday", "Monday", "Tuesday", "Webnesday", "Thursday", "Friday", "Saturday"};

string key[200];
// day la stt cua tung sk duoc nhan vao va co id rieng.
int stt = 0;
//logging in ra file txt hien thi [day/month/year hh:mm] [string action] 
void writeLog(string action){
    ofstream file(
        "log.txt", ios::app);
    time_t now = time(0);
    tm *current = localtime(&now);
    file << "[" << current->tm_mday << "/" << current->tm_mon + 1 << "/" << current->tm_year + 1900 << " "
    << current->tm_hour << ":" << current->tm_min << "]" << action << endl;
    file.close();

}
// them ngay thang nam gio phut va mo ta lich trinh cua thoi gian do, (value la day, month, year, hour, minute) de nhap thong tin de quan ly thoi gian.
void ADD(){
    char c1, c2, c3;
    cout<<"Nhap theo dinh dang (hh:mm dd/mm/yyyy): ";
    cin>> hour[stt] >> c1 >> minute[stt] >> day[stt] >> c2 >> month[stt] >> c3 >> year[stt];
    // cin>> day[stt] >> month[stt]>>year[stt]>>hour[stt]>>minute[stt];
    if (day[stt] < 0 || day[stt]> 31){
        cout<<"Moi nhap lai ngay!";
        return;
    }
    if(month[stt] < 0 || month[stt] >= 13){
        cout<<"Moi nhap lai thang!";
        return;
    }
    // if(year[stt] < 0000){
    //     cout<<"Moi nhap lai nam!";
    //     return;
    // }
    if (hour[stt]< 0 || hour[stt]>=24){
        cout<<"Moi nhap lai gio!";
        return;
    }
    if (minute[stt] < 0 || minute[stt] >=60){
        cout<<"Moi nhap lai phut";
        return;
    }
    cout<<"Nhap duration(minutes): ";
    cin>>duration[stt];

    cin.ignore();
    cout<<"Nhap description: ";
    getline(cin, description[stt]);
    
    cout<<"Nhap dia chi(address): ";
    getline(cin, address[stt]);
    
    cout<<"Nhap nguoi can gap(meeting): ";
    getline(cin, person_to_meet[stt]);
    
    // cout<<"Trang thai va can chu y(Done and note): ";
    // getline(cin, state[stt]);
    // cin.ignore();
    int chooseState;
    cout<<"\n==STATUS===\n";
    cout<<"0. Pending\n";
    cout<<"1. Done\n";
    cout<<"2. Canceled\n";
    cout<<"Choose: ";
    cin>>chooseState;
    cin.ignore();
    if(chooseState == 0 || chooseState == 1 || chooseState == 2){
        switch (chooseState)
        {
            case 0:
                state[stt] = "Pending";
                break;
            case 1:
                state[stt]  = "Done";
                break;
    
            default:
                state[stt] = "Canceled";
                break;
        }
    }
    else{
        cout<<"Nhap lai!\n";
        return;
    }
    

    cout<<"Nhap doanh thu(USD): ";
    cin>> statistics[stt];
    
    cout<<"Nhap email(example@gmail.com): ";
    cin>>email[stt];

    int priorityChoice;
    cout<<"\n==PRIORITY===\n";
    cout<<"1. High\n";
    cout<<"2. Medium\n";
    cout<<"3. Low\n";

    cout<<"Choose: ";
    cin>>priorityChoice;
    cin.ignore();
    switch (priorityChoice)
    {
    case 1:
        priority[stt] = "High";
        break;
    case 2:
        priority[stt]  = "Medium";
        break;
    case 3:
        priority[stt] = "Low";
    
    default:
        priority[stt] = "Low";
        break;
    }

    int chooseCategory;
    cout<<"\n====CATEGORY====\n";
    cout<<"1. Work\n";
    cout<<"2. Study\n";
    cout<<"3. Personal\n";
    cout<<"4. Meeting\n";
    cout<<"5. Health\n";
    cout<<"Choose: ";
    cin>>chooseCategory;
    cin.ignore();
    switch (chooseCategory)
    {
    case 1:
        category[stt] = "Work";
        break;
    case 2:
        category[stt] = "Study";
        break;
    case 3:
        category[stt] = "Personal";
        break;
    case 4:
        category[stt] = "Meeting";
        break;
    case 5:
        category[stt] = "Health";
        break;
    default:
        category[stt] = "Personal";
        break;
    }
    
    int m = month[stt];
    int n = year[stt];
    int d = day[stt];
    int a = (14 - m)/ 12;
    int y = (n - a);
    int mon = m + 12*a - 2;
    int dayofweek = (d  + y + y/4 - y/100 + y/400 + (31 * mon)/12) % 7;
    places[dayofweek];
    cout<<"Thu: "<<places[dayofweek]<< endl;
    if(stt == 199){
        cout<<"Da day thong tin!"<<endl;
    }
    
    //dem nguoc thoi gian
    tm cd = {};
    cd.tm_mday = day[stt];
    cd.tm_mon = month[stt] - 1;
    cd.tm_year = year[stt] - 1900;
    cd.tm_hour = hour[stt];
    cd.tm_min = minute[stt];

    time_t timet = mktime(&cd);
    time_t now = time(0);

    double diff = difftime(timet, now);
    if (diff <= 0){
        cout<<"Da qua!\n";
        return;
    }
    int k = abs(diff / (60 * 60 * 24)); // 86400
    diff = abs(diff - (k * (60 * 60 * 24)));
   

    int h = abs(diff / (60 * 60));
    diff = abs(diff - (h * (60 * 60)));
    
    int p = abs(diff/ 60);
    cout<<"Con lai: "<< k <<"Ngay: "<< h <<" gio "<< p <<" phut\n";
    
    cout<<"";
    stt++;
    rear++;
    q[rear] = stt;
    writeLog("ADD EVENT");
    cout<<"Add thanh cong"<<endl;
}


//dequeue neu front = 0 dau tien va rear rear ++ cuoi front > rear rong 
//lay phan tu va xoa phan tu dau tien FIFO
void dequeueEvent(){
    if (front > rear){
        cout<<"Queue rong!\n";
        return;
    }
    int index = q[front];
    front++;
    cout<<"\n===PROCESS EVENT====\n";
    cout<<"STT: "<<index<<endl;
    cout<<"Description: "<<description[index]<<endl;
}
//enqueue them vao cuoi hang queue
void enqueueEvent(int stt){
    if (rear == 201 -1){
        cout<<"Queue full!\n";
        return;
    }
    rear++;
    q[rear] = stt;
}
//export Queue csv 
void exportQueueCSV(){
    if (front > rear){
        cout<< "Queue rong!\n";
        return;
    }
    ofstream file("Event.csv");

    if(!file.is_open()){
        cout<<"Khong mo duoc file!\n";
        return;
    }

    file<< "QueueOrder   "<<"Date   "<<"Time   "<<"Description   "<<"Priority   "<<"State\n";
    int order = 1;
    for(int i = front; i <= rear; i++){
        int index = q[i];
        string status = state[index] ? "Done" : "Pending";

        string date = to_string(day[index]) + "/" + to_string(month[index]) + "/" + to_string(year[index]);

        string timeStr;

        if(hour[index] < 10) timeStr += "0";
        timeStr += to_string(hour[index]);
        timeStr += ":";
        if(minute[index]< 10) timeStr += "0";
        timeStr += to_string(minute[index]);

        file << order <<"   "<<"\""<< date << "\""<< "   "<< "\""<< timeStr << "\"" << "   "<< "\""<< description[index] << "\"" << "   " <<"\""<< priority[index] << "\"" << "   "<< "\""<<status << "\"" << "\n";
        order++;

    }
    file.close();
    writeLog("EXPORT QUEUE CSV");
    cout<<"=============\n";
    cout<<"EXport CSV Successfully!\n";
    cout<<"File: Event.csv\n";
    cout<<"=============\n";
    
}
//sang phut bat dau
int startMinutes(int i){
    return hour[i] * 60 + minute[i];
}
//sang phut ket thuc
int endMinutes(int i){
    return startMinutes(i) + duration[i];
}
//trung lap khoang thoi gian va thoi i de thay va day month year
//  1  = 0 old 1 ; new 0
bool checkConflict(){
    int newStart = startMinutes(stt);
    int newEnd = endMinutes(stt);
    for(int i =0; i<stt ;i++){
        if (day[i] == day[stt] && month[i] == month[stt] && year[i] == year[stt]){
            int oldStart = startMinutes(i);

            int oldEnd = endMinutes(i);
            if(newStart < oldEnd && newStart > oldStart){
                return true;
            }
        }
    }
    return false;
    
}
// in ra cac ngay thang nam gio phut cua cac su kien da nhap vao.
void Display(){
    if (stt < 0 || stt >= 200){
        cout<<"Khong the in ra neu khong co stt nao hoac qua 100 su kien"<<endl;
        return;
    }
    for(int i = 0; i < stt; i++){
        int m = month[i];
    int n = year[i];
    int d = day[i];

    int a = (14 - m) / 12;
    int y = n - a;
    int mon = m + 12 * a - 2;

    int dayofweek =
    (d + y + y/4 - y/100 + y/400 + (31 * mon)/12) % 7;
        cout<<"STT: "<< i << " --> "<< hour[i] << ":"<< minute[i]<< " " << day[i]<< "/"<< month[i] << "/"<< year[i] << "\n"<<"Thu: "<<places[dayofweek] <<"\n"<<"Description: "<< description[i] << "\n" << "Address: "<<address[i]<<"\n"<<"Person to meet: "<<person_to_meet[i]<<"\n" <<"Email: "<<email[i]<< "\n"<< "State: "<< state[i]<< "\n" <<priority[i]<<"\n"<<"Duration: "<<duration[i]<<" minutes\n"<<"Category: "<<category[i]<<endl;
        cout<<"==============="<<endl;
    }
    
    writeLog("DISPLAY EVENT");
    cout<<"Display successfully!"<<endl;
}
//function priority transfer number
int priorityValue(string p){
    if (p == "High") return 1;
    if (p == "Medium") return 2;
    if (p == "Low") return 3;
    bool found = false;
    if (1){
        for(int i =0; i<stt; i++){
            cout<<"\n==========\n";
            cout<<"STT: "<<i<<endl;
            cout<<"Date: "<< day[i]<<"/"<<month[i]<<"/"<<year[i]<<endl;
            cout<<"Time: "<<hour[i]<<":"<<minute[i]<<endl;
            cout<<"Priority: "<<priority[i]<<endl;
            found = true;
        }
    }
    if(!found){
        cout<<"Khong co event nao!\n";
    }
    writeLog("PRIORITY VALUE");
    return 0;
}
//sort priority selection sort
void sortPriority(){
    for(int i =0; i< stt -1; i++){
        int minIndex = i;
        for(int j = i + 1; j < stt; j++){
            if(priorityValue(priority[j]) < priorityValue(priority[minIndex])){
                minIndex = j;
            }
            
        }
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

            string tempPriority;
            tempPriority = priority[i];
            priority[i] = priority[minIndex];
            priority[minIndex] = tempPriority;

            
        }
        cout<<"\n==DEBUG==\n";
        cout<<"Swap "<< i <<"<->"<<minIndex<<endl;
        
    }
    
    writeLog("SORT PRIORITY");
    cout<<"Sort Priority Successfully!\n";
}

// xoa su kien theo index, (value index) de nhap so muon xoa khoi su kien da duoc nhap vao.
void Delete(){
    int index;
    cout<< "Nhap stt need delete: ";
    cin>> index;
    if (index < 0 || index >= stt){
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
    cout<<"\n==DEBUG==\n";
    cout<<"Delete index: "<<index<<endl;
    writeLog("DELETE EVENT");
    cout<<"Delete successfully!"<<endl;
}
// chinh sua su kien da co trong su kien (value index) de nhap vao so muon chinh sua trong su kien da chon.
void Edit(){
    int index;
    int luachon;
    cout<<"======LUACHON======="<<endl;
    cout<<"1. Sua ngay\n";
    cout<<"2. Sua thang\n";
    cout<<"3. Sua nam\n";
    cout<<"4. Sua gio\n";
    cout<<"5. Sua phut\n";
    cout<<"6. Sua description\n";
    cout<<"7. Sua address\n";
    cout<<"8. Sua person to meet\n";
    cout<<"9. Sua email\n";
    cout<<"10. Sua State\n";
    cout<<"11. Sua tat ca cac thong tin\n";

    cout<<"Lua chon: ";
    cin>>luachon;
    cout<<"\n";
    cout<<"Nhap index need edit: ";
    cin>> index;
    if ( index < 0 || index >= stt){
        cout<<"Sai stt\n";
        return;
    }
    switch (luachon)
    {
    case 1:
        cout<<"Sua ngay: ";
        cin>>day[index];
        if (day[index] < 0 || day[index]>= 33){
            cout<<"Moi nhap lai ngay!";
            return;
    }
        break;
    case 2:
        cout<<"Sua thang: ";
        cin>>month[index];
        if(month[index] < 0 || month[index]>=13){
            cout<<"Moi nhap la thang!";
            return;
        }
        break;
    case 3:
        cout<<"Sua nam: ";
        cin>>year[index];
        if(year[index] < 0000){
            cout<<"Moi nhap lai nam!";
            return;
        }
        break;
    case 4:
        cout<<"Sua gio: ";
        cin>>hour[index];
        if(hour[index] < 0 || hour[index] >= 24){
            cout<<"Moi nhap lai gio!";
            return;
        }
        break;
    case 5:
        cout<<"Sua phut: ";
        cin>>minute[index];
        if(minute[index] < 0 || minute[index] >=60){
            cout<<"Moi nhap lai phut!";
            return;
        }
        break;
    case 6:
        cout<<"Sua description: ";
        getline(cin, description[index]);
        break;
    case 7:
        cout<<"Sua address: ";
        getline(cin, address[index]);
        break;
    case 8:
        cout<<"Sua person to meet: ";
        getline(cin, person_to_meet[index]);
        break;
    case 9: 
        cout<<"Sua email: ";
        getline(cin, email[index]);
        break;
    case 10:
        cout<<"Sua state: ";
        cin>>state[index];
        break;
    case 11:   
        cout<< "Nhap ngay thang nam gio phut: ";
        cin>> day[index] >> month[index] >> year[index] >> hour[index] >> minute[index];
        cin.ignore();
        cout<<"  Sua description: ";
        getline(cin, description[index]);
        cout<<"\n";
        cout<<" Sua address: ";
        getline(cin, address[index]);
        cout<<"\n";
        cout<<" Sua person to meet: ";
        getline(cin, person_to_meet[index]);
        cout<<"\n";
        cout<<" Sua email: ";
        getline(cin, email[index]);
        cout<<"\n";
        cout<<" Sua state: ";
        cin>>state[index];
        break;
    default:
        cout<<"Moi chon lai";
        return;
    }
    // cout<< "Nhap ngay thang nam gio phut: ";
    // cin>> day[index] >> month[index] >> year[index] >> hour[index] >> minute[index];
    // cin.ignore();
    // getline(cin, description[index]);
    writeLog("EDIT EVENT");
    cout<<"Edit successfully!"<<endl;
}
// La dem nguoc thoi gian da va sap xep lich tuan tu va cu the co ngay thang nam gio phut.
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
    cout<<"\n==DEBUG==\n";
    cout<<"Diff: "<<diff<<endl;
    writeLog("COUNT DOWN");
    cout<<"Count down successfully!"<<endl;
}
//priority_queue
// long long encodeTime(int i){
//         return
//         year[i] * 100000000ll + month[i] * 1000000ll + day[i]* 10000ll + hour[i]* 100ll + minute[i];
//     }
// void PriorityDate(){
//     if (stt == 0){
//         cout<<"Khong co du lieu";
//         return;
//     }
    
//     priority_queue<long long, deque<long long>, greater<long long>> pq;
//     // push all time in heap
//     for(int i =0; i<stt;i++){
//         pq.push(encodeTime(i));
//     }
//     cout<<"SAP XEP THOI GIAN"<<endl;
//     while(!pq.empty()){
//         long long x = pq.top();
//         pq.pop();
//         int minute1 = x % 100;
//         x /= 100;
//         int hour1 = x % 100;
//         x /= 100;
//         int day1 = x % 100;
//         x /= 100;
//         int month1 = x % 100;
//         x /= 100;
//         int year1 = x;
//         cout<< day1 << "/" <<month1 << "/" << year1 << " " << hour1 << ":" << minute1 <<endl; 
//     }
// }
// La sap xep cac su kien theo huong la small to big theo ngay thang nam gio phut.
void sort(){
    for (int i =0; i < stt -1 ; i++){
        int minIndex =i;
        for (int j = i + 1; j < stt; j++){
            // so sanh time
            if (year[j] < year[minIndex] || (year[j] == year[minIndex] && month[j]  < month[minIndex])
            || (year[j] == year[minIndex] && month[j] == month[minIndex] && day[j]< day[minIndex]) || 
            (year[j] == year[minIndex] && month[j] == month[minIndex] && day[j] == day[minIndex] && hour[j] < hour[minIndex]) || 
            (year[j] == year[minIndex] && month[j] == month[minIndex] && day[j] == day[minIndex] && hour[j] == hour[minIndex] && minute[j] < minute[minIndex])){
                minIndex = j;
            }
        }
        
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
    writeLog("SORT SELECTION");
    cout<<"Sort successfully!"<<endl;
    
}
// sort binary sort
// int binaryPosition(long long value, int low, int high){
//     while(low <= high){
//         int mid = (low + high)/2;
//         if(encodeTime(mid) > value){
//             high = mid -1;

//         }
//         else{
//             low = mid + 1;
//         }
//     }
//     return low;
// }

// void sort(){
//     for (int i = 1; i < stt; i++){
//         long long currentTime = year[i]* 100000000ll + month[i]* 1000000ll + day[i]* 10000ll + hour[i]* 100ll + minute[i];
//         // save data
//         int tempDay = day[i];
//         int tempMonth = month[i];
//         int tempYear = year[i];
//         int tempHour = hour[i];
//         int tempMinute = minute[i];

//         int tempStatistics = statistics[i];

//         string tempDes = description[i];
//         string tempaddress = address[i];
//         string tempPerson = person_to_meet[i];
//         string tempEmail = email[i];
//         bool tempState = state[i];

//         //find position by binary sort
//         int pos = binaryPosition(currentTime,0, i-1);

//         //doi mang
//         for(int j = i; j > pos; j--){
//             day[j] = day[j -1];
//             month[j] = month[j -1];
//             year[j] = year[j - 1];
//             hour[j] = hour[j -1];

//             statistics[j] = statistics[j -1];

//             description[j] = description[j -1];
//             address[j] = address[j -1];
//             person_to_meet[j] = person_to_meet[j -1];
//             email[j] = email[j -1];
//             state[j] = state[j -1];
//         }
//         //chen lai
//         day[pos] = tempDay;
//         month[pos] = tempMonth;
//         year[pos] = tempYear;
//         hour[pos] = tempHour;
//         minute[pos] = tempMinute;

//         statistics[pos] = tempStatistics;

//         description[pos] = tempDes;
//         address[pos] = tempaddress;
//         person_to_meet[pos] = tempPerson;
//         email[pos] = tempEmail;
//         state[pos] = tempState;
//     }
//     writeLog("SORT EVENT");
//     cout<<"Binary sort successfully!\n";
// }
// La tim kiem tu khoa trong description cua tung su kien va in ra (value key).
//void search(){
    // int chon;
    // bool found = false;
    // cout<<"===================MENU===============";
    // cout<<" 1.Tim kiem address\n";
    // cout<<" 2.Tim kiem person to meet\n";
    // cout<<" 3.Tim kiem email\n";
    // cout<<" 4.Tim kiem trang thai\n";
    // cin>> chon;
    // try{
    //     switch(chon){
    //         case 1:
    //             string keyaddress;
    //             cout<<" Enter a word to search (address): ";
    //             cin.ignore();
    //             getline(cin, keyaddress);
    //             if (keyaddress.empty()){
    //                 cout<<"Moi nhap thong tin vao\n";
    //                 return;
    //             }
    //             for(int i =0; i< stt; i++){
    //                 if(address[i].find(keyaddress) != string::npos){
    //                     cout<<" Match found at stt: "<< i << " Address: "<< address[i]<< endl;
    //                     found = true;
    //             }
    //             }
    //             if (!found){
    //                 cout<<" No match found!"<<endl;
    //                 return;
    //             }
    //         return;
    //         break;

    //         case 2:
    //             string keyperson;
    //             cout<<" Enter a word to search (person to meet): ";
    //             cin.ignore();
    //             getline(cin, keyperson);
    //             if (keyperson.empty()){
    //                 cout<<"Moi nhap thon tin vao\n";
    //                 return;
    //             }
    //             for(int i =0; i< stt; i++ ){
    //                 if (person_to_meet[i].find(keyperson) != string::npos){
    //                     cout<<" Match found at stt: "<< i << " Person to meet: "<< person_to_meet[i]<< endl;
    //                     found = true;
    //             }
    //             }
    //             if (!found){
    //                 cout<<" No match found!";
    //                 return;
    //             }
    //         return;
    //         break;
    //         case 3:
    //             string keyemail;
    //             cout<<" Enter a word to search (email): ";
    //             cin.ignore();
    //             getline(cin, keyemail);
    //             if (keyemail.empty()){
    //                 cout<<"MOi nhap thong tin vao\n";
    //                 return;
    //             }
    //             for(int i =0; i<stt; i++){
    //                 if(email[i].find(keyemail) != string::npos){
    //                     cout<<" Match found at stt: "<< i << " Eamil: "<<email[i]<<endl;
    //                     found = true;
    //                 }
    //             }
    //             if(!found){
    //                 cout<<"Khong tim thay ket qua!"<<endl;
    //                 return;
    //             }
    //         return;
    //         break;
    //         case 4:
    //             string keystate;
    //             cout<<" Enter a word to search (state): ";
    //             cin.ignore();
    //             getline(cin, keystate);
    //             if (keystate.empty()){
    //                 cout<<"Moi nhap thong tin vao\n";
    //                 return;
    //             }
    //             for(int i =0; i< stt; i++){
    //                 if (state[i].find(keystate) != string::npos){
    //                     cout<<"Match a found to stt: "<< i << " State: "<< state[i]<<endl;
    //                     found = true;
    //                 }
    //             }
    //             if(!found){
    //                 cout<<"Khong tim thay ket qua!\n";
    //                 return;
    //             }
    //         break;
    //     }
    //     default:
    //         if(chon == 0){
    //             return ;
    //         }
    // }
    // catch(exception e){

    // }
    
    // tim kiem dia chi value keyaddress
    // string keyaddress;
    // cout<<" Enter a word to search (address): ";
    // cin.ignore();
    // getline(cin, keyaddress);
    // if (keyaddress.empty()){
    //     cout<<" Khong tim duoc ket qua!";
    //     return;
    // }
    // for(int i =0; i< stt; i++){
    //     if(address[i].find(keyaddress) != string::npos){
    //         cout<<" Match found at stt: "<< i << " Address: "<< address[i]<< endl;
    //         found = true;
    //     }
    // }
    // if (!found){
    //     cout<<" No match found!"<<endl;
    //     return;
    // }
    // person_ to _meet value keyperson
    // string keyperson;
    // cout<<" Enter a word to search (person to meet): ";
    // cin.ignore();
    // getline(cin, keyperson);
    // if (keyperson.empty()){
    //     cout<<" Khong tim duoc ket qua!";
    //     return;
    // }
    // for(int i =0; i< stt; i++ ){
    //     if (person_to_meet[i].find(keyperson) != string::npos){
    //         cout<<" Match found at stt: "<< i << " Person to meet: "<< person_to_meet[i]<< endl;
    //         found = true;
    //     }
    // }
    // if (!found){
    //     cout<<" No match found!";
    //     return;
    // }
    
    // bool found = false;
    // // tim kiem linh gom address, state, author,... author sap xep goi y theo thu tu
    // for(int i = 0; i < stt; i++){
    //     cout<<" Match found at stt: "<< i <<" Person to meet: "<< person_to_meet[i]<< endl;
    // }
    
    // string key;
    // cout<< "Enter a word to search: ";
    // cin.ignore();
    // getline(cin, key);
    // if (key.empty()){
    //     cout<<"chuoi can tim khong co\n";
    //     return;
    // }
    // for (int i =0; i< stt; i++){
    //     if (description[i].find(key) != string::npos){
    //         cout<< "Match found at stt: "<<  i << " Nam: "<< year[i]<< 
    //         " thang: "<<month[i]<<" ngay: "<<day[i]<< " Hour: "<< hour[i]<< 
    //         " minute: "<< minute[i]<< endl;
    //         found = true;
    //     }
    // }
    // if (!found){
    //     cout<<" No match found."<< endl;
    // }
//}
// Tim kiem nguoi can gap mat tron su kien cua lich trinh voi (value keyperson)
// void search_person_to_meet(){
//     bool found = false;
//     string keyperson;
//     cout<<" Enter a word to search (person to meet): ";
//     cin.ignore();
//     getline(cin, keyperson);
//     if (keyperson.empty()){
//         cout<<"Moi nhap thon tin vao\n";
//         return;
//     }
//     for(int i =0; i< stt; i++ ){
//         if (person_to_meet[i].find(keyperson) != string::npos){
//             cout<<" Match found at stt: "<< i << " Person to meet: "<< person_to_meet[i]<< endl;
//             found = true;
//     }
//     }
//     if (!found){
//         cout<<" No match found!";
//         return;
//     }
// }
// Binary search string
void searchPersonBinary(){
    string keyPerson;
    cout<<"Nhap ten can tim: ";
    cin.ignore();
    getline(cin, keyPerson);
    int left = 0;
    int right = stt -1;
    bool found = false;
    while(left <= right){
        int mid = (left + right)/2;
        if(person_to_meet[mid] == keyPerson){
            cout<<"Find at STT: "<< mid << endl;
            found = true;
            break;
        }
        else if(person_to_meet[mid] < keyPerson){
            left = mid + 1;
        }
        else{
            right = mid - 1;
        }
    }
    // while(left <= right){
    //     int mid = (left + right)/2;
    //     cout<<"\n==DEBUG==\n";
    //     cout<<"LEFT: "<<left<<endl;
    //     cout<<"RIGHT: "<<right<<endl;
    //     cout<<"VALUE: "<<person_to_meet[mid]<<endl;
    // }
    if(!found){
        cout<<"Khong tim thay!\n";
        return;
    }
    writeLog("SEARCH PERSONAL BINARY");
}
//Binary search address
void Search_address_binary(){
    string keyAddress_Binary;
    cout<<"Nhap address can tim: ";
    cin.ignore();
    getline(cin, keyAddress_Binary);

    int left = 0;
    int right = stt -1;
    bool found = false;
    while (left <= right){
        int mid = (left + right)/2;
        if (address[mid] == keyAddress_Binary){
            cout<< "Find at STT: "<<mid<<endl;
            found = true;
            break;
        }
        else if(address[mid] < keyAddress_Binary){
            left = mid + 1;
        }
        else{
            right = mid -1;
        }
    }
    if(!found){
        cout<<"KHong tim thay!\n";
    }
    writeLog("SEARCH ADDRESS BINARY");

}


//Tim kiem dia chi thong tin cua su kien (value keyaddress)
// void search_address(){
//     bool found = false;
//     string keyaddress;
//     cout<<" Enter a word to search (address): ";
//     cin.ignore();
//     getline(cin, keyaddress);
//     if (keyaddress.empty()){
//         cout<<"Moi nhap thong tin vao\n";
//         return;
//     }
//     for(int i =0; i< stt; i++){
//         if(address[i].find(keyaddress) != string::npos){
//             cout<<" Match found at stt: "<< i << " Address: "<< address[i]<< endl;
//             found = true;
//     }
//     }
//     if (!found){
//         cout<<" No match found!"<<endl;
//         return;
//     }
// }
//Tim kiem email trong su kien (value keyemail)
// void search_email(){
//     bool found = false;
//     string keyemail;
//     cout<<" Enter a word to search (email): ";
//     cin.ignore();
//     getline(cin, keyemail);
//     if (keyemail.empty()){
//         cout<<"Moi nhap thong tin vao\n";
//         return;
//     }
//     for(int i =0; i<stt; i++){
//         if(email[i].find(keyemail) != string::npos){
//             cout<<" Match found at stt: "<< i << " Eamil: "<<email[i]<<endl;
//             found = true;
//     }
//     }
//     if(!found){
//         cout<<"Khong tim thay ket qua!"<<endl;
//         return;
//     }
// }

void SearchEmailBinary(){
    string keyEmail_Binary;
    cout<<"Nhap email can tim: ";
    cin.ignore();
    getline(cin, keyEmail_Binary);
    int left = 0;
    int right = stt -1;
    bool found = false;
    while(left <= right){
        int mid = (left + right)/2;

        if(email[mid] == keyEmail_Binary){
            cout<<"Find at STT: "<<mid << endl;
            found = true;
            break;
        }
        else if(email[mid] < keyEmail_Binary){
            left = mid + 1;
        }
        else{
            right = mid - 1;
        }
    }
    if(!found){
        cout<<"Khong tim that!\n";
    }
    writeLog("SEARCH EMAIL BINARY");
}
//Tim kiem trang thai (value keystate)
// void state_trangthai(){
//     bool found = false;
//     string keystate;
//     cout<<" Enter a word to search (state): ";
//     cin.ignore();
//     getline(cin, keystate);
//     if (keystate.empty()){
//         cout<<"Moi nhap thong tin vao\n";
//         return;
//     }
//     for(int i =0; i< stt; i++){
//         if (state[i].find(keystate) != string::npos){
//             cout<<"Match a found to stt: "<< i << " State: "<< state[i]<<endl;
//             found = true;
//     }
//     }
//     if(!found){
//         cout<<"Khong tim thay ket qua!\n";
//         return;
//     }
// }


//Thong ke theo bieu do
void Revenue(){
    if ( stt ==0 ){
         cout<< "Khong co du lieu!\n";
         return;
    }
    int tempRev[200];
    int tempIndex[200];
    for(int i = 0; i < stt; i++){
        tempRev[i] = statistics[i];
        tempIndex[i] = i;
    }
    for(int i =0; i < stt-1; i++){
        int maxIndex = i;
        for (int j = i + 1; j < stt; j++){
            if (tempRev[j] > tempRev[maxIndex]){
                maxIndex = j;
            }
        }
        int temp = tempRev[i];
        tempRev[i] = tempRev[maxIndex];
        tempRev[maxIndex] = temp;

        int temp2 = tempIndex[i];
        tempIndex[i] = tempIndex[maxIndex];
        tempIndex[maxIndex] = temp2;
    }
    for(int i =0; i < stt; i++){
        cout<<"STT: "<<tempIndex[i]<<" ";
        for(int j = 0; j < tempRev[i]/ 10; j++){
            cout<<"==";
        }
        cout<<" "<< tempRev[i];
        cout<<endl;
    }
    writeLog("REVENUE");
    cout<<"Revenue thanh cong!"<<endl;
}

int main(){
    int chosen;
    time_t now = time(nullptr);//lay tg thuc
    tm *currentTime = localtime(&now);//chuyen sang thoi gian cau truc tm
    cout<<"Ngay hien tai: " <<currentTime ->tm_mday<<"/"<<currentTime->tm_mon+1 <<"/"<<currentTime->tm_year+1900<< "\n"
    <<" Thoi gian thuc: "<< currentTime->tm_hour << ":"<<currentTime->tm_min<<":"<<currentTime->tm_sec<<endl;
    while(1){
        //validate.
        if (stt < 0 || stt >= 200){
            writeLog("ERROR" "INVALID INDEX");
            break;
        }
        if (stt < 0 || stt >= 200){
            cout<<"Ban chi co the them 100 su kien!"<< endl;
            break;
        }
        
        cout<< "\n=====Menu=====\n";
        cout<< "1. Them su kien\n";
        cout<< "2. In ra su kien\n";
        cout<< "3. Xoa su kien\n";
        cout<< "4. Chinh sua su kien\n";
        cout<< "5. Diem nguoc thoi gian cua su kien\n";
        cout<< "6. Sap xep su kien\n";
        cout<< "7. Tim kiem su kien\n";
        cout<< "8. Thong ke doanh thu su kien\n";
        cout<< "9. Uu tien ngay thang nam gio phut\n";
        cout<< "10. dequeue\n";
        cout<< "11. Xuat file .csv\n";
        cout<< "12. Unit test serach\n";
        cout<< "13. Log\n";
        cout<< "14. Search test\n"; 
        cout<< "0. Thoat\n";
        cout<<"Enter chosen: ";
        cin>> chosen;
        switch(chosen)
        {
        case 0:
            return 0;
        case 1:
        ADD();
        if(checkConflict){
            cout<<"\n[WARNING]";
            cout<<"CONFLICT EVENT!\n";
            writeLog("CONFLICT EVENT");
        }
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
            // search();
            int choise;
            cout<<"Nhung nguoi can gap: ";
            for(int i = 0; i < stt; i++){
            cout<<" Match found at stt: "<< i <<" Person to meet: "<< person_to_meet[i]<< endl;
            }
            cout<<"====Lua chon ====="<<endl;
            cout<<"1. Tim kiem address\n";
            cout<<"2. Tim kiem person to meet\n";
            cout<<"3. Tim kiem email\n";
            
            cin>>choise;
            
            switch (choise)
            {
            case 1:
                // search_address();
                Search_address_binary();
                break;
            case 2:
                // search_person_to_meet();
                searchPersonBinary();
                break;
            case 3:
                // search_email();
                SearchEmailBinary();
                break;
            default:
                cout<<"Moi nhap lai!";
                break;
            }
            break;
        case 8:
            Revenue();
            break;
        case 9:
            // PriorityDate();
            // int chon;
            // cout<<"1. High\n";
            // cout<<"2 .Medium\n";
            // cout<<"3 .Low\n";
            // cout<<"Chon: ";
            // cin>>chon;
            // string target;
            // switch (chon)
            // {
            // case 1:
            //     target = "High";
            //     break;
            // case 2:
            //     target = "Medium";
            //     break;
            // case 3:
            //     target = "Low";
            //     break;
            // default:
            //     cout<<"Khong hop le!\n";
            //     break;
            // }
            // bool found = false;
            // for(int i =00; i< stt; i++){
            //     if (priority[i] == target){
            //         cout<<"\n==========\n";
            //         cout<<"STT: "<< i<< endl;
            //         cout<<"Date: "<< day[i] << "/"<<month[i]<<"/"<<year[i]<<endl;
            //         cout<<"Time: "<< hour[i]<<":"<<minute[i]<<endl;
            //         cout<<"Description: "<<description[i]<<endl;
            //         cout<<"Priority: "<<priority[i]<<endl;
            //         found = true;
            //     }
            // }
            // if(!found){
            //     cout<<"Khong co event nao!\n";
            // }
            // break;
            // prioritycheck();
            // int chond;
            // cout<<"1. High\n";
            // cout<<"2. Medium\n";
            // cout<<"3. Low\n";
            // cout<<"Chon: ";
            // cin>>chond;
            // if (chond ==1){
            //     priorityValue("High");
            //     break;
            // }
            // else if(chond == 2){
            //     priorityValue("Medium");
            //     break;
            // }
            // else if(chond == 3){
            //     priorityValue("Low");
            //     break;
            // }
            // else{
            //     cout<<"Nhap lai!\n";
            //     break;
            // }
            // break;
            // priorityCheck();
            sortPriority();
            break;
        case 10:
            dequeueEvent();
            break;
        case 11:
            exportQueueCSV();
            break;
        case 12:
                    stt = 3;
                    day[0] = 10;
                    month[0] = 8;
                    year[0] = 2026;

                    day[1] = 5;
                    month[1] = 8;
                    year[1] = 2026;
                    
                    day[2] = 20;
                    month[2] = 8;
                    year[2] =2026;

                    sort();
                    if(day[0] = 5){
                        cout<<"Test pass!\n";
                    }
                    else{
                        cout<<"Test fail!\n";
                    }
                    break;
        case 13:
                    writeLog("REPORT");
                    break;
        case 14:
                    // testSearch();
                    
                    stt = 4;
                    person_to_meet[0] = "Thanh";
                    person_to_meet[1] = "Tuyen";
                    person_to_meet[2] = "Duc";
                    person_to_meet[3] = "Anh";

                    int left = 0;
                    int right = stt - 1;
                    int mid = (left + right)/2;
                    bool found = false;
                   

                    while(left <= right){
                        mid;
                        if(person_to_meet[mid] == person_to_meet[2]){
                            found = true;
                            break;
                        }
                        else if(person_to_meet[mid] < person_to_meet[2]) {
                            left = mid + 1;

                        }
                        else{
                            right = mid - 1;
                        }
                    }
                    if(found){
                        cout<<"[PASS] Tim thay"<<endl;
                    }
                    else{
                        cout<<"[FAIL] Khong tim thay "<< endl;
                    }
                    return 0;
                    break;
        
        
                }
         }
         return 0;
}
// string convertPriority(int chon){
//     switch (chon)
//     {
//     case 1:
//         return "High";
//     case 2:
//         return "Medium";
//     case 3:
//         return "Low";
    
//     default:
//         return "Inavlid";
//     }
// }
// void priorityCheck(){
//     int chon;
//     cout<<"1. High\n";
//     cout<<"2. Medium\n";
//     cout<<"3. Low\n";
//     cout<<"Chon: ";
//     string target = convertPriority(chon);
//     if(target == "Inavlid"){
//         cout<<"Khong hop le!\n";
//         return;
//     }
//     bool found = false;
//     for(int i =0; i<stt;i++){
//         if(priority[i] == target){
//             cout<<"\n===========\n";
//             cout<<"STT: "<<i<<endl;
//             cout<<"Date: "<< day[i]<<"/"<<month[i]<<'/'<<year[i]<<endl;
//             cout<<"Time: "<<hour[i]<<":"<<minute[i]<<endl;
//             cout<<"Priority: "<<priority[i]<<endl;
//             found = true;
//         }
//     }
//     if(!found){
//         cout<<"Khong co event nao!\n";
//     }
// }
//string priority test
// bool checkPriority(string p){
//     if(p == "High" || p =="Medium" || p == "Low"){
//         return true;
//     }
//     return false;
// }
//unit test

//test sort
// void testSort(){
//     stt = 3;
//     day[0] = 10;
//     month[0] = 8;
//     year[0] = 2026;

//     day[1] =5;
//     month[1] = 8;
//     year[1] = 2026;

//     day[2] = 20;
//     month[2] = 8;
//     year[2] = 2026;

//     sort();
//     if(day[0] == 5){
//         cout<<"TEST PASS\n";
//     }
//     else{
//         cout<<"TEST FAIL\n";
//     }
// }
//test binary search
void testSearch(){
    stt = 3;
    person_to_meet[0] = "An";
    person_to_meet[1] = "Binh";
    person_to_meet[2] = "Thanh";

    string keySera = "Binh";
    int left =0;
    int right = stt -1;
    bool found = false;

    while(left <= right){
        int mid = (left + right) /2;
        if(person_to_meet[mid] == keySera){
            found = true;
            break;
        }
        else if(person_to_meet[mid] < keySera){
            left = mid + 1;
        }
        else{
            right = mid - 1;
        }
    }
    if (found){
        cout<<"TEST PASS\n";
    }
    else{
        cout<<"TEST FAIL\n";
    }
}
//test conflict 
// void testconflict(){
//     stt = 1;
//     hour[0] = 14;
//     minute[0] =0;

//     duration[0] = 120;

//     hour[1] = 15;
//     minute[1] =0;
//     duration[1] = 30;

//     if(checkConflict()){
//         cout<<"TEST PASS\n";
//     }
//     else{
//         cout<<"TEST FAIL\n";
//     }
// }
// void prioritycheck(){
//     int chon;
//     cout<<"1. High\n";
//     cout<<"2 .Medium\n";
//     cout<<"3 .Low\n";
//     cout<<"Chon: ";
//     cin>>chon;
//     string target;
//     switch (chon)
//     {
//     case 1:
//         target = "High";
//         break;
//     case 2:
//         target = "Medium";
//         break;
//     case 3:
//         target = "Low";
//         break;
//     default:
//         cout<<"Khong hop le!\n";
//         break;
//     }
//     bool found = false;
//     for(int i =0; i< stt; i++){
//     if (priority[i] == target){
//         cout<<"\n==========\n";
//         cout<<"STT: "<< i<< endl;
//         cout<<"Date: "<< day[i] << "/"<<month[i]<<"/"<<year[i]<<endl;
//         cout<<"Time: "<< hour[i]<<":"<<minute[i]<<endl;
//         cout<<"Description: "<<description[i]<<endl;
//         cout<<"Priority: "<<priority[i]<<endl;
//         found = true;
//     }
//     }
//     if(!found){
//         cout<<"Khong co event nao!\n";
//     }
// }

bool validDay(int d){
    return d > 0 && d <= 31;
}
bool validMonth(int m){
    return m > 0 && m <= 12;
}
bool validHour(int h){
    return h >= 0 && h < 24;
}
bool validMinute(int m){
    return m >= 0 && m < 60;
}
void test(string name, bool result){
    if(result){
        cout<<"[PASS]"<< name<<endl;
    }
    else{
        cout<<"[FAIL]"<< name << endl;
    }
}

void testday_month_year_hour_minute(){
    test("Day = 15", validDay(15) == true);
    test("Day = 40", validDay(40) == false);

    test("Month = 5", validMonth(5) == true);
    test("Month = 15", validMonth(15) == false);

    test("Hour = 23", validHour(23) == true);
    test("Hour = 30", validHour(30) == false);

    test("Minute = 45", validMinute(45) == true);
    test("Minute = 70", validMinute(70) == false);
    return;
}
