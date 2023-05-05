// SAMOnnxRunner.cpp : ���ļ����� "main" ����������ִ�н��ڴ˴���ʼ��������
//
#include <iostream>
#include "SAMOnnxRunner.h"

int main()
{
    std::string encoder_model_path = "E:\\OroChiLab\\segment-anything-main\\model_weights\\withEncoder\\vit_b\\encoder.onnx";
    std::string decoder_model_path = "E:\\OroChiLab\\segment-anything-main\\model_weights\\withEncoder\\vit_b\\decoder.onnx";
    std::string image_path = "E:\\OroChiLab\\Data\\NailsJpgfile\\images\\1_1-2.jpg";
    double threshold = 0.95;
    
    Configuration cfg;
    cfg.EncoderModelPath = encoder_model_path;
    cfg.DecoderModelPath = decoder_model_path;
    cfg.SegThreshold = threshold;

    // Init Onnxruntime Env
    SAMOnnxRunner Segmentator;
    Segmentator.InitOrtEnv(cfg);

    ClickInfo clickinfo;
    clickinfo.positive = true;
    clickinfo.pt = cv::Point(1156,550);
    cv::Mat srcImage = cv::imread(image_path , CV_8UC3);
    
    Segmentator.InferenceSingleImage(cfg , srcImage , clickinfo);

    std::cout << "Hello World!\n";
}


