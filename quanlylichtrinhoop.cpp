#include <iostream>
#include <string>
#include <ctime>
#include <queue>
#include <cmath>
#include <fstream>
#include <iomanip>
#include <vector>
#include <algorithm>
using namespace std;
class Event{
    // private:
    //     int day;
    //     int month;
    //     int year;

    //     int hour;
    //     int minute;
    //     int statistic;
    //     int duration;

    //     string description;
    //     string address;
    //     string person_to_meet;
    //     string email;

    //     string priority;
    //     string category;
    //     string status;

    public: 
        int day;
        int month;
        int year;

        int hour;
        int minute;
        int statistic;
        int duration;

        string description;
        string address;
        string person_to_meet;
        string email;

        string priority;
        string category;
        string status;

        virtual void display(){
            cout<<description<<endl;
        }
        virtual ~Event(){}
};
//da hinh cua display()
class MeetingEvent : public Event {
    public: 
        string meettingRoom;
        void display() override{
            cout<<"[MEETING] "<<description<<endl;
        }
};
//da hinh
class StudyEvent : public Event{
    public:
        string subject;
        void display() override{
            cout<<"[STUDY] "<<description<<endl;
        }
};
class quanly{
    private:
        Event events[200];//static
        //vector<Event> events;
        const string places[7]= {"Sunday", "Monday", "Tuesday",
             "Wednesday", "Thursday", "Friday", "Saturday"};
        string status[200];
        int q[200];
        int front = 0;
        int rear = -1;
        int stt = 0;
        //queue<int> eventQueue;
        //eventQueue.push(index);
        //eventQueue.pop();
        //eventQueue.front();
    public:
        void add();
        void delet();
        void log(string action);
        void edit();
        void exportQueueCSV();
        bool checkConflict();
        void display();
        int priorityValue(string p);
        void sort();
        void search();
        void countDown();
        int startMinute(int i);
        int endMinute(int i);
        void sortPriority();
        void commitAdd();
        void clear(int i);
        ~quanly(){
            cout<<"\nCam on da su dung chuong trinh!\n";
        }
};
//clear lai code lam cac bien thanh 0 va rong
void quanly::clear(int i){
    events[i].day = 0;
    events[i].month = 0;
    events[i].year = 0;
    events[i].hour =0;
    events[i].minute = 0;
    events[i].duration =0;
    events[i].description = ""; events[i].address = "";
    events[i].person_to_meet = ""; events[i].email = ""; events[i].priority = ""; events[i].category = "";
    events[i].status = false;
}
//Gan vao mang khi thanh cong va khong mac loi sai ky tu va nhap sai form
void quanly::commitAdd(){
    q[++rear] = stt;
    stt++;
    log("ADD EVENT");
    cout<<"ADD SUCCESSFULLY!\n";
}
//sap xep thu tu selection sort
void quanly::sort(){
    //STL
    cout<<"=====================\n";
    cout<<"=======SORT=========\n";
    int minIndex = 0;
    for(int i = 0; i< stt -1; i++){
        minIndex = i;
        for(int j =i + 1; j < stt; j++){
            if (events[j].year < events[minIndex].year || (events[j].year == events[minIndex].year && events[j].month  < events[minIndex].month)
            || (events[j].year == events[minIndex].year && events[j].month == events[minIndex].month && events[j].day < events[minIndex].day) || 
            (events[j].year == events[minIndex].year && events[j].month == events[minIndex].month && events[j].day == events[minIndex].day && events[j].hour < events[minIndex].hour) || 
            (events[j].year == events[minIndex].year && events[j].month == events[minIndex].month && events[j].day == events[minIndex].day && events[j].hour == events[minIndex].hour && events[j].minute < events[minIndex].minute)){
                minIndex = j;
            }
        }
        if(minIndex != i){
            swap(events[i], events[minIndex]);
        }
    }
    //complexity o(n^2)
    
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
                if(events[j].person_to_meet < events[i].person_to_meet){
                    swap(events[i], events[j]);
                }
            }
        }
        for(int i = 0; i< stt; i++){
            cout<<"";
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
            if(events[mid].person_to_meet == key){
                cout<<"\n===SEARCH====\n";
                cout<<"STT: "<<mid<<endl;
                cout<<"Description: "<< events[mid].description << endl;
                cout<<"Address: "<< events[mid].address<<endl;
                cout<<"Email: "<< events[mid].email<<endl;
                found = true;
                break;
            }
            if(events[mid].person_to_meet < key){
                left = mid + 1;
            }
            else{
                right = mid - 1;
            }
            
        }
        if(!found){
            cout<<"Khong tim thay!\n";
        }
        log("SEARCH PERSON TO MEET");
        return;
    }
    else if(chonsearch == 2){
        for(int i =0; i <stt -1; i++){
            for(int j = i+ 1; j <stt; j++){
                if(events[j].email < events[i].email){
                    swap(events[i], events[j]);
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
            if(events[mid].email == key){
                cout<<"\n===SEARCH====\n";
                cout<<"STT: "<<mid<<endl;
                cout<<"Description: "<<events[mid].description<< endl;
                cout<<"Address: "<<events[mid].address<<endl;
                cout<<"Email: "<<events[mid].email<<endl;
                found = true;
                break;
            }
            if(events[mid].email < key){
                left = mid + 1;
            }
            else{
                right = mid - 1;
            }
            
            
        }
        if(!found){
            cout<<"Khong tim thay!\n";
        }
        log("SEARCH EMAIL");
        return;
    }
    else if(chonsearch == 3){
        //sort truoc de sap xep
        for(int i = 0; i < stt -1; i++){
            for(int j = i + 1; j < stt; j++){
                if(events[j].address< events[i].address){
                    swap(events[i], events[j]);
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
            if(events[mid].address == key){
                cout<<"\n===SEARCH====\n";
                cout<<"STT: "<<mid<<endl;
                cout<<"Description: "<<events[mid].description<< endl;
                cout<<"Address: "<<events[mid].address<<endl;
                cout<<"Email: "<<events[mid].email<<endl;
                found = true;
                break;
            }
            if(events[mid].address < key){
                left = mid + 1;
            }
            else{
                right = mid - 1;
            }
            
        }
        if(!found){
            cout<<"KHong tim thay!\n";
        }

        log("SEARCH ADDRESS ");
        return;
    }

}
//sap xep prioriry theo so nho nhat vi so 1 la HIGH, 2 la MEDIUM, 3 la LOW
void quanly::sortPriority(){
    for(int i = 0; i< stt- 1; i++){
        int minIndex = i;
        for(int j = i + 1; j <stt; j++){
            if(priorityValue(events[j].priority) < priorityValue(events[minIndex].priority)){
                minIndex = j;
            }
        }
        if(minIndex != i){
            //co them chuyen thanh function de swap
            int temp;
            temp = events[i].year; events[i].year = events[minIndex].year; events[minIndex].year = temp;
            temp = events[i].month; events[i].month = events[minIndex].month; events[minIndex].month = temp;
            temp = events[i].day; events[i].day = events[minIndex].day; events[minIndex].day = temp;
            temp = events[i].hour; events[i].hour = events[minIndex].hour; events[minIndex].hour = temp;
            temp = events[i].minute; events[i].minute = events[minIndex].minute; events[minIndex].minute = temp;
            temp = events[i].duration; events[i].duration = events[minIndex].duration; events[minIndex].duration = temp;
            
            temp = events[i].statistic; events[i].statistic = events[minIndex].statistic; events[minIndex].statistic = temp;
            string tempStr;
            tempStr = events[i].description; events[i].description= events[minIndex].description; events[minIndex].description = tempStr;
            tempStr = events[i].address; events[i].address = events[minIndex].address; events[minIndex].address = tempStr;
            tempStr = events[i].person_to_meet; events[i].person_to_meet = events[minIndex].person_to_meet; events[minIndex].person_to_meet = tempStr;
            tempStr = events[i].email; events[i].email = events[minIndex].email; events[minIndex].email = tempStr;
            tempStr = events[i].priority; events[i].priority= events[minIndex].priority; events[minIndex].priority = tempStr;
            tempStr = events[i].category; events[i].category = events[minIndex].category; events[minIndex].category = tempStr;
            tempStr = events[i].status; events[i].status = events[minIndex].status; events[minIndex].status = tempStr;
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
    return 3;
    bool found = false;
    if(1){
        for(int i = 0; i<stt; i++){
            cout<<"===============\n";
            cout<<"STT: "<<i<<endl;
            cout<<"Date: "<< events[i].day<<"/"<<events[i].month<<"/"<<events[i].year<<endl;
            cout<<"Time: "<<events[i].hour<<" : "<< events[i].minute<<endl;
            cout<<"Priority: "<<events[i].priority<<endl;
            found = true; 
        }
    }
    if(!found) cout<<"Khong co event nao!"<<endl;
    return 0;
}
//IN ra cac thong tin trong su kien khi in ra
void quanly::display(){
    //stt == 0 khong co su kien
    if(stt == 0){
        cout<<"Khong co su kien nao!\n";
        return;
    }

    cout<<"\n========== EVENT LIST ==========\n";
    //in ra thu ngay thang
    for(int i = 0; i < stt; i++){

        int m = events[i].month;
        int y = events[i].year;
        int d = events[i].day;

        int a = (14 - m) / 12;
        int yy = y - a;
        int mon = m + 12 * a - 2;
        //tim thu
        int dayOfWeek =
            (d + yy + yy/4 - yy/100 + yy/400 +
            (31 * mon)/12) % 7;

        cout<<"\n---------------------------------\n";
        cout<<"STT        : "<<i<<endl;
        cout<<"Date       : "
            <<events[i].day<<"/"
            <<events[i].month<<"/"
            <<events[i].year
            <<" ("<<places[dayOfWeek]<<")\n";

        cout<<"Time       : "
            <<events[i].hour<<":"
            <<events[i].minute<<endl;

        cout<<"Description: "
            <<events[i].description<<endl;

        cout<<"Address    : "
            <<events[i].address<<endl;

        cout<<"Meet       : "
            <<events[i].person_to_meet<<endl;

        cout<<"Email      : "
            <<events[i].email<<endl;

        cout<<"Priority   : "
            <<events[i].priority<<endl;

        cout<<"Category   : "
            <<events[i].category<<endl;

        cout<<"Status     : "
            <<status[i]<<endl;
    }

    cout<<"\n===============================\n";
}
// Kiem tra se thong tin co bi trung hay khong va nguoc lai
bool quanly::checkConflict(){
    int newStart = startMinute(stt), newEnd = endMinute(stt);
    for(int i =0; i<stt; i++){
        if(events[i].day == events[stt].day && events[i].month == events[stt].month && events[i].year == events[stt].year){
            int oldStart = startMinute(i), oldEnd = endMinute(i);
            if(newStart < oldEnd && newEnd > oldStart){
                cout<<"\n=============\n";
                cout<<"Trung voi su kien STT "<<i<<endl;
                return true;
            }
        }
    }
    return false;
}
//thooi gian bat dau cua sk chuyen gio thanh p
int quanly::startMinute(int i){
    return events[i].hour * 60 + events[i].minute;
}
//them timestart va cong duration
int quanly::endMinute(int i){
    return startMinute(i) + events[i].duration;
}
// Export thong tin va kiem tra front va rear theo thong tin cua queue 
void quanly::exportQueueCSV(){
    cout<<"===================\n";
    cout<<"=======EXPORT=======\n";
    if(front > rear){
        cout<<"Queue rong!"; 
        return;
    }
    ofstream file("EVENT.csv");
    if(!file.is_open()){ 
        cout<<"Khong mo duoc file!";
        return;
    }
    file<<"QueueOrder "<< " DATE   "<<" TIME   "<<" DESCRIPTION   "<<" PRIORITY   "<<" STATUS   "<<endl;
    int order =1;
    for(int i = front; i <= rear; i++){
        int index = q[i];
        string state = (status[index]=="Done") ? "Done":"Pending";
        string date = to_string(events[index].day) + "/" + to_string(events[index].month) + "/" + to_string(events[index].year);
        string timeStr;
        if(events[index].hour < 10) timeStr += "0";
        timeStr += to_string(events[index].hour);
        timeStr += " : ";
        if(events[index].minute < 10) timeStr += "0";
        timeStr += to_string(events[index].minute);
        file<< order<<"   "<< "\""<< date<< "\""<< "   "<<"\""<<timeStr<<"\""<<"   "<<"\""<<events[index].description<<"\""<<"   "<<"\""<<events[index].priority<<"\""<<"   "<< "\""<<state<<"\""<<endl;
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
    if(index < 0 || index >= stt){ 
        cout<<"Sai stt!\n"; return;
    }
    switch (luachon)
    {
    case 1:
        cout<<"Sua ngay: ";
        cin>>events[index].day;
        if(events[index].day < 0|| events[index].day >= 33){ 
            cout<<"Moi nhap lai ngay!"; return;
        }
        break;
    case 2:
        cout<<"Sua thang: ";
        cin>>events[index].month;
        if(events[index].month < 0|| events[index].month >= 13) 
        {
            cout<<"Moi nhap lai thang!"; 
            return;
        }

        break;
    case 3:
        cout<<"Sua nam: ";
        cin>>events[index].year;
        if(events[index].year <0000) {
            cout<<"Moi nhap lai nam!"; return;
        }
        break;
    case 4:
        cout<<"Sua gio: ";
        cin>>events[index].hour;
        if(events[index].hour < 0 || events[index].hour >= 24) {cout<<"Moi nhap lai gio!"; return;}
        break;
    case 5:
        cout<<"Sua description: "; getline(cin, events[index].description);
        break;
    case 6:
        cout<<"Sua phut: ";
        cin>>events[index].minute;
        if(events[stt].minute < 0 || events[stt].minute >= 60) {cout<<"Moi nhap lai phut!"; return;}
        break;
    case 7:
        cout<<"Sua address: ";
        cin>>events[index].address;
        break;
    case 8: 
        cout<<"Sua person to meet: "; getline(cin, events[index].person_to_meet); 
        break;
    case 9:
        cout<<"Sua email: "; getline(cin, events[index].email);
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
    file << "[" 
     << setw(2) << setfill('0') << current->tm_mday << "/"
     << setw(2) << current->tm_mon + 1 << "/"
     << current->tm_year + 1900
     << " "
     << setw(2) << current->tm_hour << ":"
     << setw(2) << current->tm_min
     << "] "
     << action << endl;
    file.close();
}
//Xoa su kien theo lua chon cua su kien muon xoa va cong don thanh cong se in ra successfully
void quanly::delet(){
     if(stt == 0){
        cout<<"Danh sach rong!\n";
        return;
    }

    int index;

    cout<<"Nhap STT can xoa: ";
    cin>>index;

    if(index < 0 || index >= stt){
        cout<<"Sai STT!\n";
        return;
    }

    for(int i = index; i < stt - 1; i++){

        events[i] = events[i + 1];
    }

    stt--;
    //events.erse(events.begin() +index);
    

    cout<<"Xoa thanh cong!\n";
}
//Them su kien voi cac phuong thuc theo dinh dang cu the va se in ra successfully khi thanh cong va neu nhap sai se in lai thong tin
void quanly::add(){
    
    if(stt >= 200){
        cout<<"Danh sach da day!\n";
        return;
    }
    char c1, c2, c3;
    cout<< "Nhap them su kien theo dinh dang (hh:mm dd/mm/yyyy): "<< endl;
    cin >> events[stt].hour>>c1>>events[stt].minute>>events[stt].day>>c2>>events[stt].month>>c3>>events[stt].year;
    if(events[stt].day < 0 || events[stt].day > 31){
        cout<<"Moi nhap lai!"<< endl; 
        clear(stt);
        return;
        
    }
    if(events[stt].month < 0 || events[stt].month >= 13){
        cout<<"Moi nhap lai!"<<endl;
        clear(stt);
        return; 
    }
    if(events[stt].hour < 0 || events[stt].hour >23){
        cout<<"Moi nhap lai!"<<endl;
        clear(stt);
        return; 
    }
    if(events[stt].minute < 0|| events[stt].minute >59){
        cout<<"Moi nhap lai!"<<endl;
        clear(stt);
        return; 
    }
    cout<<"===================\n";
    cout<<"Duration: ";
    cin>>events[stt].duration;
    cin.ignore();
    cout<<"===================\n";
    cout<<"Nhap description: ";
    getline(cin, events[stt].description);

    cout<<"====================\n";
    cout<<"Nhap address:";
    getline(cin, events[stt].address);

    cout<<"====================\n";
    cout<<"Nhap person_to_meet: ";
    getline(cin, events[stt].person_to_meet);

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
            events[stt].status = "Pending";
            break;
        case 1:
            events[stt].status  = "Done";
            break;
        default:
            events[stt].status  = "Canceled";
            break;
        }
    }
    else{
        cout<<"Moi nhap lai!"<<endl;
        clear(stt);
        return; 
    }

    cout<<"============\n";
    cout<<"======DOANH THU=======\n";
    cout<<"Nhap doanh thu(USD): "; cin>>events[stt].statistic;

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
        events[stt].priority = "HIGH";
        break;
    case 2:
        events[stt].priority = "MEDIUM";
        break;
    case 3:
        events[stt].priority = "LOW";
        break;
    default:
        events[stt].priority = "LOW";
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
        events[stt].category = "WORK";
        break;
    case 2:
        events[stt].category= "STUDY";
        break;
    case 3:
        events[stt].category = "PERSON TO MEET";
        break;
    case 4:
        events[stt].category= "MEETING";
        break;
    case 5:
        events[stt].category = "HEALTH";
        break;
    default:
        events[stt].category = "PERSON TO MEET";
        break;
    }
    int m = events[stt].month, n = events[stt].year, d = events[stt].day, a = (14 - m)/12, y = (n - a), mon = m + 12*a -2, 
    dayofweek = (d + y + y/4 - y/100 + y/400 + (31 * mon)/12)%7;
    places[dayofweek];
    cout<<"Thu: "<< places[dayofweek]<<endl;


    tm cd = {};
    cd.tm_mday = events[stt].day;
    cd.tm_mon = events[stt].month - 1;
    cd.tm_year = events[stt].year - 1900;
    cd.tm_hour = events[stt].hour;
    cd.tm_min = events[stt].minute;

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
    //Event e;
    //events.push_back(e); khong can stt++;
    //events.size(); so luong phan tu
    log("ADD EVENT");
    cout<<"Thoi gian con lai: "<<" Ngay: "<<k<<" gio: "<<h<<" phut: "<<p<<endl;
}
int main(){
    quanly p;
    int choice;
    do{
        cout<<"\n=====MENU=====\n";
        cout<<"1. ADD\n";
        cout<<"2. Delete\n";
        cout<<"3. Edit\n";
        cout<<"4. Display\n";
        cout<<"5. Sort\n";
        cout<<"6. Sort priority\n";
        cout<<"7. Search\n";
        cout<<"8. Export CSV\n";
        cout<<"9. Meeting Evenet\n";
        cout<<"10. Study Evenet\n";
        cout<<"0. Exit\n";
        cout<<"Nhap lua chon: ";
        cin>>choice;
        switch (choice)
        {
        case 1:
            p.add();
            if(p.checkConflict()){
                cout<<"Them su kien that ba!\n";
                cout<<"Ly do: Trung lich\n";
            }
            else{
                p.commitAdd();
            }
            break;
        case 2:
            p.delet();
            break;
        case 3:
            p.edit();
            break;
        case 4:
            p.display();
            break;
        case 5:
            p.sort();
            break;
        case 6:
            p.sortPriority();
            break;
        case 7:
            p.search();
            break;
        case 8:
            p.exportQueueCSV();
            break;
        case 9:
            MeetingEvent();
            break;
        case 10:
            StudyEvent();
            break;
        case 0:
            cout<<"Tam biet!\n";
            p.log("REPORT");
            break;
        default:
            cout<<"Lua chon khong hop le!\n";
        }
    }while (choice != 0);
    return 0;
}