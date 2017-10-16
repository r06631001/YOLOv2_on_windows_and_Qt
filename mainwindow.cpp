#include "mainwindow.h"
#include "ui_mainwindow.h"

void draw_boxes(cv::Mat mat_img, std::vector<bbox_t> result_vecd, std::vector<std::string> obj_namesd);
std::vector<std::string> objects_names_from_file(std::string const filename);
void show_result(std::vector<bbox_t> const result_vec, std::vector<std::string> const obj_names);

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    std::string cfg_file = "D:\\yolo\\yolo-demo\\demo_yolo\\data\\yolo-voc.cfg";
    std::string weights_file = "D:\\yolo\\yolo-demo\\demo_yolo\\data\\yolo-voc.weights";
    std::string names_file = "D:\\yolo\\yolo-demo\\demo_yolo\\data\\voc.names";

    Detector detector(cfg_file, weights_file);
    auto obj_names = objects_names_from_file(names_file);

    QString filename = QFileDialog::getOpenFileName(this, tr("OpenFile"));
    auto img = detector.load_image(filename.toStdString());
    std::vector<bbox_t> result_vec = detector.detect(img);
    detector.free_image(img);
    show_result(result_vec, obj_names);

    cv::Mat mat_imgf = cv::imread(filename.toStdString());
    draw_boxes(mat_imgf, result_vec, obj_names);

}

MainWindow::~MainWindow()
{
    delete ui;
}

void draw_boxes(cv::Mat mat_img, std::vector<bbox_t> result_vecd, std::vector<std::string> obj_namesd) {
    cv::imshow("Original", mat_img);
    for (auto &i : result_vecd) {
        cv::Scalar color(60, 160, 260);
        cv::rectangle(mat_img, cv::Rect(i.x, i.y, i.w, i.h), color, 5);
        if (obj_namesd.size() > i.obj_id) {
            std::string obj_name = obj_namesd[i.obj_id];
            if (i.track_id > 0) obj_name += " - " + std::to_string(i.track_id);
            cv::Size const text_size = getTextSize(obj_name, cv::FONT_HERSHEY_COMPLEX_SMALL, 1.2, 2, 0);
            int const max_width = (text_size.width > i.w + 2) ? text_size.width : (i.w + 2);
            cv::rectangle(mat_img, cv::Point2f(std::max((int)i.x - 3, 0), std::max((int)i.y - 30, 0)),
                          cv::Point2f(std::min((int)i.x + max_width, mat_img.cols-1), std::min((int)i.y, mat_img.rows-1)),
                          color, CV_FILLED, 8, 0);
            putText(mat_img, obj_name, cv::Point2f(i.x, i.y + 10), cv::FONT_HERSHEY_COMPLEX_SMALL, 1.2, cv::Scalar(0, 0, 0), 2);
        }
    }
    cv::namedWindow("Facial dysmorphism syndrome recognition result", cv::WINDOW_AUTOSIZE);
    cv::imshow("Facial dysmorphism syndrome recognition result", mat_img);

    //cv::imwrite("Prediction", mat_img);
}

std::vector<std::string> objects_names_from_file(std::string const filename) {
    std::ifstream file(filename);
    std::vector<std::string> file_lines;
    if (!file.is_open()) return file_lines;
    for(std::string line; file >> line;) file_lines.push_back(line);
    std::cout << "object names loaded \n";
    return file_lines;
}

void show_result(std::vector<bbox_t> const result_vec, std::vector<std::string> const obj_names) {
    //qDebug() << "show result";
    //qDebug() << result_vec.size();
    for (auto &i : result_vec) {
        if (obj_names.size() > i.obj_id){
            std::cout << obj_names[i.obj_id] << " - ";
        }
        std::cout << "obj_id = " << i.obj_id << ",  x = " << i.x << ", y = " << i.y
                  << ", w = " << i.w << ", h = " << i.h
                  << std::setprecision(3) << ", prob = " << i.prob << std::endl;
    }
}
