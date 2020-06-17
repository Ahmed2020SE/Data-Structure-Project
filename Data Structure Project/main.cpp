#include <bits/stdc++.h>

using namespace std;

struct times{
    int hr;
    int mnt;
    int sec;
};

struct task{
    string type;
    times start;
    times en;
};

int length = 0;
task arr[20005];

int comp_2(int one , int two){
    if(arr[one].en.hr < arr[two].en.hr) return 1;
    if(arr[one].en.hr == arr[two].en.hr && arr[one].en.mnt < arr[two].en.mnt) return 1;
    if(arr[one].en.hr == arr[two].en.hr && arr[one].en.mnt == arr[two].en.mnt && arr[one].en.sec < arr[two].en.sec) return 1;
    return 0;
}

bool compare(int one , int two){ // to compare between two tasks
    if(arr[one].start.hr < arr[two].start.hr) return 1;
    if(arr[one].start.hr == arr[two].start.hr && arr[one].start.mnt < arr[two].start.mnt) return 1;
    if(arr[one].start.hr == arr[two].start.hr && arr[one].start.mnt == arr[two].start.mnt && arr[one].start.sec < arr[two].start.sec) return 1;
    if(arr[one].start.hr == arr[two].start.hr && arr[one].start.mnt == arr[two].start.mnt
       && arr[one].start.sec == arr[two].start.sec && comp_2(one , two)) return 1;
    return 0;
}

void increase_val(int i , int st_1 , int st_2 , int st_3 , int end_1 , int end_2 , int end_3 , string type){ // to arrange tasks after deleting
    task x;
    x.start = {st_1 , st_2 , st_3};
    x.en = {st_1 + end_1 , st_2 + end_2 , st_3 + end_3};
    x.type = type;
    arr[i] = x;

    while(i > 1 && !compare(i / 2 , i)){
        swap(arr[i / 2] , arr[i]);
        i /= 2;
    }

}


void insert_p_q(int st_1 , int st_2 , int st_3 , int end_1 , int end_2 , int end_3 , string type){ // to insert a task
    length++;
    increase_val(length , st_1 , st_2 , st_3 , end_1 , end_2 , end_3 , type);
}

void arrange(int i){ //to arrange the priority queue
    int left = i * 2;
    int right = i * 2 + 1;

    int smallest;

    if(left <= length && compare(left , i))
        smallest = left;
    else smallest = i;

    if(right <= length && compare(right , i))
        smallest = right;

    if(smallest != i){
        swap(arr[i] , arr[smallest]);
        arrange(smallest);
    }
}

void done(){ // to output the top task and arrange the priority queue
    if(length == 0){
        cout << "There's No Tasks\n";
        return;
    }
    cout << arr[1].type << endl;
    arr[1] = arr[length];
    length--;
    arrange(1);
    return;
}

int main()
{

    int s_hr , s_mn , s_sec , e_hr , e_mn , e_sec , choice;
    string proc_type;
    do
    {
        cout<<"1.Insert\n";
        cout<<"2.Delete\n";
        cout<<"3.Display\n";
        cout<<"4.Quit\n";
        cout<<"Enter your choice : ";
        cin>>choice;

        if(choice == 1){
            cout << "Enter the task :\n";
            cin >> proc_type;
            cout << "Enter starting time in the form hr min sec :\n";
            cin >> s_hr >> s_mn >> s_sec;
            cout << "Enter the length in the form hr min sec :\n";
            cin >> e_hr >> e_mn >> e_sec;
            insert_p_q(s_hr , s_mn , s_sec , e_hr , e_mn , e_sec , proc_type);
        }else if(choice == 2){
            done();
        }else if(choice == 3){
            for(int i = 1;i <= length;i++)
                cout << arr[i].type << " " << arr[i].start.hr << " " << arr[i].start.mnt << " " << arr[i].start.sec
                << " " << arr[i].en.hr << " " << arr[i].en.mnt << " " << arr[i].en.sec << endl;
            if(length == 0)
                cout << "There is no tasks\n";
        }else if(choice == 4){
            break;
        }else{
            cout<<"Wrong choice\n";
        }
    }while(1);

    return 0;
}
