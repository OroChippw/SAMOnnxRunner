// SAMOnnxRunner.cpp : ���ļ����� "main" ����������ִ�н��ڴ˴���ʼ��������
//
#include <iostream>
#include "SAMOnnxRunner.h"

int main()
{
    std::string model_path = "";
    // 
    SAMOnnxRunner Segmentator;
    Segmentator.setSegThreshold(0.95);
    
    std::cout << "Hello World!\n";
}


