#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <set>
#include <QMap>

class Cloud{ public: QString    user_name, company_provider, directory, file, file_revision; };
enum Mode  {                    user_name, company_provider, directory, file, file_revision  } flag = user_name;

template<class T>
class List{
    struct Node{
         T x;
         Node *Next, *Prev;
     };
    Node *Head, *Tail;
public:
    List():Head(NULL),Tail(NULL){};
    ~List(){
        while (Head){
            Tail = Head->Next;
            delete Head;
            Head = Tail;
        }
    }
    QVector<T> Show(){
        QVector<T> res;

        Node *temp = Head;
        while (temp != NULL){
            res.push_back(temp->x);
            temp = temp->Next;
        }

        return res;
    }

    void add(T x){
        Node *temp = new Node;
        temp->Next = NULL;
        temp->x = x;

        if (Head != NULL){
            temp->Prev = Tail;
            Tail->Next = temp;
            Tail = temp;
        }
        else{
            temp->Prev = NULL;
            Head = Tail = temp;
        }
      }
};

bool operator <  (Cloud first, Cloud second){
    switch (flag) {
        case Mode::user_name:           return first.user_name          < second.user_name;
        case Mode::company_provider:    return first.company_provider   < second.company_provider;
        case Mode::directory:           return first.directory          < second.directory;
        case Mode::file:                return first.file               < second.file;
        case Mode::file_revision:       return first.file_revision      < second.file_revision;
    }
}

bool operator >  (Cloud first, Cloud second){
    switch (flag) {
        case Mode::user_name:           return first.user_name          > second.user_name;
        case Mode::company_provider:    return first.company_provider   > second.company_provider;
        case Mode::directory:           return first.directory          > second.directory;
        case Mode::file:                return first.file               > second.file;
        case Mode::file_revision:       return first.file_revision      > second.file_revision;
    }
}

bool operator == (Cloud first, Cloud second){
    switch (flag) {
        case Mode::user_name:           return first.user_name          == second.user_name;
        case Mode::company_provider:    return first.company_provider   == second.company_provider;
        case Mode::directory:           return first.directory          == second.directory;
        case Mode::file:                return first.file               == second.file;
        case Mode::file_revision:       return first.file_revision      == second.file_revision;
    }
}

template<class T>
void insertion_sort(T arr[], int n){
    T key;
    for (int j, i = 1; i < n; i++) {

        key = arr[i];
        j = i - 1;
        while (j >= 0 && arr[j] > key) {

            arr[j + 1] = arr[j];
            j = j - 1;
        }
        arr[j + 1] = key;
    }
}

template<class T>
int partition (T arr[], int low, int high){
    T pivot = arr[high];
    int i = (low - 1);

    for (int j = low; j <= high - 1; j++)
        if (arr[j] < pivot)
            std::swap(arr[++i], arr[j]);

    std::swap(arr[i + 1], arr[high]);
    return i + 1;
}

template<class T>
void quick_sort(T arr[], int low, int high){
    if (low < high){
        int pi = partition(arr, low, high);

        quick_sort(arr, low, pi - 1);
        quick_sort(arr, pi + 1, high);
    }
}

template<class T>
void heapify(T arr[], int n, int i){

    int largest = i;
    int l = 2 * i + 1;
    int r = 2 * i + 2;

    if (l < n && arr[l] > arr[largest])
        largest = l;

    if (r < n && arr[r] > arr[largest])
        largest = r;

    if (largest != i){
        std::swap(arr[i], arr[largest]);
        heapify(arr, n, largest);
    }
}

template<class T>
void heap_sort(T arr[], int n){

    for (int i = n / 2 - 1; i >= 0; i--)
        heapify(arr, n, i);

    for (int i=n-1; i>0; i--)
    {
        std::swap(arr[0], arr[i]);
          heapify(arr, i, 0);
    }
}

template<class T>
void counting_sort(T* array, int n) {
    QMap<Cloud, int> c;
    std::set<Cloud> set;
    for (int i = 0; i < n; i++){
        c[array[i]]++;
        set.insert(array[i]);
    }

    int b = 0;
    for(auto cloud : set)
        for (int j = 0; j < c[cloud]; j++)
            array[b++] = cloud;
}


Cloud get_rand_cloud(){
    Cloud cloud;
    cloud.user_name         = QVector<QString>{"Gerard", "Felix", "Joshua", "Ernest", "Bernard"}            [rand() % 5];
    cloud.company_provider  = QVector<QString>{"Express", "Hiptel", "MainStream", "Dniprolink", "Global"}   [rand() % 5];
    cloud.directory         = QVector<QString>{"Temp", "Tmp", "Imgs", "Dowload", "Src"}                     [rand() % 5];
    cloud.file              = QVector<QString>{"Hello.cpp", "main.cpp", "Img1.jpg", "Img2.jpg", "Lab.zip"}  [rand() % 5];
    cloud.file_revision     = QVector<QString>{"None", "None", "Date change", "Owner", "Flags"}             [rand() % 5];
    return cloud;
}

Cloud cloud1 = {"Bob", "MaxSpeed", "Imgs", "Photo.jpg", "None"},
cloud2 = {"Alisa", "Omega", "Src", "Hello.cpp", "5 line - return 0;"},
cloud3 = {"Eva", "Omega", "Download", "lab.rar", "None"};
QVector<Cloud> Cloud_vect = {cloud1, cloud2, cloud3};

void init(List<Cloud> *clouds){
    for(auto a : Cloud_vect)
    clouds->add(a);
}

MainWindow::MainWindow(QWidget *parent): QMainWindow(parent), ui(new Ui::MainWindow){
    ui->setupUi(this);
    srand(time(0));
    for (int i = 0; i < 500 ; i++)
        Cloud_vect.push_back(get_rand_cloud());
}
MainWindow::~MainWindow(){ delete ui; }

