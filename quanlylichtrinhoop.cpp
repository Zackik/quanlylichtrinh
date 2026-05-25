#include <iostream>
#include <string>
#include <ctime>
#include <queue>
#include <cmath>
#include <fstream>
using namespace std;
class quanly{
    private:
        int day[200], month[200], year[200], hour[200], minute[200], statistic[200],
         duration[200], q[200], front = 0, rear = -1, revenue[200], stt = 0;
        string description[200], address[200], person_to_meet[200],
         email[200], priority[200], category[200];
        const string places[7]= {"Sunday", "Monday", "Tuesday",
             "Webnesday", "Thursday", "Friday", "Saturday"};
        bool status[200];
    public:
        void add();
        void delet();
        void log(string action);
        void edit();
        void exportQueueCSV();
        void checkConflict();
        void display();
        int priorityValue(string p);
        void sort();
        void search();
        void countDown();
        int startMinute(int i);
        int endMinute(int i);
        void sortPriority();

        ~quanly() = default;
};
void quanly::sort(){
    cout<<"=====================\n";
    cout<<"=======SORT=========\n";
    int minIndex = 0;
    for(int i = 0; i< stt -1; i++){
        minIndex = i;
        for(int j =i + 1; j < stt; j++){
            if (year[j] < year[minIndex] || (year[j] == year[minIndex] && month[j]  < month[minIndex])
            || (year[j] == year[minIndex] && month[j] == month[minIndex] && day[j]< day[minIndex]) || 
            (year[j] == year[minIndex] && month[j] == month[minIndex] && day[j] == day[minIndex] && hour[j] < hour[minIndex]) || 
            (year[j] == year[minIndex] && month[j] == month[minIndex] && day[j] == day[minIndex] && hour[j] == hour[minIndex] && minute[j] < minute[minIndex])){
                minIndex = j;
            }
        }
        if(minIndex != i){
            swap(person_to_meet[i], person_to_meet[minIndex]);
                    swap(day[i], day[minIndex]); swap(month[i], month[minIndex]);
                    swap(year[i],year[minIndex]); swap(hour[i], hour[minIndex]);
                    swap(minute[i], minute[minIndex]); swap(description[i], description[minIndex]);
                    swap(address[i], address[minIndex]); swap(email[i], email[minIndex]);
                    swap(status[i], status[minIndex]); swap(priority[i], priority[minIndex]);
                    swap(category[i], category[minIndex]); swap(duration[i], duration[minIndex]);
                    swap(statistic[i], statistic[minIndex]);
        }
    }
    log("SORT EVENT");
    cout<<"SORT SUCCESSFULLY!"<<endl;
}
//Tim kiem ten cua persontomeet, email, address voi binary sort va sort de sap xep truoc xong moi tim kiem tranh sai xot trong thuat toan 
void quanly::search(){
    int chonsearch;
    cout<<"\n===============\n";
    cout<<"======SEARCH========\n";
    cout<<"1. Person to meet\n";
    cout<<"2. Email\n";
    cout<<"3. Address\n";
    cout<<"Chon search: "; cin>>chonsearch;
    if(chonsearch == 1){
        for(int i = 0; i< stt -1; i++){
            for(int j = i+1; j <stt; j++){
                if(person_to_meet[j] < person_to_meet[i]){
                    swap(person_to_meet[i], person_to_meet[j]);
                    swap(day[i], day[j]); swap(month[i], month[j]);
                    swap(year[i],year[j]); swap(hour[i], hour[j]);
                    swap(minute[i], minute[j]); swap(description[i], description[j]);
                    swap(address[i], address[j]); swap(email[i], email[j]);
                    swap(status[i], status[j]); swap(priority[i], priority[j]);
                    swap(category[i], category[j]); swap(duration[i], duration[j]);
                    swap(statistic[i], statistic[j]);
                }
            }
        }
        int left = 0, right = stt -1;
        string key;
        bool found = false;
        cout<<"Nhap ten can tim: "; 
        cin.ignore();
        getline(cin, key);
        while (left <= right)
        {
            int mid = (left + right)/2;
            if(person_to_meet[mid] == key){
                cout<<"\n===SEARCH====\n";
                cout<<"STT: "<<mid<<endl;
                cout<<"Description: "<<description[mid]<< endl;
                cout<<"Address: "<<address[mid]<<endl;
                cout<<"Email: "<<email[mid]<<endl;
                found = true;
                break;
            }
            if(person_to_meet[mid] < key){
                left = mid + 1;
            }
            else{
                right = mid - 1;
            }
            
        }
        log("SEARCH PERSON TO MEET");
        cout<<"Khong tim thay!\n";
        return;
    }
    else if(chonsearch == 2){
        for(int i =0; i <stt -1; i++){
            for(int j = i+ 1; j <stt; j++){
                if(email[j] < email[i]){
                    swap(person_to_meet[i], person_to_meet[j]);
                    swap(day[i], day[j]); swap(month[i], month[j]);
                    swap(year[i],year[j]); swap(hour[i], hour[j]);
                    swap(minute[i], minute[j]); swap(description[i], description[j]);
                    swap(address[i], address[j]); swap(email[i], email[j]);
                    swap(status[i], status[j]); swap(priority[i], priority[j]);
                    swap(category[i], category[j]); swap(duration[i], duration[j]);
                    swap(statistic[i], statistic[j]);
                }
            }
        }
        int left = 0, right = stt -1;
        string key;
        bool found = false;
        cout<<"Nhap email can tim: "; 
        cin.ignore();
        getline(cin, key);
        while (left <= right)
        {
            int mid = (left + right)/2;
            if(email[mid] == key){
                cout<<"\n===SEARCH====\n";
                cout<<"STT: "<<mid<<endl;
                cout<<"Description: "<<description[mid]<< endl;
                cout<<"Address: "<<address[mid]<<endl;
                cout<<"Email: "<<email[mid]<<endl;
                found = true;
                break;
            }
            if(email[mid] < key){
                left = mid + 1;
            }
            else{
                right = mid - 1;
            }
            
        }
        log("SEARCH EMAIL");
        cout<<"Khong tim thay!\n";
        return;
    }
    else if(chonsearch == 3){
        for(int i = 0; i < stt -1; i++){
            for(int j = i + 1; j < stt; j++){
                if(address[j]< address[i]){
                    swap(person_to_meet[i], person_to_meet[j]);
                    swap(day[i], day[j]); swap(month[i], month[j]);
                    swap(year[i],year[j]); swap(hour[i], hour[j]);
                    swap(minute[i], minute[j]); swap(description[i], description[j]);
                    swap(address[i], address[j]); swap(email[i], email[j]);
                    swap(status[i], status[j]); swap(priority[i], priority[j]);
                    swap(category[i], category[j]); swap(duration[i], duration[j]);
                    swap(statistic[i], statistic[j]);
                }
            }
        }
        int left = 0, right = stt -1;
        string key;
        bool found = false;
        cout<<"Nhap address can tim: "; 
        cin.ignore();
        getline(cin, key);
        while (left <= right)
        {
            int mid = (left + right)/2;
            if(address[mid] == key){
                cout<<"\n===SEARCH====\n";
                cout<<"STT: "<<mid<<endl;
                cout<<"Description: "<<description[mid]<< endl;
                cout<<"Address: "<<address[mid]<<endl;
                cout<<"Email: "<<email[mid]<<endl;
                found = true;
                break;
            }
            if(address[mid] < key){
                left = mid + 1;
            }
            else{
                right = mid - 1;
            }
            
        }
        log("SEARCH ADDRESS ");
        cout<<"Khong tim thay!\n";
        return;
    }

}
//sap xep prioriry theo so nho nhat vi so 1 la HIGH, 2 la MEDIUM, 3 la LOW
void quanly::sortPriority(){
    for(int i = 0; i< stt- 1; i++){
        int minIndex = i;
        for(int j = i + 1; j <stt; j++){
            if(priorityValue(priority[j]) < priorityValue(priority[minIndex])){
                minIndex = j;
            }
        }
        if(minIndex != i){
            int temp;
            temp = year[i]; year[i] = year[minIndex]; year[minIndex] = temp;
            temp = month[i]; month[i] = month[minIndex]; month[minIndex] = temp;
            temp = day[i]; day[i] = day[minIndex]; day[minIndex] = temp;
            temp = hour[i]; hour[i] = hour[minIndex]; hour[minIndex] = temp;
            temp = minute[i]; minute[i] = minute[minIndex]; minute[minIndex] = temp;
            temp = duration[i]; duration[i] = duration[minIndex]; duration[minIndex] = temp;
            temp = status[i]; status[i] = status[minIndex]; status[minIndex] = temp;
            temp = statistic[i]; statistic[i] = statistic[minIndex]; statistic[minIndex] = temp;
            string tempStr;
            tempStr = description[i]; description[i]= description[minIndex]; description[minIndex] = tempStr;
            tempStr = address[i]; address[i] = address[minIndex]; address[minIndex] = tempStr;
            tempStr = person_to_meet[i]; person_to_meet[i] = person_to_meet[minIndex]; person_to_meet[minIndex] = tempStr;
            tempStr = email[i]; email[i] = email[minIndex]; email[minIndex] = tempStr;
            tempStr = priority[i]; priority[i]= priority[minIndex]; priority[minIndex] = tempStr;
            tempStr = category[i]; category[i] = category[minIndex]; category[minIndex] = tempStr;
        }
        cout<<"Swap"<<i<<"<->"<<minIndex<<endl;
    }
    log("SORT PRIORITY");
    cout<<"SORT PRIORITY SUCCESSFULLY!"<<endl;
}
// Chuyen priority string sang int voi bang so 1,2,3 va in ra priority
int quanly::priorityValue(string p){
    if(p == "HIGH") return 1;
    if(p == "MEDIUM") return 2;
    if(p == "LOW") return 3;
    bool found = false;
    if(1){
        for(int i = 0; i<stt; i++){
            cout<<"===============\n";
            cout<<"STT: "<<i<<endl;
            cout<<"Date: "<< day[i]<<"/"<<month[i]<<"/"<<year[i]<<endl;
            cout<<"Time: "<<hour[i]<<" : "<<minute[i]<<endl;
            cout<<"Priority: "<<priority[i]<<endl;
            found = true; 
        }
    }
    if(!found) cout<<"Khong co event nao!"<<endl;
    return 0;
}
//IN ra cac thong tin trong su kien khi in ra
void quanly::display(){
    cout<<"=======================\n";
    cout<<"=======DISPLAY=========\n";
    if(stt < 0 || stt >= 200) cout<<"Khong the in ra neu khong co stt va stt lon hon 200"; return;
    for(int i =0; i<stt; i++){
        int m = month[i], n = year[i], d = day[i], a = (14 -m)/ 12, y = n - a, mon = m + 12*a -2, 
        dayofweek = (d + y + y/4 - y/100 + y/400 + (31 * mon)/12)%7;
        cout<<"STT: "<<i<< "-->"<<hour[i]<<" : "<<minute[i]<<" "<< day[i]<<"/"<<month[i]<<"/"<<year[i]<< "\n";
        cout<<"Thu: "<<places[dayofweek]<<" "<<"Description: "<<description[i]<<" "<<" Address: "<<address[i]<< "\n";
        cout<<"Person to meet: "<<person_to_meet[i]<< " "<<"Email: "<<email[i]<<endl;
        cout<<"State: "<<status[i]<< " "<< "Priority: "<<priority[i]<<" "<<"Category: "<<category[i]<<endl;
    }
}
// Kiem tra se thong tin co bi trung hay khong va nguoc lai
void quanly::checkConflict(){
    bool kt = false;
    int newStart = startMinute(stt), newEnd = endMinute(stt);
    for(int i =0; i<stt; i++){
        if(day[i] == day[stt] && month[i] == month[stt] && year[i] == year[stt]){
            int oldStart = startMinute(i), oldEnd = endMinute(i);
            if(newStart < oldEnd && newStart > oldStart) kt = true;
        }
    }
    kt = false;
}
int quanly::startMinute(int i){
    return hour[i] * 60 + minute[i];
}
int quanly::endMinute(int i){
    return startMinute(i) + duration[i];
}
// Export thong tin va kiem tra front va rear theo thong tin cua queue 
void quanly::exportQueueCSV(){
    cout<<"===================\n";
    cout<<"=======EXPORT=======\n";
    if(front > rear) cout<<"Queue rong!"; return;
    ofstream file("EVENT.csv");
    if(!file.is_open()) cout<<"Khong mo duoc file!"; return;
    file<<"QueueOrder "<< " DATE   "<<" TIME   "<<" DESCRIPTION   "<<" PRIORITY   "<<" STATUS   "<<endl;
    int order =1;
    for(int i = front; i <= rear; i++){
        int index = q[i];
        string state = status[index] ? "Done":"Pending";
        string date = to_string(day[index]) + "/" + to_string(month[index]) + "/" + to_string(year[index]);
        string timeStr;
        if(hour[index] < 10) timeStr += "0";
        timeStr += to_string(hour[index]);
        timeStr += " : ";
        if(minute[index] < 10) timeStr += "0";
        timeStr += to_string(minute[index]);
        file<< order<<"   "<< "\""<< date<< "\""<< "   "<<"\""<<timeStr<<"\""<<"   "<<"\""<<description[index]<<"\""<<"   "<<"\""<<priority[index]<<"\""<<"   "<< "\""<<state<<"\""<<endl;
        order++;
    }
    file.close();
    log("EXPORT QUEUE CSV");
    cout<<"EXPORT SUCCESSFULLY!"<<endl;
}
//Sua thong tin su kien voi chi sua thong tin chi tiet cua cac menu da in ra san khi thanh cong se in ra successfully
void quanly::edit(){
    int index, luachon;
    cout<<"===================\n";
    cout<<"=====LUACHON========\n";
    cout<<"1. Sua ngay\n";
    cout<<"2. Sua thang\n";
    cout<<"3. Sua nam\n";
    cout<<"4. Sua gio\n";
    cout<<"5. Sua phut\n";
    cout<<"6. Sua description\n";
    cout<<"7. Sua address\n";
    cout<<"8. Sua person to meet\n";
    cout<<"9. Sua email\n";
    cout<<"10. Sua state\n";
    cout<<"LUACHON: ";
    cin>>luachon;
    cout<<endl;
    cout<<"Nhap index need delete: ";
    cin>>index;
    if(index < 0 || index >= stt) cout<<"Sai stt!\n"; return;
    switch (luachon)
    {
    case 1:
        cout<<"Sua ngay: ";
        cin>>day[index];
        if(day[index] < 0|| day[index] >= 33) cout<<"Moi nhap lai ngay!"; return;
        break;
    case 2:
        cout<<"Sua thang: ";
        cin>>month[index];
        if(month[index] < 0||month[index] >= 13) cout<<"Moi nhap lai thang!"; return;
        break;
    case 3:
        cout<<"Sua nam: ";
        cin>>year[index];
        if(year[index] <0000) cout<<"Moi nhap lai nam!"; return;
        break;
    case 4:
        cout<<"Sua gio: ";
        cin>>hour[index];
        if(hour[index] < 0 || hour[index] >= 24) cout<<"Moi nhap lai gio!"; return;
        break;
    case 5:
        cout<<"Sua description: "; getline(cin, description[index]);
        break;
    case 6:
        cout<<"Sua phut: ";
        cin>>minute[index];
        if(minute[stt] < 0 || minute[stt] >= 60) cout<<"Moi nhap lai phut!"; return;
        break;
    case 7:
        cout<<"Sua address: ";
        cin>>address[index];
        break;
    case 8: 
        cout<<"Sua person to meet: "; getline(cin, person_to_meet[index]); 
        break;
    case 9:
        cout<<"Sua email: "; getline(cin, email[index]);
        break;
    case 10:
        cout<<"Sua status: "; cin>>status[index];
        break;
    default:
        cout<<"Moi chon lai!"; return;
    }
    log("EDIT EVENT");
    cout<<"EDIT SUCCESSFULLY!"<<endl;
}
//Ghi lai cac su kien ma khong the sua lai qua khu cua log no se ghi lai thong tin khi nhap vao va nhap tong tin su kien
void quanly::log(string action){
    ofstream file("log.txt", ios::app);
    time_t now = time(0);
    tm *current = localtime(&now);
    file <<"["<<current->tm_mday << "/"<<current->tm_mon + 1<<"/"<<current->tm_year + 1900<< " "<<
    current->tm_hour<<" : "<< current->tm_min<<"]"<<action<<endl;
    file.close();
}
//Xoa su kien theo lua chon cua su kien muon xoa va cong don thanh cong se in ra successfully
void quanly::delet(){
    int index;
    cout<<"Nhap stt need delete: "; cin>>index;
    if(index < 0 || index >= stt) cout<<"Sai stt!\n"; return;
    for(int i = index; i< stt - 1; i++){
        day[i] = day[i + 1]; month[i] = month[i + 1]; year[i] = year[i + 1]; hour[i] = hour[i + 1]; minute[i] = minute[i + 1];
        description[i] = description[i + 1]; email[i] = email[i + 1]; person_to_meet[i] = person_to_meet[i + 1]; duration[i] =duration[i + 1];
        status[i] = status[i + 1]; category[i] = category[i + 1];
    }
    stt--;
    log("DELETE EBENT");
    cout<<"DELETE SUCCESSFULLY INDEX: "<<index<<endl;
}
//Them su kien voi cac phuong thuc theo dinh dang cu the va se in ra successfully khi thanh cong va neu nhap sai se in lai thong tin
void quanly::add(){
    char c1, c2, c3;
    cout<< "Nhap them su kien theo dinh dang (hh:mm dd/mm/yyyy): "<< endl;
    cin >> hour[stt]>>c1>>minute[stt]>>day[stt]>>c2>>month[stt]>>c3>>year[stt];
    if(day[stt] < 0 || day[stt] > 31){
        cout<<"Moi nhap lai!"<< endl; return;
    }
    if(month[stt] < 0 || month[stt] >= 13){
        cout<<"Moi nhap lai!"<<endl; return;
    }
    if(hour[stt]< 0 || hour[stt] >23){
        cout<<"Moi nhap lai!"<<endl; return;
    }
    if(minute[stt]< 0|| minute[stt]>59){
        cout<<"Moi nhap lai!"<<endl; return;
    }
    cout<<"===================\n";
    cout<<"Duration: ";
    cin>>duration[stt];
    cin.ignore();
    cout<<"===================\n";
    cout<<"Nhap description: ";
    getline(cin, description[stt]);

    cout<<"====================\n";
    cout<<"Nhap address:";
    getline(cin, address[stt]);

    cout<<"====================\n";
    cout<<"Nhap person_to_meet: ";
    getline(cin, person_to_meet[stt]);

    int chonn;
    cout<<"\n======STATUS======\n";
    cout<<"0. Pending"<<endl;
    cout<<"1. Done"<<endl;
    cout<<"2. Canceled"<<endl;
    cout<<"Chon STATUS: ";
    cin>>chonn;
    if(chonn == 0 || chonn == 1 || chonn == 2){
        switch (chonn)
        {
        case 0:
            status[stt] = "Pending";
            break;
        case 1:
            status[stt] = "Done";
            break;
        default:
            status[stt] = "Canceled";
            break;
        }
    }
    else{
        cout<<"Moi nhap lai!"<<endl; return;
    }

    cout<<"============\n";
    cout<<"======DOANH THU=======\n";
    cout<<"Nhap doanh thu(USD): "; cin>>statistic[stt];

    int chonpriority;
    cout<<"===================\n";
    cout<<"======PRIORITY=========\n";
    cout<<"1. HIGH\n";
    cout<<"2. MEDIUM\n";
    cout<<"3. LOW\n";
    cout<<"Chon Priority: ";
    cin>>chonpriority;
    switch (chonpriority)
    {
    case 1:
        priority[stt] = "HIGH";
        break;
    case 2:
        priority[stt] = "MEDIUM";
        break;
    case 3:
        priority[stt] = "LOW";
        break;
    default:
        priority[stt] = "LOW";
        break;
    }

    int choncategory;
    cout<<"===============\n";
    cout<<"=====CATEGORY=====\n";
    cout<<"1. WORK\n";
    cout<<"2 .STUDY\n";
    cout<<"3. PERSON TO MEET\n";
    cout<<"4.MEETING\n";
    cout<<"5.HEALTH\n";
    cout<<"CHON CATEGORY: ";
    cin>> choncategory;
    switch (choncategory)
    {
    case 1:
        category[stt] = "WORK";
        break;
    case 2:
        category[stt] = "STUDY";
        break;
    case 3:
        category[stt] = "PERSON TO MEET";
        break;
    case 4:
        category[stt] = "MEETING";
        break;
    case 5:
        category[stt] = "HEALTH";
        break;
    default:
        category[stt] = "PERSON TO MEET";
        break;
    }
    int m = month[stt], n = year[stt], d = day[stt], a = (14 - m)/12, y = (n - a), mon = m + 12*a -2, dayofweek = (d + y + y/4 - y/100 + y/400 + (31 * mon)/12)%7;
    places[dayofweek];
    cout<<"Thu: "<< places[dayofweek]<<endl;


    tm cd = {};
    cd.tm_mday = day[stt];
    cd.tm_mon = month[stt] - 1;
    cd.tm_year = year[stt] - 1900;
    cd.tm_hour = hour[stt];
    cd.tm_min = minute[stt];

    time_t timet = mktime(&cd);
    time_t now = time(0);

    double diff = difftime(timet, now);
    if(diff <= 0){
        cout<< "Da qua!\n"; return;
    }
    int k = abs(diff/(60*60*24));
    diff = abs(diff - (k * (60 * 60 * 24)));

    int h = abs(diff / (60*60));
    diff = abs(diff - (h *(60 * 60)));

    int p = abs(diff/60);
    cout<<"Thoi gian con lai: "<<" Ngay: "<<k<<" gio: "<<h<<" phut: "<<p<<endl;
    
    stt++;
    rear++;
    q[rear] = stt;
    log("ADD EVENT");
    cout<<"ADD SUCCESSFULLY!"<<endl;
}
int main(){
    while(true){
        quanly p;
        p.add();
        p.checkConflict();
    }
    return 0;
}