void MainWindow::on_radioButton_clicked()   { flag = Mode::user_name; }
void MainWindow::on_radioButton_3_clicked() { flag = Mode::company_provider; }
void MainWindow::on_radioButton_4_clicked() { flag = Mode::directory; }
void MainWindow::on_radioButton_5_clicked() { flag = Mode::file; }
void MainWindow::on_radioButton_6_clicked() { flag = Mode::file_revision; }

void MainWindow::on_Insertion_sort_clicked(){
    ui->output->clear();
    List<Cloud> *clouds = new List<Cloud>;
    init(clouds);
    QVector<Cloud> tmp = clouds->Show();
    unsigned int start_time =  clock();
    insertion_sort(tmp.data(), tmp.size());
    unsigned int end_time = clock();
    unsigned int search_time = end_time - start_time;
    for(auto tmp_cloud : tmp){
        ui->output->append("user_name = " + tmp_cloud.user_name);
        ui->output->append("company_provider = " + tmp_cloud.company_provider);
        ui->output->append("directory = " + tmp_cloud.directory);
        ui->output->append("file = " + tmp_cloud.file);
        ui->output->append("file_revision = " + tmp_cloud.file_revision);
        ui->output->append("insertion_sort time = " + QString::number(search_time) + "ms");
        ui->output->append("");
    }
}

void MainWindow::on_Quicksort_clicked(){
    ui->output->clear();
    List<Cloud> *clouds = new List<Cloud>;
    init(clouds);
    QVector<Cloud> tmp = clouds->Show();
    unsigned int start_time =  clock();
    quick_sort(tmp.data(), 0, tmp.size() - 1);
    unsigned int end_time = clock();
    unsigned int search_time = end_time - start_time;
    for(auto tmp_cloud : tmp){
        ui->output->append("user_name = " + tmp_cloud.user_name);
        ui->output->append("company_provider = " + tmp_cloud.company_provider);
        ui->output->append("directory = " + tmp_cloud.directory);
        ui->output->append("file = " + tmp_cloud.file);
        ui->output->append("file_revision = " + tmp_cloud.file_revision);
        ui->output->append("quick_sort time = " + QString::number(search_time) + "ms");
        ui->output->append("");
    }
}

void MainWindow::on_Heap_sort_clicked(){
    ui->output->clear();
    List<Cloud> *clouds = new List<Cloud>;
    init(clouds);
    QVector<Cloud> tmp = clouds->Show();
    unsigned int start_time =  clock();
    heap_sort(tmp.data(), tmp.size());
    unsigned int end_time = clock();
    unsigned int search_time = end_time - start_time;
    for(auto tmp_cloud : tmp){
        ui->output->append("user_name = " + tmp_cloud.user_name);
        ui->output->append("company_provider = " + tmp_cloud.company_provider);
        ui->output->append("directory = " + tmp_cloud.directory);
        ui->output->append("file = " + tmp_cloud.file);
        ui->output->append("file_revision = " + tmp_cloud.file_revision);
        ui->output->append("heap_sort time = " + QString::number(search_time) + "ms");
        ui->output->append("");
    }
}

void MainWindow::on_Counting_clicked(){
    ui->output->clear();
    List<Cloud> *clouds = new List<Cloud>;
    init(clouds);
    QVector<Cloud> tmp = clouds->Show();
    unsigned int start_time =  clock();
    counting_sort(tmp.data(), tmp.size());
    unsigned int end_time = clock();
    unsigned int search_time = end_time - start_time;
    for(auto tmp_cloud : tmp){
        ui->output->append("user_name = " + tmp_cloud.user_name);
        ui->output->append("company_provider = " + tmp_cloud.company_provider);
        ui->output->append("directory = " + tmp_cloud.directory);
        ui->output->append("file = " + tmp_cloud.file);
        ui->output->append("file_revision = " + tmp_cloud.file_revision);
        ui->output->append("counting_sort time = " + QString::number(search_time) + "ms");
        ui->output->append("");
    }
}

void MainWindow::on_Show_list_clicked(){
    ui->output->clear();
    List<Cloud> *clouds = new List<Cloud>;
    init(clouds);
    for(auto tmp_cloud : clouds->Show()){
        ui->output->append("user_name = " + tmp_cloud.user_name);
        ui->output->append("company_provider = " + tmp_cloud.company_provider);
        ui->output->append("directory = " + tmp_cloud.directory);
        ui->output->append("file = " + tmp_cloud.file);
        ui->output->append("file_revision = " + tmp_cloud.file_revision);
        ui->output->append("");
    }
}

void MainWindow::on_Show_tree_clicked(){
    ui->output->clear();
}

void MainWindow::on_Generate_clicked(){
    Cloud tmp_cloud = get_rand_cloud();
    ui->User_name->setText(tmp_cloud.user_name);
    ui->Company_provider->setText(tmp_cloud.company_provider);
    ui->Directory->setText(tmp_cloud.directory);
    ui->File->setText(tmp_cloud.file);
    ui->File_revision->setText(tmp_cloud.file_revision);
}

void MainWindow::on_Add_clicked(){
    Cloud tmp_cloud;
    tmp_cloud.user_name = ui->User_name->toPlainText();
    tmp_cloud.company_provider = ui->Company_provider->toPlainText();
    tmp_cloud.directory = ui->Directory->toPlainText();
    tmp_cloud.file = ui->File->toPlainText();
    tmp_cloud.file_revision = ui->File_revision->toPlainText();
    Cloud_vect.push_back(tmp_cloud);
}
